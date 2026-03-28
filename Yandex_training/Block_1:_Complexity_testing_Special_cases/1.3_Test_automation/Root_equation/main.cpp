#include <iostream>
#include <fstream>
#include <cstdint>
#include <format>
#include <string>

using namespace std;

string solve(const int32_t& a, const int32_t& b, const int32_t& c) {
    if (c < 0) {
        return "NO SOLUTION";
    }

    if (a == 0) {
        if (c * c == b) {
            return "MANY SOLUTIONS";
        } else {
            return "NO SOLUTION";
        }
    }

    const int32_t numerator = c * c - b;

    if (numerator % a != 0) {
        return "NO SOLUTION";
    }

    int32_t x = numerator / a;

    if (a * x == c * c - b) {
        return to_string(x);
    } else {
        return "NO SOLUTION";
    }
}

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");

    // int32_t n = 0;
    // in >> n;

    int32_t a = 0;
    int32_t b = 0;
    int32_t c = 0;

    // for (int32_t i = 0; i < n; ++i) {
    //     in >> a >> b >> c;
    //     out << solve(a, b, c) << '\n';
    // }

    in >> a >> b >> c;
    out << solve(a, b, c) << '\n';

    return 0;
}
