#include <Adafruit_MAX31865.h>
#include <EEPROM.h>
#include <math.h>

// Cableado comprobado: CS D10, MOSI D11, MISO D9, CLK D8
Adafruit_MAX31865 pt100(10, 11, 9, 8);

const float RNOMINAL = 100.0f;
const float RREF = 430.0f;
const byte PIN_LED = 3;
const byte PIN_BUZZER = 4;
const bool BUZZER_HABILITADO = true;

// RANGO DE REFERENCIA DEL PROYECTO (NO LIMITES CERTIFICADOS DE SEGURIDAD)
const float MIN_REFERENCIA = 22.0f;
const float MAX_REFERENCIA = 32.0f;

// Criterios EXPERIMENTALES derivados de las pruebas A y B
const float UMBRAL_AUMENTO_10S = 0.15f;  // grados C en 10 segundos
const byte CONFIRMACIONES = 3;           // tres lecturas consecutivas
const byte RECUPERACIONES = 5;           // cinco lecturas para desactivar
const unsigned long INTERVALO_MS = 1000UL;

// Mismo formato de EEPROM usado durante la calibracion
const uint32_t FIRMA = 0x50543130UL;
struct DatosCalibracion {
  uint32_t firma;
  float a;
  float b;
};
DatosCalibracion cal;

// Buffer circular: conserva las 10 temperaturas anteriores (1 Hz)
float historial[10];
byte indiceHistorial = 0;
byte muestrasHistorial = 0;

bool alarmaCambio = false;
bool alarmaSuperior = false;
byte confirmCambio = 0, confirmarFinCambio = 0;
byte confirmSuperior = 0, confirmarFinSuperior = 0;

bool sensorCorrecto = true;
int errorAnterior = -1;
unsigned long ultimaMedicion = 0;
unsigned long segundoMuestra = 0;

void apagarSalidas() {
  noTone(PIN_BUZZER);
  digitalWrite(PIN_BUZZER, LOW);
  digitalWrite(PIN_LED, LOW);
}

void pruebaInicial() {
  Serial.println(F("# Prueba inicial de LED y buzzer: 2 s"));
  digitalWrite(PIN_LED, HIGH);
  if (BUZZER_HABILITADO) tone(PIN_BUZZER, 2000);
  delay(2000);
  apagarSalidas();
}

bool obtenerTemperatura(float &t, uint8_t &codigo) {
  uint16_t rtd = pt100.readRTD();
  codigo = pt100.readFault(MAX31865_FAULT_NONE);
  pt100.clearFault();
  if (codigo != 0 || rtd == 0) return false;
  t = pt100.calculateTemperature(rtd, RNOMINAL, RREF);
  return !isnan(t) && !isinf(t);
}

void explicarFalla(uint8_t error) {
  if (error == errorAnterior) return;  // no repetir el diagnostico
  errorAnterior = error;
  Serial.print(F("# NUEVA FALLA MAX31865: 0x"));
  if (error < 0x10) Serial.print('0');
  Serial.println(error, HEX);
  if (error & 0x80) Serial.println(F("# RTD supera el limite superior: revisar circuito abierto."));
  if (error & 0x40) Serial.println(F("# RTD bajo limite inferior: revisar conexion y cortocircuitos."));
  if (error & 0x20) Serial.println(F("# REFIN- anormalmente alto."));
  if (error & 0x10) Serial.println(F("# REFIN- anormalmente bajo."));
  if (error & 0x08) Serial.println(F("# RTDIN- anormalmente bajo: revisar lado negativo."));
  if (error & 0x04) Serial.println(F("# Falla de tension: revisar alimentacion."));
  if (error == 0) Serial.println(F("# Lectura invalida sin bandera de falla (RTD RAW=0)."));
  Serial.println(F("# Revisar continuidad, puentes y soldaduras; son causas orientativas."));
}

void limpiarHistorialYAlertas() {
  indiceHistorial = 0;
  muestrasHistorial = 0;
  alarmaCambio = false;
  alarmaSuperior = false;
  confirmCambio = 0;
  confirmarFinCambio = 0;
  confirmSuperior = 0;
  confirmarFinSuperior = 0;
}

void actualizarAlertas(float t, bool disponibleDelta, float delta10) {
  // Deteccion de subida sostenida: tres ventanas de 10 s consecutivas
  bool subida = disponibleDelta && delta10 > UMBRAL_AUMENTO_10S;
  if (subida) {
    if (confirmCambio < CONFIRMACIONES) confirmCambio++;
    confirmarFinCambio = 0;
  } else {
    confirmCambio = 0;
    if (alarmaCambio && confirmarFinCambio < RECUPERACIONES)
      confirmarFinCambio++;
  }
  if (confirmCambio >= CONFIRMACIONES) alarmaCambio = true;
  if (confirmarFinCambio >= RECUPERACIONES) alarmaCambio = false;

  // Temperatura superior al rango de referencia: no implica peligro certificado
  bool superior = t > MAX_REFERENCIA;
  if (superior) {
    if (confirmSuperior < CONFIRMACIONES) confirmSuperior++;
    confirmarFinSuperior = 0;
  } else {
    confirmSuperior = 0;
    if (alarmaSuperior && confirmarFinSuperior < RECUPERACIONES)
      confirmarFinSuperior++;
  }
  if (confirmSuperior >= CONFIRMACIONES) alarmaSuperior = true;
  if (confirmarFinSuperior >= RECUPERACIONES) alarmaSuperior = false;
}

void salidasNoBloqueantes(unsigned long ahora) {
  if (!sensorCorrecto) {
    // Error del sensor: LED parpadea, buzzer apagado
    digitalWrite(PIN_LED, ((ahora / 500UL) % 2UL) ? LOW : HIGH);
    noTone(PIN_BUZZER);
    return;
  }

  if (alarmaCambio || alarmaSuperior) {
    // En una alerta: LED encendido y pitido de 250 ms cada segundo
    digitalWrite(PIN_LED, HIGH);
    if (BUZZER_HABILITADO && (ahora % 1000UL) < 250UL)
      tone(PIN_BUZZER, 2000);
    else
      noTone(PIN_BUZZER);
  } else {
    apagarSalidas();
  }
}

void registrarMedicion() {
  float original;
  uint8_t error = 0;
  bool valido = obtenerTemperatura(original, error);

  Serial.print(segundoMuestra++);
  Serial.print(',');

  if (!valido) {
    sensorCorrecto = false;
    limpiarHistorialYAlertas();
    Serial.print(F("NA,NA,NA,ERROR_SENSOR,0x"));
    if (error < 0x10) Serial.print('0');
    Serial.println(error, HEX);
    explicarFalla(error);
    return;
  }

  if (errorAnterior >= 0) {
    Serial.println(F("# Sensor recuperado, reiniciando ventana de 10 s."));
    errorAnterior = -1;
  }
  sensorCorrecto = true;
  float corregida = cal.a * original + cal.b;

  // Antes de reemplazar el dato mas antiguo, comparar con t - 10 s
  bool ventanaCompleta = (muestrasHistorial == 10);
  float delta10 = 0.0f;
  if (ventanaCompleta) {
    delta10 = corregida - historial[indiceHistorial];
  }
  historial[indiceHistorial] = corregida;
  indiceHistorial = (indiceHistorial + 1) % 10;
  if (muestrasHistorial < 10) muestrasHistorial++;

  actualizarAlertas(corregida, ventanaCompleta, delta10);

  Serial.print(original, 2);
  Serial.print(',');
  Serial.print(corregida, 2);
  Serial.print(',');
  if (ventanaCompleta) Serial.print(delta10, 3);
  else Serial.print(F("NA"));
  Serial.print(',');

  if (alarmaCambio && alarmaSuperior)
    Serial.print(F("CAMBIO_Y_SOBRE_RANGO"));
  else if (alarmaCambio)
    Serial.print(F("CALENTAMIENTO_RAPIDO"));
  else if (alarmaSuperior)
    Serial.print(F("SOBRE_RANGO_REFERENCIA"));
  else if (corregida < MIN_REFERENCIA)
    Serial.print(F("BAJO_RANGO_REFERENCIA"));
  else
    Serial.print(F("NORMAL"));

  Serial.println(F(",0x00"));
}

void setup() {
  Serial.begin(115200);
  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_BUZZER, OUTPUT);
  apagarSalidas();

  pt100.begin(MAX31865_2WIRE);
  EEPROM.get(0, cal);

  bool calValida = (cal.firma == FIRMA &&
                    !isnan(cal.a) && !isinf(cal.a) &&
                    !isnan(cal.b) && !isinf(cal.b) &&
                    cal.a > 0.5f && cal.a < 1.5f &&
                    cal.b > -10.0f && cal.b < 10.0f);
  if (!calValida) {
    Serial.println(F("# ERROR: calibracion EEPROM ausente o invalida."));
    Serial.println(F("# No se habilita la deteccion termica."));
    while (true) {
      digitalWrite(PIN_LED, (millis() / 500UL) % 2UL);
      noTone(PIN_BUZZER);
    }
  }

  Serial.println(F("# Sistema TEI: monitoreo termico experimental"));
  Serial.print(F("# Calibracion: a=")); Serial.print(cal.a, 6);
  Serial.print(F(" b=")); Serial.println(cal.b, 6);
  Serial.println(F("# Referencia asumida: 22-32 C (no seguridad certificada)"));
  Serial.println(F("# Cambio rapido: > 0.15 C en 10 s, 3 confirmaciones"));
  Serial.println(F("# Alarma se desactiva tras 5 lecturas sin condicion"));
  pruebaInicial();
  Serial.println(F("tiempo_s,PT100_C,calibrada_C,delta10_C,estado,error_hex"));
  ultimaMedicion = millis() - INTERVALO_MS; // primera lectura inmediata
}

void loop() {
  unsigned long ahora = millis();
  if (ahora - ultimaMedicion >= INTERVALO_MS) {
    ultimaMedicion += INTERVALO_MS;
    registrarMedicion();
  }
  salidasNoBloqueantes(millis());
}
