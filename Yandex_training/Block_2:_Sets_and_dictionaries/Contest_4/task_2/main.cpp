#include <fstream>
#include <map>
#include <vector>
#include <string>
#include <cstdint>

using namespace std;

bool canPair(const vector<string>& words, int k, int len) {
    if (k == 0) return true;

    map<string, int32_t> prefixCount;

    for (const string& word : words) {
        string prefix = word.substr(0, k);
        prefixCount[prefix]++;
    }

    for (const auto& p : prefixCount) {
        if ((p.second & 1) == 1) {
            return false;
        }
    }

    return true;
}

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");

    int32_t n = 0;
    in >> n;

    vector<string> words(n);

    for (int32_t i = 0; i < n; i++) {
        in >> words[i];
    }

    int32_t len = words[0].length();

    int32_t left = 0, right = len;
    int32_t answer = 0;

    while (left <= right) {
        int32_t mid = left + (right - left) / 2;

        if (canPair(words, mid, len)) {
            answer = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    out << answer << endl;

    in.close();
    out.close();
    return 0;
}
