#include <fstream>
#include <cstdint>
#include <vector>
#include <string>

using namespace std;

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");

    int32_t n = 0, m = 0;
    in >> n >> m;

    int32_t retrovirus = 0;

    vector<string> grid(n);
    for (int32_t i = 0; i < n; i++) {
        grid[i].resize(m);
        for (int32_t j = 0; j < m; j++) {
            in >> grid[i][j];
        }
    }

    vector<vector<int32_t>> prefix(n + 1, vector<int32_t>(m + 1, 0));
    for (int32_t i = 0; i < n; i++) {
        for (int32_t j = 0; j < m; j++) {
            prefix[i + 1][j + 1] = prefix[i][j + 1] + prefix[i + 1][j] - prefix[i][j] + (grid[i][j] == '#' ? 1 : 0);
        }
    }

    vector<vector<bool>> visited(n, vector<bool>(m, false));
    int32_t bacteria_count = 0;

    for (int32_t i = 0; i < n; i++) {
        for (int32_t j = 0; j < m; j++) {
            if (grid[i][j] == '#' && !visited[i][j]) {
                int32_t max_side = min(n - i, m - j);

                for (int32_t side = max_side; side >= 1; side--) {
                    int32_t sum = prefix[i + side][j + side] - prefix[i][j + side] - prefix[i + side][j] + prefix[i][j];

                    if (sum == side * side) {
                        bacteria_count++;
                        for (int32_t x = i; x < i + side; x++) {
                            for (int32_t y = j; y < j + side; y++) {
                                visited[x][y] = true;
                            }
                        }
                        break;
                    }
                }
            }
        }
    }

    out << bacteria_count << '\n';

    in.close();
    out.close();
    return 0;
}