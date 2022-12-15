#ifndef UNTITLED1_BIGINT_H
#define UNTITLED1_BIGINT_H

#endif //UNTITLED1_BIGINT_H
#include <iostream>
#include <vector>
using namespace std;

class BigInt {
private:
    static int const base_ = 1000000000;

    vector<int> digits_;

    bool is_negative_;

    void _remove_leading_zeros();
    BigInt& dif(const BigInt& num);
    BigInt& sum(const BigInt& num);
public:
    BigInt();
    explicit BigInt(int);
    explicit BigInt(std::string str); // бросать исключение std::invalid_argument при ошибке
    BigInt(const BigInt&);
    ~BigInt();

    BigInt& operator=(const BigInt& vec);  //возможно присваивание самому себе!

    BigInt operator~() const; //инверсия (побитовая операция)

    BigInt& operator++();
    const BigInt operator++(int);
    BigInt& operator--();
    const BigInt operator--(int);

    BigInt& operator+=(const BigInt& vec);
    BigInt& operator*=(const BigInt& vec);
    BigInt& operator-=(const BigInt& vec);
    BigInt& operator/=(const BigInt& vec);
    BigInt& operator^=(const BigInt& vec);
    BigInt& operator%=(const BigInt& vec);
    BigInt& operator&=(const BigInt& vec);
    BigInt& operator|=(const BigInt& vec);

    BigInt operator+() const;  // unary +, умножает на 1: const BigInt res = -res2; просто поменять знау  укакого т о аргумента, = +res2;
    BigInt operator-() const;  // unary -

    bool operator==(const BigInt&) const;
    bool operator!=(const BigInt&) const;
    bool operator<(const BigInt&) const;
    bool operator>(const BigInt&) const;
    bool operator<=(const BigInt&) const;
    bool operator>=(const BigInt&) const;

    operator int() const;
    explicit operator std::string() const ;

    size_t size() const;  // size in bytes

};
BigInt operator+(const BigInt& vec1, const BigInt& vec2);
BigInt operator-(const BigInt& vec1, const BigInt& vec2);
BigInt operator*(const BigInt& vec1, const BigInt& vec2);
BigInt operator/(const BigInt& vec1, const BigInt& vec2);
BigInt operator^(const BigInt& vec1, const BigInt& vec2);
BigInt operator%(const BigInt& vec1, const BigInt& vec2);
BigInt operator&(const BigInt& vec1, const BigInt& vec2);
BigInt operator|(const BigInt& vec1, const BigInt& vec2);


std::ostream& operator<<(std::ostream& o, const BigInt& i);
