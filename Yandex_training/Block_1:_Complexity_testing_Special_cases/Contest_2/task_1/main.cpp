#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");

    int32_t n = 0;
    string s;

    in >> n >> s;

    int32_t max_len = 0;
    int32_t current_len = 0;
    char last_char = 0;

    for (int32_t i = 0; i < n; ++i) {
        if (s[i] == 'a' || s[i] == 'h') {
            if (current_len == 0) {
                current_len = 1;
                last_char = s[i];
            } else if ((s[i] == 'a' && last_char == 'h') ||
                       (s[i] == 'h' && last_char == 'a')) {
                current_len++;
                last_char = s[i];
            } else {
                current_len = 1;
                last_char = s[i];
            }
            max_len = max(max_len, current_len);
        } else {
            current_len = 0;
            last_char = 0;
        }
    }

    out << max_len << endl;

    in.close();
    out.close();
    return 0;
}
