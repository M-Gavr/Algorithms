#include <algorithm>
#include <cstdint>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int32_t n = 0;
    int64_t x = 0;
    cin >> n >> x;

    vector<int64_t> a(n);
    for (int32_t i = 0; i < n; ++i) {
        cin >> a[i];
    }

    if (n == 1) {
        cout << x << '\n';
        return 0;
    }

    vector<int64_t> ratio(n - 1, 1);
    for (int32_t i = 0; i + 1 < n; ++i) {
        ratio[i] = a[i + 1] / a[i];
    }

    vector<int64_t> digit(n, 0);
    for (int32_t i = 0; i + 1 < n; ++i) {
        digit[i] = (x / a[i]) % ratio[i];
    }
    digit[n - 1] = x / a[n - 1];

    constexpr int64_t INF = numeric_limits<int64_t>::max() / 4;
    int64_t dp_no_carry = 0;
    int64_t dp_with_carry = INF;

    for (int32_t i = 0; i + 1 < n; ++i) {
        int64_t next_no_carry = INF;
        int64_t next_with_carry = INF;

        if (dp_no_carry < INF) {
            const int64_t t = digit[i];
            next_no_carry = min(next_no_carry, dp_no_carry + t);
            next_with_carry = min(next_with_carry, dp_no_carry + (ratio[i] - t));
        }

        if (dp_with_carry < INF) {
            const int64_t t = digit[i] + 1;
            next_no_carry = min(next_no_carry, dp_with_carry + t);
            next_with_carry = min(next_with_carry, dp_with_carry + (ratio[i] - t));
        }

        dp_no_carry = next_no_carry;
        dp_with_carry = next_with_carry;
    }

    const int64_t answer = min(dp_no_carry + digit[n - 1], dp_with_carry + digit[n - 1] + 1);
    cout << answer << '\n';
    return 0;
}
