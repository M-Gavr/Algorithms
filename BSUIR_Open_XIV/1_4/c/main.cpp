#include <iostream>
#include <fstream>
#include <cstdint>
#include <vector>

using namespace std;

int main() {
    // ifstream in("input.txt");
    // ofstream out("output.txt");

    int32_t n = 0;
    cin >> n;
    vector<vector<int32_t>> numbers (n, vector<int32_t>(10, 0));
    vector<vector<int32_t>> count (n, vector<int32_t>(10, 0));

    char number = 0;
    for (int32_t i = 0; i < n; ++i) {
        for (int32_t j = 0; j < 10; ++ j) {
            cin >> number;
            number = number - '0';
            numbers[i][j] = number;
            ++count[i][number];
        }
    }

    // for (int32_t i = 0; i < n; ++i) {
    //     for (int32_t j = 0; j < 10; ++ j) {
    //         out << numbers[i][j] << ' ';
    //     }
    //     out << '\n';
    // }
    //
    // out << '\n';
    //
    // for (int32_t i = 0; i < n; ++i) {
    //     for (int32_t j = 0; j < 10; ++ j) {
    //         out << count[i][j] << ' ';
    //     }
    //     out << '\n';
    // // }
    //
    // out << '\n';

    vector<vector<int32_t>> results (n, vector<int32_t>(10, -1));
    for (int32_t i = 0; i < n; ++i) {
        for (int32_t j = 9; j >= 0; --j) {
            if (count[i][j] > 0) {
                results[i][9 - j] = j;
                --count[i][j];
            }

        }
    }

    for (int32_t i = 0; i < n; ++i) {
        for (int32_t j = 0; j < 10; ++j) {
            if (results[i][j] == -1) {
                for (int32_t k = 9 - j; k < 10; ++k) {
                    if (count[i][k] > 0) {
                        results[i][j] = k;
                        --count[i][k];
                        break;
                    }

                }
            }

        }
    }

    for (int32_t i = 0; i < n; ++i) {
        for (int32_t j = 0; j < 10; ++ j) {
            cout << results[i][j];
        }
        cout << '\n';
    }

    cout << '\n';

    // for (int32_t i = 0; i < n; ++i) {
    //     for (int32_t j = 0; j < 10; ++ j) {
    //         out << count[i][j] << ' ';
    //     }
    //     out << '\n';
    // }

    // in.close();
    // out.close();
    return 0;
}
