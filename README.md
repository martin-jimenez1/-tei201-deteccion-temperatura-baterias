# -tei201-deteccion-temperatura-baterias
Sistema de monitoreo de temperatura para baterías de litio en scooters eléctricos urbanos, desarrollado mediante un sensor PT100, módulo MAX31865 y Arduino Nano.

# Sistema de monitoreo térmico para baterías de litio en scooters eléctricos

## Descripción del proyecto

Este proyecto consiste en el desarrollo de un sistema experimental de monitoreo térmico para baterías de litio utilizadas en scooters eléctricos urbanos. Su objetivo es medir la temperatura de la batería e identificar condiciones anormales, generando alertas mediante señales visuales y sonoras.

## Integrantes

- Alejandro Fauré
- Gabriel de la Fuente
- Martín Jiménez
- Nicolás King

## Problemática

Las baterías de ion-litio utilizadas en scooters eléctricos pueden experimentar aumentos anormales de temperatura que, en determinadas condiciones, pueden desencadenar una fuga térmica. Este fenómeno representa un riesgo para los usuarios y su entorno.

Frente a esta problemática, el proyecto propone un sistema experimental que permite monitorear la temperatura e identificar cambios que puedan requerir atención.

## Componentes utilizados

| Componente | Descripción |
|:---|:---|
| Arduino Nano | Microcontrolador del sistema |
| Sensor PT100 | Medición de temperatura |
| Módulo MAX31865 | Interfaz para la lectura del sensor PT100 |
| LED | Señalización visual de alertas |
| Buzzer | Señalización sonora de alertas |
| Protoboard | Montaje del circuito |
| Batería | Alimentación del sistema |
| Cables Dupont | Conexiones eléctricas |
| Cápsula impresa en 3D | Estructura para alojar los componentes |

## Estructura del repositorio

- `firmware/`: código fuente del sistema y documentación para su instalación.
- `hardware/`: esquemas eléctricos y lista de materiales.
- `diseño-3d/`: archivos de diseño, planos y renders de la cápsula.
- `testing/`: documentación de pruebas experimentales.
- `docs/`: documentación técnica complementaria.
- `FUENTES.md`: declaración de bibliotecas, recursos externos y herramientas utilizadas.

## Instalación y uso

### Requisitos

- Arduino IDE.
- Placa Arduino Nano.
- Biblioteca `Adafruit_MAX31865`.

### Instal
