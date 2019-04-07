#pragma once
#include <exception>
#include <iostream>
#include <iosfwd>

using std::ostream;
using std::istream;

class Rational {
public:
    int numerator;
    int denominator;
    Rational(int nu = 0, int de = 1) throw(std::underflow_error);
    Rational operator-() const;

    friend long NOD(const Rational&, const Rational&) throw(std::underflow_error);
    friend long NOK(const Rational&, const Rational&) throw(std::underflow_error);
    friend Rational OPT(const Rational&) throw(std::underflow_error);
    friend Rational operator+(const Rational&, const Rational&) throw(std::underflow_error);
    friend Rational operator-(const Rational&, const Rational&) throw(std::underflow_error);
    friend Rational operator*(const Rational&, const Rational&) throw(std::underflow_error);
    friend Rational operator/(const Rational&, const Rational&) throw(std::underflow_error);
    friend ostream& operator<<(ostream&, const Rational&);
    friend istream& operator>>(istream&, Rational&);
    Rational& operator+=(const Rational&) throw(std::underflow_error);
    Rational& operator-=(const Rational&) throw(std::underflow_error);
    Rational& operator*=(const Rational&) throw(std::underflow_error);
    Rational& operator/=(const Rational&) throw(std::underflow_error);
    friend bool operator<(const Rational&, const Rational&);
    friend bool operator>(const Rational&, const Rational&);
    friend bool operator<=(const Rational&, const Rational&);
    friend bool operator>=(const Rational&, const Rational&);
    friend bool operator==(const Rational&, const Rational&);
    friend bool operator!=(const Rational&, const Rational&);
};