#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {

    int32_t n = 0;
    cin >> n;
    vector<int64_t> p(n);
    for (int32_t i = 0; i < n; i++) {
        cin >> p[i];
    }

    if (n < 2) {
        cout << 0 << '\n';
        return 0;
    }

    vector<int64_t> left(n, 0);
    int64_t min_price = p[0];
    for (int32_t i = 1; i < n; i++) {
        left[i] = max(left[i-1], p[i] - min_price);
        min_price = min(min_price, p[i]);
    }

    vector<int64_t> right(n, 0);
    int64_t max_price = p[n-1];
    for (int32_t i = n-2; i >= 0; i--) {
        right[i] = max(right[i+1], max_price - p[i]);
        max_price = max(max_price, p[i]);
    }

    int64_t ans = left[n-1];
    for (int32_t i = 0; i < n-1; i++) {
        ans = max(ans, left[i] + right[i+1]);
    }

    cout << ans << '\n';

    return 0;
}