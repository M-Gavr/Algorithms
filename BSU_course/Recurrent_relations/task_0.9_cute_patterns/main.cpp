#include <fstream>
#include <vector>
#include <cstdint>

using namespace std;

class BigInteger {
private:
    static const int BASE = 1'000'000'000;
    static const int BASE_DIGITS = 9;
    vector<uint32_t> digits;
    bool isNegative;

public:
    BigInteger() : isNegative(false) {
        digits.push_back(0);
    }

    BigInteger(uint64_t num) : isNegative(false) {
        if (num == 0) {
            digits.push_back(0);
        }
        else {
            while (num > 0) {
                digits.push_back(num % BASE);
                num /= BASE;
            }
        }
    }

    BigInteger(const BigInteger& other) = default;
    BigInteger& operator=(const BigInteger& other) = default;

    BigInteger& operator+=(const BigInteger& other) {
        if (other.digits.size() == 1 && other.digits[0] == 0) return *this;

        uint64_t carry = 0;
        size_t maxSize = max(digits.size(), other.digits.size());

        if (digits.size() < maxSize) {
            digits.resize(maxSize, 0);
        }

        for (size_t i = 0; i < maxSize; ++i) {
            uint64_t sum = digits[i] + carry;
            if (i < other.digits.size()) {
                sum += other.digits[i];
            }

            if (sum >= BASE) {
                digits[i] = sum - BASE;
                carry = 1;
            }
            else {
                digits[i] = sum;
                carry = 0;
            }
        }

        if (carry != 0) {
            digits.push_back(1);
        }

        return *this;
    }

    BigInteger operator+(const BigInteger& other) const {
        BigInteger result = *this;
        result += other;
        return result;
    }

    /*
    BigInteger& multiplyByInt(uint32_t multiplier) {
        if (multiplier == 0) {
            digits.clear();
            digits.push_back(0);
            return *this;
        }

        uint64_t carry = 0;
        for (size_t i = 0; i < digits.size(); ++i) {
            uint64_t product = (uint64_t)digits[i] * multiplier + carry;
            digits[i] = product % BASE;
            carry = product / BASE;
        }

        if (carry) {
            digits.push_back(carry);
        }

        return *this;
    }
    */

    string toString() const {
        string result;
        if (isNegative && !(digits.size() == 1 && digits[0] == 0)) {
            result += '-';
        }

        result += to_string(digits.back());

        char buffer[16];
        for (int i = digits.size() - 2; i >= 0; --i) {
            snprintf(buffer, sizeof(buffer), "%09d", digits[i]);
            result += buffer;
        }
        return result;
    }

    friend ostream& operator<<(ostream& os, const BigInteger& num) {
        os << num.toString();
        return os;
    }
};

int main() {
    std::ifstream in("in.txt");
    std::ofstream out("out.txt");

    int32_t m = 0, n = 0;
    in >> m >> n;

    int32_t size = 1 << m;

    /*
    vector<vector<short>> tiles(m, vector<short>(size, 0));
    for (int32_t i = 0; i < m; ++i) {
        for (int32_t j = 0; j < size; ++j) {
            tiles[i][j] = (j >> i) & 1;
        }
    }

    int32_t count = 0;
    vector<vector<short>> table(size, vector<short>(size, 1));
    for (int32_t i = 0; i < size; ++i) {
        for (int32_t j = i; j < size; ++j) {
            for (int32_t k = 0; k < m - 1; ++k) {
                count = tiles[k][i] + tiles[k + 1][i] + tiles[k][j] + tiles[k + 1][j];
                if (count == 4 || count == 0) {
                    table[i][j] = 0;
                    table[j][i] = 0;
                    break;
                }
            }
        }
    }

    vector<vector<int32_t>> transitions(size);
    for (int32_t i = 0; i < size; ++i) {
        transitions[i].reserve(size);
        for (int32_t j = 0; j < size; ++j) {
            if (table[i][j] != 0) {
                transitions[i].push_back(j);
            }
        }
    }
    */

    vector<uint32_t> pairMasks(size, 0);
    for (int32_t mask = 0; mask < size; ++mask) {
        uint32_t pm = 0;
        for (int32_t k = 0; k < m - 1; ++k) {
            pm |= ((mask >> k) & 3) << (k * 2);
        }
        pairMasks[mask] = pm;
    }

    vector<vector<int32_t>> transitions(size);
    for (int32_t mask1 = 0; mask1 < size; ++mask1) {
        uint32_t pm1 = pairMasks[mask1];
        vector<int32_t> buffer;
        buffer.reserve(size);

        for (int mask2 = 0; mask2 < size; ++mask2) {
            uint32_t pm2 = pairMasks[mask2];
            bool valid = true;

            for (int32_t k = 0; k < m - 1; ++k) {
                int32_t p1 = (pm1 >> (k * 2)) & 3;
                int32_t p2 = (pm2 >> (k * 2)) & 3;
                if (p1 == p2 && (p1 == 0 || p1 == 3)) {
                    valid = false;
                    break;
                }
            }

            if (valid) {
                buffer.push_back(mask2);
            }
        }
        transitions[mask1] = move(buffer);
    }

    /*
    vector<vector<BigInteger>> results(size, vector<BigInteger>(n, 0));
    for (int32_t i = 0; i < size; ++i) {
        results[i][0] = 1;
    }
    BigInteger result = 0;
    for (int32_t i = 1; i < n; ++i) {
        for (int32_t j = 0; j < size; ++j) {
            result = 0;
            for (int32_t k = 0; k < size; ++k) {
                if (table[j][k] != 0) {
                    result = result + results[k][i - 1];
                }
            }
            results[j][i] = result;
        }
    }
    */

    vector<vector<BigInteger>> results(n, vector<BigInteger>(size, BigInteger(0)));
    for (int32_t i = 0; i < size; ++i) {
        results[0][i] = BigInteger(1);
    }
    for (int32_t i = 1; i < n; ++i) {
        const auto& prevRow = results[i - 1];
        auto& currRow = results[i];
        for (int32_t j = 0; j < size; ++j) {
            BigInteger result = BigInteger(0);
            for (int32_t k : transitions[j]) {
                result += prevRow[k];
            }
            currRow[j] = move(result);
        }
    }

    BigInteger result = BigInteger(0);
    const auto& lastRow = results[n - 1];
    for (const auto& k : lastRow) {
        result += k;
    }

    /*
    out << m << ' ' << n << endl;
    out << endl;
    for (int32_t i = 0; i < m; ++i) {
        for (int32_t j = 0; j < size; ++j) {
            out << tiles[i][j] << ' ';
        }
        out << endl;
    }
    out << endl;
    for (int32_t i = 0; i < size; ++i) {
        for (int32_t j = 0; j < size; ++j) {
            out << table[i][j] << ' ';
        }
        out << endl;
    }
    out << endl;
    for (int32_t i = 0; i < size; ++i) {
        for (int32_t j = 0; j < n; ++j) {
            out << results[i][j] << ' ';
        }
        out << endl;
    }
    out << endl;
    */

    out << result << endl;

    return 0;
}
