## Modul 2 — Pemrograman GPIO

---


# 2.5.4 Pertanyaan Praktikum

---

## 1️ Gambarkan rangkaian schematic yang digunakan!

Jawaban:

Rangkaian ini menggunakan Seven Segment Display yang terhubung ke Arduino dengan resistor di setiap segmennya. Segmen a hingga g terhubung ke pin digital Arduino, dan common cathode terhubung ke GND. Arduino mengirim sinyal HIGH atau LOW untuk mengaktifkan segmen tertentu, sehingga membentuk digit angka.

---

## 2️ Apa yang terjadi jika nilai `num` lebih dari 15?

Jawaban:

Apabila nilai num melebihi 15, maka:

* Program akan berusaha menampilkan informasi yang tidak ada dalam array.
* Seven segment mungkin menunjukkan karakter yang salah atau tidak menampilkan apa-apa.
* Kadang-kadang, program bisa mengalami error logika karena indeks array melampaui batasnya.

---

## 3️ Apakah program menggunakan common cathode atau common anode? Jelaskan alasannya!

Jawaban:

Program ini memanfaatkan Common Cathode.

Penjelasannya:

* Common cathode tersambung ke GND
* Segmen akan menyala saat mendapat sinyal HIGH
* Dalam kode, sinyal HIGH dipakai untuk mengaktifkan segmen

---

## 4️ Modifikasi program agar tampilan berjalan dari F ke 0

### Program:

```cpp
int segmentPins[7] = {2,3,4,5,6,7,8};

byte numbers[16][7] = {
  {1,1,1,1,1,1,0}, //0
  {0,1,1,0,0,0,0}, //1
  {1,1,0,1,1,0,1}, //2
  {1,1,1,1,0,0,1}, //3
  {0,1,1,0,0,1,1}, //4
  {1,0,1,1,0,1,1}, //5
  {1,0,1,1,1,1,1}, //6
  {1,1,1,0,0,0,0}, //7
  {1,1,1,1,1,1,1}, //8
  {1,1,1,1,0,1,1}, //9
  {1,1,1,0,1,1,1}, //A
  {0,0,1,1,1,1,1}, //b
  {1,0,0,1,1,1,0}, //C
  {0,1,1,1,1,0,1}, //d
  {1,0,0,1,1,1,1}, //E
  {1,0,0,0,1,1,1}  //F
};

void setup() {

  for(int i=0;i<7;i++){
    pinMode(segmentPins[i], OUTPUT);
  }

}

void loop() {

  for(int num=15; num>=0; num--){

    for(int i=0;i<7;i++){
      digitalWrite(segmentPins[i], numbers[num][i]);
    }

    delay(1000);

  }

}
```

---

## Penjelasan Baris Kode

```cpp
int segmentPins[7] = {2,3,4,5,6,7,8};
```

Menentukan pin Arduino yang digunakan untuk setiap segmen.

---

```cpp
byte numbers[16][7]
```

Array yang berisi pola biner untuk angka **0–F**.

---

```cpp
pinMode(segmentPins[i], OUTPUT);
```

Mengatur semua pin sebagai output.

---

```cpp
for(int num=15; num>=0; num--)
```

Menampilkan angka dari **F ke 0**.

---

```cpp
digitalWrite(segmentPins[i], numbers[num][i]);
```

Menghidupkan segmen sesuai pola angka.

---

```cpp
delay(1000);
```

Memberi jeda 1 detik sebelum angka berikutnya.

---

# 2.6.4 Pertanyaan Percobaan 

---

## 2 Mengapa menggunakan INPUT_PULLUP?

Jawaban:

Mode INPUT_PULLUP digunakan untuk:

* Mengaktifkan resistor pull-up internal
* Menghindari kondisi floating input
* Menjaga nilai input tetap stabil

Keuntungan:

* Tidak perlu resistor eksternal
* Rangkaian lebih sederhana
* Mengurangi noise

---

## 3 Jika salah satu LED segmen tidak menyala, apa penyebabnya?

Jawaban:

Kemungkinan dari sisi hardware:

* Kabel jumper longgar
* Resistor rusak
* Pin Arduino rusak
* Seven segment rusak

Kemungkinan dari sisi software:

* Pin salah pada program
* Kesalahan array pola angka
* Kesalahan logika HIGH/LOW

---

## 4 Modifikasi dengan dua push button (UP dan DOWN)

### Konsep:

* Button 1 → Tambah angka
* Button 2 → Kurangi angka

### Fungsi:

* UP → Counter naik
* DOWN → Counter turun

---

# 2.7 Pertanyaan Praktikum

---

## 1️ Uraikan hasil praktikum

Jawaban:

Pada percobaan pertama, seven segment berhasil menampilkan angka dari 0 hingga F secara berurutan.Pada percobaan kedua, push button berhasil digunakan untuk mengontrol perubahan angka pada seven segment secara manual.Hal ini menunjukkan bahwa Arduino mampu mengontrol output digital dan membaca input digital dengan baik.

---

## 2️ Bagaimana prinsip kerja Seven Segment?

Jawaban:

Seven segment bekerja dengan menyalakan kombinasi 7 LED kecil yang membentuk angka atau huruf.
Setiap LED disebut segmen:

a, b, c, d, e, f, g

Dengan menyalakan kombinasi tertentu, angka dapat ditampilkan.
Contoh:

Angka 0 → Segmen a,b,c,d,e,f aktif
Segmen g mati

---

## 3️ Jelaskan bagaimana sistem counter bekerja!

Jawaban:

Sistem counter pada program bekerja dengan cara menghitung nilai angka secara berurutan dan menampilkannya pada seven segment display. Proses ini dilakukan secara terus-menerus di dalam fungsi loop().Pada awal program, sebuah variabel digunakan untuk menyimpan nilai angka yang akan ditampilkan pada seven segment. Nilai ini biasanya dimulai dari 0. Program kemudian menggunakan array yang berisi pola penyalaan segmen untuk setiap angka dari 0 hingga F.

Ketika program berjalan, Arduino akan mengirimkan sinyal HIGH atau LOW ke masing-masing pin seven segment sesuai dengan pola angka yang tersimpan di dalam array. Hal ini membuat segmen tertentu menyala sehingga membentuk angka yang diinginkan.Pada sistem counter yang menggunakan push button, setiap kali tombol ditekan, Arduino akan membaca perubahan input menggunakan fungsi digitalRead(). Jika tombol terdeteksi ditekan, nilai counter akan bertambah (increment) atau berkurang (decrement) tergantung fungsi tombol yang digunakan. Setelah nilai berubah, program kembali mengirimkan data baru ke seven segment sehingga angka yang ditampilkan ikut berubah.

Proses ini berlangsung berulang kali selama Arduino aktif, sehingga seven segment dapat terus menampilkan angka yang berubah sesuai dengan kondisi counter. Dengan demikian, sistem counter bekerja berdasarkan perubahan nilai variabel yang dikontrol oleh perulangan program dan input dari pengguna.