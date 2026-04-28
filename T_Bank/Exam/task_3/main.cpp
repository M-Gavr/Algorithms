#include <iostream>
#include <cstdint>

using namespace std;

constexpr int32_t MOD = 1e9 + 7;

int64_t mod_pow(int64_t base, int64_t exp, const int64_t mod) {
    int64_t result = 1;
    while (exp > 0) {
        if (exp & 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp >>= 1;
    }
    return result;
}

int main() {
    int64_t n = 0;
    int64_t m = 0;
    cin >> n >> m;

    if (m == 1) {
        cout << 0 << '\n';
        return 0;
    }

    const int64_t first = m * (m - 1) % MOD;
    int64_t step = ((m * m) % MOD - 3*m + 3) % MOD;
    step = (step + MOD) % MOD;

    const int64_t ans = first * mod_pow(step, n - 1, MOD) % MOD;

    cout << ans << '\n';

    return 0;
}