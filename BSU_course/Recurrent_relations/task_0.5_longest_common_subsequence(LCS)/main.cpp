#include <iostream>
// #include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    // std::ifstream in("input.txt");
    // std::ofstream out("output.txt");

    int32_t n = 0;
    cin >> n;
    // in >> n;
    vector<int32_t> a(n + 1, 0);
    vector<int32_t> b(n + 1, 0);
    for (int32_t i = 1; i <= n; ++i) {
        cin >> a[i];
        // in >> a[i];
    }
    for (int32_t i = 1; i <= n; ++i) {
        cin >> b[i];
        // in >> b[i];
    }
    vector<vector<int32_t>> results(n + 1, vector<int32_t>(n + 1, 0));

    for (int32_t i = 1; i <= n; ++i) {
        for (int32_t j = 1; j <= n; ++j) {
            if (a[i] == b[j]) {
                results[i][j] = results[i - 1][j - 1] + 1;
            }
            else {
                results[i][j] = max(results[i - 1][j], results[i][j - 1]);
            }
        }
    }
    int32_t k = results[n][n];
    cout << k << endl;

    vector<int32_t> lcs(k, 0);
    vector<int32_t> a_res(k, 0);
    vector<int32_t> b_res(k, 0);
    int32_t i = n, j = n, l = 0;
    while (i > 0 && j > 0) {
        if (a[i] == b[j]) {
            lcs[l] = a[i];
            a_res[l] = i - 1;
            b_res[l] = j - 1;
            ++l;
            --i;
            --j;
        } else if (results[i - 1][j] > results[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }

    reverse(lcs.begin(), lcs.end());
    reverse(a_res.begin(), a_res.end());
    reverse(b_res.begin(), b_res.end());

    /*
    out << n << endl;
    for (int32_t i = 1; i <= n; ++i) {
        out << a[i] << ' ';
    }
    out << endl;
    for (int32_t i = 1; i <= n; ++i) {
        out << b[i] << ' ';
    }
    out << endl << endl;
    for (int32_t i = 1; i <= n; ++i) {
        for (int32_t j = 1; j <= n; ++j) {
            out << results[i][j] << ' ';
        }
        out << endl;
    }
    out << endl;

    for (int32_t i = 0; i < k; ++i) {
        out << lcs[i] << ' ';
    }
    out << endl;
    */

    for (int32_t i = 0; i < k; ++i) {
        cout << a_res[i] << ' ';
    }
    cout << endl;
    for (int32_t i = 0; i < k; ++i) {
        cout << b_res[i] << ' ';
    }
    cout << endl;


    return 0;
}
