#include <algorithm>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    int32_t n = 0;
    string s;
    cin >> n >> s;

    const string toi = "TOI";
    vector<vector<int32_t>> dp(n, vector<int32_t>(n, 0));

    for (int32_t len = 1; len <= n; ++len) {
        for (int32_t l = 0; l + len - 1 < n; ++l) {
            const int32_t r = l + len - 1;
            int32_t best = INT32_MAX / 2;

            best = min(best, 1 + (l + 1 <= r ? dp[l + 1][r] : 0));
            best = min(best, 1 + (l <= r - 1 ? dp[l][r - 1] : 0));

            for (const char c : toi) {
                const int32_t cost_left = (s[l] == c ? 0 : 1);
                const int32_t cost_right = (s[r] == c ? 0 : 1);
                const int32_t mid_cost = (l + 1 <= r - 1 ? dp[l + 1][r - 1] : 0);
                best = min(best, cost_left + cost_right + mid_cost);
            }

            dp[l][r] = best;
        }
    }

    cout << dp[0][n - 1] << '\n';

    return 0;
}