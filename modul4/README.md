## 4.5.4 Pertanyaan Praktikum

### 1. Apa fungsi perintah `analogRead()` pada rangkaian praktikum ini?

Fungsi `analogRead()` digunakan untuk membaca nilai tegangan analog yang masuk ke pin analog Arduino, misalnya dari potensiometer. Nilai tegangan tersebut kemudian dikonversi oleh ADC (Analog to Digital Converter) menjadi data digital dengan rentang nilai 0 sampai 1023.

Pada praktikum ini, `analogRead()` berfungsi untuk membaca posisi putaran potensiometer. Semakin besar putaran potensiometer, maka nilai ADC yang dibaca juga semakin besar. Nilai tersebut kemudian digunakan untuk menentukan sudut gerak servo motor.

Contoh penggunaan:

```cpp
val = analogRead(potensioPin);
```

Artinya Arduino membaca nilai analog pada pin potensiometer lalu menyimpannya ke variabel `val`.

---

### 2. Mengapa diperlukan fungsi `map()` dalam program tersebut?

Fungsi `map()` digunakan untuk mengubah rentang nilai ADC menjadi rentang nilai yang sesuai dengan kebutuhan servo motor.

Nilai ADC hasil `analogRead()` memiliki rentang:

```txt
0 – 1023
```

Sedangkan servo motor bergerak dalam rentang sudut:

```txt
0° – 180°
```

Karena kedua rentang berbeda, maka diperlukan fungsi `map()` agar nilai ADC dapat dikonversi menjadi sudut servo.

Contoh:

```cpp
pos = map(val, 0, 1023, 0, 180);
```

Artinya:

* Nilai ADC 0 → sudut servo 0°
* Nilai ADC 1023 → sudut servo 180°
* Nilai di antaranya akan disesuaikan secara proporsional

Tanpa fungsi `map()`, servo tidak dapat bergerak sesuai pembacaan potensiometer.

---

### 3. Modifikasi program agar servo hanya bergerak pada rentang 30°–150°

### Program Modifikasi

```cpp
#include <Servo.h>

Servo myservo;

// ===================== PIN SETUP =====================
const int potensioPin = A0;
const int servoPin = 9;

// ===================== VARIABEL =====================
int pos = 0;
int val = 0;

void setup() {

  // Hubungkan servo ke pin 9
  myservo.attach(servoPin);

  // Aktifkan serial monitor
  Serial.begin(9600);
}

void loop() {

  // Membaca nilai ADC dari potensiometer
  val = analogRead(potensioPin);

  // Mapping ADC 0–1023 menjadi sudut 30–150
  pos = map(val, 0, 1023, 30, 150);

  // Menggerakkan servo
  myservo.write(pos);

  // Menampilkan data
  Serial.print("ADC Potensio: ");
  Serial.print(val);

  Serial.print(" | Sudut Servo: ");
  Serial.println(pos);

  // Delay stabilisasi
  delay(50);
}
```

### Penjelasan Program

Program di atas digunakan untuk mengontrol servo motor menggunakan potensiometer. Arduino membaca nilai analog dari potensiometer melalui pin A0 menggunakan fungsi `analogRead()`.

Nilai ADC yang awalnya memiliki rentang 0–1023 kemudian dikonversi menggunakan fungsi `map()` menjadi sudut servo dengan rentang 30° sampai 150°.

```cpp
pos = map(val, 0, 1023, 30, 150);
```

Artinya:

* Saat potensiometer minimum → servo berada di sudut 30°
* Saat potensiometer maksimum → servo berada di sudut 150°

Dengan modifikasi ini, servo tidak akan bergerak penuh dari 0° hingga 180°, sehingga gerakan menjadi lebih aman dan stabil.

---

# 4.6.4 Pertanyaan Praktikum

### 1. Jelaskan mengapa LED dapat diatur kecerahannya menggunakan fungsi `analogWrite()`!

Fungsi `analogWrite()` digunakan untuk menghasilkan sinyal PWM (Pulse Width Modulation). PWM bekerja dengan mengatur lebar pulsa HIGH dan LOW dalam waktu tertentu.

Walaupun pin Arduino sebenarnya hanya menghasilkan sinyal digital HIGH dan LOW, PWM membuat LED menerima tegangan rata-rata yang berbeda-beda sehingga kecerahannya terlihat berubah.

* Nilai PWM kecil → LED redup
* Nilai PWM besar → LED terang

Contoh:

```cpp
analogWrite(ledPin, 50);
```

LED akan menyala redup karena duty cycle kecil.

Sedangkan:

```cpp
analogWrite(ledPin, 255);
```

LED akan menyala penuh karena duty cycle maksimum.

---

### 2. Apa hubungan antara nilai ADC (0–1023) dan nilai PWM (0–255)?

Nilai ADC memiliki rentang:

```txt
0 – 1023
```

Sedangkan PWM memiliki rentang:

```txt
0 – 255
```

Karena rentangnya berbeda, maka nilai ADC perlu dikonversi menjadi PWM menggunakan fungsi `map()`.

Contoh:

```cpp
pwm = map(nilaiADC, 0, 1023, 0, 255);
```

Hubungannya adalah:

* ADC kecil → PWM kecil → LED redup
* ADC besar → PWM besar → LED terang

Nilai ADC menentukan besar kecilnya duty cycle PWM yang dikirim ke LED.

---

### 3. Modifikasi program agar LED hanya menyala pada PWM 50–200

### Program Modifikasi

```cpp
#include <Arduino.h>

// ===================== PIN SETUP =====================
const int potPin = A0;
const int ledPin = 9;

// ===================== VARIABEL =====================
int nilaiADC = 0;
int pwm = 0;

void setup() {

  // Set LED sebagai output
  pinMode(ledPin, OUTPUT);

  // Serial monitor
  Serial.begin(9600);
}

void loop() {

  // Membaca ADC
  nilaiADC = analogRead(potPin);

  // Konversi ADC ke PWM
  pwm = map(nilaiADC, 0, 1023, 0, 255);

  // LED hanya aktif pada PWM 50–200
  if (pwm >= 50 && pwm <= 200) {
    analogWrite(ledPin, pwm);
  } else {
    analogWrite(ledPin, 0);
  }

  // Monitoring data
  Serial.print("ADC: ");
  Serial.print(nilaiADC);

  Serial.print(" | PWM: ");
  Serial.println(pwm);

  // Delay stabilisasi
  delay(50);
}
```

### Penjelasan Program

Program membaca nilai analog dari potensiometer menggunakan `analogRead()`, kemudian mengubahnya menjadi nilai PWM menggunakan fungsi `map()`.

```cpp
pwm = map(nilaiADC, 0, 1023, 0, 255);
```

Setelah itu dilakukan pengecekan kondisi:

```cpp
if (pwm >= 50 && pwm <= 200)
```

Jika nilai PWM berada pada rentang 50 sampai 200, maka LED akan menyala dengan tingkat kecerahan sedang.

Namun jika nilai PWM kurang dari 50 atau lebih dari 200, LED dimatikan dengan:

```cpp
analogWrite(ledPin, 0);
```

Modifikasi ini membuat LED hanya aktif pada rentang kecerahan tertentu.

---

# 4.7 Pertanyaan Praktikum

### 1. Bagaimana proses konversi sinyal analog menjadi digital pada Arduino?

Arduino menggunakan modul ADC (Analog to Digital Converter) untuk mengubah sinyal analog menjadi data digital.

Prosesnya:

1. Sensor atau potensiometer menghasilkan tegangan analog.
2. Tegangan masuk ke pin analog Arduino.
3. ADC mengubah tegangan tersebut menjadi nilai digital.
4. Nilai digital dapat diproses oleh mikrokontroler.

Pada Arduino Uno:

* Resolusi ADC = 10 bit
* Rentang nilai = 0–1023
* Tegangan referensi default = 0–5V

Artinya:

* 0V → nilai 0
* 5V → nilai 1023

Konversi dilakukan menggunakan:

```cpp
analogRead(pin);
```

---

### 2. Faktor apa saja yang dapat mempengaruhi keakuratan pembacaan ADC?

Beberapa faktor yang mempengaruhi keakuratan ADC antara lain:

#### a. Noise atau gangguan listrik

Gangguan listrik dapat menyebabkan nilai ADC berubah-ubah sehingga pembacaan tidak stabil.

#### b. Tegangan referensi tidak stabil

ADC sangat bergantung pada tegangan referensi. Jika tegangan berubah, hasil pembacaan juga berubah.

#### c. Kualitas sensor atau potensiometer

Komponen yang kurang baik dapat menghasilkan sinyal yang tidak stabil.

#### d. Kabel terlalu panjang

Kabel panjang dapat menangkap noise dari lingkungan.

#### e. Resolusi ADC terbatas

Arduino Uno hanya memiliki resolusi 10 bit sehingga ketelitian pembacaan terbatas.

#### f. Suhu dan kondisi lingkungan

Perubahan suhu dapat mempengaruhi performa komponen elektronik.

---

### 3. Apa kendala yang mungkin terjadi saat mengintegrasikan ADC dan PWM dalam satu sistem?

Beberapa kendala yang mungkin terjadi yaitu:

#### a. Noise pada pembacaan ADC

Sinyal PWM dapat menimbulkan gangguan listrik yang mempengaruhi pembacaan ADC.

#### b. Data ADC tidak stabil

Nilai ADC bisa berubah cepat sehingga output PWM menjadi tidak stabil.

#### c. Servo atau LED berkedip

Perubahan ADC yang terlalu sensitif dapat menyebabkan output bergerak terus-menerus.

#### d. Delay sistem

Jika program memiliki delay terlalu besar, respon sistem menjadi lambat.

#### e. Konsumsi daya

Servo motor dan LED PWM dapat membutuhkan arus cukup besar sehingga sistem menjadi tidak stabil jika catu daya kurang baik.

#### f. Jitter pada servo

Perubahan kecil pada ADC dapat membuat servo bergetar karena sudut terus berubah.

Untuk mengatasi masalah tersebut biasanya digunakan:

* Filtering data ADC
* Delay stabilisasi
* Kapasitor tambahan
* Power supply yang stabil
* Teknik smoothing data ADC
