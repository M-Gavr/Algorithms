#include <cstdint>
#include <fstream>
#include <queue>
#include <vector>

using namespace std;

vector<int32_t> bfs(vector<vector<int32_t>>& g) {
    const int32_t n = g.size();
    vector<int32_t> result(n, -1);
    vector<bool> visited(n, false);
    queue<int32_t> q;

    int32_t index = 1;

    for (int32_t start = 0; start < n; ++start) {
        if (!visited[start]) {
            q.push(start);
            visited[start] = true;

            while (!q.empty()) {
                const int32_t v = q.front();
                q.pop();
                result[v] = index;
                index++;

                for (int32_t i = 0; i < n; ++i) {
                    if (g[v][i] == 1 && !visited[i]) {
                        visited[i] = true;
                        q.push(i);
                    }
                }
            }
        }
    }

    return result;
}

int main() {
    std::ifstream in("input.txt");
    std::ofstream out("output.txt");

    int32_t n = 0;
    in >> n;

    vector<vector<int32_t>> g(n, vector<int32_t>(n, 0));
    for (int32_t i = 0; i < n; ++i) {
        for (int32_t j = 0; j < n; ++j) {
            in >> g[i][j];
        }
    }

    vector<int32_t> m = bfs(g);

    for (int32_t i = 0; i < n; ++i) {
        out << m[i] << ' ';
    }
    out << '\n';

    in.close();
    out.close();
    return 0;
}
