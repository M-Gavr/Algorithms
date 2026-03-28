#include <iostream>
#include <cstdint>
#include <fstream>
#include <vector>

using namespace std;

bool check_binary_heap(const vector<int32_t>& numbers) {
    const int32_t n = numbers.size();
    int32_t left_son = 0;
    int32_t right_son = 0;
    for (int32_t i = 0; i < n; ++i) {
        left_son = 2 * i + 1;
        right_son = 2 * i + 2;

        if (left_son < n && numbers[left_son] < numbers[i]) {
            return false;
        }

        if (right_son < n && numbers[right_son] < numbers[i]) {
            return false;
        }
    }

    return true;
}

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");

    int32_t n = 0;
    in >> n;
    vector<int32_t> numbers(n, 0);

    for (int32_t i = 0; i < n; ++i) {
        in >> numbers[i];
    }

    // for (int32_t i = 0; i < n; ++i) {
    //     out << numbers[i] << ' ';
    // }
    //
    // out << '\n';

    out << (check_binary_heap(numbers) ? "Yes" : "No") << '\n';

    in.close();
    out.close();
    return 0;
}
