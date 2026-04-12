#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <limits>
#include <queue>
#include <vector>

using namespace std;

struct Edge {
    int32_t to;
    size_t rev;
    int64_t cap;
};

void add_edge(vector<vector<Edge>>& g, const int32_t from, const int32_t to, const int64_t cap) {
    const Edge a{.to = to, .rev = g[to].size(), .cap = cap};
    const Edge b{.to = from, .rev = g[from].size(), .cap = 0};
    g[from].push_back(a);
    g[to].push_back(b);
}

int64_t dinic_dfs(
    vector<vector<Edge>>& g, vector<size_t>& ptr, vector<int32_t>& level, const int32_t v,
    const int32_t t, const int64_t pushed) {
    if (pushed == 0 || v == t) {
        return pushed;
    }
    for (size_t& cid = ptr[v]; cid < g[v].size(); ++cid) {
        Edge& e = g[v][cid];
        if (e.cap > 0 && level[e.to] == level[v] + 1) {
            const int64_t tr = dinic_dfs(g, ptr, level, e.to, t, min(pushed, e.cap));
            if (tr == 0) {
                continue;
            }
            e.cap -= tr;
            g[e.to][e.rev].cap += tr;
            return tr;
        }
    }
    return 0;
}

int64_t dinic(vector<vector<Edge>>& g, const int32_t s, const int32_t t) {
    int64_t max_flow = 0;
    vector<int32_t> level(g.size());
    vector<size_t> ptr(g.size());

    constexpr int64_t kInfFlow = numeric_limits<int64_t>::max() / 2;

    while (true) {
        fill(level.begin(), level.end(), -1);
        level[s] = 0;
        queue<int32_t> q;
        q.push(s);
        while (!q.empty()) {
            const int32_t v = q.front();
            q.pop();
            for (const Edge& e : g[v]) {
                if (e.cap > 0 && level[e.to] < 0) {
                    level[e.to] = level[v] + 1;
                    q.push(e.to);
                }
            }
        }
        if (level[t] < 0) {
            break;
        }
        fill(ptr.begin(), ptr.end(), 0);
        while (const int64_t pushed = dinic_dfs(g, ptr, level, s, t, kInfFlow)) {
            max_flow += pushed;
        }
    }
    return max_flow;
}

int main() {
    // std::ifstream in("input.txt");
    // std::ofstream out("output.txt");

    int32_t n = 0;
    int32_t m = 0;
    cin >> n >> m;

    vector<vector<Edge>> g(n);

    for (int32_t i = 0; i < m; ++i) {
        int32_t u = 0;
        int32_t v = 0;
        int64_t c = 0;
        cin >> u >> v >> c;
        u--;
        v--;
        add_edge(g, u, v, c);
    }

    const int32_t s = 0;
    const int32_t t = n - 1;
    cout << dinic(g, s, t);

    // in.close();
    // out.close();
    return 0;
}
