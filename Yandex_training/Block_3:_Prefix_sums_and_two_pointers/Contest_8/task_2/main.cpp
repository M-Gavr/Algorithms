#include <fstream>
#include <map>
#include <cstdint>
#include <vector>

using namespace std;

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");

    ios::sync_with_stdio(false);
    in.tie(nullptr);

    int32_t cases = 0;
    in >> cases;

    while (cases--) {
        int32_t n = 0;
        int64_t d = 0;
        in >> n >> d;

        vector<int64_t> t(n), k(n);
        for (int32_t i = 0; i < n; i++) {
            in >> t[i] >> k[i];
        }

        vector<int64_t> prefix(n + 1, 0);
        for (int32_t i = 0; i < n; i++) {
            prefix[i + 1] = prefix[i] + k[i];
        }

        vector<int64_t> max_diff(n + 1, -1e18);
        for (int32_t i = n - 1; i >= 0; i--) {
            max_diff[i] = max(prefix[i] - t[i], max_diff[i + 1]);
        }

        int32_t pos = n + 1;
        for (int32_t i = 0; i <= n; i++) {
            if (max_diff[i] + d <= 0) {
                pos = i + 1;
                break;
            }
        }

        out << pos << '\n';
    }

    in.close();
    out.close();
    return 0;
}
