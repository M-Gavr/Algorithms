#include <bits/stdc++.h>
using namespace std;
using i32 = int32_t;
using u64 = uint64_t;

inline void sb(vector<u64>& b, i32 p) {
    b[p >> 6] |= 1ULL << (p & 63);
}

inline bool gb(const vector<u64>& b, i32 p) {
    return (b[p >> 6] >> (p & 63)) & 1ULL;
}

bool vis(i32 r1, i32 c1, i32 r2, i32 c2, const vector<string>& a) {
    i32 r = r1, c = c1, dr = r2 - r1, dc = c2 - c1, sr = 0, sc = 0;
    if (!dr && !dc)
        return 1;
    const long double INF = 1e100L, EPS = 1e-15L;
    long double tr = INF, tc = INF, dtr = INF, dtc = INF;
    if (dr > 0)
        sr = 1, dtr = 1.0L / dr, tr = 0.5L * dtr;
    else
        if (dr < 0)
            sr = -1, dtr = 1.0L / (-dr), tr = 0.5L * dtr;
    if (dc > 0)
        sc = 1, dtc = 1.0L / dc, tc = 0.5L * dtc;
    else
        if (dc < 0)
            sc = -1, dtc = 1.0L / (-dc), tc = 0.5L * dtc;
    while (r != r2 || c != c2) {
        if (fabsl(tr - tc) <= EPS)
            r += sr, c += sc, tr += dtr, tc += dtc;
        else if (tr < tc)
            r += sr, tr += dtr;
        else
            c += sc, tc += dtc;
        if (a[r][c] == '0')
            return 0;
    }
    return 1;
}

int main() {
    if (FILE* f = freopen("../input.txt", "r", stdin))
        (void)f;
    if (FILE* f = freopen("../output.txt", "w", stdout))
        (void)f;
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    i32 n, m, k;
    if (!(cin >> n >> m >> k))
        return 0;
    vector<string> a(n);
    for (auto& s : a)
        cin >> s;

    vector<pair<i32, i32>> p;
    vector<vector<i32>> id(n, vector<i32>(m, -1));
    for (i32 i = 0; i < n; ++i)
        for (i32 j = 0; j < m; ++j)
            if (a[i][j] != '0') {
                id[i][j] = (i32)p.size();
                p.push_back({i, j});
            }

    i32 v = (i32)p.size(), W = (v + 63) >> 6;
    vector<vector<u64>> g(v, vector<u64>(W));
    for (i32 i = 0; i < v; ++i)
        sb(g[i], i);
    for (i32 i = 0; i < v; ++i)
        for (i32 j = i + 1; j < v; ++j)
            if (vis(p[i].first, p[i].second, p[j].first, p[j].second, a))
                sb(g[i], j), sb(g[j], i);

    auto bfs = [&](i32 s, i32 t) -> i32 {
        if (s == t)
            return 0;
        vector<u64> unv(W, ~0ULL), fr(W), nx(W);
        if (v & 63)
            unv.back() = (1ULL << (v & 63)) - 1;
        sb(fr, s), unv[s >> 6] &= ~(1ULL << (s & 63));
        for (i32 d = 0;; ++d) {
            if (gb(fr, t))
                return d;
            fill(nx.begin(), nx.end(), 0ULL);
            for (i32 w = 0; w < W; ++w) {
                u64 msk = fr[w];
                while (msk) {
                    i32 b = (i32)__builtin_ctzll(msk), u = (w << 6) + b;
                    if (u < v)
                        for (i32 ww = 0; ww < W; ++ww)
                            nx[ww] |= g[u][ww];
                    msk &= msk - 1;
                }
            }
            bool ok = 0;
            for (i32 ww = 0; ww < W; ++ww) {
                nx[ww] &= unv[ww];
                if (nx[ww])
                    ok = 1;
            }
            if (!ok)
                return -1;
            for (i32 ww = 0; ww < W; ++ww)
                unv[ww] &= ~nx[ww];
            fr.swap(nx);
        }
    };

    while (k--) {
        i32 x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        --x1, --y1, --x2, --y2;
        cout << bfs(id[x1][y1], id[x2][y2]) << '\n';
    }
}