#include <iostream>
#include <vector>

using namespace std;

bool binary_search(const vector<int32_t>& numbers, const int32_t& request) {
    int32_t left = 0;
    auto right = static_cast<int32_t>(numbers.size());

    int32_t mid = 0;
    while (left < right) {
        mid = left + (right - left) / 2;

        if (numbers[mid] == request) {
            return true;
        }
        else if (numbers[mid] < request) {
            left = mid + 1;
        }
        else {
            right = mid;
        }
    }

    return false;
}

int main() {
    int32_t n = 0;
    cin >> n;

    vector<int32_t> numbers(n);
    int32_t number = 0;
    for (size_t i = 0; i < n; i++) {
        cin >> number;
        numbers[i] = number;
    }

    int32_t k = 0;
    cin >> k;

    const bool b = binary_search(numbers, k);

    cout << b << endl;

    return 0;
}
