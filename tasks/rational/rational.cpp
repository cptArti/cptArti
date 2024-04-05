#include "rational.h"

Rational::Rational() : numer_(0), denom_(1) {
}
Rational::Rational(int value) : numer_(value), denom_(1) {
}
Rational::Rational(int numer, int denom) {
    Set(numer, denom);
}
void Rational::Set(int64_t numer, int64_t denom) {
    if (denom == 0) {
        throw RationalDivisionByZero{};
    }
    int mult = (denom > 0) ? 1 : -1;
    int64_t divisor = std::gcd(numer, denom);
    numer_ = mult * static_cast<int>(numer / divisor);
    denom_ = static_cast<int>(std::abs(denom) / divisor);
}
int Rational::GetNumerator() const {
    return numer_;
}
int Rational::GetDenominator() const {
    return denom_;
}
void Rational::SetNumerator(int value) {
    Set(value, denom_);
}
void Rational::SetDenominator(int value) {
    Set(numer_, value);
}
Rational operator+(const Rational& ratio) {
    return ratio;
}

Rational operator-(const Rational& ratio) {
    return {-ratio.GetNumerator(), ratio.GetDenominator()};
}

Rational& operator*=(Rational& lhs, const Rational& rhs) {
    int64_t numer = static_cast<int64_t>(lhs.numer_) * static_cast<int64_t>(rhs.numer_);
    int64_t denom = static_cast<int64_t>(lhs.denom_) * static_cast<int64_t>(rhs.denom_);
    lhs.Set(numer, denom);
    return lhs;
}

Rational& operator+=(Rational& lhs, const Rational& rhs) {
    int d = lhs.denom_ * rhs.denom_;
    int n = lhs.numer_ * rhs.denom_ + rhs.numer_ * lhs.denom_;
    lhs.Set(n, d);
    return lhs;
}

Rational& operator-=(Rational& lhs, const Rational& rhs) {
    lhs += -rhs;
    return lhs;
}

Rational& operator/=(Rational& lhs, const Rational& rhs) {
    lhs *= {rhs.GetDenominator(), rhs.GetNumerator()};
    return lhs;
}

Rational operator+(const Rational& lhs, const Rational& rhs) {
    Rational res = lhs;
    return (res += rhs);
}

Rational operator-(const Rational& lhs, const Rational& rhs) {
    Rational res = lhs;
    return (res -= rhs);
}

Rational operator*(const Rational& lhs, const Rational& rhs) {
    Rational res = lhs;
    return (res *= rhs);
}

Rational operator/(const Rational& lhs, const Rational& rhs) {
    Rational res = lhs;
    return (res /= rhs);
}

Rational& operator++(Rational& ratio) {
    ratio.numer_ += ratio.denom_;
    return ratio;
}

Rational operator++(Rational& ratio, int) {
    Rational res = ratio;
    ++ratio;
    return res;
}

Rational& operator--(Rational& ratio) {
    ratio.numer_ -= ratio.denom_;
    return ratio;
}

Rational operator--(Rational& ratio, int) {
    Rational res = ratio;
    --ratio;
    return res;
}

bool operator<(const Rational& lhs, const Rational& rhs) {
    return ((lhs - rhs).GetNumerator() < 0);
}

bool operator>(const Rational& lhs, const Rational& rhs) {
    return (rhs < lhs);
}

bool operator<=(const Rational& lhs, const Rational& rhs) {
    return !(lhs > rhs);
}

bool operator>=(const Rational& lhs, const Rational& rhs) {
    return !(lhs < rhs);
}
bool operator==(const Rational& lhs, const Rational& rhs) {
    return ((lhs - rhs).GetNumerator() == 0);
}

bool operator!=(const Rational& lhs, const Rational& rhs) {
    return !(lhs == rhs);
}
std::istream& operator>>(std::istream& is, Rational& ratio) {
    int numer = 0;
    int denom = 1;
    is >> numer;
    if (is.peek() == '/') {
        is.ignore();
        is >> denom;
    } else {
        denom = 1;
    }
    ratio.Set(numer, denom);
    return is;
}
std::ostream& operator<<(std::ostream& os, const Rational& ratio) {
    os << ratio.GetNumerator();
    if (ratio.GetDenominator() != 1) {
        os << '/' << ratio.GetDenominator();
    }
    return os;
}
