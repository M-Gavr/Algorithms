#include <algorithm>
#include <cmath>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

struct Point {
    int32_t x;
    int32_t y;
    int32_t z;
};

static inline long double dist(const Point& a, const Point& b) {
    const long double dx = static_cast<long double>(a.x) - static_cast<long double>(b.x);
    const long double dy = static_cast<long double>(a.y) - static_cast<long double>(b.y);
    const long double dz = static_cast<long double>(a.z) - static_cast<long double>(b.z);
    return std::sqrt((dx * dx) + (dy * dy) + (dz * dz));
}

int32_t main() {
    // ifstream in("input.txt");
    // ofstream out("output.txt");

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int32_t t = 0;
    cin >> t;

    while (t--) {
        int32_t n = 0;
        cin >> n;

        vector<Point> p(n);
        for (int32_t i = 0; i < n; ++i) {
            cin >> p[i].x >> p[i].y >> p[i].z;
        }

        vector<long double> dis_1(n, 0.0L);
        for (int32_t i = 1; i < n; ++i) {
            dis_1[i] = dist(p[0], p[i]);
        }

        long double ans = 1e300L;
        for (int32_t i = 1; i < n; ++i) {
            for (int32_t j = i + 1; j < n; ++j) {
                const long double dij = dist(p[i], p[j]);
                const long double cur = (dis_1[i] + dis_1[j] + dij) * 0.5L;
                ans = std::min(cur, ans);
            }
        }

        cout << fixed << setprecision(10) << ans << '\n';
    }

    // in.close();
    // out.close();
    return 0;
}