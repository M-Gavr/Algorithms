#include <cstdint>
#include <fstream>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>

using namespace std;

const int32_t dx[4] = {1, -1, 0, 0};
const int32_t dy[4] = {0, 0, 1, -1};

vector<pair<int32_t, int32_t>> bfs_shortest_path(
    const vector<string>& lab,
    int32_t start_x, int32_t start_y,
    int32_t target_x, int32_t target_y,
    const vector<vector<vector<bool>>>& used_edges) {

    int32_t m = lab.size();
    int32_t n = lab[0].size();

    vector<vector<bool>> visited(m, vector<bool>(n, false));
    vector<vector<pair<int32_t, int32_t>>> parent(m, vector<pair<int32_t, int32_t>>(n, {-1, -1}));

    queue<pair<int32_t, int32_t>> q;
    q.push({start_x, start_y});
    visited[start_x][start_y] = true;

    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();

        if (x == target_x && y == target_y) {
            vector<pair<int32_t, int32_t>> path;
            int32_t cx = x, cy = y;
            while (!(cx == start_x && cy == start_y)) {
                path.push_back({cx, cy});
                auto [px, py] = parent[cx][cy];
                cx = px;
                cy = py;
            }
            path.push_back({start_x, start_y});
            reverse(path.begin(), path.end());
            return path;
        }

        for (int32_t d = 0; d < 4; d++) {
            int32_t nx = x + dx[d];
            int32_t ny = y + dy[d];

            if (nx >= 0 && nx < m && ny >= 0 && ny < n &&
                lab[nx][ny] != '*' && !visited[nx][ny]) {

                if (!used_edges[x][y][d]) {
                    visited[nx][ny] = true;
                    parent[nx][ny] = {x, y};
                    q.push({nx, ny});
                }
            }
        }
    }

    return {};
}

void mark_path_edges(vector<vector<vector<bool>>>& used_edges,
                     const vector<pair<int32_t, int32_t>>& path) {
    for (size_t i = 0; i < path.size() - 1; i++) {
        int32_t x1 = path[i].first;
        int32_t y1 = path[i].second;
        int32_t x2 = path[i+1].first;
        int32_t y2 = path[i+1].second;

        if (x2 == x1 + 1 && y2 == y1) {
            used_edges[x1][y1][0] = true;
            used_edges[x2][y2][1] = true;
        } else if (x2 == x1 - 1 && y2 == y1) {
            used_edges[x1][y1][1] = true;
            used_edges[x2][y2][0] = true;
        } else if (y2 == y1 + 1 && x2 == x1) {
            used_edges[x1][y1][2] = true;
            used_edges[x2][y2][3] = true;
        } else if (y2 == y1 - 1 && x2 == x1) {
            used_edges[x1][y1][3] = true;
            used_edges[x2][y2][2] = true;
        }
    }
}

int32_t main() {
    ifstream fin("walk.in");
    ofstream fout("walk.out");

    int32_t m = 0, n = 0;
    fin >> m >> n;

    vector<string> lab(m);
    for (int32_t i = 0; i < m; i++) {
        fin >> lab[i];
    }

    int32_t start_x = -1, start_y = -1;
    int32_t key_x = -1, key_y = -1;

    for (int32_t i = 0; i < m; i++) {
        for (int32_t j = 0; j < n; j++) {
            if (lab[i][j] == 'M') {
                start_x = i;
                start_y = j;
            } else if (lab[i][j] == 'G') {
                key_x = i;
                key_y = j;
            }
        }
    }

    vector<vector<vector<bool>>> used_edges(
        m, vector<vector<bool>>(n, vector<bool>(4, false)));

    vector<pair<int32_t, int32_t>> path1 = bfs_shortest_path(
        lab, start_x, start_y, key_x, key_y, used_edges);

    if (path1.empty()) {
        fout << -1 << '\n';
        return 0;
    }

    mark_path_edges(used_edges, path1);

    vector<pair<int32_t, int32_t>> path2 = bfs_shortest_path(
        lab, start_x, start_y, key_x, key_y, used_edges);

    if (path2.empty()) {
        fout << -1 << '\n';
        return 0;
    }

    int32_t total_cost = (path1.size() - 1) + (path2.size() - 1);
    fout << total_cost << '\n';

    fin.close();
    fout.close();
    return 0;
}