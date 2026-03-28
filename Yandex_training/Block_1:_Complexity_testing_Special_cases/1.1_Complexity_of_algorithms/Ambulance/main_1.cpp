#include <iostream>
#include <cstdint>
#include <set>

using namespace std;

int main() {
    int32_t k1 = 0;
    int32_t m = 0;
    int32_t k2 = 0;
    int32_t p2 = 0;
    int32_t n2 = 0;
    cin >> k1 >> m >> k2 >> p2 >> n2;

    if (n2 > m) {
        cout << "-1 -1\n";
        return 0;
    }

    int64_t const fl_before = ((p2 - 1) * m) + (n2 - 1);

    if (fl_before == 0) {
        if (k1 <= k2) {
            cout << "1 1\n";
        } else if (m == 1) {
            cout << "0 1\n";
        } else {
            cout << "0 0\n";
        }
        return 0;
    }

    int64_t const max_x = (k2 - 1) / fl_before;
    int64_t const min_x = (k2 + fl_before) / (fl_before + 1);

    if (min_x > max_x) {
        cout << "-1 -1\n";
        return 0;
    }

    set<int64_t> possible_p1;
    set<int64_t> possible_n1;

    int64_t iterations = 0;
    constexpr int64_t kMaxIterations = 2000000;

    for (int64_t x = min_x; x <= max_x && iterations < kMaxIterations; ++x, ++iterations) {
        int64_t const floors_before_k1 = (k1 - 1) / x;
        int64_t const p1 = (floors_before_k1 / m) + 1;
        int64_t const n1 = (floors_before_k1 % m) + 1;

        possible_p1.insert(p1);
        possible_n1.insert(n1);

        if (possible_p1.size() > 1 && possible_n1.size() > 1) {
            break;
        }
    }

    int64_t const p1_result = (possible_p1.size() == 1) ? *possible_p1.begin() : 0;
    int64_t n1_result = (possible_n1.size() == 1) ? *possible_n1.begin() : 0;

    if (p1_result == 0) {
        n1_result = 0;
    }

    cout << p1_result << " " << n1_result << "\n";
    return 0;
}
