#include <vector>
#include <iostream>

using namespace std;

constexpr int MOD = 1e9 + 7;

int main() {
    int32_t n = 0;
    int32_t m = 0;
    cin >> n >> m;

    if (n == 0 || m == 0) {
        cout << 0 << endl;
        return 0;
    }

    vector<int32_t> prev(m , 1);
    vector<int32_t> cur(m, 1);

    for (int32_t i = 1; i < n; i++) {
        // for (int32_t j = 0; j < m; j++) {
        //     cout << prev[j] << ' ';
        // }
        // cout << endl;

        for (int32_t j = 1; j < m; j++) {
            cur[j] = ((cur[j - 1] + prev[j]) % MOD + prev[j - 1]) % MOD;
        }

        prev = cur;

        for (int32_t j = 0; j < m; j++) {
            cur[j] = 1;
        }
    }

    // for (int32_t j = 0; j < m; j++) {
    //     cout << prev[j] << ' ';
    // }
    // cout << endl;

    cout << prev[m - 1] << endl;

    return 0;
}
