#include<bits/stdc++.h>
typedef long long ll;
using namespace std;

int main()
{
  // ifstream cin("input.txt");
 //    ofstream cout("output.txt");
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  ll n, m, A, B; ll seed, X, Y; cin >> n >> m >> A >> B >> seed >> X >> Y;
    if (A <= 0 || B <= 0 || A > n || B > m) {
        cout << 0 << '\n' << 1 << ' ' << 1 << '\n';
        return 0;
    }
    Y += 1'000'000'000;
    Y %= 1'000'000'000;
    X += 1'000'000'000;
    X %= 1'000'000'000;
    vector<vector<int>> g(n, vector<int>(m));
    vector<vector<ll>> pref(n + 1, vector<ll>(m + 1));
    vector<vector<int>> mn(n, vector<int>(m, INT_MAX));
    auto s0 = seed;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            g[i][j] = (s0 * X % 1'000'000'000 + Y) % 1'000'000'000;
            pref[i + 1][j + 1] = g[i][j] + pref[i][j + 1] + pref[i + 1][j] - pref[i][j];
            s0 = g[i][j];
        }
    }

    auto add = [&](deque<int>& d, int x) {
        while(!d.empty() && d.front() > x) d.pop_front();
        d.push_front(x);
    };

    auto rem = [&](deque<int>& d, int x) {
        if (!d.empty() && x == d.back()) d.pop_back();
    };

    for (int i = 0; i < n; i++) {
        deque<int> dq;
        for (int j = 0; j < B; j++) add(dq, g[i][j]);
        mn[i][B - 1] = dq.back();
        for (int j = B; j < m; j++) {
            add(dq, g[i][j]);
            rem(dq, g[i][j - B]);
            mn[i][j] = dq.back();
        }
    }

    auto calc = [&](int x, int y, int mn) {
        ll res = pref[x + 1][y + 1] - pref[x + 1 - A][y + 1] - pref[x + 1][y + 1 - B] + pref[x + 1 - A][y + 1 - B];
        res -= A * B * mn;
        return res;
    };

    array<ll, 3> ans = {(ll)1e18, 0, 0};
    for (int j = B - 1; j < m; j++) {
        deque<int> dq;
        for (int i = 0; i < A; i++) add(dq, mn[i][j]);
        ans = min(ans, {calc(A - 1, j, dq.back()), A - 1, j});
        for (int i = A; i < n; i++) {
            add(dq, mn[i][j]);
            rem(dq, mn[i - A][j]);
            ans = min(ans, {calc(i, j, dq.back()), i, j});
        }
    }
    cout << ans[0] << '\n' << ans[1] - A + 2 << ' ' << ans[2] - B + 2 << '\n';
}