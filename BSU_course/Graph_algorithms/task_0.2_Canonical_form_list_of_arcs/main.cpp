#include <cstdint>
#include <fstream>
#include <vector>

using namespace std;

int main() {
    std::ifstream in("input.txt");
    std::ofstream out("output.txt");

    int32_t n = 0;
    in >> n;

    vector<int32_t> g(n + 1, 0);

    int32_t u = 0;
    int32_t v = 0;
    for (int32_t i = 0; i < n - 1; ++i) {
        in >> u >> v;
        g[v] = u;
    }

    for (int32_t i = 1; i <= n; ++i) {
        out << g[i] << ' ';
    }

    in.close();
    out.close();
    return 0;
}
