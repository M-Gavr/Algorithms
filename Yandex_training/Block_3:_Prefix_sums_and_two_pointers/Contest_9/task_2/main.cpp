#include <fstream>
#include <cstdint>
#include <vector>
#include <algorithm>
#include <climits>

int main() {
    std::ifstream in("input.txt");
    std::ofstream out("output.txt");

    int32_t N = 0;
    int32_t K = 0;
    in >> N >> K;

    std::vector<int64_t> a(N);
    for (int32_t i = 0; i < N; i++) {
        in >> a[i];
    }

    std::vector<int64_t> min_pref(K, LLONG_MAX);

    int64_t pref = 0;
    int64_t ans = 0;

    int64_t best1_val = 0;
    int32_t best1_rem = 0;
    int64_t best2_val = LLONG_MAX;
    int32_t best2_rem = -1;

    min_pref[0] = 0;

    for (int32_t i = 0; i < N; i++) {
        pref += a[i];
        int32_t const rem = ((pref % K) + K) % K;

        int64_t best = LLONG_MAX;
        if (best1_rem != rem) {
            best = best1_val;
        } else if (best2_rem != -1) {
            best = best2_val;
        }

        if (best != LLONG_MAX) {
            ans = std::max(pref - best, ans);
        }

        if (pref < min_pref[rem]) {
            min_pref[rem] = pref;

            if (pref < best1_val) {
                if (best1_rem != rem) {
                    best2_val = best1_val;
                    best2_rem = best1_rem;
                }
                best1_val = pref;
                best1_rem = rem;
            } else if (pref < best2_val && best1_rem != rem) {
                best2_val = pref;
                best2_rem = rem;
            }
        }
    }

    if (ans < 0) {
        ans = 0;
    }
    out << ans << '\n';

    in.close();
    out.close();
    return 0;
}
