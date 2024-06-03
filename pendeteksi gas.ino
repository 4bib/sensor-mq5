#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// Inisialisasi LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Pin untuk sensor MQ-5
int valorsensorgas;
const int mq5Pin = A1;

// Pin untuk LED
int LED = 7;

// Pin untuk HC-SR04
const int trigPin = 9;
const int echoPin = 10;

// Pin untuk buzzer
int buzzerPin = 12;

// Batas bawah dan atas untuk deteksi gas
const int gasThresholdLow = 300;  
const int gasThresholdHigh = 1000; 

// Variabel untuk durasi dan jarak
long duration;
int distance;

void setup() { 
  pinMode(LED, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  
  lcd.init(); // Inisialisasi LCD
  lcd.backlight(); // Mengaktifkan lampu latar LCD
  Serial.begin(9600);
}

void loop() {
  // Membaca nilai dari sensor gas
  valorsensorgas = analogRead(mq5Pin);

  // Mengirimkan pulse dari trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Membaca durasi waktu dari echoPin
  duration = pulseIn(echoPin, HIGH);

  // Menghitung jarak berdasarkan durasi
  distance = duration * 0.034 / 2;

  // Menampilkan nilai sensor gas dan jarak pada LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Gas: ");
  lcd.print(valorsensorgas);
  lcd.setCursor(0, 1);
  lcd.print("Dist: ");
  lcd.print(distance);
  lcd.print(" cm");

  // Menampilkan nilai sensor gas dan jarak pada Serial Monitor
  Serial.print("Gas: ");
  Serial.print(valorsensorgas);
  Serial.print(" | Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Mengecek apakah nilai sensor gas berada dalam rentang tertentu
  if (valorsensorgas >= gasThresholdLow && valorsensorgas <= gasThresholdHigh) {
    digitalWrite(LED, HIGH); // Nyalakan LED
    tone(buzzerPin, HIGH); // Menyalakan Buzzer
  } else {
    digitalWrite(LED, LOW); // Matikan LED
    noTone(buzzerPin); // Mematikan Buzzer
  }
  
  delay(1000); // Tunggu 1 detik sebelum loop berikutnya
}