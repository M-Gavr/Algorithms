#include <cstdint>
#include <fstream>
#include <vector>

using namespace std;

int main() {
    std::ifstream in("input.txt");
    std::ofstream out("output.txt");

    int32_t n = 0;
    in >> n;

    vector<int32_t> g(n + 1);

    int16_t w = 0;
    for (int32_t u = 1; u <= n; ++u) {
        for (int32_t v = 1; v <= n; ++v) {
            in >> w;
            if (w == 1) {
                g[v] = u;
            }
        }
    }

    for (int32_t i = 1; i <= n; ++i) {
        out << g[i] << ' ';
    }
    out << '\n';

    in.close();
    out.close();
    return 0;
}
