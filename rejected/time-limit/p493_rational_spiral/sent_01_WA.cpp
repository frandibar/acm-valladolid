/* @JUDGE_ID:  40922FK  493  C++  */
/* @BEGIN_OF_SOURCE_CODE */    
/******************************************************************************
 Solution to Problem 493 - Rational Spiral
 by: Francisco Dibar
 date: Aug-08-2006
******************************************************************************/

//#define DEBUG
//#define ONLINE_JUDGE 
#include <iostream>
#ifndef ONLINE_JUDGE 
    #include <fstream>
#endif 
#include <vector>
#include <set>
#include <exception>

#ifdef DEBUG
    #define START_DEBUG "START DEBUG ********************************************************************\n"
    #define END_DEBUG   "END DEBUG **********************************************************************\n"
    // g++-2.95 doesn't support asserts
    #define ASSERT(x,y)   if (!(x)) { std::cerr << "ASSERTION FAILED!: " << y << "\n"; exit(1); }
#endif

/**************************************************************************
 Rational Library Header
 by: Francisco Dibar
 date: Aug-08-2006
 include libraries: sstream 
 notes: compile with fexceptions flag
**************************************************************************/

#ifndef RATIONAL_H_INCLUDED
#define RATIONAL_H_INCLUDED

#include <sstream>      // ostringstream
#include <functional>   // binary_function

namespace rationalExceptions {

class DivideByZeroException: public std::exception {
public:
   virtual const char* what() const throw() { return "divide by zero"; }
};

}; // namespace

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

}; // namespace

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

    friend std::ostream &operator<<(std::ostream&, const Rational&);
    friend std::istream &operator>>(std::istream&, Rational&);

    // conversion operators
    double toDouble() const;
    long   toLong() const;
    string toString() const;

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
std::ostream &operator<<(std::ostream& os, const Rational& rhs) 
{
    os << rhs.num_ << " / " << rhs.den_;
    return os;
}

///////////////////////////////////////////////////////////////////////////
std::istream &operator>>(std::istream& is, Rational& rhs) 
{
    long num, den;
    is >> num >> den;
    rhs = Rational(num, den);
    return is;
}


////////////////////////////////////////////////////////////////////////////////
std::string Rational::toString() const
{
    std::ostringstream os;
    os << num_ << " / " << den_;
    return os.str();
}

////////////////////////////////////////////////////////////////////////////////
double Rational::toDouble() const
{
    return (static_cast<double>(num_) / den_);
}

////////////////////////////////////////////////////////////////////////////////
long Rational::toLong() const
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


using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::set;

////////////////////////////////////////////////////////////////////////////////
void calcRationals(vector<Rational>& vRationals, unsigned long n)
// fills vRationals with n rationals
{
    enum direction { UP, DOWN, LEFT, RIGHT };
    set<Rational, LessRationalCmp> sRationals; // used to avoid repetitions
    // add first 3 rationals
    sRationals.insert(Rational(1));
    sRationals.insert(Rational(0));
    sRationals.insert(Rational(-1));
    vRationals.push_back(Rational(1));
    vRationals.push_back(Rational(0));
    vRationals.push_back(Rational(-1));
    int num = -1;
    int den = 1;
    int nextNum = -1;
    int nextDen = -1;
    int stepNum = 0;
    int stepDen = -1;
    direction dir = LEFT;
    while ((unsigned long)vRationals.size() <= n) {
#ifdef DEBUG
        cout << "visiting " << num << " / " << den << endl;
#endif
        if (den != 0) {
            Rational r(num, den);
            // insert r in set and determine if already exists
            pair<set<Rational, LessRationalCmp>::const_iterator, bool > p;
            p = sRationals.insert(r);
            if (p.second) {  // indicates if r was inserted
                vRationals.push_back(r);
#ifdef DEBUG
                cout << "added " << r << endl;
#endif
            }
        }
        if ((num == nextNum) && (den == nextDen)) {
            // change direction
            if (dir == LEFT) {
                // finished going left, now go up
                stepDen = 0;
                stepNum = 1;
                nextNum = 1 - num;
                nextDen = den;
                dir = UP;
#ifdef DEBUG
                cout << "finished going LEFT, now going UP to " << nextNum << " / " << nextDen << endl;
#endif
            } else if (dir == RIGHT) {
                // finished going right, now go down
                stepDen = 0;
                stepNum = -1;
                nextNum = -num;
                nextDen = den;
                dir = DOWN;
#ifdef DEBUG
                cout << "finished going RIGHT, now going DOWN to " << nextNum << " / " << nextDen << endl;
#endif
            } else if (dir == UP) {
                // finished going up, now go right
                stepNum = 0;
                stepDen = 1;
                nextNum = num;
                nextDen = 1 - den;
                dir = RIGHT;
#ifdef DEBUG
                cout << "finished going UP, now going RIGHT to " << nextNum << " / " << nextDen << endl;
#endif
            } else {    // dir = DOWN
                // finished going down, now left
                stepNum = 0;
                stepDen = -1;
                nextNum = num;
                nextDen = -den;
                dir = LEFT;
#ifdef DEBUG
                cout << "finished going DOWN, now going LEFT to " << nextNum << " / " << nextDen << endl;
#endif
            }
        }
        num += stepNum;
        den += stepDen;
    }
}


////////////////////////////////////////////////////////////////////////////////
//  MAIN PROGRAM
////////////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{
	// redirect input and output
	#ifndef ONLINE_JUDGE 
		cin.rdbuf((new std::ifstream("input"))->rdbuf()); 
		cout.rdbuf((new std::ofstream("output"))->rdbuf()); 
	#endif 

    // READ INPUT
    vector<long> vInput;
    long max = 0;   // stores max input
    long n;
    cin >> n;
    while (!cin.eof()) {
        vInput.push_back(n);
        if (n > max) max = n;
        cin >> n;
    }

    // PROCESS
    vector<Rational> vRationals;
    calcRationals(vRationals, max);

    // SHOW OUTPUT
    for (int i = 0; i < (int)vInput.size(); ++i)
        cout << vRationals[vInput[i]] << endl;

#ifdef DEBUG
    cout << START_DEBUG;

    cout << END_DEBUG;
#endif

    return 0;
}

/* @END_OF_SOURCE_CODE */
