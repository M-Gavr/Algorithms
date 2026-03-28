#include <cstdint>
#include <fstream>
#include <vector>

using namespace std;

string getOrder(int i, int j, const vector<vector<int32_t>>& split,
                const vector<int32_t>& n, const vector<int32_t>& m) {
    if (i == j) {
        return "A" + to_string(i);
    }

    int k = split[i][j];

    string left = getOrder(i, k, split, n, m);
    string right = getOrder(k + 1, j, split, n, m);
    return "(" + left + " × " + right + ")";
}

int main() {
    std::ifstream in("input.txt");
    std::ofstream out("output.txt");

    int32_t s = 0;
    in >> s;
    vector<int32_t> n(s + 1, 0);
    vector<int32_t> m(s + 1, 0);
    for (int32_t i = 1; i <= s; ++i) {
        in >> n[i] >> m[i];
    }

    vector<vector<int32_t>> results(s + 1, vector<int32_t>(s + 1, 0));
    vector<vector<int32_t>> results_2(s + 1, vector<int32_t>(s + 1, 0));

    for (int32_t i = 1; i < s; ++i) {
        results[i][i + 1] = n[i] * m[i] * m[i + 1];
    }

    int32_t mul = 0;
    for (int32_t i = s - 2; i > 0; --i) {
        for (int32_t j = i + 2; j <= s; ++j) {
            mul = results[i][i] + results[i + 1][j] + n[i] * m[i] * m[j];
            for (int32_t k = 1; k < j - i; k++) {
                mul = min(mul, results[i][i + k] + results[i + 1 + k][j] + n[i] * m[i + k] * m[j]);
            }
            results[i][j] = mul;
        }
    }

    /*
    out << s << endl;
    for (int32_t i = 1; i <= s; ++i) {
        out << n[i] << ' ' <<  m[i] << endl;
    }

    for (int32_t i = 1; i <= s; ++i) {
        for (int32_t j = 1; j <= s; ++j) {
            out << results[i][j] << ' ';
        }
        out << endl;
    }
    */

    out << results[1][s] << endl;

    /*
    vector<vector<int32_t>> split(s + 1, vector<int32_t>(s + 1, 0));

    for (int32_t i = 1; i < s; ++i) {
        results_2[i][i + 1] = n[i] * m[i] * m[i + 1];
        split[i][i + 1] = i;
    }

    for (int32_t length = 3; length <= s; ++length) {
        for (int32_t i = 1; i <= s - length + 1; ++i) {
            int32_t j = i + length - 1;

            results[i][j] = results[i][i] + results[i + 1][j] + n[i] * m[i] * m[j];
            split[i][j] = i;

            for (int32_t k = i + 1; k < j; ++k) {
                int32_t current = results[i][k] + results[k + 1][j] + n[i] * m[k] * m[j];

                if (current < results[i][j]) {
                    results[i][j] = current;
                    split[i][j] = k;
                }
            }
        }
    }

    out << results[1][s] << endl;
    out << getOrder(1, s, split, n, m) << endl;

    out << s << endl;
    for (int32_t i = 1; i <= s; ++i) {
        out << n[i] << ' ' <<  m[i] << endl;
    }

    for (int32_t i = 1; i <= s; ++i) {
        for (int32_t j = 1; j <= s; ++j) {
            out << results_2[i][j] << ' ';
        }
        out << endl;
    }
    */

    in.close();
    out.close();
    return 0;
}
