#include <fstream>
#include <cstdint>
#include <algorithm>

using namespace std;

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");

    int64_t n = 0;
    int64_t m = 0;
    int64_t h = 0;
    int64_t w = 0;
    in >> n >> m >> h >> w;

    int64_t h1 = h;
    int64_t w1 = w;
    int32_t count_nh = 0;
    int32_t count_mw = 0;

    while (n > h1) {
        ++count_nh;
        h1 = h1 << 1;
    }

    while (m > w1) {
        ++count_mw;
        w1 = w1 << 1;
    }

    int64_t var1 = count_nh + count_mw;

    h1 = h;
    w1 = w;
    int32_t count_nw = 0;
    int32_t count_mh = 0;

    while (n > w1) {
        ++count_nw;
        w1 = w1 << 1;
    }

    while (m > h1) {
        ++count_mh;
        h1 = h1 << 1;
    }

    int64_t var2 = count_nw + count_mh;

    out << min(var1, var2) << '\n';

    in.close();
    out.close();
    return 0;
}
