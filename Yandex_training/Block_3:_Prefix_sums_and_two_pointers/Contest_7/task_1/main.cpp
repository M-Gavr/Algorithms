#include <fstream>
#include <cstdint>
#include <vector>
#include <unordered_map>

using namespace std;

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");

    int32_t n = 0;
    string s;

    in >> n >> s;


    vector<int32_t> prefix_sum(n + 1, 0);
    for (int32_t i = 0; i < n; i++) {
        prefix_sum[i + 1] = prefix_sum[i] + (s[i] == 'a' ? 1 : -1);
    }

    unordered_map<int32_t, int64_t> count;
    int64_t result = 0;

    for (int32_t i = 0; i <= n; i++) {
        result += count[prefix_sum[i]];
        count[prefix_sum[i]]++;
    }

    out << result << '\n';


    in.close();
    out.close();
    return 0;
}
