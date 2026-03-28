#include <iostream>
#include <vector>

using namespace std;

constexpr int MOD = 1e9 + 7;

int32_t bin_pow_mod(int64_t a, int32_t b, int32_t mod) {
    int64_t res = 1;
    while (b > 0) {
        if (b & 1) {
            res = (res * a) % mod;
        }
        a = (a * a) % mod;
        b >>= 1;
    }
    return static_cast<int32_t>(res);
}

int main() {
    int32_t n = 0;
    int32_t k = 0;
    cin >> n >> k;

    /*
    vector<vector<int32_t>> results(n + 1, vector<int32_t>(n + 1, 0));

    for (int32_t i = 0; i <= n; i++) {
        results[0][i] = 1;
    }

    for (int32_t i = 1; i <= k; i++) {
        for (int32_t j = i; j <= n; j++) {
            results[i][j] = (results[i][j - 1] + results[i - 1][j - 1]) % MOD;
        }
    }

    for (int32_t i = 0; i <= n; i++) {
        for (int32_t j = 0; j <= n; j++) {
            cout << results[i][j] << ' ';
        }
        cout << endl;
    }

    cout << results[k][n] << endl;
    */

    vector<int64_t> fact(n + 1);
    fact[0] = 1;
    for (int i = 1; i <= n; i++) {
        fact[i] = (fact[i-1] * i) % MOD;
        // cout << fact[i] << ' ';
    }
    // cout << endl;

    int64_t result = fact[n];
    // cout << result << endl;
    result = (result * bin_pow_mod(fact[k], MOD - 2, MOD)) % MOD;
    // cout << result << endl;
    result = (result * bin_pow_mod(fact[n-k], MOD - 2, MOD)) % MOD;

    cout << result << endl;

    return 0;
}
