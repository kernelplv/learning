#include <iostream>
#include "2_2.h"
using namespace std;

Rational::Rational(int nu, int de) throw(underflow_error) {
    if (de <= 0) 
        throw(underflow_error("denominator < 0 !"));
    else {
        this->numerator = nu;
        this->denominator = de;
    }
    
}

long NOD(const Rational& l, const Rational& r) 
                        throw(underflow_error) {
                                
    l.denominator && r.denominator
    ? false : throw(underflow_error("Zero denominator!"));
    
    long A = l.denominator;
    long B = r.denominator;
    
    while ((A %= B) && (B %= A));
    return A | B;
    
}

long NOD(const long l, const long r) 
                        throw(underflow_error) {
                                
    l && r
    ? false : throw(underflow_error("Zero denominator!"));
    
    long A = l;
    long B = r;
    
    while ((A %= B) && (B %= A));
    return A | B;
    
}

long NOK(const Rational& l, const Rational& r)
                        throw(underflow_error) {
                            
    l.denominator && r.denominator
    ? false : throw(underflow_error("Zero denominator!"));
    
    return l.denominator / NOD (l, r) * r.denominator;
    
}

long NOK(const long l, const long r)
                        throw(underflow_error) {
                            
    l && r
    ? false : throw(underflow_error("Zero denominator!"));
    
    return l / NOD (l, r) * r;
    
}

Rational OPT(const Rational& r) throw(underflow_error) {
    
    Rational n(r.numerator, r.denominator);
    long divn = NOD(n.numerator, n.denominator);
    n.numerator /= divn ;
    n.denominator /= divn;
    
    return n;
    
}

Rational Rational::operator -() const {
    return Rational(this->numerator * -1, this->denominator);
}

Rational operator+(const Rational& l, const Rational& r) 
                                  throw(underflow_error) {
    
    Rational n(1,NOK(l,r));
    n.numerator = (n.denominator / l.denominator) * l.numerator
                + (n.denominator / r.denominator) * r.numerator;
    return n; 
    
}

Rational operator-(const Rational& l, const Rational& r) 
                                  throw(underflow_error) {
    
    Rational n(1,NOK(l,r));
    n.numerator = (n.denominator / l.denominator) * l.numerator
                - (n.denominator / r.denominator) * r.numerator;
    return n; 
    
}

Rational operator*(const Rational& l, const Rational& r) 
                                  throw(underflow_error) {
    
    Rational n(1,1);
    n.numerator = l.numerator * r.numerator;
    n.denominator = l.denominator * r.denominator;
    
    return n;
}

Rational operator/(const Rational& l, const Rational& r) 
                                  throw(underflow_error) {
    
    Rational n(1,1);
    n.numerator = l.numerator * r.denominator;
    n.denominator = l.denominator * r.numerator;
    
    return n;
}

Rational& Rational::operator+=(const Rational& r) 
                           throw(underflow_error) {
                               
    &r == this
    ? throw(underflow_error("Self-Assignment!")) : true;
                     
    *this = *this + r;
    
    return *this;
    
}

Rational& Rational::operator-=(const Rational& r) 
                           throw(underflow_error) {
                               
    &r == this
    ? throw(underflow_error("Self-Assignment!")) : true;
                     
    *this = *this - r;
    
    return *this;
    
}

Rational& Rational::operator*=(const Rational& r) 
                           throw(underflow_error) {
                               
    &r == this
    ? throw(underflow_error("Self-Assignment!")) : true;
                     
    *this = *this * r;
    
    return *this;
    
}

Rational& Rational::operator/=(const Rational& r) 
                           throw(underflow_error) {
                               
    &r == this
    ? throw(underflow_error("Self-Assignment!")) : true;
                     
    *this = *this / r;
    
    return *this;
    
}

bool operator<(const Rational& l, const Rational& r) {
    
    return (static_cast<double>(l.numerator) / static_cast<double>(l.denominator) )
           <
           (static_cast<double>(r.numerator) / static_cast<double>(r.denominator) );
    
}

bool operator>(const Rational& l, const Rational& r) {
           
    return (static_cast<double>(l.numerator) / static_cast<double>(l.denominator) )
           >
           (static_cast<double>(r.numerator) / static_cast<double>(r.denominator) );
    
}

bool operator<=(const Rational& l, const Rational& r) {
           
    return (static_cast<double>(l.numerator) / static_cast<double>(l.denominator) )
           <=
           (static_cast<double>(r.numerator) / static_cast<double>(r.denominator) );
    
}

bool operator>=(const Rational& l, const Rational& r) {
           
    return (static_cast<double>(l.numerator) / static_cast<double>(l.denominator) )
           >=
           (static_cast<double>(r.numerator) / static_cast<double>(r.denominator) );
    
}

bool operator==(const Rational& l, const Rational& r) {
           
    return (static_cast<double>(l.numerator) / static_cast<double>(l.denominator) )
           ==
           (static_cast<double>(r.numerator) / static_cast<double>(r.denominator) );
    
}

bool operator!=(const Rational& l, const Rational& r) {
           
    return (static_cast<double>(l.numerator) / static_cast<double>(l.denominator) )
           !=
           (static_cast<double>(r.numerator) / static_cast<double>(r.denominator) );
    
}

ostream& operator<<(ostream& stream, const Rational& r) {
    
    stream << r.numerator << "/" 
           << r.denominator << endl;
    return stream;
    
}
istream& operator>>(istream& stream, Rational& r) {
    
    stream >> r.numerator;
    stream.ignore(1);
    stream >> r.denominator;
           
    return stream;
    
}