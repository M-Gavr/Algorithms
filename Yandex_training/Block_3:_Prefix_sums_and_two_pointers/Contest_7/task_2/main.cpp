#include <cstdint>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");

    int32_t n = 0;
    in >> n;

    vector<int32_t> p(n, 0);
    for (int32_t i = 0; i < n; i++) {
        in >> p[i];
    }

    if (n == 0) {
        out << 0 << '\n';
        return 0;
    }

    unordered_map<int32_t, int32_t> last_pos;
    int32_t max_len = 0;
    int32_t left = 0;
    int32_t distinct_count = 0;

    for (int32_t right = 0; right < n; right++) {
        int32_t type = p[right];

        if (last_pos.find(type) == last_pos.end()) {
            distinct_count++;
        }

        last_pos[type] = right;

        while (distinct_count > 2) {
            int32_t left_type = p[left];
            if (last_pos[left_type] == left) {
                last_pos.erase(left_type);
                distinct_count--;
            }
            left++;
        }

        if (distinct_count == 2) {
            max_len = max(max_len, right - left + 1);
        }
    }

    out << max_len << '\n';

    in.close();
    out.close();
    return 0;
}