#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    std::ifstream in("input.txt");
    std::ofstream out("output.txt");

    string str;
    in >> str;
    int32_t n = str.size();

    vector<vector<int32_t>> results (n, vector<int32_t>(n, 0));

    for (int32_t i = 0; i <= n - 1; ++i) {
        results[i][i] = 1;
    }

    for (int32_t length = 2; length <= n; ++length) {
        for (int32_t i = 0; i <= n - length; ++i) {
            int32_t j = i + length - 1;
            if (str[i] == str[j]) {
                results[i][j] = results[i + 1][j - 1] + 2;
            }
            else {
                results[i][j] = max(results[i + 1][j], results[i][j - 1]);
            }
        }
    }

    int32_t k = results[0][n - 1];

    string result(k, ' ');
    int32_t left = 0, right = k - 1;
    int32_t i = 0, j = n - 1;

    while (i <= j) {
        if (i == j) {
            result[left] = str[i];
            break;
        }

        if (str[i] == str[j]) {
            result[left] = str[i];
            result[right] = str[j];
            left++;
            right--;
            i++;
            j--;
        } else if (results[i + 1][j] > results[i][j - 1]) {
            i++;
        } else {
            j--;
        }
    }

    /*
    out << str << endl;
    for (int32_t i = 0; i < n; ++i) {
        for (int32_t j = 0; j < n; ++j) {
            out << results[i][j] << ' ';
        }
        out << endl;
    }
    */

    out << k << endl;
    out << result;

    return 0;
}
