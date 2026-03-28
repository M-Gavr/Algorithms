#include <iostream>
#include <cstdint>
#include <fstream>
#include <vector>

using namespace std;

vector<int32_t> binomial_tree(int64_t n) {
    vector<int32_t> result;
    int32_t order = 0;

    while (n > 0) {
        if ((n & 1) == 1) {
            result.push_back(order);
        }
        n >>= 1;
        ++order;
    }
    return result;
}

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");

    int64_t n = 0;
    in >> n;

    // out << n << "\n";

    const vector<int32_t> result = binomial_tree(n);

    for (auto number : result) {
        out << number << '\n';
    }

    in.close();
    out.close();
    return 0;
}
