# Firmware – Sistema de Monitoreo Térmico

## 1. Descripción

Este directorio contiene el código fuente del sistema de monitoreo de temperatura para baterías de litio en scooters eléctricos urbanos.

El firmware utiliza un sensor PT100 conectado a un módulo MAX31865 y un Arduino Nano. Permite registrar mediciones de temperatura, aplicar una corrección de calibración y activar alertas visuales y sonoras ante determinadas condiciones.

## 2. Hardware utilizado

- Arduino Nano.
- Sensor de temperatura PT100.
- Módulo MAX31865.
- LED indicador.
- Buzzer.

## 3. Conexiones

Las conexiones utilizadas entre el Arduino Nano y el módulo MAX31865 son las siguientes:

| Arduino Nano | Módulo MAX31865 |
|:---:|:---:|
| D10 | CS |
| D11 | MOSI |
| D9 | MISO |
| D8 | CLK |
| 5V | VIN |
| GND | GND |

**Otros componentes:**

| Componente | Pin Arduino |
|:---|:---:|
| LED indicador | D3 |
| Buzzer | D4 |

**Configuración del sensor:** PT100 de 2 cables (`MAX31865_2WIRE`).

## 4. Librerías utilizadas

| Librería | Función |
|:---|:---|
| `Adafruit_MAX31865` | Comunicación con el módulo MAX31865 y lectura del PT100. |
| `EEPROM` | Lectura de los parámetros de calibración almacenados. |
| `math.h` | Operaciones y comprobaciones matemáticas. |

La librería `Adafruit_MAX31865` debe instalarse desde el administrador de bibliotecas de Arduino IDE.

## 5. Instalación y ejecución

1. Instalar [Arduino IDE](https://www.arduino.cc/en/software).
2. Conectar el Arduino Nano al computador mediante USB.
3. Instalar la librería `Adafruit MAX31865`.
4. Abrir el archivo `main.ino`.
5. Seleccionar la placa Arduino Nano y el puerto correspondiente.
6. Cargar el programa en el microcontrolador.
7. Abrir el Monitor Serie a **115200 baudios** para visualizar las mediciones.


## 6. Funcionalidades del firmware

- Lectura de temperatura aproximadamente cada segundo.
- Corrección de las mediciones mediante parámetros de calibración.
- Evaluación de variaciones de temperatura en ventanas de 10 segundos.
- Detección de temperaturas superiores al rango de referencia.
- Activación de alertas mediante LED y buzzer.
- Identificación y diagnóstico de fallas del sensor.
- Registro de mediciones y estados mediante el Monitor Serie.

## 7. Formato de salida

El programa entrega los datos en formato CSV, utilizando las siguientes columnas:

| Columna | Descripción |
|:---|:---|
| `tiempo_s` | Tiempo transcurrido en segundos. |
| `PT100_C` | Temperatura original medida por el PT100. |
| `calibrada_C` | Temperatura después de aplicar la calibración. |
| `delta10_C` | Variación de temperatura en los últimos 10 segundos. |
| `estado` | Estado del sistema o condición detectada. |
| `error_hex` | Código de diagnóstico del sensor. |

## 8. Consideraciones

Los umbrales y criterios de detección implementados corresponden a parámetros experimentales del proyecto. No representan límites certificados de seguridad ni garantizan la prevención de una fuga térmica.
