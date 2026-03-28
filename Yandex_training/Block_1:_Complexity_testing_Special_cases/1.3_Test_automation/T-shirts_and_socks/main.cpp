#include <iostream>
#include <fstream>
#include <cstdint>

using namespace std;

pair<int64_t, int64_t> solve(
    const int32_t& a, const int32_t& b, const int32_t& c, const int32_t& d) {
    if ((a == 0 && c == 0) || (b == 0 && d == 0)) {
        return {1, 1};
    }

    if (a == 0) {
        return {1, c + 1};
    }
    if (b == 0) {
        return {1, d + 1};
    }
    if (c == 0) {
        return {a + 1, 1};
    }
    if (d == 0) {
        return {b + 1, 1};
    }

    if (a == b) {
        return {a + 1, 1};
    }

    if (c == d) {
        return {1, c + 1};
    }

    int32_t m_min = min(a, b) + 1;
    int32_t n_min = min(c, d) + 1;
    int32_t m_max = max(a, b) + 1;
    int32_t n_max = max(c, d) + 1;
    if (((n_min + m_min) <= (m_max + 1)) && ((n_min + m_min) <= (n_max + 1))) {
        return {m_min, n_min};
    }
    if (((n_min + m_min) > (m_max + 1)) && ((n_min + m_min) <= (n_max + 1))) {
        return {m_max, 1};
    }
    if (((n_min + m_min) <= (m_max + 1)) && ((n_min + m_min) > (n_max + 1))) {
        return {1, n_max};
    }
    if (((n_min + m_min) > (m_max + 1)) && ((n_min + m_min) > (n_max + 1))) {
        if ((m_max + 1) >= (n_max + 1)) {
            return {1, n_max};
        } else {
            return {m_max, 1};
        }
    }
    return {-1, -1};
}

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");

    int32_t a = 0;
    int32_t b = 0;
    int32_t c = 0;
    int32_t d = 0;

    int32_t n = 0;
    in >> n;

    for (int32_t i = 0; i < n; ++i) {
        in >> a >> b >> c >> d;
        auto result = solve(a, b, c, d);
        out << result.first << ' ' << result.second << '\n';
    }

    // in >> a >> b >> c >> d;
    // auto result = solve(a, b, c, d);
    // out << result.first << ' ' << result.second << '\n';

    return 0;
}
