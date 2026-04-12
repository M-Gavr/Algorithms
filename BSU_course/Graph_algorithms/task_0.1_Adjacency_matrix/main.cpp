#include <cstdint>
#include <fstream>
#include <vector>

using namespace std;

int main() {
    std::ifstream in("input.txt");
    std::ofstream out("output.txt");

    int32_t n = 0;
    int32_t m = 0;

    in >> n >> m;

    int32_t u = 0;
    int32_t v = 0;
    vector<vector<int32_t>> matrix(n + 1, vector<int32_t> (n + 1, 0));

    for (int32_t i = 0; i < m; ++i) {
        in >> u >> v;
        matrix[u][v] = 1;
        matrix[v][u] = 1;
    }

    for (int32_t i = 1; i <= n; ++i) {
        for (int32_t j = 1; j <= n; ++j) {
            out << matrix[i][j] << ' ';
        }
        out << '\n';
    }

    in.close();
    out.close();
    return 0;
}
