# RoadLoad System

## System Description

The RoadLoad system is designed to scan road elevations using ultrasonic sensors. This system aims to provide precise measurements of road surface irregularities to facilitate data analysis for various applications, such as load data analysis.

## Components

- **Ultrasonic Sensors**: Used to scan road elevations.
- **Microcontroller**: ESP32, connected to the ultrasonic sensors.
- **Motors**: Stepper motors used to pull the sensors at a constant speed.
- **Data Transmission**: Sends data via email to the user.

## System Operation

1. **Scanning Process**:
   - The ultrasonic sensors are mounted on a platform and connected to an ESP32 microcontroller.
   - Stepper motors move the platform at a constant speed over the road surface.
   - The ultrasonic sensors scan the road elevations as the platform moves.

2. **Data Collection**:
   - The collected data is transmitted from the ESP32 to the user via email at specific intervals.
   - The data includes measurements of road surface elevations.

3. **Data Processing**:
   - The transmitted data is processed and filtered to remove noise and irrelevant information.
   - The processed data is then used for further analysis.

## Applications

- Load data analysis for vehicles and robots.
- Assessment of road surface conditions.
- Research and development

## References
- [Ultrasonic Sensor and ESP32]https://randomnerdtutorials.com/esp32-hc-sr04-ultrasonic-arduino/
- [Sending Emails with ESP32]https://randomnerdtutorials.com/esp32-send-email-smtp-server-arduino-ide/
