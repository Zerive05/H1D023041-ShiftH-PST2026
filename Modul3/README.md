# 3.5 Pertanyaan Praktikum (UART)

---

# 1) Jelaskan proses dari input keyboard hingga LED menyala/mati!

Proses dimulai ketika pengguna mengetik karakter pada keyboard di Serial Monitor. Karakter yang diketik akan dikirim dari komputer ke Arduino melalui komunikasi serial UART.

Langkah prosesnya sebagai berikut:

1. Pengguna mengetik karakter pada keyboard, misalnya '1' atau '0'.
2. Serial Monitor mengirim data karakter tersebut melalui komunikasi serial (UART).
3. Arduino menerima data serial melalui pin RX.
4. Program memeriksa apakah terdapat data masuk menggunakan `Serial.available()`.
5. Jika ada data, Arduino membaca data tersebut menggunakan `Serial.read()`.
6. Jika karakter yang diterima adalah '1', maka Arduino memberi perintah `digitalWrite()` untuk menyalakan LED.
7. Jika karakter yang diterima adalah '0', maka Arduino memberi perintah untuk mematikan LED.
8. LED menyala atau mati sesuai perintah yang diterima dari keyboard.

Dengan demikian, komunikasi UART memungkinkan Arduino menerima input dari komputer secara langsung.

---

# 2) Mengapa digunakan Serial.available() sebelum membaca data? Apa yang terjadi jika baris tersebut dihilangkan?

Fungsi `Serial.available()` digunakan untuk memeriksa apakah terdapat data yang tersedia di buffer serial sebelum dilakukan pembacaan data.

Tujuan penggunaan fungsi ini adalah:

* Untuk memastikan bahwa data sudah tersedia sebelum dibaca.
* Untuk menghindari pembacaan data kosong.
* Untuk menjaga kestabilan komunikasi serial.

Jika baris `Serial.available()` dihilangkan, maka:

* Arduino akan tetap mencoba membaca data meskipun tidak ada data masuk.
* Fungsi `Serial.read()` dapat membaca data kosong atau nilai tidak valid.
* Program dapat bekerja tidak stabil.
* LED dapat menyala atau mati secara tidak terduga.

Oleh karena itu, penggunaan `Serial.available()` sangat penting dalam komunikasi serial.

---

# 3) Modifikasi program agar LED berkedip ketika menerima input '2'

## Program Arduino

```cpp
int led = 13;
char data;
bool blinkMode = false;

void setup() {
  pinMode(led, OUTPUT);
  Serial.begin(9600);
}

void loop() {

  if (Serial.available()) {
    data = Serial.read();

    if (data == '1') {
      digitalWrite(led, HIGH);
      blinkMode = false;
    }

    else if (data == '0') {
      digitalWrite(led, LOW);
      blinkMode = false;
    }

    else if (data == '2') {
      blinkMode = true;
    }

  }

  if (blinkMode == true) {
    digitalWrite(led, HIGH);
    delay(500);
    digitalWrite(led, LOW);
    delay(500);
  }

}
```

---

## Penjelasan Setiap Baris Kode

```cpp
int led = 13;
```

Menentukan pin LED berada pada pin digital 13.

```cpp
char data;
```

Digunakan untuk menyimpan karakter data dari Serial Monitor.

```cpp
bool blinkMode = false;
```

Variabel untuk menyimpan status mode berkedip.

```cpp
void setup() {
```

Fungsi awal yang dijalankan satu kali saat Arduino dinyalakan.

```cpp
pinMode(led, OUTPUT);
```

Menentukan pin LED sebagai output.

```cpp
Serial.begin(9600);
```

Memulai komunikasi serial dengan baudrate 9600.

```cpp
void loop() {
```

Fungsi utama yang berjalan berulang.

```cpp
if (Serial.available()) {
```

Memeriksa apakah terdapat data masuk.

```cpp
data = Serial.read();
```

Membaca data dari Serial Monitor.

```cpp
if (data == '1') {
digitalWrite(led, HIGH);
blinkMode = false;
}
```

Jika menerima '1', LED menyala dan mode blink dimatikan.

```cpp
else if (data == '0') {
digitalWrite(led, LOW);
blinkMode = false;
}
```

Jika menerima '0', LED mati dan mode blink dimatikan.

```cpp
else if (data == '2') {
blinkMode = true;
}
```

Jika menerima '2', mode blink diaktifkan.

```cpp
if (blinkMode == true) {
```

Jika mode blink aktif, LED akan berkedip.

```cpp
digitalWrite(led, HIGH);
delay(500);
digitalWrite(led, LOW);
delay(500);
```

LED menyala dan mati dengan jeda 500 ms.

---

# 4) Tentukan apakah menggunakan delay() atau millis()! Jelaskan pengaruhnya terhadap sistem

Pada program di atas digunakan **delay()** untuk membuat LED berkedip.

Namun, penggunaan `millis()` sebenarnya lebih baik dibandingkan `delay()`.

Perbandingan:

### delay()

Keuntungan:

* Mudah digunakan.
* Cocok untuk program sederhana.

Kerugian:

* Menghentikan sementara seluruh program.
* Arduino tidak dapat menerima input baru selama delay berlangsung.
* Kurang efisien untuk sistem multitasking.

### millis()

Keuntungan:

* Tidak menghentikan program.
* Arduino tetap dapat membaca input serial.
* Cocok untuk sistem yang kompleks.

Kerugian:

* Lebih sulit diprogram.
* Membutuhkan logika tambahan.

Pengaruh terhadap sistem:

Jika menggunakan `delay()`, respon terhadap input baru bisa menjadi lambat.
Jika menggunakan `millis()`, sistem akan lebih responsif dan stabil.

---

# 3.6.4 Pertanyaan Praktikum (I2C)

---

# 1) Jelaskan bagaimana cara kerja komunikasi I2C antara Arduino dan LCD

Komunikasi I2C menggunakan dua jalur utama, yaitu SDA (data) dan SCL (clock).

Cara kerjanya:

1. Arduino bertindak sebagai master.
2. LCD bertindak sebagai slave.
3. Arduino mengirim alamat I2C LCD, misalnya 0x27.
4. Jika alamat sesuai, LCD merespon.
5. Arduino mengirim data melalui jalur SDA.
6. Sinyal clock dikirim melalui jalur SCL.
7. LCD menerima data dan menampilkannya pada layar.

Dengan metode ini, hanya dua pin yang dibutuhkan untuk mengendalikan LCD.

---

# 2) Apakah pin potensiometer harus seperti itu? Apa yang terjadi jika pin kiri dan kanan tertukar?

Pin potensiometer biasanya terdiri dari:

* Pin kiri → Ground
* Pin tengah → Analog input
* Pin kanan → 5V

Jika pin kiri dan kanan tertukar, maka:

* Nilai analog tetap dapat dibaca.
* Namun arah perubahan nilai menjadi terbalik.
* Saat diputar ke kanan, nilai akan menurun.
* Saat diputar ke kiri, nilai akan meningkat.

Hal ini tidak merusak rangkaian, tetapi arah pembacaan menjadi kebalikan.

---

# 3) Program Gabungan UART dan I2C

(Ini bagian penting — biasanya bernilai besar)

## Program Arduino

```cpp
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);

int potPin = A0;

int adc;
float volt;
int persen;

void setup() {

  Serial.begin(9600);

  lcd.init();
  lcd.backlight();

}

void loop() {

  adc = analogRead(potPin);

  volt = adc * (5.0 / 1023.0);

  persen = map(adc, 0, 1023, 0, 100);

  Serial.print("ADC: ");
  Serial.print(adc);
  Serial.print("  ");

  Serial.print("Volt: ");
  Serial.print(volt);
  Serial.print(" V  ");

  Serial.print("Persen: ");
  Serial.print(persen);
  Serial.println("%");

  lcd.setCursor(0,0);
  lcd.print("ADC:");
  lcd.print(adc);

  lcd.setCursor(0,1);

  int bar = map(adc,0,1023,0,16);

  for(int i=0;i<bar;i++){
    lcd.print("|");
  }

  delay(500);

}
```

---

# 4) Tabel Pengamatan

Menggunakan rumus:

Volt = ADC × (5 / 1023)
Persen = (ADC / 1023) × 100%

| ADC | Volt (V) | Persen (%) |
| --- | -------- | ---------- |
| 1   | 0.00     | 0%         |
| 21  | 0.10     | 2%         |
| 49  | 0.24     | 5%         |
| 74  | 0.36     | 7%         |
| 96  | 0.47     | 9%         |

---

# 3.7 Pertanyaan Tambahan

---

# 1) Keuntungan dan Kerugian UART dan I2C

## UART

Keuntungan:

* Mudah digunakan.
* Tidak membutuhkan clock.
* Cocok untuk komunikasi jarak pendek.

Kerugian:

* Hanya dapat komunikasi dua perangkat.
* Membutuhkan dua pin untuk setiap perangkat.

## I2C
Keuntungan:
* Hanya menggunakan dua pin.
* Dapat menghubungkan banyak perangkat.
* Hemat pin.

Kerugian:
* Lebih lambat dibanding SPI.
* Membutuhkan alamat perangkat.

# 2) Peran alamat I2C pada LCD (0x27 vs 0x20)

Alamat I2C digunakan untuk mengidentifikasi perangkat pada jalur komunikasi.
Contohnya sebagai berikut:

0x27 → alamat LCD tertentu
0x20 → alamat LCD lain

Jika alamat yang digunakan tidak sesuai:
* LCD tidak akan merespon.
* Data tidak akan tampil.
* Program tetap berjalan tetapi LCD kosong.

Setiap perangkat I2C harus memiliki alamat yang berbeda.

# 3) Alur kerja jika UART dan I2C digabung

Alur jika UART dan I2C digabung dalam satu sistem:
1. Pengguna mengirim data melalui Serial Monitor.
2. Arduino menerima data melalui UART.
3. Arduino memproses data tersebut.
4. Arduino mengirim hasil ke LCD menggunakan I2C.
5. Data ditampilkan di LCD.
6. Data juga dapat ditampilkan kembali ke Serial Monitor.

Arduino dapat mengelola dua protokol sekaligus karena:
* UART menggunakan hardware serial.
* I2C menggunakan library Wire.
* Kedua protokol berjalan secara independen.
Hal ini memungkinkan sistem menjadi lebih fleksibel dan kompleks.