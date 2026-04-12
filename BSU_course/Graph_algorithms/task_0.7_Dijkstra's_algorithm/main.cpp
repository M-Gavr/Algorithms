#include <cstdint>
#include <fstream>
#include <limits>
#include <queue>
#include <vector>

using namespace std;

constexpr int64_t kInf = numeric_limits<int64_t>::max() / 4;

vector<int64_t> dijkstra(const vector<vector<pair<int32_t, int32_t>>>& g, const int32_t start) {
    const int32_t n = static_cast<int32_t>(g.size());
    vector<int64_t> dist(n, kInf);
    dist[start] = 0;

    using P = pair<int64_t, int32_t>;
    priority_queue<P, vector<P>, greater<>> pq;

    pq.emplace(0, start);

    while (!pq.empty()) {
        const int64_t current_dist = pq.top().first;
        const int32_t v = pq.top().second;
        pq.pop();

        if (current_dist > dist[v]) {
            continue;
        }

        for (const auto& [neighbour, w] : g[v]) {
            const int32_t to = neighbour;
            const int64_t nd = dist[v] + static_cast<int64_t>(w);

            if (nd < dist[to]) {
                dist[to] = nd;
                pq.emplace(dist[to], to);
            }
        }
    }

    return dist;
}

int main() {
    std::ifstream in("input.txt");
    std::ofstream out("output.txt");

    int32_t n = 0;
    int32_t m = 0;
    in >> n >> m;

    vector<vector<pair<int32_t, int32_t>>> g(n);

    int32_t u = 0;
    int32_t v = 0;
    int32_t w = 0;
    for (int32_t i = 0; i < m; ++i) {
        in >> u >> v >> w;
        u--; v--;
        g[u].emplace_back(v, w);
        g[v].emplace_back(u, w);
    }

    vector<int64_t> dist = dijkstra(g, 0);

    out << dist[n - 1];

    // for (int32_t i = 1; i <= n; ++i) {
    //     out << g[i].size();
    //
    //     for (auto [v, w] : g[i]) {
    //         out << ' ' << v << ' ' << w << '\n';
    //     }
    //     out << "\n";
    // }

    in.close();
    out.close();
    return 0;
}
