#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <cstdint>
#include <climits>

using namespace std;

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");

    int64_t n = 0;
    in >> n;

    int64_t ans = n - 1;

    int64_t limit = 2 * sqrt(n) + 1000000;

    for (int64_t x = 1; x <= limit; x++) {
        if (n % x == 0) {
            ans = min(ans, abs(x - n / x));
        }

        for (int64_t variant = 0; variant <= 1; variant++) {
            int64_t r = x;
            int64_t subtract = (variant == 0) ? r / 2 : (r + 1) / 2;
            int64_t k = (n + subtract) / r;
            if (k >= 1) {
                int64_t students = r * k - subtract;
                if (students == n) {
                    ans = min(ans, abs(r - k));
                }
            }

            int64_t k_sym = x;
            int64_t subtract_sym = (variant == 0) ? k_sym / 2 : (k_sym + 1) / 2;
            int64_t r_sym = (n + subtract_sym) / k_sym;
            if (r_sym >= 1) {
                int64_t students = r_sym * k_sym - subtract_sym;
                if (students == n) {
                    ans = min(ans, abs(r_sym - k_sym));
                }
            }
        }

        if (ans <= 1) break;
    }

    out << ans << '\n';

    in.close();
    out.close();
    return 0;
}
