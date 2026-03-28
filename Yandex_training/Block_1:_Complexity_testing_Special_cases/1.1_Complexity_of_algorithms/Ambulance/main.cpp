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

    set<int32_t> possible_p1;
    set<int32_t> possible_n1;

    constexpr int32_t MAX_X = 2000000;

    for (int32_t x = 1; x <= MAX_X; ++x) {
        const int32_t floors_before_k2 = (k2 - 1) / x;
        const int32_t p2_calc = floors_before_k2 / m + 1;
        int32_t n2_calc = floors_before_k2 % m + 1;

        if (p2_calc == p2 && n2_calc == n2) {
            const int32_t floors_before_k1 = (k1 - 1) / x;
            int32_t p1 = floors_before_k1 / m + 1;
            int32_t n1 = floors_before_k1 % m + 1;

            possible_p1.insert(p1);
            possible_n1.insert(n1);
        }
    }

    if (possible_p1.empty()) {
        cout << "-1 -1\n";
        return 0;
    }

    const int32_t p1_result = (possible_p1.size() == 1) ? *possible_p1.begin() : 0;
    const int32_t n1_result = (possible_n1.size() == 1) ? *possible_n1.begin() : 0;

    cout << p1_result << " " << n1_result << "\n";
    return 0;
}
