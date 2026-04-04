#include <fstream>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    // ifstream in("input.txt");
    // ofstream out("output.txt");
    // in.tie(nullptr);
    // out.tie(nullptr);

    int32_t n = 0;
    cin >> n;
    vector<int32_t> numbers(n);
    for (int32_t i = 0; i < n; ++i) {
        cin >> numbers[i];
    }

    vector<pair<int32_t, int32_t>> blocks;
    int32_t start = 0;
    for (int32_t i = 0; i < n; i++) {
        if ((numbers[i] & 1) == 1) {
            if (start < i) {
                blocks.emplace_back(start, i - 1);
            }
            start = i + 1;
        }
    }
    if (start < n) {
        blocks.emplace_back(start, n - 1);
    }

    vector<int32_t> fenwick(n + 2, 0);

    auto add = [&](int32_t idx, int32_t delta) {
        idx++;
        while (idx <= n) {
            fenwick[idx] += delta;
            idx += idx & -idx;
        }
    };

    auto sum = [&](int32_t idx) {
        if (idx < 0) {
            return 0;
        }
        idx++;
        int32_t res = 0;
        while (idx > 0) {
            res += fenwick[idx];
            idx -= idx & -idx;
        }
        return res;
    };

    int64_t ans = 0;

    for (int32_t b = blocks.size() - 1; b >= 0; b--) {
        auto [l, r] = blocks[b];
        for (int32_t idx = l; idx <= r; idx++) {
            int32_t val = numbers[idx];
            if (val > 0) {
                ans += sum(val - 1);
            }
        }
        for (int32_t idx = l; idx <= r; idx++) {
            add(numbers[idx], 1);
        }
    }

    cout << ans << '\n';

    // in.close();
    // out.close();

    return 0;
}