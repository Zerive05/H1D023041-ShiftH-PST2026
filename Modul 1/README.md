## Modul 1 – Percabangan dan Perulangan  
**Nama** : Dwi Bagus Purwo Aji  
**NIM** : H1D023041 

---

# 1.5.4 Pertanyaan Praktikum (Percabangan)

## 1. Pada kondisi apa program masuk ke blok `if`?
Program akan masuk ke blok `if` ketika ekspresi logika atau kondisi yang didefinisikan di dalam kurung `if(kondisi)` bernilai **benar (true)** atau memiliki nilai non-nol.

---

## 2. Pada kondisi apa program masuk ke blok `else`?
Program akan masuk ke blok `else` ketika kondisi pada blok `if` (dan semua `else if` jika ada) bernilai **salah (false)** atau nol. Blok `else` berfungsi sebagai pilihan terakhir jika tidak ada kondisi di atasnya yang terpenuhi.

---

## 3. Apa fungsi dari perintah `delay(timeDelay)`?
Fungsi `delay(timeDelay)` digunakan untuk **menghentikan sementara (pause)** eksekusi program selama durasi waktu tertentu. Satuan yang digunakan dalam parameter `timeDelay` adalah **milidetik (ms)**, sehingga `delay(1000)` berarti program berhenti selama 1 detik.

---

## 4. Modifikasi Program  
### Alur: cepat → sedang → mati
Berikut adalah contoh logika program menggunakan `if-else` untuk mengatur kecepatan kedip LED:

```cpp
int ledPin = 13;
int state = 0; // 0: Cepat, 1: Sedang, 2: Mati

void setup() {
  pinMode(ledPin, OUTPUT);
}

void loop() {
  if (state == 0) {
    // Cepat
    digitalWrite(ledPin, HIGH);
    delay(100);
    digitalWrite(ledPin, LOW);
    delay(100);
    state = 1; 
  } else if (state == 1) {
    // Sedang
    digitalWrite(ledPin, HIGH);
    delay(500);
    digitalWrite(ledPin, LOW);
    delay(500);
    state = 2;
  } else {
    // Mati
    digitalWrite(ledPin, LOW);
    delay(1000);
    state = 0; // Kembali ke Cepat
  }
}
```

---

# **1.6.4 Pertanyaan Praktikum (Perulangan)**

## **1. Gambarkan rangkaian schematic 5 LED running yang digunakan pada percobaan!**
*(Deskripsi Rangkaian)*:
*   **LED 1 - 5**: Kaki Anoda (positif) masing-masing dihubungkan ke Digital Pin Arduino (misal: Pin 2, 3, 4, 5, dan 6).
*   **Resistor**: Tiap LED dihubungkan seri dengan resistor (220Ω) untuk membatasi arus.
*   **Ground**: Kaki Katoda (negatif) semua LED dihubungkan ke jalur **GND** pada Arduino.

---

## **2. Jelaskan bagaimana program membuat efek LED berjalan dari kiri ke kanan!**
Efek ini dibuat menggunakan perulangan `for` dengan indeks yang **meningkat (increment)**. Program akan menyalakan LED pada pin terendah, memberikan delay, mematikannya, lalu melanjutkan ke pin berikutnya yang lebih tinggi secara berurutan.

---

## **3. Jelaskan bagaimana program membuat LED kembali dari kanan ke kiri!**
Efek ini merupakan kebalikan dari sebelumnya, yaitu menggunakan perulangan `for` dengan indeks yang **menurun (decrement)**. Dimulai dari pin LED paling kanan (indeks terbesar), lalu dikurangi satu per satu hingga mencapai LED paling kiri (indeks terkecil).

---

## **4. Buatkan program agar LED menyala tiga LED kanan dan tiga LED kiri secara bergantian**

```cpp
// Asumsi menggunakan 6 LED pada Pin 2 sampai 7
void setup() {
  for (int i = 2; i <= 7; i++) {
    pinMode(i, OUTPUT);
  }
}

void loop() {
  // Tiga LED Kiri Menyala (Pin 2, 3, 4)
  for (int i = 2; i <= 4; i++) digitalWrite(i, HIGH);
  for (int i = 5; i <= 7; i++) digitalWrite(i, LOW);
  delay(500);

  // Tiga LED Kanan Menyala (Pin 5, 6, 7)
  for (int i = 2; i <= 4; i++) digitalWrite(i, LOW);
  for (int i = 5; i <= 7; i++) digitalWrite(i, HIGH);
  delay(500);
}
```

### **Penjelasan Program**
Program di atas membagi 6 LED menjadi dua grup. Grup pertama (pin 2, 3, 4) dikontrol secara bersamaan menggunakan perulangan `for` untuk dinyalakan (`HIGH`), sementara grup kedua dimatikan. Setelah jeda 500ms, kondisi dibalik sehingga tercipta efek visual bergantian antara sisi kiri dan sisi kanan.

---

# **1.7 Pertanyaan Analisis**

## **1. Uraikan hasil tugas pada praktikum yang telah dilakukan pada setiap percobaan!**
Hasil praktikum menunjukkan bahwa penggunaan **Percabangan** sangat efektif untuk membuat keputusan berdasarkan kondisi tertentu (seperti pergantian mode), sedangkan **Perulangan** mempermudah pengendalian banyak komponen (seperti banyak LED) dengan baris kode yang lebih ringkas. LED dapat dikontrol urutannya dan durasinya dengan presisi.

---

## **2. Bagaimana pengaruh penggunaan struktur perulangan (seperti for dan while) terhadap jalannya program pada Arduino?**
Struktur perulangan membuat program menjadi lebih **efisien dan dinamis**. Tanpa perulangan, kita harus menulis perintah `digitalWrite` berulang kali untuk setiap pin. Dengan `for` atau `while`, kita cukup mendefinisikan rentang pin, sehingga kode lebih mudah dibaca, dikelola, dan meminimalkan kesalahan penulisan.

---

## **3. Bagaimana cara kerja percabangan (`if-else`) dalam menentukan kondisi LED menyala atau mati berdasarkan input yang diberikan?**
`if-else` bekerja sebagai **gerbang logika**. Program akan mengevaluasi nilai input (misal dari tombol atau variabel sensor). Jika nilai input sesuai dengan syarat yang ditentukan, perintah di dalam `if` dieksekusi (misal: LED menyala). Jika tidak sesuai, program akan melewati perintah tersebut atau menjalankan perintah alternatif di dalam `else` (misal: LED mati).

---

## **4. Bagaimana kombinasi antara perulangan dan percabangan dapat digunakan untuk membuat sistem Arduino yang responsif terhadap perubahan kondisi lingkungan?**
Kombinasi ini memungkinkan sistem melakukan **pemantauan terus-menerus dan aksi spesifik**. Perulangan (loop) digunakan untuk membaca data sensor secara kontinu, sementara percabangan (`if-else`) digunakan untuk menentukan respon yang tepat terhadap data tersebut. 
*Contoh*: Perulangan membaca sensor cahaya setiap saat, dan jika (`if`) cahaya di bawah ambang batas (gelap), maka perulangan lain akan menjalankan animasi LED berjalan sebagai peringatan.

---
