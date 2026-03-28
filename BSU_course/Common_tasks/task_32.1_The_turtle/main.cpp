#include <vector>
#include <fstream>

using namespace std;

constexpr int MOD = 1e9 + 7;

int main() {
    std::ifstream in("input.txt");
    std::ofstream out("output.txt");

    int32_t n = 0;
    int32_t m = 0;
    in >> n >> m;

    /*
    vector<vector<int32_t>> results(n, vector<int32_t>(m, 0));

    for (int32_t i = 0; i < m; i++) {
        results[0][i] = 1;
    }

    for (int32_t i = 0; i < n; i++) {
        results[i][0] = 1;
    }

    for (int32_t i = 1; i < n; i++) {
        for (int32_t j = 1; j < m; j++) {
            results[i][j] = (results[i][j - 1] + results[i - 1][j]) % MOD;
        }
    }

    for (int32_t i = 0; i < n; i++) {
        for (int32_t j = 0; j < m; j++) {
            cout << results[i][j] << ' ';
        }
        cout << endl;
    }

    cout << results[n - 1][m - 1] << endl;
    */


    vector<int32_t> prev(m , 1);
    vector<int32_t> cur(m, 1);

    for (int32_t i = 1; i < m; i++) {
        cur[i] = i;
    }

    for (int32_t i = 1; i < n; i++) {
        for (int32_t j = 1; j < m; j++) {
            cur[j] = (cur[j - 1] + prev[j]) % MOD;
        }
        prev = cur;
        for (int32_t j = 0; j < m; j++) {
            cur[j] = 1;
            // out << prev[j] << ' ';
        }
        // out << endl;
    }

    out << prev[m - 1] << endl;

    return 0;
}
