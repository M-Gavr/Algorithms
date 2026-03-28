#include <iostream>
#include <fstream>
#include <cstdint>
#include <vector>

using namespace std;

int32_t solve(int32_t number) {
    int32_t count = 0;
    while (number > 0) {
        count += (number & 1);
        number >>= 1;
    }
    return (1 << count - 1) - 1;
}

int main() {
    // ifstream in("input.txt");
    // ofstream out("output.txt");

    int32_t n = 0;
    cin >> n;
    int32_t k = 0;

    for (int32_t i = 0; i < n; ++i) {
        cin >> k;
        cout << solve(k) << '\n';
    }

    cout << '\n';

    // in.close();
    // out.close();
    return 0;
}
