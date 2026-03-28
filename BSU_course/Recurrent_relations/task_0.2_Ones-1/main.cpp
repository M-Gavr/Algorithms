#include <iostream>
#include <vector>

using namespace std;

constexpr int MOD = 1e9 + 7;

int main() {
    int32_t n = 0;
    int32_t k = 0;
    cin >> n >> k;

    vector<vector<int32_t>> results(k + 1, vector<int32_t>(n + 1, 0));

    for (int32_t i = 0; i <= n; i++) {
        results[0][i] = 1;
    }

    for (int32_t i = 1; i <= k; i++) {
        for (int32_t j = 1; j <= n; j++) {
            results[i][j] = (results[i][j - 1] + results[i - 1][j - 1]) % MOD;
        }
    }

    /*
    for (int32_t i = 0; i <= k; i++) {
        for (int32_t j = 0; j <= n; j++) {
            cout << results[i][j] << ' ';
        }
        cout << endl;
    }
    */

    cout << results[k][n] << endl;
    return 0;
}
