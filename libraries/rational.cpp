/**************************************************************************
 Rational Library Header
 by: Francisco Dibar
 date: Aug-08-2006
 include libraries: functional, sstream 
 notes: compile with fexceptions flag
**************************************************************************/

#ifndef RATIONAL_H_INCLUDED
#define RATIONAL_H_INCLUDED

#include <functional>   // binary_function
#include <sstream>      // ostringstream

namespace rationalExceptions {

class DivideByZeroException: public std::exception {
public:
   virtual const char* what() const throw() { return "divide by zero"; }
};

} // namespace

using rationalExceptions::DivideByZeroException;

namespace {

long gcd(long u, long v)
// returns maximum common divisor between u and v
{
    while (v != 0) {
        long t = u % v; 
        u = v;
        v = t;
    }
    return u;
}

} // namespace

////////////////////////////////////////////////////////////////////////////////
class Rational {
public:
    // constructor
    Rational(long aNum = 0): num_(aNum), den_(1) {};
    Rational(long, long) throw(DivideByZeroException);
    Rational(const Rational&);  // copy constuctor
    
    // overloaded operators
    Rational& operator+=(const Rational&);
    Rational& operator-=(const Rational&);
    Rational& operator*=(const Rational&);
    Rational& operator/=(const Rational&) throw(DivideByZeroException);

    friend Rational operator+(const Rational&, const Rational&);
    friend Rational operator-(const Rational&, const Rational&);
    friend Rational operator*(const Rational&, const Rational&);
    friend Rational operator/(const Rational&, const Rational&);

    friend std::ostream& operator<<(std::ostream&, const Rational&);
    friend std::istream& operator>>(std::istream&, Rational&);

    // comparison operators
    inline bool operator==(const Rational&) const;
    inline bool operator!=(const Rational&) const;
    inline bool operator<(const Rational&) const;
    inline bool operator>(const Rational&) const;
    inline bool operator<=(const Rational&) const;
    inline bool operator>=(const Rational&) const;

    // conversion operators
    inline double toDouble() const;
    inline long   toLong() const;
    inline string toString() const;

    // getters
    long getNum() { return num_; }
    long getDen() { return den_; }

private:
    long num_, 
         den_;
};

#endif      // RATIONAL_H_INCLUDED

////////////////////////////////////////////////////////////////////////////////
class LessRationalCmp : public std::binary_function<Rational, Rational, bool> {
public:
    bool operator()(const Rational& lhs, const Rational& rhs) {
        return (lhs.toDouble() < rhs.toDouble());
    }
};

/**************************************************************************
 Rational Library Implementation
 by: Francisco Dibar
 date: Aug-08-2006
**************************************************************************/

////////////////////////////////////////////////////////////////////////////////
Rational::Rational(const Rational& rhs)
{
    num_ = rhs.num_;
    den_ = rhs.den_;
}

////////////////////////////////////////////////////////////////////////////////
Rational::Rational(long aNum, long aDen) throw(DivideByZeroException)
{
    if (aDen == 0)
        throw DivideByZeroException();

    long m = gcd(aNum, aDen);
    num_ = aNum / m;
    den_ = aDen / m;
    if (den_ < 0) {
        den_ *= -1;
        num_ *= -1;
    }
}

///////////////////////////////////////////////////////////////////////////
inline bool Rational::operator==(const Rational& rhs) const
{
    return ((num_ == rhs.num_) && (den_ == rhs.den_));
}

///////////////////////////////////////////////////////////////////////////
inline bool Rational::operator!=(const Rational& rhs) const
{
    return ((num_ != rhs.num_) || (den_ != rhs.den_));
}

///////////////////////////////////////////////////////////////////////////
inline bool Rational::operator<(const Rational& rhs) const
{
    return (toDouble() < rhs.toDouble());
}

///////////////////////////////////////////////////////////////////////////
inline bool Rational::operator>(const Rational& rhs) const
{
    return (toDouble() > rhs.toDouble());
}

///////////////////////////////////////////////////////////////////////////
inline bool Rational::operator<=(const Rational& rhs) const
{
    return (toDouble() <= rhs.toDouble());
}

///////////////////////////////////////////////////////////////////////////
inline bool Rational::operator>=(const Rational& rhs) const
{
    return (toDouble() >= rhs.toDouble());
}

///////////////////////////////////////////////////////////////////////////
Rational& Rational::operator+=(const Rational& rhs)
{
    // TODO
    return (*this);
}

///////////////////////////////////////////////////////////////////////////
Rational& Rational::operator-=(const Rational& rhs)
{
    // TODO
    return (*this);
}

///////////////////////////////////////////////////////////////////////////
Rational& Rational::operator*=(const Rational& rhs)
{
    // TODO
    return (*this);
}

///////////////////////////////////////////////////////////////////////////
Rational& Rational::operator/=(const Rational& rhs) throw(DivideByZeroException)
{
    // TODO
    return (*this);
}

///////////////////////////////////////////////////////////////////////////
std::ostream& operator<<(std::ostream& os, const Rational& rhs) 
{
    os << rhs.num_ << " / " << rhs.den_;
    return os;
}

///////////////////////////////////////////////////////////////////////////
std::istream& operator>>(std::istream& is, Rational& rhs) 
{
    long num, den;
    is >> num >> den;
    rhs = Rational(num, den);
    return is;
}


////////////////////////////////////////////////////////////////////////////////
inline std::string Rational::toString() const
{
    std::ostringstream os;
    os << num_ << " / " << den_;
    return os.str();
}

////////////////////////////////////////////////////////////////////////////////
inline double Rational::toDouble() const
{
    return (static_cast<double>(num_) / den_);
}

////////////////////////////////////////////////////////////////////////////////
inline long Rational::toLong() const
{
    return (num_ / den_);
}


///////////////////////////////////////////////////////////////////////////
Rational operator+(const Rational& lhs, const Rational& rhs)
{
    Rational temp(lhs);
    return temp += rhs;
}

///////////////////////////////////////////////////////////////////////////
Rational operator-(const Rational& lhs, const Rational& rhs)
{
    Rational temp(lhs);
    return temp -= rhs;
}

///////////////////////////////////////////////////////////////////////////
Rational operator*(const Rational& lhs, const Rational& rhs)
{
    Rational temp(lhs);
    return temp *= rhs;
}

///////////////////////////////////////////////////////////////////////////
Rational operator/(const Rational& lhs, const Rational& rhs)
{
    Rational temp(lhs);
    return temp /= rhs;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <vector>
#include <algorithm>

using std::cout;
using std::endl;
using std::vector;

int main()
{
    // test class

    // constructors
    Rational r1(2,-3), r2(0,1);
    Rational r3(-1,-1), r4(-2,2);
    //cout << "Initialized 2 rationals r1 = 1/-1 and r2 = 0/1" << endl;
    cout << "r1 = " << r1 << endl << "r2 = " << r2 << endl;
    cout << "r3 = " << r3 << endl << "r4 = " << r4 << endl;
    cout << Rational(-45) << endl;
    r4 = r2;
    cout << r4 << endl;
    cout << Rational(r1) << endl;
    cout << Rational(1,3).toDouble() << endl;
    cout << Rational(1,3).toLong() << endl;
    cout << r1.toString() << endl;
    vector<Rational> v(3);
    v[0] = r3;
    v[1] = r2;
    v[2] = r1;
    std::sort(v.begin(), v.end(), LessRationalCmp());
    cout << v[0] << "    " << v[1] << "    " << v[2] << endl;
    cout << (r1 == r2) << endl;
    cout << (r1 != r2) << endl;
    cout << ((r1 == r1) ? "ok" : "wrong!") << endl;
    cout << ((r1 < r1) ? "wrong" : "ok") << endl;
    cout << Rational(4,6) << endl; // prints 2/3
    return 0;
}
