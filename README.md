# GMRT Programmer Day 1 - Solution & Documentation

Dokumentasi dan pembahasan lengkap untuk penyelesaian **Studi Kasus Programmer Day 1 - Universitas Gadjah Mada (GMRT)**. Seluruh solusi diimplementasikan dalam bahasa **C++** (dan C++17 kompatibel) serta didesain untuk berjalan secara efisien.

---

## 📑 Daftar Isi
- [Problem 1: Dok Logistik Otomatis](#problem-1-dok-logistik-otomatis)
- [Problem 2: Baterai Robot & Misi](#problem-2-baterai-robot--misi)
- [Problem 3: Penelusuran Kunci Loker](#problem-3-penelusuran-kunci-loker)
- [Problem 4: Validasi Perintah Gerak Robot](#problem-4-validasi-perintah-gerak-robot)
- [Cara Menjalankan Kode](#cara-menjalankan-kode)

---

## 🚚 Problem 1: Dok Logistik Otomatis

### 📌 Deskripsi Singkat
Sebuah robot ditugaskan untuk menyeimbangkan barang di antara 3 kotak penyimpanan:
* **Kotak 1**: $n$ barang berbobot $2	ext{ kg}$
* **Kotak 2**: $m$ barang berbobot $1	ext{ kg}$
* **Kotak 3**: Kosong ($0$ barang, $0	ext{ kg}$)
* **Kapasitas Robot**: Maksimal $k	ext{ kg}$ per angkut, dan hanya boleh membawa satu jenis barang dalam satu kali jalan.

Setiap aksi **memuat** (mengambil dari kotak) atau **membongkar** (meletakkan ke kotak) dihitung sebagai **1 langkah**. Tujuan akhir adalah membuat ketiga kotak memiliki **jumlah barang yang sama** dan **total berat yang sama persis**.

### 💡 Analisis & Logika Penyelesaian
1. **Target Kondisi Akhir**:
   - Total barang = $n + m$
   - Total berat = $2n + m$
   - Agar seimbang di 3 kotak, maka $(n + m)$ dan $(2n + m)$ **harus habis dibagi 3**. Jika tidak, cetak `-1`.
   - Di kondisi akhir, setiap kotak harus berisi $T_{\text{barang}} = \frac{n + m}{3}$ barang dan total $T_{\text{berat}} = \frac{2n + m}{3}	ext{ kg}$.

2. **Formulasi Jumlah Barang per Kotak**:
   Misal $a$ adalah jumlah barang $2	ext{ kg}$ per kotak dan $b$ adalah jumlah barang $1	ext{ kg}$ per kotak:
   $$\begin{cases} a + b = T_{\text{barang}} \\ 2a + b = T_{\text{berat}} \end{cases}$$
   Dari sistem persamaan linear di atas, kita dapatkan:
   $$a = T_{\text{berat}} - T_{\text{barang}} = \frac{n - m}{3}$$
   $$b = T_{\text{barang}} - a = \frac{2m - n}{3}$$
   * **Syarat Keberhasilan**: $a \ge 0$ dan $b \ge 0$. Jika $a < 0$ atau $b < 0$, konfigurasi seimbang tidak mungkin dicapai dengan komposisi barang yang ada ($\rightarrow \text{output } -1$).

3. **Perhitungan Langkah Minimum**:
   - Barang $2	ext{ kg}$ yang harus dipindahkan keluar dari Kotak 1: $n - a$.
   - Barang $1	ext{ kg}$ yang harus dipindahkan keluar dari Kotak 2: $m - b$.
   - Setiap 1 unit barang yang dipindah membutuhkan **2 langkah** (1 kali ambil dari kotak asal + 1 kali letak ke kotak tujuan).
   - Total langkah minimum = $2 \times ((n - a) + (m - b))$.

---

## 🔋 Problem 2: Baterai Robot & Misi

### 📌 Deskripsi Singkat
Robot harus menjalankan $n$ misi secara berurutan. Baterai awal penuh ($C$ energi). Sebelum setiap misi, robot dapat memilih untuk melakukan *charging* (menambah $R$ energi, tidak melebihi $C$) dengan batasan maksimal $K$ kali *charging* sepanjang seluruh misi. Tentukan jumlah **maksimum misi berurutan** yang dapat diselesaikan.

### 💡 Analisis & Logika Penyelesaian
Masalah ini diselesaikan menggunakan pendekatan **Dynamic Programming (DP)**:
- **State DP**: `dp[k]` menyimpan **energi baterai maksimum** yang tersisa setelah menyelesaikan misi saat ini dengan total telah melakukan $k$ kali *charging* ($0 \le k \le K$).
- **Inisialisasi**: `dp[0] = C`, sisanya `-1` (berarti state belum tercapai).
- **Transisi State** pada setiap misi $i$ dengan kebutuhan energi $x_i$:
  1. **Tanpa Charge**: Jika `dp[k]` $\ge x_i$, energi menjadi `dp[k] - x_i`.
  2. **Dengan Charge**: Jika $k > 0$ dan `dp[k-1]` valid, energi setelah isi ulang menjadi $\min(C, \text{dp}[k-1] + R)$. Jika energi ini $\ge x_i$, maka nilai `next_dp[k]` diupdate dengan $\max(\dots, \text{energi} - x_i)$.
- Iterasi terhenti jika tidak ada state valid yang dapat menyelesaikan misi ke-$i$.

---

## 🔑 Problem 3: Penelusuran Kunci Loker

### 📌 Deskripsi Singkat
Terdapat 8 loker (nomor 1–8). Anda dibekali **1 kunci master** di awal yang bebas digunakan untuk membuka 1 loker mana saja. Di dalam tiap loker terdapat nomor kunci loker lain (atau `0` jika kosong). Kunci yang didapat wajib langsung digunakan untuk membuka loker berikutnya. Tentukan apakah seluruh 8 loker dapat dibuka.

### 💡 Analisis & Logika Penyelesaian
- Kasus ini direpresentasikan sebagai **Directed Graph / Permutasi Terarah** dengan *out-degree* maksimal 1.
- Untuk membuka **seluruh 8 loker**, seluruh elemen harus membentuk **satu siklus tunggal (single cycle)** sepanjang 8 simpul.
- **Strategi**: Cobalah setiap loker (dari 1 hingga 8) sebagai titik awal penggunaan kunci master. Lakukan simulasi penelusuran (*traversal*). Jika ada set setidaknya satu titik awal yang berhasil membuka 8 loker secara berurutan tanpa terputus/perulang sebelum mencapai 8 loker, maka hasilnya **YES**. Jika tidak ada, cetak **NO**.

---

## 🤖 Problem 4: Validasi Perintah Gerak Robot

### 📌 Deskripsi Singkat
Diberikan sebuah string yang terdiri dari karakter `(` (robot masuk ruangan) dan `)` (robot keluar ruangan). Tentukan apakah urutan perintah valid dengan syarat:
1. Setiap `)` memiliki `(` pendahulu yang sesuai.
2. Robot tidak boleh keluar ruangan saat sedang berada di luar (tidak dalam ruangan).
3. Di akhir rangkaian, robot kembali ke kondisi awal (jumlah `(` dan `)` seimbang).

### 💡 Analisis & Logika Penyelesaian
Menggunakan algoritma **Balance Counter** / **Stack**:
- Inisialisasi variabel `balance = 0`.
- Iterasi setiap karakter dari kiri ke kanan:
  - Karakter `(` $\rightarrow$ `balance++`
  - Karakter `)` $\rightarrow$ `balance--`
  - Jika pada titik mana pun `balance < 0`, artinya robot mencoba keluar padahal sedang tidak di dalam ruangan $\rightarrow$ **Validasi Gagal (NO)**.
- Setelah seluruh karakter diproses, jika `balance == 0` maka **YES**, selain itu **NO**.

---

## 🛠️ Cara Menjalankan Kode

### Kompilasi & Eksekusi (GCC / Clang)

```bash
# Kompilasi Problem 1
g++ -O2 problem1.cpp -o problem1
./problem1

# Kompilasi Problem 2
g++ -O2 problem2.cpp -o problem2
./problem2

# Kompilasi Problem 3
g++ -O2 problem3.cpp -o problem3
./problem3

# Kompilasi Problem 4
g++ -O2 problem4.cpp -o problem4
./problem4
```

---
*Dibuat untuk Tugas Seleksi Magang GMRT - Universitas Gadjah Mada.*
