#include <cstdint>
#include <fstream>
#include <stack>
#include <vector>

using namespace std;

vector<int32_t> dfs(vector<vector<int32_t>>& g) {
    const int32_t n = g.size();
    vector<int32_t> result(n, -1);
    vector<bool> visited(n, false);
    stack<int32_t> st;

    int32_t index = 1;

    for (int32_t start = 0; start < n; ++start) {
        if (!visited[start]) {
            st.push(start);

            while (!st.empty()) {
                const int32_t v = st.top();
                st.pop();

                if (visited[v]) {
                    continue;
                }

                visited[v] = true;
                result[v] = index;
                ++index;

                for (int32_t i = n - 1; i >= 0; --i) {
                    if (g[v][i] == 1 && !visited[i]) {
                        st.push(i);
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

    vector<int32_t> m = dfs(g);

    for (int32_t i = 0; i < n; ++i) {
        out << m[i] << ' ';
    }
    out << '\n';

    in.close();
    out.close();
    return 0;
}
