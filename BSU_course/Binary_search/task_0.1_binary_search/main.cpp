#include <iostream>
#include <vector>

using namespace std;

int32_t binary_search_equal_or_higher(const vector<int32_t>& numbers, const int32_t& request) {
    int32_t left = 0;
    auto right = static_cast<int32_t>(numbers.size());

    int32_t mid = 0;
    while (left < right) {
        mid = left + (right - left) / 2;

        if (numbers[mid] >= request) {
            right = mid;
        }
        else if (numbers[mid] < request) {
            left = mid + 1;
        }
    }

    return left;
}

int32_t binary_search_higher(const vector<int32_t>& numbers, const int32_t& request) {
    int32_t left = 0;
    auto right = static_cast<int32_t>(numbers.size());

    int32_t mid = 0;
    while (left < right) {
        mid = left + (right - left) / 2;

        if (numbers[mid] > request) {
            right = mid;
        }
        else if (numbers[mid] <= request) {
            left = mid + 1;
        }
    }

    return left;
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

    int32_t request = 0;
    for (int32_t i = 0; i < k; i++) {
        cin >> request;

        int32_t l = binary_search_equal_or_higher(numbers, request);
        int32_t r = binary_search_higher(numbers, request);

        int b = (l < n && numbers[l] == request) ? 1 : 0;

        cout << b << " " << l << " " << r << endl;
    }

    return 0;
}
