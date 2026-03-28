#include <iostream>
#include <cstdint>

using namespace std;

int main() {
    int32_t p = 0;
    int32_t v = 0;
    int32_t q = 0;
    int32_t m = 0;
    cin >> p >> v;
    cin >> q >> m;

    int32_t result = 0;
    int32_t const v_left = p - v;
    int32_t const v_right = p + v;
    int32_t const m_left = q - m;
    int32_t const m_right = q + m;


    if (v_left > m_right || v_right < m_left) {
        result = (2 * v + 1) + (2 * m + 1);
    } else {
        result = max(v_right, m_right) - min(v_left, m_left) + 1;
    }

    cout << result << '\n';
    return 0;
}