#include <algorithm>
#include <cstdint>
#include <fstream>
#include <functional>
#include <string>
#include <utility>
#include <vector>

using namespace std;

static bool isStraightHVLine(const vector<pair<int32_t, int32_t>>& cells) {
    const int32_t n = cells.size();
    int32_t r0 = cells[0].first;
    int32_t minc = cells[0].second;
    int32_t maxc = cells[0].second;
    bool horiz = true;
    for (const auto& p : cells) {
        if (p.first != r0) {
            horiz = false;
        }
        minc = min(minc, p.second);
        maxc = max(maxc, p.second);
    }
    if (horiz && maxc - minc + 1 == n) {
        return true;
    }
    int32_t c0 = cells[0].second;
    int32_t minr = cells[0].first;
    int32_t maxr = cells[0].first;
    bool vert = true;
    for (const auto& p : cells) {
        if (p.second != c0) {
            vert = false;
        }
        minr = min(minr, p.first);
        maxr = max(maxr, p.first);
    }
    return vert && maxr - minr + 1 == n;
}

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");

    vector<string> g(10);
    for (int32_t i = 0; i < 10; ++i) {
        in >> g[i];
    }

    const int32_t dr[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
    const int32_t dc[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

    int32_t vis[10][10] = {};
    vector<int32_t> shipLens;

    function<void(int32_t, int32_t, vector<pair<int32_t, int32_t>>&)> dfs8 =
        [&](int32_t r, int32_t c, vector<pair<int32_t, int32_t>>& comp) {
            if (r < 0 || r >= 10 || c < 0 || c >= 10 || g[r][c] != '#' || vis[r][c]) {
                return;
            }
            vis[r][c] = 1;
            comp.emplace_back(r, c);
            for (int32_t k = 0; k < 8; ++k) {
                dfs8(r + dr[k], c + dc[k], comp);
            }
        };

    for (int32_t i = 0; i < 10; ++i) {
        for (int32_t j = 0; j < 10; ++j) {
            if (g[i][j] == '#' && !vis[i][j]) {
                vector<pair<int32_t, int32_t>> comp;
                dfs8(i, j, comp);
                if (!isStraightHVLine(comp)) {
                    out << "NO\n";
                    return 0;
                }
                shipLens.push_back(static_cast<int32_t>(comp.size()));
            }
        }
    }

    sort(shipLens.begin(), shipLens.end());
    const vector<int32_t> expected = {1, 1, 1, 1, 2, 2, 2, 3, 3, 4};
    if (shipLens != expected) {
        out << "NO\n";
    } else {
        out << "YES\n";
    }

    return 0;
}
