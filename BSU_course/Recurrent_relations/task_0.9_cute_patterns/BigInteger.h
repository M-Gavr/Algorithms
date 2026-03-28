#ifndef BIGINTEGER_H
#define BIGINTEGER_H

#include <vector>
#include <string>
#include <iostream>

class BigInteger {
private:
    static const int BASE = 10;           // Основание системы счисления
    static const int BASE_DIGITS = 1;      // Количество десятичных цифр в BASE
    
    std::vector<short> digits;               // Цифры числа (в обратном порядке)
    bool isNegative;                        // Знак числа

    // Удаляет ведущие нули
    void removeLeadingZeros();

    // Сравнение по модулю (предполагается, что оба числа положительные)
    int compareAbs(const BigInteger& other) const;

public:
    // Конструкторы
    BigInteger();
    BigInteger(int64_t num);
    BigInteger(const std::string& str);
    
    // Копирование и присваивание
    BigInteger(const BigInteger& other) = default;
    BigInteger& operator=(const BigInteger& other) = default;

    // Операторы сравнения
    bool operator==(const BigInteger& other) const;
    bool operator!=(const BigInteger& other) const;
    bool operator<(const BigInteger& other) const;
    bool operator>(const BigInteger& other) const;
    bool operator<=(const BigInteger& other) const;
    bool operator>=(const BigInteger& other) const;

    // Арифметические операции
    BigInteger operator+(const BigInteger& other) const;
    BigInteger operator-(const BigInteger& other) const;
    BigInteger operator*(const BigInteger& other) const;
    BigInteger operator/(const BigInteger& other) const;
    BigInteger operator%(const BigInteger& other) const;

    // Унарные операции
    BigInteger operator-() const;
    BigInteger operator+() const;

    // Префиксный инкремент/декремент
    BigInteger& operator++();
    BigInteger& operator--();

    // Постфиксный инкремент/декремент
    BigInteger operator++(int32_t);
    BigInteger operator--(int32_t);

    // Составные операторы присваивания
    BigInteger& operator+=(const BigInteger& other);
    BigInteger& operator-=(const BigInteger& other);
    BigInteger& operator*=(const BigInteger& other);
    BigInteger& operator/=(const BigInteger& other);
    BigInteger& operator%=(const BigInteger& other);

    // Вспомогательные функции
    BigInteger abs() const;
    std::string toString() const;

    // Дружественные функции для ввода/вывода
    friend std::ostream& operator<<(std::ostream& os, const BigInteger& num);
    friend std::istream& operator>>(std::istream& is, BigInteger& num);

    // Дополнительные функции
    BigInteger pow(int32_t exponent) const;
    static BigInteger factorial(int32_t n);
    static BigInteger gcd(const BigInteger& a, const BigInteger& b);
};

// Дополнительные операторы для работы с базовыми типами
BigInteger operator+(int64_t lhs, const BigInteger& rhs);
BigInteger operator-(int64_t lhs, const BigInteger& rhs);
BigInteger operator*(int64_t lhs, const BigInteger& rhs);
BigInteger operator/(int64_t lhs, const BigInteger& rhs);
bool operator<(int64_t lhs, const BigInteger& rhs);
bool operator>(int64_t lhs, const BigInteger& rhs);

#endif // BIGINTEGER_H