
/**************************************************************************
 Polynomial Library Header
 by: Francisco Dibar
 date: Aug-06-2006
 include libraries: cmath, exception, vector
**************************************************************************/

#ifndef POLY_H_INCLUDED
#define POLY_H_INCLUDED

#include <cmath>        // abs
#include <exception>
#include <vector>

namespace polyExceptions {

class OutOfRange: public std::exception {
public:
   virtual const char* what() const throw() { return "out of range"; }
};

class DivideByZeroException: public std::exception {
public:
   virtual const char* what() const throw() { return "divide by zero"; }
};

};  // namespace

using std::vector;
using polyExceptions::OutOfRange;
using polyExceptions::DivideByZeroException;


////////////////////////////////////////////////////////////////////////////////
class Poly {
public:
    // constructors
    Poly(const Poly&);                          // copy constructor
    Poly(const vector<double>&);
    Poly(const double*, unsigned int size);
    Poly(double, int);
    Poly(double);

    unsigned int degree() const;
    double coef(unsigned int) const throw (OutOfRange);   // returns coefficient i

    // overloaded operators
    Poly& operator=(const Poly&);

    Poly& operator+=(const Poly&);
    Poly& operator-=(const Poly&);
    Poly& operator*=(const Poly&);
    //Poly& operator/=(const Poly&) throw (DivideByZeroException);  // TODO

    friend Poly operator+(const Poly&, const Poly&);
    friend Poly operator-(const Poly&, const Poly&);
    friend Poly operator*(const Poly&, const Poly&);
    //friend Poly operator/(const Poly&, const Poly&); // TODO

    // comparison operators
    bool operator==(const Poly&) const;

    Poly operator-() const;
    Poly power(unsigned int) const;

    double evaluate(double);

protected:
    void calculateDegree();

private:
    vector<double> vCoef_;
    unsigned int degree_;

    static const double EPSILON = 0.0001; // values under EPSILON are considered 0
};

#endif      // POLY_H_INCLUDED

/**************************************************************************
 Polynomial Library Implementation
 by: Francisco Dibar
 date: Aug-06-2006
 include libraries: vector
**************************************************************************/

////////////////////////////////////////////////////////////////////////////////
Poly::Poly(const Poly& aPoly)
// aPoly[i] = coefficient for x^i
{
    vCoef_ = aPoly.vCoef_;
    degree_ = aPoly.degree_;
}

////////////////////////////////////////////////////////////////////////////////
Poly::Poly(const vector<double>& avPoly)
// avPoly[i] = coefficient for x^i
{
    vCoef_ = avPoly;
    calculateDegree();
}

////////////////////////////////////////////////////////////////////////////////
Poly::Poly(double num = 0)
{
    vCoef_.push_back(num);
    degree_ = 0;
}

////////////////////////////////////////////////////////////////////////////////
Poly::Poly(double num, int degree)
{
    vCoef_.resize(degree + 1);
    vCoef_[degree] = num;
    degree_ = degree;
}

////////////////////////////////////////////////////////////////////////////////
Poly::Poly(const double* avPoly, unsigned int aSize)
// avPoly[i] = coefficient for x^i
{
    vCoef_.resize(aSize);
    for (unsigned int i = 0; i < aSize; ++i)
        vCoef_[i] = avPoly[i];

    degree_ = 0;
    calculateDegree();
}

////////////////////////////////////////////////////////////////////////////////
void Poly::calculateDegree()
{
    for (int i = vCoef_.size(); i >= 0; --i) {
        if (std::abs(vCoef_[i]) > EPSILON) {
            degree_ = i;
            return;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////
unsigned int Poly::degree() const
{
    return degree_;
}

////////////////////////////////////////////////////////////////////////////////
double Poly::coef(unsigned int i) const throw (OutOfRange)
{
    if (i > degree_)
        throw OutOfRange();

    return vCoef_[i];
}

////////////////////////////////////////////////////////////////////////////////
Poly& Poly::operator=(const Poly& rhs)
{
    vCoef_ = rhs.vCoef_;
    degree_ = rhs.degree_;
    return (*this);
}

////////////////////////////////////////////////////////////////////////////////
bool Poly::operator==(const Poly& rhs) const
{
    if (degree_ != rhs.degree_)
        return false;

    for (unsigned int i = 0; i <= degree_; ++i)
        if (vCoef_[i] != rhs.vCoef_[i])
            return false;

    return true;
}

///////////////////////////////////////////////////////////////////////////
Poly& Poly::operator+=(const Poly& rhs)
{
    if (degree_ < rhs.degree_) {
        vCoef_.resize(rhs.degree_ + 1);
        for (unsigned int i = 0; i <= degree_; ++i)
            vCoef_[i] += rhs.vCoef_[i];
        for (unsigned int i = degree_+1; i <= rhs.degree_; ++i)
            vCoef_[i] = rhs.vCoef_[i];
    } else {
        for (unsigned int i = 0; i <= rhs.degree_; ++i)
            vCoef_[i] += rhs.vCoef_[i];
    }
    calculateDegree();
    return (*this);
}

///////////////////////////////////////////////////////////////////////////
Poly& Poly::operator-=(const Poly& rhs)
{
    if (degree_ < rhs.degree_) {
        vCoef_.resize(rhs.degree_ + 1);
        for (unsigned int i = 0; i <= degree_; ++i)
            vCoef_[i] -= rhs.vCoef_[i];
        for (unsigned int i = degree_+1; i <= rhs.degree_; ++i)
            vCoef_[i] = -rhs.vCoef_[i];
    } else {
        for (unsigned int i = 0; i <= rhs.degree_; ++i)
            vCoef_[i] -= rhs.vCoef_[i];
    }
    calculateDegree();
    return (*this);
}

///////////////////////////////////////////////////////////////////////////
Poly& Poly::operator*=(const Poly& rhs)
// apply convolution
// TODO: implement as FFT    
{
    vector<double> vtemp(degree_ + rhs.degree_ + 1);
    for (unsigned int i = 0; i <= degree_; ++i) {
        for (unsigned int j = 0; j <= rhs.degree_; ++j) {
            vtemp[i+j] = vCoef_[i] * rhs.vCoef_[j];
        }
    }
    degree_ += rhs.degree_;
    vCoef_ = vtemp;
    return (*this);
}

///////////////////////////////////////////////////////////////////////////
Poly operator+(const Poly& lhs, const Poly& rhs)
{
    Poly temp(lhs);
    return temp += rhs;
}

///////////////////////////////////////////////////////////////////////////
Poly operator-(const Poly& lhs, const Poly& rhs)
{
    Poly temp(lhs);
    return temp -= rhs;
}

///////////////////////////////////////////////////////////////////////////
Poly operator*(const Poly& lhs, const Poly& rhs)
{
    Poly temp(lhs);
    return temp *= rhs;
}

///////////////////////////////////////////////////////////////////////////
Poly Poly::power(unsigned int rhs) const
{
    Poly temp(*this);
    for (unsigned int i = 0; i < rhs; ++i)
        temp *= (*this);
    return temp;
}

///////////////////////////////////////////////////////////////////////////
Poly Poly::operator-() const
{
    Poly temp(*this);
    for (unsigned int i = 0; i <= degree_; ++i)
        temp.vCoef_[i] *= -1;

    return temp;
}

////////////////////////////////////////////////////////////////////////////////
double Poly::evaluate(double num)
{
    double temp = vCoef_[0];
    double pow = 1;
    for (unsigned int i = 1; i <= degree_; ++i) {
        pow *= num;
        temp += pow * vCoef_[i];
    }
    return temp;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#include <iostream>

using std::cout;
using std::cin;

void printPoly(const Poly& p)
{
    for (unsigned int i = 0; i <= p.degree(); ++i)
        cout << p.coef(i) << " ";
    cout << endl;
}

int main()
{
    vector<double> vp(3);
    vp[0] = 0;
    vp[1] = 1;
    vp[2] = 2;
    double ap[] = { 0, 1, 2, 0 };
    Poly p1(vp);
    Poly p2(ap, 3);
    printPoly(p1);
    printPoly(p2);
    cout << ((p1 == p2) ? "p1 = p2\n" : "p1 != p2\n");
    printPoly(p1+p2);
    printPoly(p1-p2);
    Poly p3;
    p3 = p1+10;
    printPoly(p3);
    printPoly(-p3);
    Poly p4(1);
    Poly p5(1,1);
    Poly p6(1,2);
    printPoly(p4);
    printPoly(p5);
    printPoly(p6);
    printPoly(p4+p5);
    printPoly(p4+p5+p6);
    printPoly(p6-p4);
    printPoly(1*p6);
    Poly p7(2*p4+3*p5-4*p6);
    printPoly(p7);
    cout << p7.evaluate(1) << endl;
    cout << p7.evaluate(2) << endl;
    printPoly(p5.power(2));
    return 0;
}
