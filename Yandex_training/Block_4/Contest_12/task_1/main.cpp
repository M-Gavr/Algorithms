#include <cstdint>
#include <fstream>
#include <vector>

using namespace std;

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");

    int32_t n = 0;
    in >> n;
    vector<int32_t> v(n, 0);
    for (int32_t i = 0; i < n; ++i) {
        in >> v[i];
    }

    int32_t lo = -1;
    int32_t hi = -1;
    for (int32_t i = 0; i < n;) {
        int32_t j = i;
        while (j + 1 < n && v[j + 1] == v[i]) {
            ++j;
        }
        if (j - i + 1 >= 3) {
            lo = i;
            hi = j;
            break;
        }
        i = j + 1;
    }

    int32_t ans = 0;
    if (lo >= 0) {
        ans += hi - lo + 1;
        v.erase(v.begin() + lo, v.begin() + hi + 1);
        int32_t cur_n = n - (hi - lo + 1);
        int32_t pos = lo;
        while (pos > 0 && pos < cur_n && v[pos - 1] == v[pos]) {
            const int32_t c = v[pos - 1];
            int32_t i_left = pos - 1;
            while (i_left > 0 && v[i_left - 1] == c) {
                --i_left;
            }
            int32_t i_right = pos;
            while (i_right + 1 < cur_n && v[i_right + 1] == c) {
                ++i_right;
            }
            const int32_t len = i_right - i_left + 1;
            if (len < 3) {
                break;
            }
            ans += len;
            v.erase(v.begin() + i_left, v.begin() + i_right + 1);
            cur_n -= len;
            pos = i_left;
        }
    }

    out << ans << '\n';

    in.close();
    out.close();
    return 0;
}
