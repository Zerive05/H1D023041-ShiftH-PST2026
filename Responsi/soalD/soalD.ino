#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Arduino.h>

// Ganti alamat jika perlu (Ox27 / Ox20) 
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int pinPot = A0;
const int ledPin = 8;    // pin PWM

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  // Atur pin LED sebagai output
  pinMode(ledPin, OUTPUT);
}

void loop() {
  int nilai = analogRead(pinPot);

  // Mapping ke bar (0-16)
  int panjangBar = map(nilai, 0, 1023, 0, 20);
  // ===================== PEMROSESAN DATA (SCALING) =====================
  // Ubah nilai ADC (0–1023) menjadi nilai PWM (0–255)
  int pwm = map(nilaiADC,
            0,    // nilai minimum ADC
            1023, // nilai maksimum ADC
            0,    // PWM minimum
            255); // PWM maksimum

  // Tampilkan ke Serial
  Serial.print("Status lampu: ");
  if (panjangBar >= 5){
    Serial.println("Lampu Menyala");
  } else {
    Serial.println("Lampu Mati");
  }
  // ===================== OUTPUT PWM =====================
  // Kirim sinyal PWM ke LED (mengatur kecerahan)
  analogWrite(ledPin, pwm);

  // Baris 1: nilai ADC
  lcd.setCursor(0, 0);
  lcd.print("Tingkat kecerahan: ");
  lcd.print(nilai);
  lcd.print(" "); // clear sisa

  // Baris 2: bar
  lcd.setCursor(0, 1);
  for (int i = 0; i < 16; i++) {
    if (i < panjangBar) {
      lcd.print((char)255);
    }
    else {
    lcd.print(" ");
    }
  }
  delay(200);  

}