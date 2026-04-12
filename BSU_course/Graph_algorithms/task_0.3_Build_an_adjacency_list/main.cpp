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

    vector<vector<int32_t>> adj(n + 1);

    int32_t u = 0;
    int32_t v = 0;
    for (int32_t i = 0; i < m; ++i) {
        in >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    for (int32_t i = 1; i <= n; ++i) {
        out << adj[i].size();

        for (int32_t const neighbor : adj[i]) {
            out << " " << neighbor;
        }
        out << "\n";
    }

    in.close();
    out.close();
    return 0;
}
