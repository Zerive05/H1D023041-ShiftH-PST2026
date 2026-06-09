# README Modul 5 – Real-Time Operating System (RTOS)

# 5.5.4 Pertanyaan Praktikum

## 1. Apakah ketiga task berjalan secara bersamaan atau bergantian? Jelaskan mekanismenya!

Ketiga task pada RTOS sebenarnya tidak benar-benar berjalan secara bersamaan karena Arduino Uno hanya memiliki satu prosesor (single core). Task berjalan secara bergantian dengan sangat cepat sehingga terlihat seperti berjalan bersamaan.

RTOS menggunakan mekanisme yang disebut scheduler. Scheduler bertugas mengatur kapan sebuah task dijalankan, dihentikan sementara, lalu digantikan task lain.

Mekanisme kerja:

1. RTOS menjalankan task pertama.
2. Setelah waktu tertentu atau saat task melakukan delay, scheduler memindahkan eksekusi ke task lain.
3. Pergantian ini terjadi sangat cepat sehingga semua task terlihat aktif secara simultan.

Contohnya:

* Task 1 → mengontrol LED
* Task 2 → membaca sensor
* Task 3 → menampilkan data Serial Monitor

Semua task mendapat giliran eksekusi secara teratur melalui teknik multitasking.

---

## 2. Bagaimana cara menambahkan task keempat? Jelaskan langkahnya!

Untuk menambahkan task keempat pada RTOS, langkah-langkahnya adalah:

### a. Membuat fungsi task baru

Pertama membuat fungsi task tambahan.

Contoh:

```cpp id="9ymcim"
void Task4(void *pvParameters) {
  while(1) {
    Serial.println("Task 4 berjalan");
    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
}
```

---

### b. Membuat task menggunakan `xTaskCreate()`

Task baru didaftarkan ke scheduler RTOS.

Contoh:

```cpp id="c25wg4"
xTaskCreate(
  Task4,
  "Task4",
  128,
  NULL,
  1,
  NULL
);
```

Penjelasan parameter:

* `Task4` → nama fungsi task
* `"Task4"` → nama task
* `128` → ukuran stack
* `NULL` → parameter task
* `1` → prioritas task
* `NULL` → handle task

---

### c. Compile dan upload program

Setelah task ditambahkan, scheduler RTOS akan menjalankan task tersebut bersama task lainnya secara bergantian.

Dengan langkah ini sistem dapat menjalankan lebih banyak proses secara multitasking.

---

## 3. Modifikasi program dengan menambah potensiometer untuk mengontrol kecepatan LED

## Program Modifikasi

```cpp id="vrlwq9"
#include <Arduino_FreeRTOS.h>

const int ledPin = 9;
const int potPin = A0;

int delayLed = 500;

void TaskLED(void *pvParameters);
void TaskPotensio(void *pvParameters);

void setup() {

  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);

  xTaskCreate(TaskLED, "LED", 128, NULL, 1, NULL);
  xTaskCreate(TaskPotensio, "Pot", 128, NULL, 1, NULL);

  vTaskStartScheduler();
}

void loop() {
}

void TaskLED(void *pvParameters) {

  while(1) {

    digitalWrite(ledPin, HIGH);
    vTaskDelay(delayLed / portTICK_PERIOD_MS);

    digitalWrite(ledPin, LOW);
    vTaskDelay(delayLed / portTICK_PERIOD_MS);
  }
}

void TaskPotensio(void *pvParameters) {

  while(1) {

    int adc = analogRead(potPin);

    // Mapping ADC menjadi delay LED
    delayLed = map(adc, 0, 1023, 100, 1000);

    Serial.print("ADC: ");
    Serial.print(adc);

    Serial.print(" | Delay LED: ");
    Serial.println(delayLed);

    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}
```

---

## Penjelasan Program

Program menggunakan dua task:

* TaskLED → mengontrol kedipan LED
* TaskPotensio → membaca nilai potensiometer

Potensiometer dibaca menggunakan:

```cpp id="cfzytv"
analogRead(potPin);
```

Nilai ADC kemudian dikonversi menjadi delay LED:

```cpp id="06cxva"
delayLed = map(adc, 0, 1023, 100, 1000);
```

Hasilnya:

* Potensiometer kecil → delay kecil → LED berkedip cepat
* Potensiometer besar → delay besar → LED berkedip lambat

RTOS memungkinkan kedua task berjalan secara multitasking tanpa saling mengganggu.

---

# 5.6.4 Pertanyaan Praktikum

## 1. Apakah kedua task berjalan secara bersamaan atau bergantian? Jelaskan mekanismenya!

Kedua task berjalan secara bergantian, bukan benar-benar paralel. RTOS menggunakan scheduler untuk mengatur pembagian waktu CPU kepada setiap task.

Ketika satu task sedang delay atau menunggu, scheduler akan memberikan kesempatan kepada task lain untuk berjalan.

Proses ini disebut context switching, yaitu perpindahan eksekusi antar task secara cepat.

Akibatnya:

* Task pembacaan sensor tetap berjalan
* Task tampilan data juga tetap berjalan
* Sistem terlihat bekerja bersamaan

Padahal sebenarnya CPU hanya menjalankan satu task pada satu waktu.

---

## 2. Apakah program ini berpotensi mengalami race condition? Jelaskan!

Ya, program RTOS berpotensi mengalami race condition jika dua task mengakses variabel yang sama secara bersamaan tanpa mekanisme sinkronisasi.

Race condition terjadi ketika:

* Satu task sedang mengubah data
* Task lain membaca data pada waktu yang sama

Akibatnya data bisa:

* Tidak sinkron
* Berubah secara tidak stabil
* Menyebabkan output salah

Contoh:

```cpp id="gs4t1f"
temperature = sensorValue;
```

Jika task lain membaca `temperature` saat nilai sedang diubah, maka hasil pembacaan bisa tidak valid.

Untuk mencegah race condition biasanya digunakan:

* Mutex
* Semaphore
* Queue
* Critical section

Pada praktikum sederhana kemungkinan race condition kecil, tetapi tetap bisa terjadi jika banyak task menggunakan data bersama.

---

## 3. Modifikasi program menggunakan sensor DHT asli

## Program Modifikasi

```cpp id="j2dv1p"
#include <Arduino_FreeRTOS.h>
#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

float suhu = 0;
float kelembapan = 0;

void TaskSensor(void *pvParameters);
void TaskDisplay(void *pvParameters);

void setup() {

  Serial.begin(9600);

  dht.begin();

  xTaskCreate(TaskSensor, "Sensor", 128, NULL, 1, NULL);
  xTaskCreate(TaskDisplay, "Display", 128, NULL, 1, NULL);

  vTaskStartScheduler();
}

void loop() {
}

void TaskSensor(void *pvParameters) {

  while(1) {

    suhu = dht.readTemperature();
    kelembapan = dht.readHumidity();

    vTaskDelay(2000 / portTICK_PERIOD_MS);
  }
}

void TaskDisplay(void *pvParameters) {

  while(1) {

    Serial.print("Suhu: ");
    Serial.print(suhu);

    Serial.print(" C | Kelembapan: ");
    Serial.print(kelembapan);

    Serial.println(" %");

    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}
```

---

## Penjelasan Program

Program menggunakan sensor DHT11 untuk membaca suhu dan kelembapan secara real-time.

Task yang digunakan:

* `TaskSensor` → membaca data sensor
* `TaskDisplay` → menampilkan data ke Serial Monitor

Pembacaan sensor:

```cpp id="91n74x"
suhu = dht.readTemperature();
kelembapan = dht.readHumidity();
```

Hasil pembacaan akan berubah secara dinamis sesuai kondisi lingkungan.

Contoh hasil:

```txt id="xcm8ff"
Suhu: 29 C | Kelembapan: 74 %
```

RTOS memungkinkan pembacaan sensor dan tampilan data berjalan secara multitasking sehingga sistem lebih responsif.

---

# 5.7 Pertanyaan Praktikum

## 1. Jelaskan perbedaan antara `loop()` pada Arduino biasa dengan sistem RTOS!

### Arduino Biasa

Pada Arduino biasa, seluruh program dijalankan di dalam fungsi:

```cpp id="4v4m1k"
void loop()
```

Semua proses berjalan secara berurutan (sequential). Jika ada delay panjang, maka proses lain harus menunggu.

Contoh:

* LED berkedip
* Sensor dibaca
* Data ditampilkan

Semuanya dilakukan satu per satu.

---

### Sistem RTOS

Pada RTOS, program dibagi menjadi beberapa task yang dikelola scheduler.

Keunggulan:

* Multitasking
* Task dapat memiliki prioritas
* Sistem lebih responsif
* Lebih mudah mengelola program kompleks

RTOS memungkinkan beberapa proses berjalan secara bergantian dengan cepat sehingga terlihat paralel.

---

## 2. Mengapa fungsi `loop()` dibiarkan kosong?

Pada sistem RTOS, fungsi utama program sudah diambil alih oleh scheduler RTOS.

Setelah:

```cpp id="6o1j04"
vTaskStartScheduler();
```

Scheduler akan menjalankan semua task yang sudah dibuat.

Karena seluruh proses sudah berada di dalam task RTOS, maka fungsi:

```cpp id="wrb4x5"
void loop()
```

tidak lagi digunakan sehingga biasanya dibiarkan kosong.

---

## 3. Apa insight utama yang Anda pelajari dari praktikum ini?

Insight utama dari praktikum ini adalah memahami bagaimana RTOS memungkinkan mikrokontroler menjalankan banyak task secara multitasking pada satu prosesor.

Selain itu dipelajari juga:

* Cara membuat task
* Cara kerja scheduler
* Konsep multitasking
* Komunikasi antar task
* Pengaturan delay menggunakan RTOS
* Pengelolaan resource sistem

Praktikum ini menunjukkan bahwa RTOS sangat membantu dalam pengembangan sistem embedded yang kompleks karena program menjadi lebih terstruktur, responsif, dan mudah dikembangkan dibandingkan menggunakan loop biasa.
