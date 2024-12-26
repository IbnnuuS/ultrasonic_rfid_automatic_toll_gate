# Implementation of an Automatic Toll Gate System Based on Ultrasonic Sensors and RFID

This project demonstrates an automated toll gate system using ultrasonic sensors for vehicle detection and RFID technology for secure access control. The system efficiently manages vehicle entry and exit, offering a seamless and contactless toll payment solution.

[![My Skills](https://skillicons.dev/icons?i=arduino,cpp)](https://skillicons.dev)

## Features

- **Vehicle Detection:** Uses ultrasonic sensors to detect vehicles at the toll gate.
- **RFID Authentication:** Allows access only to authorized vehicles via RFID cards.
- **Automated Gate Control:** Controls the gate barrier using a servo motor.
- **Visual and Audio Feedback:** Provides status updates through an LCD display, LED indicators, and a buzzer.

## Required Components

- Arduino Uno (or compatible microcontroller)
- Ultrasonic Sensor (HC-SR04)
- RFID Module (MFRC522)
- Servo Motor
- LCD Display (I2C)
- LED Indicators (Red, Green, Blue)
- Buzzer
- Jumper Wires and Breadboard

## Wiring Diagram

### Ultrasonic Sensor (HC-SR04)

| Ultrasonic Sensor | Arduino |
|-------------------|---------|
| VCC               | 5V      |
| GND               | GND     |
| TRIG              | A0      |
| ECHO              | A1      |

### RFID Module (MFRC522)

| RFID Module | Arduino |
|-------------|---------|
| VCC         | 3.3V    |
| GND         | GND     |
| RST         | 9       |
| NSS (SDA)   | 10      |
| MOSI        | 11      |
| MISO        | 12      |
| SCK         | 13      |

### Servo Motor

| Servo Motor | Arduino |
|-------------|---------|
| VCC         | 5V      |
| GND         | GND     |
| SIGNAL      | 6       |

### LCD Display

| LCD Display | Arduino |
|-------------|---------|
| VCC         | 5V      |
| GND         | GND     |
| SDA         | A4      |
| SCL         | A5      |

### LED Indicators

| LED          | Arduino |
|--------------|---------|
| Red (R)      | 3       |
| Green (G)    | 4       |
| Blue (B)     | 5       |

### Buzzer

| Buzzer       | Arduino |
|--------------|---------|
| Positive (+) | 7       |
| Negative (-) | GND     |

## Installation and Usage

### 1. Setup Instructions

1. Connect the components as per the wiring diagram.
2. Clone this repository and open the source code in Arduino IDE.
3. Install the required libraries:
   - `SPI`
   - `MFRC522`
   - `Wire`
   - `LiquidCrystal_I2C`
   - `Servo`
4. Upload the code to the Arduino board.

### 2. Implementation Results
   Open the link if you want to see the results of my implementation [Google Drive](https://skillicons.dev)
