#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    vector<int> A(8);
    for (int i = 0; i < 8; ++i) {
        if (!(cin >> A[i])) return 0;
    }

    // Mencoba setiap loker sebagai titik awal kunci master
    for (int start_locker = 1; start_locker <= 8; ++start_locker) {
        vector<bool> visited(9, false);
        int count = 0;
        int current = start_locker;

        while (current != 0 && !visited[current]) {
            visited[current] = true;
            count++;
            current = A[current - 1]; // Pindah ke loker sesuai kunci yang didapat
        }

        if (count == 8) {
            cout << "YES\n";
            return 0;
        }
    }

    cout << "NO\n";

    return 0;
}
