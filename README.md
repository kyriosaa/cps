# Collision Prevention System

## About

- A collision prevention system meant for vehicles and robots.
- C++ using Arduino IDE

<!-- ![alt text](https://github.com/kyriosaa/axis/blob/main/images/axis1.JPG "Axis Image 1") -->

## Features

- **Collision Prevention -** An ultrasonic sensor constantly records and updates data to check if any object gets close to the device. Once an object gets within 10 units (cm/in) of distance to the device, the device triggers a lock on all operations.
- **Warning LED Light -** A yellow LED will blink in accordance with the distance of any object that is detected by the ultrasonic sensor.
- **Locked LED Light -** A red LED will blink when the device is locked due to a close object.

- **Light Level Monitoring -** A photoresistor keeps track of the light level near the device.
- **Light Level LED Light -** A white LED will increase in brightness as the photoresistor detects lower light levels.

- **Data Display -** Data regarding the object distance and light level is shown on a 16x2 LCD screen. The unit of distance can be changed between centimeters and inches. The choice between cm/in is remembered and kept in the Arduino's EEPROM.
- **Remote Control -** Functions of the device can be done on an IR remote controller. These functions include: 
    - Unlocking the app
    - Switching between screens showing distance data, light level data, and an option to reset settings to default
    - Switching distance units between cm/in
    - Resetting settings to default

## Hardware Components

- **Arduino Nano -** System microcontroller
- **Ultrasonic Sensor -** Sensor to detect object distance from device
- **Photoresistor -** Sensor to detect light levels
- **LEDs -** LED lights to indicate warning, locking, and light levels
- **Push Button -** Button for manual unlocking of device
- **16x2 LCD Display -** Displays the sensor data along with options for resetting the device
- **IR Remote & Receiver -** For long range device control