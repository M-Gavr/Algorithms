#include <iostream>
#include <vector>

using namespace std;

int main() {
    int32_t n = 0;
    cin >> n;

    if (n == 1) {
        cout << "1" << endl;
        return 0;
    }

    vector<int64_t> capitals(n, 0);
    for (int32_t i = 0; i < n; ++i) {
        cin >> capitals[i];
    }

    bool all_equal = true;
    for (int32_t i = 1; i < n; ++i) {
        if (capitals[i] != capitals[0]) {
            all_equal = false;
            break;
        }
    }

    if (all_equal) {
        for (int32_t i = 0; i < n; ++i) {
            cout << "0 ";
        }
        cout << endl;
        return 0;
    }

    vector<int64_t> prefix_sum(n);
    prefix_sum[0] = capitals[0];
    for (int32_t i = 1; i < n; ++i) {
        prefix_sum[i] = prefix_sum[i-1] + capitals[i];
    }

    vector<int32_t> result(n, 0);

    int32_t first_winner = n - 1;
    for (int32_t i = n - 1; i > 0; --i) {
        if (prefix_sum[i-1] <= capitals[i]) {
            first_winner = i;
            break;
        }
    }

    for (int32_t i = first_winner; i < n; ++i) {
        result[i] = 1;
    }

    for (int32_t i = 0; i < n; ++i) {
        cout << result[i] << " ";
    }
    cout << endl;

    return 0;
}