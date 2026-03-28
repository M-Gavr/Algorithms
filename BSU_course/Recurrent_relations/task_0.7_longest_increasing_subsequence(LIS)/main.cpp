#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    std::ifstream in("input.txt");
    std::ofstream out("output.txt");

    int32_t n = 0;
    in >> n;
    vector<int32_t> numbers(n, 0);
    for (int32_t i = 0; i < n; ++i) {
        in >> numbers[i];
    }

    vector<int32_t> results;

    for (int32_t number : numbers) {
        auto pos = lower_bound(results.begin(), results.end(), number);
        if (pos == results.end()) {
            results.push_back(number);
        } else {
            *pos = number;
        }
    }

    out << results.size() << endl;

    /*
    results[1] = 1;

    int32_t m = 0;
    for (int32_t i = 2; i <= n; ++i) {
        m = results[i - 1];
        for (int32_t j = 1; j < i; ++j) {
            if (numbers[j] < numbers[i]) {
                m = max(m, results[j] + 1);
            }
        }
        results[i] = m;
    }

    out << n << endl;
    for (int32_t i = 1; i <= n; ++i) {
        out << numbers[i] << ' ';
    }
    out << endl;
    for (int32_t i = 1; i <= n; ++i) {
        out << results[i] << ' ';
    }
    out << endl;

    out << results[n] << endl;
    */

    return 0;
}
