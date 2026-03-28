#include <iostream>
#include <fstream>
#include <cstdint>
#include <string>

using namespace std;

int32_t solve(const int32_t room, const int32_t cond, const string& mode) {
    if (mode == "freeze") {
        return (room <= cond ? room : cond);
    } else if (mode == "heat") {
        return (room >= cond ? room : cond);
    } else if (mode == "auto") {
        return cond;
    } else if (mode == "auto") {
        return room;
    }
    return room;
}

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");

    // int32_t n = 0;
    // in >> n;

    int32_t room = 0;
    int32_t cond = 0;
    string mode;

    // for (int32_t i = 0; i < n; ++i) {
    //     in >> room >> cond >> mode;
    //     out << solve(room, cond, mode) << '\n';
    // }

    in >> room >> cond >> mode;
    out << solve(room, cond, mode) << '\n';

    return 0;
}
