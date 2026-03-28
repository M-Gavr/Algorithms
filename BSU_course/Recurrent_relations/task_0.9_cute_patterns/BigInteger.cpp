#include "BigInteger.h"
#include <algorithm>
#include <iomanip>
#include <cmath>
#include <stdexcept>

// Удаляет ведущие нули
void BigInteger::removeLeadingZeros() {
    while (digits.size() > 1 && digits.back() == 0) {
        digits.pop_back();
    }
    if (digits.size() == 1 && digits[0] == 0) {
        isNegative = false;
    }
}

// Сравнение по модулю
int BigInteger::compareAbs(const BigInteger& other) const {
    if (digits.size() != other.digits.size()) {
        return digits.size() < other.digits.size() ? -1 : 1;
    }
    for (int i = digits.size() - 1; i >= 0; --i) {
        if (digits[i] != other.digits[i]) {
            return digits[i] < other.digits[i] ? -1 : 1;
        }
    }
    return 0;
}

// Конструкторы
BigInteger::BigInteger() : isNegative(false) {
    digits.push_back(0);
}

BigInteger::BigInteger(int64_t num) {
    isNegative = (num < 0);
    num = std::abs(num);
    if (num == 0) {
        digits.push_back(0);
    } else {
        while (num > 0) {
            digits.push_back(num % BASE);
            num /= BASE;
        }
    }
}

BigInteger::BigInteger(const std::string& str) {
    isNegative = false;
    int start = 0;
    if (str[0] == '-') {
        isNegative = true;
        start = 1;
    }
    for (int i = str.length() - 1; i >= start; --i) {
        digits.push_back(str[i] - '0');
    }
    removeLeadingZeros();
}

// Операторы сравнения
bool BigInteger::operator==(const BigInteger& other) const {
    return isNegative == other.isNegative && digits == other.digits;
}

bool BigInteger::operator!=(const BigInteger& other) const {
    return !(*this == other);
}

bool BigInteger::operator<(const BigInteger& other) const {
    if (isNegative != other.isNegative) {
        return isNegative;
    }
    if (isNegative) {
        return -(*this).compareAbs(other) > 0;
    }
    return compareAbs(other) < 0;
}

bool BigInteger::operator>(const BigInteger& other) const {
    return other < *this;
}

bool BigInteger::operator<=(const BigInteger& other) const {
    return !(other < *this);
}

bool BigInteger::operator>=(const BigInteger& other) const {
    return !(*this < other);
}

// Арифметические операции
BigInteger BigInteger::operator+(const BigInteger& other) const {
    if (isNegative == other.isNegative) {
        BigInteger result;
        result.isNegative = isNegative;
        result.digits.clear();

        int carry = 0;
        size_t maxSize = std::max(digits.size(), other.digits.size());

        for (size_t i = 0; i < maxSize || carry; ++i) {
            int sum = carry;
            if (i < digits.size()) sum += digits[i];
            if (i < other.digits.size()) sum += other.digits[i];

            result.digits.push_back(sum % BASE);
            carry = sum / BASE;
        }
        return result;
    }
    return *this - (-other);
}

BigInteger BigInteger::operator-(const BigInteger& other) const {
    if (isNegative != other.isNegative) {
        return *this + (-other);
    }

    if (isNegative) {
        return (-other) - (-*this);
    }

    if (*this < other) {
        return -(other - *this);
    }

    BigInteger result;
    result.isNegative = false;
    result.digits.clear();

    int borrow = 0;
    for (size_t i = 0; i < digits.size(); ++i) {
        int diff = digits[i] - borrow;
        if (i < other.digits.size()) {
            diff -= other.digits[i];
        }

        if (diff < 0) {
            diff += BASE;
            borrow = 1;
        } else {
            borrow = 0;
        }

        result.digits.push_back(diff);
    }

    result.removeLeadingZeros();
    return result;
}

BigInteger BigInteger::operator*(const BigInteger& other) const {
    BigInteger result;
    result.digits.resize(digits.size() + other.digits.size(), 0);

    for (size_t i = 0; i < digits.size(); ++i) {
        int carry = 0;
        for (size_t j = 0; j < other.digits.size() || carry; ++j) {
            long long product = result.digits[i + j] +
                               digits[i] * 1LL * (j < other.digits.size() ? other.digits[j] : 0) +
                               carry;
            result.digits[i + j] = product % BASE;
            carry = product / BASE;
        }
    }

    result.isNegative = isNegative ^ other.isNegative;
    result.removeLeadingZeros();
    return result;
}

BigInteger BigInteger::operator/(const BigInteger& other) const {
    BigInteger absThis = abs();
    BigInteger absOther = other.abs();

    if (absOther == BigInteger(0)) {
        throw std::runtime_error("Division by zero");
    }

    BigInteger result;
    result.digits.resize(absThis.digits.size(), 0);

    BigInteger current;
    for (int i = absThis.digits.size() - 1; i >= 0; --i) {
        current.digits.insert(current.digits.begin(), absThis.digits[i]);
        current.removeLeadingZeros();

        int x = 0;
        int l = 0, r = BASE - 1;
        while (l <= r) {
            int m = (l + r) / 2;
            BigInteger test = absOther * BigInteger(m);
            if (test <= current) {
                x = m;
                l = m + 1;
            } else {
                r = m - 1;
            }
        }

        result.digits[i] = x;
        current = current - absOther * BigInteger(x);
    }

    result.isNegative = isNegative ^ other.isNegative;
    result.removeLeadingZeros();
    return result;
}

BigInteger BigInteger::operator%(const BigInteger& other) const {
    BigInteger quotient = *this / other;
    return *this - quotient * other;
}

// Унарные операции
BigInteger BigInteger::operator-() const {
    BigInteger result = *this;
    if (result != BigInteger(0)) {
        result.isNegative = !result.isNegative;
    }
    return result;
}

BigInteger BigInteger::operator+() const {
    return *this;
}

// Префиксный инкремент/декремент
BigInteger& BigInteger::operator++() {
    *this = *this + BigInteger(1);
    return *this;
}

BigInteger& BigInteger::operator--() {
    *this = *this - BigInteger(1);
    return *this;
}

// Постфиксный инкремент/декремент
BigInteger BigInteger::operator++(int) {
    BigInteger temp = *this;
    ++(*this);
    return temp;
}

BigInteger BigInteger::operator--(int) {
    BigInteger temp = *this;
    --(*this);
    return temp;
}

// Составные операторы присваивания
BigInteger& BigInteger::operator+=(const BigInteger& other) {
    *this = *this + other;
    return *this;
}

BigInteger& BigInteger::operator-=(const BigInteger& other) {
    *this = *this - other;
    return *this;
}

BigInteger& BigInteger::operator*=(const BigInteger& other) {
    *this = *this * other;
    return *this;
}

BigInteger& BigInteger::operator/=(const BigInteger& other) {
    *this = *this / other;
    return *this;
}

BigInteger& BigInteger::operator%=(const BigInteger& other) {
    *this = *this % other;
    return *this;
}

// Вспомогательные функции
BigInteger BigInteger::abs() const {
    BigInteger result = *this;
    result.isNegative = false;
    return result;
}

std::string BigInteger::toString() const {
    std::string result;
    if (isNegative) {
        result += '-';
    }
    result += std::to_string(digits.back());
    for (int i = digits.size() - 2; i >= 0; --i) {
        result += std::to_string(digits[i]);
    }
    return result;
}

// Дружественные функции для ввода/вывода
std::ostream& operator<<(std::ostream& os, const BigInteger& num) {
    os << num.toString();
    return os;
}

std::istream& operator>>(std::istream& is, BigInteger& num) {
    std::string s;
    is >> s;
    num = BigInteger(s);
    return is;
}

// Дополнительные функции
BigInteger BigInteger::pow(int exponent) const {
    if (exponent == 0) return BigInteger(1);
    if (exponent == 1) return *this;

    BigInteger result = 1;
    BigInteger base = *this;

    while (exponent > 0) {
        if (exponent & 1) {
            result = result * base;
        }
        base = base * base;
        exponent >>= 1;
    }

    return result;
}

BigInteger BigInteger::factorial(int n) {
    BigInteger result(1);
    for (int i = 2; i <= n; ++i) {
        result = result * BigInteger(i);
    }
    return result;
}

BigInteger BigInteger::gcd(const BigInteger& a, const BigInteger& b) {
    BigInteger absA = a.abs();
    BigInteger absB = b.abs();

    while (absB != BigInteger(0)) {
        BigInteger temp = absB;
        absB = absA % absB;
        absA = temp;
    }
    return absA;
}

// Дополнительные операторы для работы с базовыми типами
BigInteger operator+(long long lhs, const BigInteger& rhs) {
    return BigInteger(lhs) + rhs;
}

BigInteger operator-(long long lhs, const BigInteger& rhs) {
    return BigInteger(lhs) - rhs;
}

BigInteger operator*(long long lhs, const BigInteger& rhs) {
    return BigInteger(lhs) * rhs;
}

BigInteger operator/(long long lhs, const BigInteger& rhs) {
    return BigInteger(lhs) / rhs;
}

bool operator<(long long lhs, const BigInteger& rhs) {
    return BigInteger(lhs) < rhs;
}

bool operator>(long long lhs, const BigInteger& rhs) {
    return BigInteger(lhs) > rhs;
}