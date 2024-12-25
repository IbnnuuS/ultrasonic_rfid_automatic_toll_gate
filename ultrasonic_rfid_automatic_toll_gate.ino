#include <SPI.h> 		            // Library untuk komunikasi SPI (SCK, MOSI, MISO, SS)
#include <MFRC522.h> 		        // Library untuk RFID MFRC522
#include <Wire.h> 		          // Library untuk komunikasi I2C
#include <LiquidCrystal_I2C.h>	// Library untuk LCD I2C
#include <Servo.h> 		          // Library untuk mengontrol servo

// Inisialisasi LCD dengan alamat 0x27, ukuran 16x2
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Pin untuk modul RFID MFRC522
#define SS_PIN 10 		            // Slave Select pin untuk SPI (SCK, MOSI, MISO, SS)
#define RST_PIN 9 		            // Pin untuk reset MFRC522
MFRC522 mfrc522(SS_PIN, RST_PIN); // Membuat objek MFRC522

// Membuat objek servo
Servo myServo;

// Definisi pin untuk perangkat lainnya
#define SERVO_PIN 6 	// Pin untuk servo
#define BUZZER_PIN 7 	// Pin untuk buzzer
#define RED_PIN 3 	  // Pin untuk LED merah
#define GREEN_PIN 4 	// Pin untuk LED hijau
#define BLUE_PIN 5 	  // Pin untuk LED biru
#define TRIG_PIN A0 	// Pin untuk trigger sensor ultrasonik
#define ECHO_PIN A1 	// Pin untuk echo sensor ultrasonik

void setup() {
  Serial.begin(9600); 		  // Memulai komunikasi serial dengan baud rate 9600
  Wire.begin(); 		        // Memulai komunikasi I2C
  lcd.begin(16, 2); 	      // Inisialisasi LCD dengan ukuran 16x2
  lcd.backlight(); 		      // Mengaktifkan backlight LCD
  lcd.setCursor(0, 0); 		  // Mengatur kursor ke kolom 0 baris 0
  lcd.print("Silahkan Tap");// Menampilkan pesan "Silahkan Tap"
  lcd.setCursor(0, 1); 		  // Mengatur kursor ke kolom 0 baris 1
  lcd.print("Kartu Anda"); 	// Menampilkan pesan "Kartu Anda"

  SPI.begin(); 		      // Memulai komunikasi SPI
  mfrc522.PCD_Init(); 	// Inisialisasi modul RFID MFRC522

  myServo.attach(SERVO_PIN); 	// Menghubungkan servo ke pin yang telah ditentukan
  myServo.write(0); 		      // Mengatur posisi servo ke 0 derajat

  // Mengatur pin perangkat lainnya sebagai input atau output
  pinMode(BUZZER_PIN, OUTPUT); 	// Mengatur pin buzzer sebagai output
  pinMode(RED_PIN, OUTPUT); 	  // Mengatur pin LED merah sebagai output
  pinMode(GREEN_PIN, OUTPUT); 	// Mengatur pin LED hijau sebagai output
  pinMode(BLUE_PIN, OUTPUT); 	  // Mengatur pin LED biru sebagai output
  setRGBColor(255, 0, 0); 	    // Mengatur LED RGB menjadi merah

  pinMode(TRIG_PIN, OUTPUT); 	// Mengatur pin trigger sensor ultrasonik sebagai output
  pinMode(ECHO_PIN, INPUT); 	// Mengatur pin echo sensor ultrasonik sebagai input
}

void loop() {
  // Memeriksa apakah kartu baru terdeteksi
  if (!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial()) {
    delay(50); 	// Menunggu 50ms sebelum mencoba lagi
    return; 	// Keluar dari fungsi loop
  }

  String uid = ""; // Variabel untuk menyimpan UID kartu
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    uid += String(mfrc522.uid.uidByte[i], HEX); // Mengonversi UID ke format heksadesimal
  }

  Serial.print("Kartu terdeteksi dengan UID: ");
  Serial.println(uid);

  // UID yang diizinkan
  String allowedUID = "d5d53d2"; // Ganti sesuai UID yang diinginkan


  // Menampilkan pesan pembayaran berhasil pada LCD
  lcd.clear(); 				      // Membersihkan layar LCD
  lcd.setCursor(0, 0); 			// Mengatur kursor ke kolom 0 baris 0
  lcd.print("Pembayaran Anda"); 	// Menampilkan pesan "Pembayaran Anda"
  lcd.setCursor(0, 1); 			// Mengatur kursor ke kolom 0 baris 1
  lcd.print("Berhasil"); 		// Menampilkan pesan "Berhasil"

  myServo.write(90); 		        // Menggerakkan servo ke 90 derajat (membuka pintu)
  setRGBColor(0, 255, 0); 	    // Mengatur LED RGB menjadi hijau
  tone(BUZZER_PIN, 1000, 500); 	// Mengaktifkan buzzer dengan frekuensi 1000Hz selama 500ms

  unsigned long startWait = millis(); 	// Mencatat waktu saat ini
  bool objectDetected = true; 	      	// Variabel untuk mendeteksi keberadaan objek

  while (objectDetected) {
    long distance = getDistance(); 	// Mengukur jarak dengan sensor ultrasonik
    if (distance >= 1 && distance <= 8) {
      startWait = millis(); 		    // Reset waktu jika objek masih terdeteksi
      objectDetected = true; 		    // Tetap mendeteksi objek
    } else if (millis() - startWait > 2000) {
      objectDetected = false; 		  // Tidak ada objek selama 2 detik, keluar dari loop
    }
    delay(100); // Menunggu 100ms sebelum loop berikutnya
  }

  myServo.write(0); 		    // Menggerakkan servo kembali ke posisi 0 derajat (menutup pintu)
  setRGBColor(255, 0, 0); 	// Mengatur LED RGB menjadi merah
  lcd.clear(); 			        // Membersihkan layar LCD
  lcd.setCursor(0, 0); 		  // Mengatur kursor ke kolom 0 baris 0
  lcd.print("Silahkan Tap");// Menampilkan pesan "Silahkan Tap"
  lcd.setCursor(0, 1); 		  // Mengatur kursor ke kolom 0 baris 1
  lcd.print("Kartu Anda"); 	// Menampilkan pesan "Kartu Anda"

  mfrc522.PICC_HaltA(); 	// Menghentikan komunikasi dengan kartu RFID
  delay(2000); 			      // Menunggu 2 detik sebelum memulai loop lagi
}

void setRGBColor(int red, int green, int blue) {
  analogWrite(RED_PIN, red); 	   // Mengatur intensitas LED merah
  analogWrite(GREEN_PIN, green); // Mengatur intensitas LED hijau
  analogWrite(BLUE_PIN, blue);   // Mengatur intensitas LED biru
}

long getDistance() {
  digitalWrite(TRIG_PIN, LOW); 	// Mengatur pin trigger ke LOW
  delayMicroseconds(2); 	      // Menunggu selama 2 mikrodetik
  digitalWrite(TRIG_PIN, HIGH); // Mengatur pin trigger ke HIGH
  delayMicroseconds(10); 	      // Mengirimkan pulsa selama 10 mikrodetik
  digitalWrite(TRIG_PIN, LOW); 	// Mengatur pin trigger kembali ke LOW

  long duration = pulseIn(ECHO_PIN, HIGH); // Mengukur durasi pantulan suara
  long distance = (duration / 2) / 29.1; // Menghitung jarak dalam cm
  return distance; // Mengembalikan nilai jarak
}