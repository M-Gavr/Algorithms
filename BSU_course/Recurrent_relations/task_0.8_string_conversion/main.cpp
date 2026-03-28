#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    std::ifstream in("in.txt");
    std::ofstream out("out.txt");

    int32_t x = 0, y = 0, z = 0;
    in >> x >> y >> z;
    string a, b;
    in >> a >> b;

    int32_t n = a.size(), m = b.size();

    vector<vector<int32_t>> results(m + 1, vector<int32_t>(n + 1,0));
    for (int32_t i = 1; i <= n; ++i) {
        results[0][i] = x * i;
    }
    for (int32_t i = 1; i <= m; ++i) {
        results[i][0] = y * i;
    }

    int32_t rep = 0, del = 0, ins = 0;
    for (int32_t i = 1; i <= m; ++i) {
        for (int32_t j = 1; j <= n; ++j) {
            del = results[i][j - 1] + x;
            ins = results[i - 1][j] + y;
            if (a[j - 1]== b[i - 1]) {
                rep = results[i - 1][j - 1];
            }
            else {
                rep = results[i - 1][j - 1] + z;
            }
            results[i][j] = min(min(del, ins), rep);
        }
    }

    /*
    for (int32_t i = 0; i <= m; ++i) {
        for (int32_t j = 0; j <= n; ++j) {
            out << results[i][j] << ' ';
        }
        out << endl;
    }

    out << x << ' ' << y << ' ' << z << endl;
    out << a << '\n' << b << endl;
    */

    out << results[m][n];

    return 0;
}
