#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, K;
    long long C, R;
    if (!(cin >> n >> C >> R >> K)) return 0;

    vector<long long> x(n);
    for (int i = 0; i < n; ++i) {
        cin >> x[i];
    }

    // dp[k] menyimpan energi maksimum untuk k kali charge
    vector<long long> dp(K + 1, -1);
    dp[0] = C;

    int max_misi = 0;

    for (int i = 0; i < n; ++i) {
        long long req = x[i];
        vector<long long> next_dp(K + 1, -1);
        bool possible = false;

        for (int k = 0; k <= K; ++k) {
            // Opsi 1: Tanpa charge sebelum misi i
            if (dp[k] >= req) {
                next_dp[k] = max(next_dp[k], dp[k] - req);
                possible = true;
            }

            // Opsi 2: Charge sebelum misi i (butuh k > 0)
            if (k > 0 && dp[k - 1] != -1) {
                long long energy_after_charge = min(C, dp[k - 1] + R);
                if (energy_after_charge >= req) {
                    next_dp[k] = max(next_dp[k], energy_after_charge - req);
                    possible = true;
                }
            }
        }

        if (!possible) {
            break;
        }

        dp = next_dp;
        max_misi = i + 1;
    }

    cout << max_misi << "\n";

    return 0;
}
