#include <SPI.h>                      // Library for SPI communication
#include <MFRC522.h>                  // Library for RFID MFRC522
#include <Wire.h>                     // Library for I2C communication
#include <LiquidCrystal_I2C.h>        // Library for I2C LCD
#include <Servo.h>                    // Library to control servo motor

LiquidCrystal_I2C lcd(0x27, 16, 2);    // Initialize the LCD with address 0x27, size 16x2
#define SS_PIN 10                      // Slave Select pin for SPI (SCK, MOSI, MISO, SS)
#define RST_PIN 9                     // Reset pin for MFRC522
MFRC522 mfrc522(SS_PIN, RST_PIN);     // Create MFRC522 instance
Servo myServo;

#define SERVO_PIN 6                    // Pin for servo motor
#define BUZZER_PIN 7                   // Pin for buzzer
#define RED_PIN 3                      // Pin for red LED
#define GREEN_PIN 4                    // Pin for green LED
#define BLUE_PIN 5                     // Pin for blue LED
#define TRIG_PIN A0                    // Pin for ultrasonic sensor trigger
#define ECHO_PIN A1                    // Pin for ultrasonic sensor echo

void setup() {
  Serial.begin(9600);                  // Start serial communication at 9600 baud
  lcd.begin(16, 2);                    // Initialize the LCD with size 16x2
  lcd.backlight();                     // Turn on LCD backlight
  lcd.print("Please Tap");            // Display "Please Tap" message
  lcd.setCursor(0, 1);                 // Set cursor to column 0, row 1
  lcd.print("Your Card");             // Display "Your Card" message

  SPI.begin();                         // Start SPI communication
  mfrc522.PCD_Init();                  // Initialize RFID module
  myServo.attach(SERVO_PIN);           // Attach servo motor to defined pin
  myServo.write(0);                    // Set servo to 0 degrees position

  pinMode(BUZZER_PIN, OUTPUT);         // Set buzzer pin as output
  pinMode(RED_PIN, OUTPUT);            // Set red LED pin as output
  pinMode(GREEN_PIN, OUTPUT);          // Set green LED pin as output
  pinMode(BLUE_PIN, OUTPUT);           // Set blue LED pin as output
  pinMode(TRIG_PIN, OUTPUT);           // Set ultrasonic trigger pin as output
  pinMode(ECHO_PIN, INPUT);            // Set ultrasonic echo pin as input
}

void loop() {
  if (!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial()) {
    delay(50);                         // Wait for 50ms before retrying
    return;                            // Exit the loop if no new card is detected
  }

  String uid = "";                     // Variable to store card UID
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    uid += String(mfrc522.uid.uidByte[i], HEX); // Convert UID to hexadecimal format
  }
  Serial.print("Card detected with UID: ");
  Serial.println(uid);

  lcd.clear();
  lcd.print("Your Payment");           // Display "Your Payment" message
  lcd.setCursor(0, 1);
  lcd.print("Successful");            // Display "Successful" message

  myServo.write(90);                   // Move servo to 90 degrees (open gate)
  delay(5000);                         // Wait for 5 seconds
  myServo.write(0);                    // Move servo back to 0 degrees (close gate)
}
