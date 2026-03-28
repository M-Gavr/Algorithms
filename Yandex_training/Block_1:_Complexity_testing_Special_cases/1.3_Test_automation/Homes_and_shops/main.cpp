#include <iostream>
#include <fstream>
#include <cstdint>
#include <vector>

using namespace std;

int32_t solve(const vector<int32_t>& street) {
    vector<int32_t> homes;
    vector<int32_t> shops;

    for (int32_t i = 0; i < 10; ++i) {
        if (street[i] == 1) {
            homes.push_back(i);
        } else if (street[i] == 2) {
            shops.push_back(i);
        }
    }

    int32_t max_min_distance = 0;

    for (int32_t home : homes) {
        int32_t min_distance = INT32_MAX;

        for (int32_t shop : shops) {
            int32_t dist = abs(home - shop);
            if (dist < min_distance) {
                min_distance = dist;
            }
        }

        if (min_distance > max_min_distance) {
            max_min_distance = min_distance;
        }
    }

    return max_min_distance;
}

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");

    // int32_t n = 0;
    // in >> n;

    // vector<vector<int32_t>> a(n, vector<int32_t>(10, 0));

    vector<int32_t> a(10, 0);

    // for (int32_t i = 0; i < n; ++i) {
    //     for (int32_t j = 0; j < 10; ++j) {
    //         in >> a[i][j];
    //     }
    //     out << solve(a[i]) << '\n';
    // }

    for (int32_t j = 0; j < 10; ++j) {
            in >> a[j];
        }
        out << solve(a) << '\n';

    return 0;
}
