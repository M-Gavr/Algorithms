#include <algorithm>
#include <cstdint>
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;
using i32 = int32_t;

struct FenwickMax {
    i32 n = 0;
    vector<i32> bit;

    void init(const i32 size) {
        n = size;
        bit.assign(n + 1, 0);
    }

    void update(const i32 idx, const i32 val) {
        for (i32 i = idx; i <= n; i += i & (-i)) {
            if (bit[i] < val) {
                bit[i] = val;
            }
        }
    }

    i32 query(const i32 idx) const {
        i32 res = 0;
        for (i32 i = idx; i > 0; i -= i & (-i)) {
            if (res < bit[i]) {
                res = bit[i];
            }
        }
        return res;
    }
};

int32_t main() {
    // ifstream in("input.txt");
    // ofstream out("output.txt");

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    i32 t = 0;
    cin >> t;
    while (t--) {
        i32 n = 0;
        cin >> n;

        vector<pair<i32, i32>> p(n);
        vector<i32> xs;
        vector<i32> ys;
        xs.reserve(n);
        ys.reserve(n);

        for (i32 i = 0; i < n; ++i) {
            i32 x = 0;
            i32 y = 0;
            cin >> x >> y;
            p[i] = {x, y};
            xs.push_back(x);
            ys.push_back(y);
        }

        sort(xs.begin(), xs.end());
        xs.erase(unique(xs.begin(), xs.end()), xs.end());
        sort(ys.begin(), ys.end());
        ys.erase(unique(ys.begin(), ys.end()), ys.end());

        const i32 xCount = static_cast<i32>(xs.size());
        const i32 yCount = static_cast<i32>(ys.size());

        vector<vector<i32>> byY(yCount);
        byY.reserve(yCount);

        for (const auto& pt : p) {
            i32 cx = static_cast<i32>(lower_bound(xs.begin(), xs.end(), pt.first) - xs.begin());
            i32 cy = static_cast<i32>(lower_bound(ys.begin(), ys.end(), pt.second) - ys.begin());
            byY[cy].push_back(cx);
        }

        FenwickMax fw;
        fw.init(xCount);
        i32 answer = 0;

        for (const auto& row : byY) {
            vector<pair<i32, i32>> pending;
            pending.reserve(row.size());

            for (i32 cx : row) {
                i32 rev = xCount - cx;
                i32 best = fw.query(rev - 1) + 1;
                pending.push_back({rev, best});
                if (answer < best) {
                    answer = best;
                }
            }

            for (const auto& upd : pending) {
                fw.update(upd.first, upd.second);
            }
        }

        cout << answer << '\n';
    }

    // in.close();
    // out.close();
    return 0;
}