#include <cstdint>
#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

struct HashPair {
    int32_t h1;
    int32_t h2;

    bool operator==(const HashPair& other) const {
        return h1 == other.h1 && h2 == other.h2;
    }
};

struct HashPairHasher {
    size_t operator()(const HashPair& v) const {
        return (static_cast<size_t>(static_cast<uint32_t>(v.h1)) << 32U) ^
               static_cast<uint32_t>(v.h2);
    }
};

class DoubleRollingHash {
   public:
    explicit DoubleRollingHash(const string& s) : n_(static_cast<int32_t>(s.size())) {
        pref1_.assign(n_ + 1, 0);
        pref2_.assign(n_ + 1, 0);
        for (int32_t i = 0; i < n_; ++i) {
            pref1_[i + 1] = (static_cast<int64_t>(pref1_[i]) * BASE1 + s[i]) % MOD1;
            pref2_[i + 1] = (static_cast<int64_t>(pref2_[i]) * BASE2 + s[i]) % MOD2;
        }
    }

    static void initPowers(const int32_t maxLen) {
        pow1_.assign(maxLen + 1, 1);
        pow2_.assign(maxLen + 1, 1);
        for (int32_t i = 1; i <= maxLen; ++i) {
            pow1_[i] = (static_cast<int64_t>(pow1_[i - 1]) * BASE1) % MOD1;
            pow2_[i] = (static_cast<int64_t>(pow2_[i - 1]) * BASE2) % MOD2;
        }
    }

    HashPair getHash(const int32_t l, const int32_t r) const {
        int64_t x1 = pref1_[r] - (static_cast<int64_t>(pref1_[l]) * pow1_[r - l]) % MOD1;
        if (x1 < 0) {
            x1 += MOD1;
        }
        int64_t x2 = pref2_[r] - (static_cast<int64_t>(pref2_[l]) * pow2_[r - l]) % MOD2;
        if (x2 < 0) {
            x2 += MOD2;
        }
        return {static_cast<int32_t>(x1), static_cast<int32_t>(x2)};
    }

   private:
    static constexpr int32_t MOD1 = 1'000'000'007;
    static constexpr int32_t MOD2 = 1'000'000'009;
    static constexpr int32_t BASE1 = 911'382'323;
    static constexpr int32_t BASE2 = 972'663'749;

    int32_t n_;
    vector<int32_t> pref1_;
    vector<int32_t> pref2_;

    static vector<int32_t> pow1_;
    static vector<int32_t> pow2_;
};

vector<int32_t> DoubleRollingHash::pow1_;
vector<int32_t> DoubleRollingHash::pow2_;

struct CheckResult {
    bool ok = false;
    vector<int32_t> starts;
};

static CheckResult canAchieveLcp(
    const int32_t len, const int32_t n, const int32_t m, const vector<DoubleRollingHash>& hashes) {
    CheckResult result;
    result.starts.assign(n, 0);

    if (len == 0) {
        result.ok = true;
        return result;
    }

    unordered_map<HashPair, int32_t, HashPairHasher> common;
    common.reserve(static_cast<size_t>(m) * 2);

    for (int32_t st = 0; st < m; ++st) {
        HashPair h = hashes[0].getHash(st, st + len);
        common.emplace(h, st);
    }

    for (int32_t i = 1; i < n && !common.empty(); ++i) {
        unordered_map<HashPair, int32_t, HashPairHasher> current;
        current.reserve(static_cast<size_t>(m) * 2);
        for (int32_t st = 0; st < m; ++st) {
            HashPair h = hashes[i].getHash(st, st + len);
            if (current.find(h) == current.end()) {
                current.emplace(h, st);
            }
        }

        unordered_map<HashPair, int32_t, HashPairHasher> nextCommon;
        nextCommon.reserve(common.size());
        for (const auto& [h, stPrev] : common) {
            auto it = current.find(h);
            if (it != current.end()) {
                nextCommon.emplace(h, stPrev);
            }
        }
        common.swap(nextCommon);
    }

    if (common.empty()) {
        return result;
    }

    const HashPair chosen = common.begin()->first;
    result.ok = true;
    result.starts[0] = common.begin()->second;

    for (int32_t i = 1; i < n; ++i) {
        int32_t found = -1;
        for (int32_t st = 0; st < m; ++st) {
            if (hashes[i].getHash(st, st + len) == chosen) {
                found = st;
                break;
            }
        }
        result.starts[i] = found;
    }

    return result;
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int32_t n = 0;
    int32_t m = 0;
    cin >> n >> m;
    vector<string> s(n);
    for (int32_t i = 0; i < n; ++i) {
        cin >> s[i];
    }

    vector<string> doubled(n);
    for (int32_t i = 0; i < n; ++i) {
        doubled[i] = s[i] + s[i];
    }

    DoubleRollingHash::initPowers(2 * m);
    vector<DoubleRollingHash> hashes;
    hashes.reserve(n);
    for (int32_t i = 0; i < n; ++i) {
        hashes.emplace_back(doubled[i]);
    }

    int32_t left = 0;
    int32_t right = m;
    int32_t bestLen = 0;
    vector<int32_t> bestStarts(n, 0);

    while (left <= right) {
        const int32_t mid = left + (right - left) / 2;
        auto [ok, starts] = canAchieveLcp(mid, n, m, hashes);
        if (ok) {
            bestLen = mid;
            bestStarts = starts;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    CheckResult finalCheck = canAchieveLcp(bestLen, n, m, hashes);
    bestStarts = finalCheck.starts;

    cout << bestLen << '\n';
    for (int32_t i = 0; i < n; ++i) {
        cout << (bestStarts[i] + 1) << '\n';
    }

    return 0;
}
