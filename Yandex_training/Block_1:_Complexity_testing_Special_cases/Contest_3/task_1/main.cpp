#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");

    string str;
    getline(in, str);

    string result = "";
    int32_t i = 0;
    int32_t n = str.length();

    while (i < n) {
        if (str[i] == ' ') {
            ++i;
            continue;
        }

        int32_t pre = 0;
        while (i < n && str[i] == '\'') {
            ++pre;
            ++i;
        }

        int32_t word_start = i;
        while (i < n && str[i] != ' ' && str[i] != '\'') {
            ++i;
        }
        string word = str.substr(word_start, i - word_start);

        int32_t post = 0;
        while (i < n && str[i] == '\'') {
            ++post;
            ++i;
        }

        if (pre > 0 || post > 0) {
            word = word.substr(pre, word.length() - pre - post);
        }

        result += word;
    }

    out << result << '\n';

    in.close();
    out.close();
    return 0;
}
