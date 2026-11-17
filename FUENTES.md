# FUENTES

Este documento reúne las fuentes bibliográficas, documentación técnica, bibliotecas, herramientas de desarrollo e inteligencia artificial utilizadas durante las distintas etapas del proyecto.

## 1. Fuentes de investigación y contexto del proyecto

- Cuerpo de Bomberos de Santiago. (2024, 17 de diciembre). *Recomendaciones ante peligro de fuego en vehículos y equipos con baterías de ion de litio*. https://www.cbs.cl/recomendaciones-ante-peligro-de-fuego-en-vehiculos-y-equipos-con-baterias-de-ion-de-litio/

- Fire Protection Association. (2026, 13 de mayo). *Statistics show Li-ion battery fires on the rise*. https://www.thefpa.co.uk/fire-and-risk-management-journal/news/statistics-show-li-ion-battery-fires-on-the-rise

- Han, D., Wang, J., Yin, C., & Zhao, Y. (2025). Advances in early warning of thermal runaway in lithium-ion battery energy storage systems. *Advanced Sensor Research, 4*(5), 2400165. https://doi.org/10.1002/adsr.202400165

- Hurtubia, R., Waintrub, N., & Raveau, S. (2024). *Encuesta de Movilidad de Santiago 2024 (EMS 2024): Informe de resultados*. Centro de Desarrollo Urbano Sustentable (CEDEUS). https://doi.org/10.7764/cedeus.li.03

- QBE European Operations. (2026, 11 de mayo). *UK fire brigades tackling lithium-ion battery fire every five hours*. https://qbeeurope.com/news-and-events/press-releases/uk-fire-brigades-tackling-lithium-ion-battery-fire-every-five-hours/

- Radio Agricultura. (2026, 4 de agosto). *Uso de scooters y bicicletas eléctricas se consolida en Chile con más de 66 mil viajes diarios*. https://www.radioagricultura.cl/noticias/nacional/uso-de-scooters-y-bicicletas-electricas-se-consolida-en-chile-con-mas-de-66-mil-viajes-diarios/

- Servicio Nacional del Consumidor. (2017, 16 de febrero). *Baterías de litio: Dilemas entre diseño y seguridad*. https://www.sernac.cl/portal/619/w3-article-8704.html

## 2. Fichas técnicas de materiales

- colorFabb B.V. (2020). *colorFabb ASA: Technical datasheet* (v1.0) [Ficha técnica]. https://matterhackers.com/r/vBDRnd

- Spectrum Group Sp. z o.o. (2024). *The Filament PLA: Technical data sheet* [Ficha técnica]. https://spectrumfilaments.com/wp-content/uploads/2024/11/eng_tds_the_filament_pla.pdf

- Xometry. (s. f.). *ASA datasheet* [Ficha técnica]. https://xometry.asia/wp-content/uploads/2025/07/17738476

## 3. Bibliotecas y documentación técnica

| Recurso | Fuente | Uso en el proyecto |
|:---|:---|:---|
| Adafruit MAX31865 | https://github.com/adafruit/Adafruit_MAX31865 | Comunicación con el módulo MAX31865 y lectura del sensor PT100. |
| EEPROM | https://docs.arduino.cc/learn/built-in-libraries/eeprom/ | Almacenamiento y recuperación de los parámetros de calibración. |
| math.h | https://avrdudes.github.io/avr-libc/avr-libc-user-manual/group__avr__math.html | Funciones matemáticas para comprobar la validez de valores numéricos. |

## 4. Herramientas de desarrollo

| Herramienta | Fuente | Uso en el proyecto |
|:---|:---|:---|
| Arduino IDE | https://www.arduino.cc/en/software | Edición, compilación y carga del firmware al microcontrolador. |
| Autodesk Fusion 360 | https://www.autodesk.com/products/fusion-360/overview | Diseño tridimensional de los componentes y la cápsula del proyecto. |

## 5. Uso de herramientas de inteligencia artificial

Durante las distintas etapas del proyecto se utilizaron herramientas de inteligencia artificial como apoyo para el diseño, la programación, la elaboración de documentación y la organización del trabajo.

### Gemini (Google)

Se utilizó como guía para resolver dudas sobre funciones básicas de Autodesk Fusion 360, incluyendo la visualización de medidas, el cambio de color de componentes y el movimiento de cuerpos.

También se utilizó para revisar la sintaxis y corroborar el contenido de informes, identificar aspectos faltantes según las instrucciones entregadas y evitar redundancias.

Además, se utilizó como apoyo para organizar los procedimientos del protocolo de pruebas del prototipo de monitoreo térmico y evaluar la lectura de temperatura.

Fuente: https://gemini.google.com/

### ChatGPT (OpenAI)

Se utilizó como apoyo para el desarrollo del código del prototipo de monitoreo térmico y para la elaboración del repositorio de GitHub. Esto incluyó la organización de carpetas y archivos, así como la redacción y estructuración del README y otros documentos.

Fuente: https://chatgpt.com/

### Claude (Anthropic)

Se utilizó como apoyo para la elaboración del esquemático eléctrico del proyecto.

Fuente: https://claude.ai/

## 6. Código externo y adaptaciones

El firmware utiliza las bibliotecas y recursos técnicos declarados en este documento.

Los ejemplos o fragmentos de código externos que se hayan utilizado o adaptado deben identificarse y atribuirse a sus respectivas fuentes.
