#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    string s, result = "";
    cin >> s;
    reverse(s.begin(), s.end());
    char letter;
    for (int32_t i = 0; i < s.size(); ++i) {
        if (s[i] == '#') {
            letter = (s[i + 1] - '0') + (s[i + 2] - '0') * 10;
            letter += 96;
            i += 2;
        }
        else {
            letter = (s[i] - '0') + 96;
        }
        result += letter;
    }
    reverse(result.begin(), result.end());
    cout << result << endl;

    return 0;
}
