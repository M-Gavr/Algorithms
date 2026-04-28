#include <algorithm>
#include <cstdint>
#include <iostream>
#include <limits>
#include <queue>
#include <vector>

using namespace std;

struct Candidate {
    int64_t x = 0;
    int64_t y = 0;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int32_t a = 0;
    int32_t b = 0;
    int32_t n = 0;
    cin >> a >> b >> n;

    vector<Candidate> c(n);
    for (int32_t i = 0; i < n; ++i) {
        cin >> c[i].x >> c[i].y;
    }

    sort(c.begin(), c.end(), [](const Candidate& lhs, const Candidate& rhs) {
        return (lhs.x - lhs.y) > (rhs.x - rhs.y);
    });

    const int64_t NEG_INF = numeric_limits<int64_t>::min() / 4;
    vector<int64_t> pref(n + 1, NEG_INF);
    vector<int64_t> suff(n + 1, NEG_INF);

    {
        priority_queue<int64_t, vector<int64_t>, greater<int64_t>> min_heap;
        int64_t sum = 0;
        pref[0] = (a == 0 ? 0 : NEG_INF);

        for (int32_t i = 1; i <= n; ++i) {
            const int64_t value = c[i - 1].x;
            min_heap.push(value);
            sum += value;
            if (static_cast<int32_t>(min_heap.size()) > a) {
                sum -= min_heap.top();
                min_heap.pop();
            }
            if (static_cast<int32_t>(min_heap.size()) == a) {
                pref[i] = sum;
            }
        }
    }

    {
        priority_queue<int64_t, vector<int64_t>, greater<int64_t>> min_heap;
        int64_t sum = 0;
        suff[n] = (b == 0 ? 0 : NEG_INF);

        for (int32_t i = n - 1; i >= 0; --i) {
            const int64_t value = c[i].y;
            min_heap.push(value);
            sum += value;
            if (static_cast<int32_t>(min_heap.size()) > b) {
                sum -= min_heap.top();
                min_heap.pop();
            }
            if (static_cast<int32_t>(min_heap.size()) == b) {
                suff[i] = sum;
            }
        }
    }

    int64_t ans = 0;
    for (int32_t split = 0; split <= n; ++split) {
        if (pref[split] == NEG_INF || suff[split] == NEG_INF) {
            continue;
        }
        ans = max(ans, pref[split] + suff[split]);
    }

    cout << ans << '\n';
    return 0;
}