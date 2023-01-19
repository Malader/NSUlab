#include "Bigint.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;
using namespace ns;
//                      блок с 13 по 21
void BigInt::_remove_leading_zeros() {
    while (this->digits_.size() > 1 && this->digits_.back() == 0) {
        this->digits_.pop_back();
    }
    if (this->digits_.size() == 1 && this->digits_[0] == 0) {
        this->is_negative_ = false; //this code is needed so that we don't have a negative zero

    }
}

BigInt::BigInt() : is_negative_(false) {
    this->digits_.push_back(0);
}

BigInt::BigInt(int number) {
    long long temp = number;
    if (abs(temp) >= base_) {
        this->digits_.push_back(abs(temp) % base_);
        this->digits_.push_back(abs(temp) / base_);
    } else {
        this->digits_.push_back(abs(temp));
    }
    is_negative_ = temp < 0;
}

BigInt::BigInt(std::string str) {
    if(str[0] == '-' && str[1] == '0'){
        is_negative_ = false;
        this->digits_.push_back(atoi(str.c_str()));
        return;
    }

    if (str.length() == 0) {
        this->is_negative_ = false;
    } else {
        if (str[0] == '-') {
            str = str.substr(1);
            this->is_negative_ = true;
        } else {
            this->is_negative_ = false;
        }

        for(char element: str){
            if(element < '0' || element > '9'){
                throw std::invalid_argument("Bad input string");
            }
        }

        for (long long i = str.length(); i > 0; i -= 9) {
            if (i < 9) {
                this->digits_.push_back(atoi(str.substr(0, i).c_str()));
            } else {
                this->digits_.push_back(atoi(str.substr(i - 9, 9).c_str()));
            }
        }
    }
}

BigInt::BigInt(const BigInt &number) : digits_(number.digits_), is_negative_(number.is_negative_) {
}

BigInt::~BigInt() {
}

BigInt &BigInt::operator=(const BigInt &number) {
    this->digits_ = number.digits_;
    this->is_negative_ = number.is_negative_;
    return *this;
}
//                          блок с 25 по 28

BigInt &BigInt::operator+=(const BigInt &number) {
    if(number.digits_[0] == 0 && number.is_negative_){
        return *this;
    }
    if (this->is_negative_) {
        if (number.is_negative_) {
            *this = -*this;
            BigInt tmp = -number;
            *this += tmp;
            *this = -*this;
            return *this;
        }
        *this = -*this;
        *this -= number;
        if(*this == 0){
            return *this;
        }
        *this = -*this;

        return *this;
    } else if (number.is_negative_) {
        BigInt tmp = -number;
        *this -= tmp;
        return *this;
    }

    int carry = 0;
    for (size_t i = 0; i < max(this->digits_.size(), number.digits_.size()) || carry != 0; ++i) {
        if (i == this->digits_.size()) {
            this->digits_.push_back(0);
        }
        this->digits_[i] += carry + (i < number.digits_.size() ? number.digits_[i] : 0);
        carry = this->digits_[i] >= BigInt::base_;
        if (carry != 0) {
            this->digits_[i] -= BigInt::base_;
        }
    }

    return *this;
}

BigInt &BigInt::operator++() {
    return (*this += BigInt(1));
}

BigInt const BigInt::operator++(int) {
    BigInt tmp = *this;
    ++*this;
    return tmp;
}

BigInt &BigInt::operator--() {
    return (*this -= BigInt(1));
}

BigInt const BigInt::operator--(int) {
    BigInt tmp = *this;
    --*this;
    return tmp;
}
//                          блок с 30 по 37

BigInt operator+(const BigInt &vec1, const BigInt &vec2) {
    BigInt tmp = vec1;
    tmp += vec2;
    return tmp;
}

BigInt &BigInt::operator*=(const BigInt &number) {
    BigInt result;
    result.digits_.resize(this->digits_.size() + number.digits_.size());
    for (size_t i = 0; i < this->digits_.size(); ++i) {
        int carry = 0;
        for (size_t j = 0; j < number.digits_.size() || carry != 0; ++j) {
            long long cur = result.digits_[i + j] +
                            this->digits_[i] * 1LL * (j < number.digits_.size() ? number.digits_[j] : 0) + carry;
            result.digits_[i + j] = static_cast<int>(cur % BigInt::base_);
            carry = static_cast<int>(cur / BigInt::base_);
        }
    }

    result.is_negative_ = this->is_negative_ != number.is_negative_;
    result._remove_leading_zeros();

    *this = result;
    return *this;
}

BigInt operator*(const BigInt &vec1, const BigInt &vec2) {
    BigInt tmp = vec1;
    tmp *= vec2;
    return tmp;
}

BigInt& BigInt::sum(const BigInt& num)
{
    int overLimit = 0;

    for (int i = 0; i < std::max(this->digits_.size(), num.digits_.size()) || overLimit != 0; ++i)
    {
        if (i == this->digits_.size())
        {
            this->digits_.push_back(0);
        }

        this->digits_[i] += overLimit + (i < num.digits_.size() ? num.digits_[i] : 0);
        overLimit = this->digits_[i] >= base_;

        if (overLimit != 0)
        {
            this->digits_[i] -= base_;
        }
    }

    return *this;
}

BigInt& BigInt::dif(const BigInt& num){
    int carry = 0;
    for (size_t i = 0; i < num.digits_.size() || carry != 0; ++i) {
        this->digits_[i] -= carry + (i < num.digits_.size() ? num.digits_[i] : 0);
        carry = this->digits_[i] < 0;
        if (carry != 0) {
            this->digits_[i] += BigInt::base_;
        }
    }

    this->_remove_leading_zeros();
    return *this;

}

BigInt &BigInt::operator-=(const BigInt &number) {
    if(digits_[0] == 0 && number.digits_[0] == 0){
        return *this;
    }

    BigInt copyNum(number);

    if(is_negative_ != copyNum.is_negative_){
        if(!is_negative_){
            copyNum.is_negative_ = false;

            return *this = sum(copyNum);
        }
        else{
            is_negative_ = false;

            return *this = -sum(copyNum);
        }
    }

    if(!is_negative_){
        return (*this < copyNum ? *this = -copyNum.dif(*this) : *this = dif(copyNum));
    }
    else{
        return (*this < copyNum ? *this = dif(copyNum) : *this = copyNum.dif(*this));
    }
}

BigInt operator-(const BigInt &vec1, const BigInt &vec2) {
    BigInt tmp = vec1;
    tmp -= vec2;
    return tmp;
}

BigInt &BigInt::operator/=(const BigInt &vec) {
    if(vec.digits_.back() == 0){
        throw std::invalid_argument("Division by zero");
    }

    string str = static_cast<string>(*this);
    string str2 = static_cast<string>(vec);

    if(str.size() < str2.size()){
        *this = BigInt(0);
        return(*this);
    }

    if(str[0] == '-'){
        str.erase(0,1);
    }
    if(str2[0] == '-'){
        str2.erase(0,1);
    }

    bool isNegativeRes = is_negative_ != vec.is_negative_;
    is_negative_ = true;

    BigInt num = vec;
    num.is_negative_ = false;

    string ans;
    string dividend;
    string divider = str2;
    int zeroesCounter = 0;

    for(char c:str){
        dividend += c;

        if(dividend.size() < divider.size()){
            ++zeroesCounter;
            continue;
        }

        int counter = 0;
        string prevDivider = "0";

        while(true){

            if(dividend.size() < divider.size()){
                break;
            }

            if(dividend.size() == divider.size() && dividend < divider){
                break;
            }

            ++counter;
            BigInt divBI(divider);
            divBI += num;
            prevDivider = divider;
            divider = static_cast<string>(divBI);
        }

        BigInt dif(0);
        BigInt dividendBI(dividend);
        BigInt prevDividerBI(prevDivider);
        dif = (dividendBI - prevDividerBI);

        if(dif.digits_.back() != 0){
            dividend = static_cast<string>(dif);
        }else{
            dividend = "";
        }

        divider = str2;
        for(size_t i = 0; i < zeroesCounter; ++i){
            ans += "0";
        }
        zeroesCounter = 0;
        ans += std::to_string(counter);
    }

    *this = BigInt(ans);
    _remove_leading_zeros();

    if(isNegativeRes){
        is_negative_ = true;
    }

    return *this;
}

BigInt operator/(const BigInt &vec1, const BigInt &vec2) {
    BigInt tmp = vec1;
    tmp /= vec2;
    return tmp;
}

BigInt &BigInt::operator^=(const BigInt &value) {
    for(int i = 0; i < std::min(value.digits_.size(), digits_.size()); ++i){
        digits_[i] = digits_[i] ^ value.digits_[i];
    }

    is_negative_ = value.is_negative_ != is_negative_;
    _remove_leading_zeros();

    return *this;
}

BigInt &BigInt::operator&=(const BigInt &vec) {
    BigInt copyNum = vec;

    int countIterations = 0;
    for (int i = 0; i < max(digits_.size(), copyNum.digits_.size()); ++i) {
        if (is_negative_) {
            digits_[i] *= -1;
        }
        if (copyNum.is_negative_) {
            copyNum.digits_[i] *= -1;
        }

        digits_[i] = digits_[i] & copyNum.digits_[i];

        if(digits_[i] < 0){
            digits_[i] *= -1;
        }
        countIterations = i;
    }
    if(countIterations < max(digits_.size(), copyNum.digits_.size())){
        for(int i = countIterations + 1; i <= max(digits_.size(), copyNum.digits_.size()); ++i){
            digits_[i] = 0;
        }
    }
    is_negative_ = copyNum.is_negative_ & is_negative_;

    _remove_leading_zeros();

    return *this;
}

BigInt operator&(const BigInt &vec1, const BigInt &vec2) {
    BigInt tmp = vec1;
    tmp &= vec2;
    return tmp;
}

BigInt &BigInt::operator|=(const BigInt &vec) {
    BigInt copyNum = vec;
    for (int i = 0; i < min(digits_.size(), copyNum.digits_.size()); ++i) {
        if (is_negative_) {
            digits_[i] *= -1;
        }
        if (copyNum.is_negative_) {
            copyNum.digits_[i] *= -1;
        }

        digits_[i] = digits_[i] | copyNum.digits_[i];

        if(digits_[i] < 0){
            digits_[i] *= -1;
        }
    }

    is_negative_ = is_negative_ || copyNum.is_negative_;
    _remove_leading_zeros();

    return *this;
}

BigInt operator|(const BigInt &vec1, const BigInt &vec2) {
    BigInt tmp = vec1;
    tmp |= vec2;
    return tmp;
}

BigInt operator^(const BigInt &vec1, const BigInt &vec2) {
    BigInt tmp = vec1;
    tmp ^= vec2;
    return tmp;
}

BigInt &BigInt::operator%=(const BigInt &number) {
    BigInt result = *this - (*this / number) * number;
    if (result.is_negative_) {
        result += number;
    }

    *this = result;
    return *this;
}

BigInt operator%(const BigInt &vec1, const BigInt &vec2) {
    BigInt tmp = vec1;
    tmp %= vec2;
    return tmp;
}

//                             блок 42,43

BigInt BigInt::operator-() const {
    BigInt copy(*this);
    copy.is_negative_ = !copy.is_negative_;
    return copy;
}

BigInt BigInt::operator+() const {
    return *this;
}

//                             блок с 42 по 50
bool BigInt::operator==(const BigInt &right) const {
    if((right.is_negative_ || is_negative_) && digits_[0] == 0 && right.digits_[0] == 0){
        return true;
    }

    if (digits_.size() != right.digits_.size()) {
        return false;
    }

    if (digits_.empty()) {
        if (right.digits_.empty() || (right.digits_.size() == 1 && right.digits_[0] == 0)) {
            return true;
        } else {
            return false;
        }
    }

    for (size_t i = 0; i < digits_.size(); ++i) {
        if (digits_[i] != right.digits_[i]) {
            return false;
        }
    }

    if (is_negative_ != right.is_negative_) {
        return false;
    }

    return true;
}

bool BigInt::operator!=(const BigInt &number) const {
    return !(*this == number);
}

bool BigInt::operator<(const BigInt &number) const {
    if (*this == number) {
        return false;
    }
    if (this->is_negative_) {
        if (number.is_negative_) {
            return ((-number) < (-*this));
        } else {
            return true;
        }
    } else {
        if (this->digits_.size() != number.digits_.size()) {
            return this->digits_.size() < number.digits_.size();
        } else {
            for (long long i = this->digits_.size() - 1; i >= 0; --i) {
                if (this->digits_[i] != number.digits_[i]) {
                    return this->digits_[i] < number.digits_[i];
                }
            }

            return false;
        }
    }
}

bool BigInt::operator>(const BigInt &value) const {
    return !(*this < value) && !(*this == value);
}

bool BigInt::operator<=(const BigInt &value) const {
    return !((*this) > value);
}


bool BigInt::operator>=(const BigInt &value) const {
    return !((*this) < value);
}

//                                 блок с 52, 53
BigInt::operator std::string() const {
    std::string res;

    for (int i = 0; i < this->digits_.size(); ++i) {
        res = std::to_string(digits_[i]) + res;
    }

    if(is_negative_){
        res = '-' + res;
    }

    return res;
}

// other
std::ostream &operator<<(std::ostream &out, const BigInt &num) {
    out << std::string(num);
    return out;
}

BigInt BigInt::operator~() const {
    BigInt tmp(*this);
    ++tmp.digits_[0];
    tmp.is_negative_ = !tmp.is_negative_;
    tmp._remove_leading_zeros();

    return tmp;
}

size_t BigInt::size() const {
    return (sizeof(int32_t) * digits_.size() + 1);
}

BigInt::operator int() const {
    int number = 0;

    if (digits_.size() > 2) {
        throw std::length_error("Int overflow");
    }

    if (digits_.size() > 1) {
        number = digits_[0] + digits_[1] * base_;
    } else {
        number = digits_[0];
    }

    if (is_negative_) {
        number *= -1;
    }

    return number;
}