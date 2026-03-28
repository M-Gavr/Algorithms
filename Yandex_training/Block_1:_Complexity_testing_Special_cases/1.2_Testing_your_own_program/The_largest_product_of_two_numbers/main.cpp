/* tests
6
3 1 2 3
5 -2 -1 0 1 3
4 100 -100 50 -49
2 0 100
2 -100 1
2 2 4
*/

#include <iostream>
#include <fstream>
#include <cstdint>
#include <vector>
#include <algorithm>

using namespace std;

pair<int32_t, int32_t> solve(const vector<int32_t>& numbers) {
    int32_t max1 = INT32_MIN, max2 = INT32_MIN;
    int32_t min1 = INT32_MAX, min2 = INT32_MAX;

    for (const int32_t num : numbers) {
        if (num > max1) {
            max2 = max1;
            max1 = num;
        } else if (num > max2) {
            max2 = num;
        }

        if (num < min1) {
            min2 = min1;
            min1 = num;
        } else if (num < min2) {
            min2 = num;
        }
    }

    const int64_t mul_max = static_cast<int64_t>(max1) * max2;
    const int64_t mul_min = static_cast<int64_t>(min1) * min2;

    if (mul_max > mul_min) {
        if (max1 < max2) {
            return {max1, max2};
        } else {
            return {max2, max1};
        }
    } else {
        if (min1 < min2) {
            return {min1, min2};
        } else {
            return {min2, min1};
        }
    }
}

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");

    // int32_t n = 0;
    // int32_t k = 0;
    int32_t number = 0;
    pair<int32_t, int32_t> result;
    // in >> n;

    // vector<vector<int32_t>> a(n);

    // for (int32_t i = 0; i < n; ++i) {
    //     in >> k;
    //     for (int32_t j = 0; j < k; ++j) {
    //         in >> number;
    //         a[i].push_back(number);
    //     }
    //     result = solve(a[i]);
    //     out << result.first << ' ' << result.second << '\n';
    // }

    vector<int32_t> numbers;
    while (in >> number) {
        numbers.push_back(number);
    }

    result = solve(numbers);

    out << result.first << ' ' << result.second << '\n';

    return 0;
}
