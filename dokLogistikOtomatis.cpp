#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    long long k, n, m;
    if (!(cin >> k >> n >> m)) return 0;

    if (n == 0 && m == 0) {
        cout << 0 << "\n";
        return 0;
    }

    // Cek syarat keterbagian
    if ((n + m) % 3 != 0 || (2 * n + m) % 3 != 0) {
        cout << -1 << "\n";
        return 0;
    }

    // Hitung target barang per kotak
    long long a = (n - m) / 3;     // barang 2kg per kotak
    long long b = (2 * m - n) / 3; // barang 1kg per kotak

    // Konfigurasi tidak valid jika bernilai negatif
    if (a < 0 || b < 0) {
        cout << -1 << "\n";
        return 0;
    }

    // Pemindahan barang
    long long pindah_2kg = n - a;
    long long pindah_1kg = m - b;

    // 1 pemindahan = 1 ambil + 1 letak (2 langkah)
    long long total_langkah = 2 * (pindah_2kg + pindah_1kg);
    cout << total_langkah << "\n";

    return 0;
}
