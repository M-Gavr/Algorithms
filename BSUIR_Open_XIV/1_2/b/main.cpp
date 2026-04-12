#include <bits/stdc++.h>
using namespace std;

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    const int32_t N = 5000, INF = 1e9;
    int32_t q; cin >> q;
    vector<char> on(N + 1);
    vector<unordered_set<int32_t>> g(N + 1), rg(N + 1);
    vector<int32_t> L(N + 1), R(N + 1), d(N + 1);

    auto ans = [&]() -> int32_t {
        fill(L.begin(), L.end(), 0);
        fill(R.begin(), R.end(), 0);
        int32_t cnt = 0; for (int32_t i = 1; i <= N; ++i) cnt += on[i];
        if (!cnt) return 0;

        auto bfs = [&]() {
            queue<int32_t> qu; bool ok = false;
            for (int32_t u = 1; u <= N; ++u) if (on[u]) {
                if (!L[u]) d[u] = 0, qu.push(u); else d[u] = INF;
            }
            while (!qu.empty()) {
                int32_t u = qu.front(); qu.pop();
                for (int32_t v : g[u]) if (on[v]) {
                    int32_t pu = R[v];
                    if (!pu) ok = true;
                    else if (d[pu] == INF) d[pu] = d[u] + 1, qu.push(pu);
                }
            }
            return ok;
        };

        function<bool(int32_t)> dfs = [&](int32_t u) {
            for (int32_t v : g[u]) if (on[v]) {
                int32_t pu = R[v];
                if (!pu || (d[pu] == d[u] + 1 && dfs(pu))) return L[u] = v, R[v] = u, true;
            }
            return d[u] = INF, false;
        };

        int32_t m = 0;
        while (bfs()) for (int32_t u = 1; u <= N; ++u) if (on[u] && !L[u] && dfs(u)) ++m;
        return cnt - m;
    };

    while (q--) {
        int32_t t, u, v; cin >> t >> u;
        if (t == 1) on[u] = 1;
        else if (t == 2) {
            on[u] = 0;
            for (int32_t x : g[u]) rg[x].erase(u);
            for (int32_t x : rg[u]) g[x].erase(u);
            g[u].clear(); rg[u].clear();
        } else {
            cin >> v;
            if (t == 3) g[u].insert(v), rg[v].insert(u);
            else g[u].erase(v), rg[v].erase(u);
        }
        cout << ans() << '\n';
    }
}
