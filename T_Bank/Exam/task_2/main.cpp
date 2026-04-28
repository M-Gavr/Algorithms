#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

int main() {
    string s;
    cin >> s;

    reverse(s.begin(), s.end());

    int32_t count_begin_a = 0;
    int32_t count_end_a = 0;

    for (size_t i = 0; i < s.size(); i++) {
        if (s[i] != 'a') {
            break;
        }
        count_begin_a++;
    }

    for (int32_t i = s.size() - 1; i >= 0; i--) {
        if (s[i] != 'a') {
            break;
        }
        count_end_a++;
    }

    if (count_end_a > count_begin_a) {
        cout << "No\n";
        return 0;
    }

    while (count_end_a < count_begin_a) {
        s.push_back('a');
        count_end_a++;
    }

    for (int32_t i = 0; 2 * i < s.size(); i++) {
        if (s[i] != s[s.size() - 1 - i]) {
            cout << "No\n";
            return 0;
        }
    }

    cout << "Yes" << '\n';

    return 0;
}