#include <cstdint>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

static int64_t GetSum(const vector<int64_t>& fenv, int32_t pos) {
    ++pos;
    int64_t sum = 0;
    for (int32_t i = pos; i > 0; i -= i & (-i)) {
        sum += fenv[i];
    }
    return sum;
}

static void Add(vector<int64_t>& fenv, int32_t index, const int32_t x) {
    ++index;
    const int32_t n = fenv.size();
    for (int32_t i = index; i < n; i += i & (-i)) {
        fenv[i] += x;
    }
}

int main() {
    // ifstream in("input.txt");
    // ofstream out("output.txt");

    int32_t n = 0;
    cin >> n;

    vector<int32_t> numbers(n + 1, 0);

    for (int32_t i = 1; i <= n; ++i) {
        cin >> numbers[i];
    }

    vector<int64_t> fenvik(n + 1, 0);
    fenvik[1] = numbers[1];

    for (int32_t i = 2; i <= n; ++i) {
        int32_t del = i & (-i);
        for (int32_t j = i - del + 1; j <= i; ++j) {
            fenvik[i] += numbers[j];
        }
    }

    // for (int32_t i = 1; i <= n; ++i) {
    //     cout << fenvik[i] << ' ';
    // }
    // cout << '\n';

    int32_t q = 0;
    cin >> q;
    string s;
    int32_t index = 0;
    int32_t x = 0;
    int32_t l = 0;
    int32_t r = 0;

    for (int32_t i = 0; i < q; ++i) {
        cin >> s;
        if (s == "Add") {
            cin >> index >> x;
            Add(fenvik, index, x);
        }
        if (s == "FindSum") {
            cin >> l >> r;
            cout << (GetSum(fenvik, r - 1) - GetSum(fenvik, l - 1)) << '\n';
        }
    }

    // in.close();
    // out.close();
    return 0;
}
