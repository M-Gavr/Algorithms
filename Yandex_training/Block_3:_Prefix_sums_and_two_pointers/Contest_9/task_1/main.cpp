#include <cstdint>
#include <fstream>
#include <map>
#include <string>
#include <cmath>

using namespace std;

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");

    string s;
    in >> s;

    int32_t sum = 0;
    int32_t bad_grade = 0;
    int32_t n = s.length();

    for (char c : s) {
        int32_t val = c - 'A';
        sum += val;
        if (val > bad_grade) {
            bad_grade = val;
        }
    }

    double avg = (double)sum / n;
    int32_t rounded;

    if (avg - floor(avg) == 0.5) {
        rounded = (int32_t)floor(avg);
    } else {
        rounded = (int32_t)round(avg);
    }

    rounded = max(rounded, bad_grade - 1);

    out << char('A' + rounded) << endl;

    in.close();
    out.close();
    return 0;
}
