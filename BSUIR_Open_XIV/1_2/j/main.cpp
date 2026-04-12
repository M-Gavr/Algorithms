#include <bits/stdc++.h>
using namespace std;

static const int64_t MOD = 1000000007LL;
static const int64_t INV2 = (MOD + 1) / 2;

static inline int64_t mul(int64_t a, int64_t b) { return (a * b) % MOD; }
static inline int64_t norm(int64_t x) { x %= MOD; return x < 0 ? x + MOD : x; }

struct Node {
    int64_t s1 = 0;
    int64_t s2 = 0;
    int32_t len = 0;
    bool flip = false;
};

class SegTree {
public:
    explicit SegTree(const vector<int64_t>& a) {
        n_ = static_cast<int32_t>(a.size()) - 1;
        t_.assign(4 * n_ + 5, Node{});
        build(1, 1, n_, a);
    }

    pair<int64_t, int64_t> query(int32_t l, int32_t r) {
        auto res = get(1, 1, n_, l, r);
        return {res.s1, res.s2};
    }

    void flipRange(int32_t l, int32_t r) { upd(1, 1, n_, l, r); }

private:
    int32_t n_ = 0;
    vector<Node> t_;

    static Node merge(const Node& a, const Node& b) {
        return {(a.s1 + b.s1) % MOD, (a.s2 + b.s2) % MOD, static_cast<int32_t>(a.len + b.len), false};
    }

    void apply(int32_t v) {
        auto& nd = t_[v];
        int64_t L = nd.len % MOD, s1 = nd.s1, s2 = nd.s2;
        nd.s1 = norm(L - s1);
        nd.s2 = norm(L - 2 * s1 + s2);
        nd.flip ^= 1;
    }

    void push(int32_t v) {
        if (!t_[v].flip) return;
        apply(v << 1);
        apply(v << 1 | 1);
        t_[v].flip = false;
    }

    void build(int32_t v, int32_t tl, int32_t tr, const vector<int64_t>& a) {
        t_[v].len = tr - tl + 1;
        if (tl == tr) {
            t_[v].s1 = a[tl];
            t_[v].s2 = mul(a[tl], a[tl]);
            return;
        }
        int32_t tm = (tl + tr) / 2;
        build(v << 1, tl, tm, a);
        build(v << 1 | 1, tm + 1, tr, a);
        t_[v] = merge(t_[v << 1], t_[v << 1 | 1]);
    }

    void upd(int32_t v, int32_t tl, int32_t tr, int32_t l, int32_t r) {
        if (l > r) return;
        if (l == tl && r == tr) {
            apply(v);
            return;
        }
        push(v);
        int32_t tm = (tl + tr) / 2;
        upd(v << 1, tl, tm, l, min(r, tm));
        upd(v << 1 | 1, tm + 1, tr, max(l, tm + 1), r);
        t_[v] = merge(t_[v << 1], t_[v << 1 | 1]);
    }

    Node get(int32_t v, int32_t tl, int32_t tr, int32_t l, int32_t r) {
        if (l > r) return Node{};
        if (l == tl && r == tr) return t_[v];
        push(v);
        int32_t tm = (tl + tr) / 2;
        return merge(get(v << 1, tl, tm, l, min(r, tm)),
                     get(v << 1 | 1, tm + 1, tr, max(l, tm + 1), r));
    }
};

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int32_t n;
    cin >> n;
    vector<int64_t> p(n + 1);
    for (int32_t i = 1; i <= n; ++i) {
        cin >> p[i];
        p[i] %= MOD;
    }
    SegTree st(p);
    int32_t q;
    cin >> q;
    while (q--) {
        int32_t type, l, r;
        cin >> type >> l >> r;
        if (type == 1) {
            int64_t x, y, z;
            cin >> x >> y >> z;
            x %= MOD; y %= MOD; z %= MOD;

            auto [S1, S2] = st.query(l, r);
            int64_t k = r - l + 1;
            int64_t km = k % MOD;
            int64_t pairs = mul(km, norm(km - 1)) * INV2 % MOD;
            int64_t a = norm(x - 2 * y + z);
            int64_t pairProd = mul(norm(mul(S1, S1) - S2), INV2);
            int64_t ans = (mul(pairs, z)
                + mul(mul(norm(km - 1), S1), norm(y - z))
                + mul(a, pairProd)) % MOD;
            cout << ans << '\n';
        } else {
            st.flipRange(l, r);
        }
    }
    return 0;
}
