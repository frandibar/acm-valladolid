/* @JUDGE_ID:  40922FK  128  C++  */
/* @BEGIN_OF_SOURCE_CODE */    
/**************************************************************************
 Solution to Problem 128 - Software CRC
 by: Francisco Dibar
 date: Dec-30-2005
**************************************************************************/

//#define DEBUG
//#define ONLINE_JUDGE 
#include <iostream>
#ifndef ONLINE_JUDGE 
	#include <fstream>
#endif 
#include <vector>
#include <string>
#include <iomanip>		// hex
#include <sstream>

#define START_DEBUG	"START DEBUG ********************************************************************\n"
#define END_DEBUG	"END DEBUG **********************************************************************\n"

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::ostream;
using std::istream;


/**************************************************************************
 Bigint Library Header
 by: Francisco Dibar
 date: Aug-06-2006
 include libraries: exception, string, vector
 notes: compile with fexceptions flag
**************************************************************************/

#ifndef BIGINT_H_INCLUDED
#define BIGINT_H_INCLUDED

#include <exception>
#include <string>
#include <vector>

namespace bigintExceptions {

class DivideByZeroException: public std::exception {
public:
   virtual const char* what() const throw() { return "divide by zero"; }
};


class UndefinedException: public std::exception {
public:
   virtual const char* what() const throw() { return "undefined operation"; }
};

class OverflowException: public std::exception {
public:
   virtual const char* what() const throw() { return "overflow"; }
};

}  // namespace

using bigintExceptions::DivideByZeroException;
using bigintExceptions::UndefinedException;
using bigintExceptions::OverflowException;

///////////////////////////////////////////////////////////////////////////
class Bigint {
public:

    // constructors
    Bigint(long num = 0, unsigned long size = DEFAULT_DIGITS);
    Bigint(const std::string&);
    Bigint(const Bigint&);  // copy constructor

    // overloaded operators
    Bigint& operator=(const Bigint&);
    Bigint  operator-() const;
    Bigint  operator%(const Bigint&) const;
    int     operator%(int) const;

    Bigint& operator+=(const Bigint&);
    Bigint& operator-=(const Bigint&);
    Bigint& operator*=(const Bigint&);
    Bigint& operator/=(const Bigint&) throw(DivideByZeroException);
    Bigint& operator^=(const Bigint&) throw(UndefinedException);

    friend Bigint operator+(const Bigint&, const Bigint&);
    friend Bigint operator-(const Bigint&, const Bigint&);
    friend Bigint operator*(const Bigint&, const Bigint&);
    friend Bigint operator/(const Bigint&, const Bigint&);
    friend Bigint operator^(const Bigint&, const Bigint&);

    friend std::ostream &operator<<(std::ostream&, const Bigint&);
    friend std::istream &operator>>(std::istream&, Bigint&);

    // comparison operators
    inline bool operator==(const Bigint&) const;
    inline bool operator!=(const Bigint&) const;
    inline bool operator<(const Bigint&) const;
    inline bool operator>(const Bigint&) const;
    inline bool operator<=(const Bigint&) const;
    inline bool operator>=(const Bigint&) const;

    inline Bigint& operator++();        // preincrement
    inline Bigint  operator++(int);     // postincrement
    inline Bigint& operator--();        // predecrement
    inline Bigint  operator--(int);     // postdecrement

    Bigint absolute() const;
    Bigint factorial() const;

    // changing bases
    bool   baseOk(unsigned int base) const;
    int    minBase() const;
    Bigint changeBase(unsigned int, unsigned int) const;
    Bigint changeBase(unsigned int base) const { return decToBase(base); }
    
    // conversion functions
    int toInt() const throw(OverflowException);
    long toLong() const throw(OverflowException);
    std::string toString() const;

    bool   isPalindrome() const;
    Bigint reverse() const;

    Bigint& shiftLeft(int);
    Bigint& shiftRight(int);

protected:

    int compareAbsolute(const Bigint&, const Bigint&) const;
    int compare(const Bigint&, const Bigint&) const;
    Bigint& removeZeros();

    Bigint decToBase(int) const;
    Bigint baseToDec(int) const;

private:

    std::vector<char> vDigits_;
    int signbit_;
    int lastDigitIndex_;      // index of highest order digit

    static const int DEFAULT_DIGITS = 64;
};

#endif      // BIGINT_H_INCLUDED

/**************************************************************************
 Bigint Library Implementation
 by: Francisco Dibar
 date: Aug-03-2006
**************************************************************************/

///////////////////////////////////////////////////////////////////////////
Bigint::Bigint(const Bigint& num)
// copy constructor    
{
    vDigits_.resize(num.lastDigitIndex_ + 1, '0');
    vDigits_ = num.vDigits_;

    signbit_ = num.signbit_;
    lastDigitIndex_ = num.lastDigitIndex_;
}

///////////////////////////////////////////////////////////////////////////
Bigint::Bigint(const std::string& num)
// precondition: num format is "-n" or "n", no 0's at beginning
{
    // accept any base
    int offset = num.find_first_of("123456789ABCDEFGHIJKLMNOPQRSTUVWXY");
    // if none of those digits are found, initialize with 0
    // TODO: should throw exception InvalidNumber
    if (offset == (int)std::string::npos)
        *this = Bigint(0);
    else {
        signbit_ = (num[0] == '-') ? -1 : 1;
        lastDigitIndex_ = num.length() - 1 - offset;

        vDigits_.resize(lastDigitIndex_ + 1, '0');
        for (int i = 0; i <= lastDigitIndex_; ++i)
            vDigits_[lastDigitIndex_ - i] = num[i + offset];
    }
}

///////////////////////////////////////////////////////////////////////////
Bigint::Bigint(long num, unsigned long size)
{
    if (size < 10) size = 10;   // at least a 'long' must fit
    vDigits_.resize(size, '0');

    // set sign
    signbit_ = (num >= 0) ? 1 : -1;

    // std::vector initializes digits with 0
    lastDigitIndex_ = -1;
    int t = abs(num);
    while (t > 0) {
        lastDigitIndex_++;
        vDigits_[lastDigitIndex_] = (t % 10) + '0';
        t /= 10;
    }
    
    if (num == 0) {
        lastDigitIndex_ = 0;
        vDigits_[0] = '0';
    }
    vDigits_.resize(lastDigitIndex_ + 1, '0');
}

///////////////////////////////////////////////////////////////////////////
int Bigint::compareAbsolute(const Bigint& lhs, const Bigint& rhs) const
// compares absolute values
// returns:  1 if absolute(lhs) < absolute(rhs), 
//          -1 if absolute(lhs) > absolute(rhs), 
//           0 if absolute(lhs) = absolute(rhs)
{
    // compare by amount of digits
    if (rhs.lastDigitIndex_ > lhs.lastDigitIndex_) return (1 * lhs.signbit_);
    if (lhs.lastDigitIndex_ > rhs.lastDigitIndex_) return (-1 * lhs.signbit_);
    // = amount of digits
    for (int i = lhs.lastDigitIndex_; i >= 0; --i) {
        if (lhs.vDigits_[i] > rhs.vDigits_[i])
            return (-1 * lhs.signbit_);
        if (rhs.vDigits_[i] > lhs.vDigits_[i])
            return (1 * lhs.signbit_);
    }
    // lhs = rhs
    return 0;
}

///////////////////////////////////////////////////////////////////////////
int Bigint::compare(const Bigint& lhs, const Bigint& rhs) const
// returns:  1 if lhs < rhs, 
//          -1 if lhs > rhs, 
//           0 if lhs = rhs
{
    // compare signs
    if ((lhs.signbit_ == -1) && (rhs.signbit_ == 1)) return 1;
    if ((lhs.signbit_ == 1) && (rhs.signbit_ == -1)) return -1;
    return compareAbsolute(lhs, rhs);
}

///////////////////////////////////////////////////////////////////////////
inline bool Bigint::operator==(const Bigint& rhs) const
{
    return (compare(*this, rhs) == 0); 
}

///////////////////////////////////////////////////////////////////////////
inline bool Bigint::operator!=(const Bigint& rhs) const
{
    return (compare(*this, rhs) != 0); 
}

///////////////////////////////////////////////////////////////////////////
inline bool Bigint::operator<(const Bigint& rhs) const
{
    return (compare(*this, rhs) == 1); 
}

///////////////////////////////////////////////////////////////////////////
inline bool Bigint::operator>(const Bigint& rhs) const
{
    return (compare(*this, rhs) == -1); 
}

///////////////////////////////////////////////////////////////////////////
inline bool Bigint::operator<=(const Bigint& rhs) const
{
    return (compare(*this, rhs) >= 0); 
}

///////////////////////////////////////////////////////////////////////////
inline bool Bigint::operator>=(const Bigint& rhs) const
{
    return (compare(*this, rhs) <= 0); 
}

///////////////////////////////////////////////////////////////////////////
Bigint& Bigint::operator=(const Bigint& rhs)
{
    vDigits_.resize(rhs.lastDigitIndex_ + 1, '0');
    vDigits_ = rhs.vDigits_;

    signbit_ = rhs.signbit_;
    lastDigitIndex_ = rhs.lastDigitIndex_;
    return (*this);
}

///////////////////////////////////////////////////////////////////////////
inline Bigint& Bigint::operator--()
// operator -- as prefix (predecrement)
{
    *this -= 1;
    return (*this);
}

///////////////////////////////////////////////////////////////////////////
inline Bigint Bigint::operator--(int)
// operator -- as sufix (postdecrement)
{
    Bigint temp = *this;
    *this -= 1;
    return temp;
}

///////////////////////////////////////////////////////////////////////////
inline Bigint& Bigint::operator++()
// operator ++ as prefix (preincrement)
{
    *this += 1;
    return (*this);
}

///////////////////////////////////////////////////////////////////////////
inline Bigint Bigint::operator++(int) 
// operator ++ as sufix (postincrement)
{
    Bigint temp = *this;
    *this += 1;
    return temp;
}

///////////////////////////////////////////////////////////////////////////
Bigint& Bigint::operator+=(const Bigint& rhs)
{
    if (signbit_ != rhs.signbit_) {
        // the idea is to perform an operation with both operands of same sign
        if (signbit_ == -1) {
            // (-a) + b = b - a
            signbit_ = 1;
            *this = rhs - (*this);
        } else {
            // a + (-b) = a - b
            *this -= rhs.absolute();
            return (*this);
        }
    }

    // do the sum, ignore sign
    lastDigitIndex_ = std::max(lastDigitIndex_, rhs.lastDigitIndex_) + 1;
    vDigits_.resize(lastDigitIndex_ + 1, '0');
    int carry = 0;
    for (int i = 0; i <= lastDigitIndex_; ++i) {
        int adigit = (i <= lastDigitIndex_) ? vDigits_[i] - '0' : 0;
        int bdigit = (i <= rhs.lastDigitIndex_) ? rhs.vDigits_[i] - '0' : 0;
        int sum = carry + adigit + bdigit;
        vDigits_[i] = (sum % 10) + '0';
        carry = sum / 10;
    }

    removeZeros();
    return (*this);
}

///////////////////////////////////////////////////////////////////////////
Bigint operator+(const Bigint& lhs, const Bigint& rhs)
{
    Bigint temp(lhs);
    return temp += rhs;
}

///////////////////////////////////////////////////////////////////////////
Bigint& Bigint::operator-=(const Bigint& rhs)
{
    if (signbit_ != rhs.signbit_) {
        // (-a) - b = -a + (-b) = -(a + b)  -> result takes a's sign
        // a - (-b) = a + b
        int sign = signbit_;
        *this += (rhs.signbit_ == 1) ? rhs : rhs.absolute(); 
        (*this).signbit_ = sign;
        return (*this);
    } else if (compareAbsolute(*this, rhs) == 1) {  // if this < rhs
        // (-a) - (-b) = -a + b = b - a
        // a - b = -(b - a)
        (*this) = rhs - (*this);
        signbit_ = -1;
        return (*this);
    }

    lastDigitIndex_ = std::max(lastDigitIndex_, rhs.lastDigitIndex_);
    int borrow = 0;
    for (int i = 0; i <= lastDigitIndex_; ++i) {
        int adigit = (i <= rhs.lastDigitIndex_) ? rhs.vDigits_[i] - '0' : 0;
        int v = (vDigits_[i] - '0' - borrow - adigit);
        if (vDigits_[i] > '0')
            borrow = 0;
        if (v < 0) {
            v += 10;
            borrow = 1;
        }
        vDigits_[i] = (v % 10) + '0';
    }

    removeZeros();
    return (*this);
}

///////////////////////////////////////////////////////////////////////////
Bigint operator-(const Bigint& lhs, const Bigint& rhs)
{
    Bigint temp(lhs);
    temp -= rhs;
    return temp;
}

///////////////////////////////////////////////////////////////////////////
Bigint& Bigint::operator*=(const Bigint& rhs)
{
    Bigint temp;

    for (int i = 0; i <= rhs.lastDigitIndex_; ++i) {
        int maxj = rhs.vDigits_[i] - '0';
        for (int j = 1; j <= maxj; ++j) 
            temp += (*this);

        shiftLeft(1);
    }
    temp.signbit_ = signbit_ * rhs.signbit_;
    (*this) = temp;
    removeZeros();
    return (*this);
}

///////////////////////////////////////////////////////////////////////////
Bigint& Bigint::operator/=(const Bigint& rhs) throw(DivideByZeroException)
{
    // avoid division by zero
    if (rhs == 0)
        throw DivideByZeroException();

    signbit_ *= rhs.signbit_;
    
    Bigint temp = rhs;
    temp.signbit_ = 1;

    Bigint row;                 // represent shifted row
    for (int i = lastDigitIndex_; i >= 0; --i) {
        row.shiftLeft(1);
        row.vDigits_[0] = vDigits_[i];
        vDigits_[i] = '0';
        while (row >= temp) {
            vDigits_[i]++;
            row -= temp;
        }
    }   
    removeZeros();
    return (*this);
}

///////////////////////////////////////////////////////////////////////////
Bigint Bigint::operator-() const
// unary operator, change sign
{
    Bigint temp(*this);
    temp.signbit_ *= -1;
    return temp;
}

///////////////////////////////////////////////////////////////////////////
Bigint operator*(const Bigint& lhs, const Bigint& rhs)
{
    Bigint temp(lhs);
    temp *= rhs;
    return temp;
}

///////////////////////////////////////////////////////////////////////////
Bigint operator/(const Bigint& lhs, const Bigint& rhs)
{ 
    Bigint temp = lhs;
    temp /= rhs;
    return temp;
}


///////////////////////////////////////////////////////////////////////////
Bigint operator^(const Bigint& lhs, const Bigint& rhs)
{
    Bigint temp = lhs;
    temp ^= rhs;
    return temp;
}

///////////////////////////////////////////////////////////////////////////
Bigint& Bigint::operator^=(const Bigint& rhs) throw(UndefinedException)
// a^n = a^(n/2) * a^(n/2) * a^(n mod 2)
{
    // special cases
    if (*this == 1) return (*this);   // 1^n = 1 (sign doesn't matter) (*1)
    if (*this == 0) 
        throw UndefinedException();   // 0^n isn't defined
    if (rhs < 0) {
        *this = 0;
        return (*this);      // return integer part (evaluate after (*1))
    }
    if (rhs == 0) {
        *this = 1;
        return (*this);      // return integer part (evaluate after (*1))
    }
    if (rhs == 1) return (*this);

    // see Algorithms from Sedgewick page 46
    // method: convert rhs N to binary and sweep from left to right
    // starting with 1 in accumulator AC. At each step power AC to 2
    // and multiply by x when there is a 1 in the binary 
    // representation of N

    Bigint base2 = rhs.changeBase(2),
           acum = 1;

    for (int i = base2.lastDigitIndex_; i >= 0; --i) {
        Bigint temp = acum;               // TODO: fix this bottleneck!
        acum *= temp;
        //acum *= acum;                   // TODO: check why this instruction loops infinitely
        if (base2.vDigits_[i] == '1') 
            acum *= (*this);
    }
    (*this) = acum;
    return (*this);
}

///////////////////////////////////////////////////////////////////////////
Bigint Bigint::operator%(const Bigint& rhs) const
{
    Bigint res = *this;
    res /= rhs;
    return (*this - (res * rhs));
}

///////////////////////////////////////////////////////////////////////////
int Bigint::operator%(int rhs) const
{
    Bigint res = *this;
    res /= (Bigint)rhs;
    return (*this - (res * rhs)).toInt();
}

///////////////////////////////////////////////////////////////////////////
std::ostream &operator<<(std::ostream& os, const Bigint& rhs) 
{
    std::string output;
    if (rhs.signbit_ == -1) 
        output = "-";
    for (int i = rhs.lastDigitIndex_; i >= 0; --i)
        output += rhs.vDigits_[i];
    return (os << output);
}

///////////////////////////////////////////////////////////////////////////
std::istream &operator>>(std::istream& is, Bigint& rhs) 
{
    std::string input;
    is >> input;
    rhs = Bigint(input);
    return is;
}

///////////////////////////////////////////////////////////////////////////
Bigint Bigint::absolute() const
{
    Bigint temp(*this);
    temp.signbit_ = 1;
    return temp;
}

///////////////////////////////////////////////////////////////////////////
Bigint& Bigint::removeZeros()
{
    while ((lastDigitIndex_ > 0) && (vDigits_[lastDigitIndex_] == '0'))
        lastDigitIndex_--;

    // avoid -0
    if ((lastDigitIndex_ == 0) && (vDigits_[0] == '0'))
        signbit_ = 1;

    return (*this);
}

///////////////////////////////////////////////////////////////////////////
Bigint& Bigint::shiftLeft(int d = 1)
// multiply by 10^d
{
    if ((lastDigitIndex_ == 0) && (vDigits_[0] == '0')) 
        return (*this);

    // TODO: optimize to avoid resizing on each shift
    vDigits_.resize(lastDigitIndex_ + d + 1);
    for (int i = lastDigitIndex_; i >= 0; --i)
        vDigits_[i+d] = vDigits_[i];

    for (int j = 0; j < d; ++j)
        vDigits_[j] = '0';

    lastDigitIndex_ += d;
    return (*this);
}

///////////////////////////////////////////////////////////////////////////
Bigint& Bigint::shiftRight(int d)
// divide by 10^d
{
    if ((lastDigitIndex_ == 0) && (vDigits_[0] == '0')) 
        return (*this);

    if (d > lastDigitIndex_) {
        // set to 0
        lastDigitIndex_ = 0;
        vDigits_[0] = '0';
        return (*this);
    }
    for (int i = lastDigitIndex_; i >= d; --i)
        vDigits_[i-d] = vDigits_[i];

    lastDigitIndex_ -= d;
    return (*this);
}

///////////////////////////////////////////////////////////////////////////
bool Bigint::isPalindrome() const
{
    int i = 0;
    while (i <= (lastDigitIndex_ / 2)) {
        if (vDigits_[i] != vDigits_[lastDigitIndex_ - i])
            return false;
        i++;
    }
    return true;
}

///////////////////////////////////////////////////////////////////////////
Bigint Bigint::reverse() const
{
    Bigint temp(*this);
    for (int i = 0; (i <= lastDigitIndex_); ++i) {
        temp.vDigits_[i]= vDigits_[lastDigitIndex_ - i];
    }
    return temp;
}

///////////////////////////////////////////////////////////////////////////
int Bigint::toInt() const throw(OverflowException)
{
    Bigint temp(INT_MAX);
    if (compareAbsolute(*this, temp) == -1)
        throw OverflowException();

    int out = 0,
        weight = 1;
    
    for (int i = 0; i <= lastDigitIndex_; ++i) {
        out += weight * (vDigits_[i] - '0');
        weight *= 10;
    }
    return out;
}

///////////////////////////////////////////////////////////////////////////
long Bigint::toLong() const throw(OverflowException)
{
    Bigint temp(LONG_MAX);
    if (compareAbsolute(*this, temp) == -1)
        throw OverflowException();

    int out = 0,
        weight = 1;
    
    for (int i = 0; i <= lastDigitIndex_; ++i) {
        out += weight * (vDigits_[i] - '0');
        weight *= 10;
    }
    return out;
}

///////////////////////////////////////////////////////////////////////////
std::string Bigint::toString() const
{
    std::string temp;
    int offset = 0;
    if (signbit_ == -1) {
        temp.resize(lastDigitIndex_ + 2);
        temp[0] = '-';
        offset++;
    } else
        temp.resize(lastDigitIndex_ + 1);

    for (int i = lastDigitIndex_, j = offset; i >= 0; --i, ++j)
        temp[j] = vDigits_[i];

    return temp;
}

///////////////////////////////////////////////////////////////////////////
Bigint Bigint::decToBase(int b) const
// convert from base b to decimal
// condition: b <= 36
{
    /* special cases */
    if (b == 10) return (*this);
    if (b < 2) return Bigint(0);
    if (*this == 0) return Bigint(0);
    if (b > 36) return Bigint(0);       // restriction
    
    Bigint tmp = (*this).absolute(),
           logb = 0,
           out = 0;
    
    // find integer log in base b, to calculate array size
    while (tmp >= b) {
        tmp /= b;
        logb++;
    }
    tmp = (*this).absolute();
    out.vDigits_.resize((logb + 1).toInt(), '0');

    // std::vector initializes digits with 0
    out.lastDigitIndex_ = -1;
    while (tmp > 0) {
        out.lastDigitIndex_++;
        Bigint resto = tmp % b;
        int iresto = resto.toInt();
        //out.vDigits_[out.lastDigitIndex_] = resto.toInt() + '0';
        if (iresto <= 9)
            out.vDigits_[out.lastDigitIndex_] = iresto + '0';
        else
            out.vDigits_[out.lastDigitIndex_] = iresto - 10 + 'A';
        tmp /= b;
    }
    // keep sign
    if ((*this) < 0) out *= -1;
    return out;
}

///////////////////////////////////////////////////////////////////////////
Bigint Bigint::baseToDec(int b) const
// convert from base b to decimal
// condition: b <= 36
{
    /* special cases */
    if (b == 10) return (*this);
    if ((*this) == 0) return Bigint(0);
    if (b > 36) return Bigint(0);       // restriction
    
    Bigint out = 0,
           bn = 1;
    
    for (int i = 0; i <= (*this).lastDigitIndex_; ++i) {
        if ((*this).vDigits_[i] <= '9') 
            out += bn * ((*this).vDigits_[i] - '0');
        else
            out += bn * ((*this).vDigits_[i] - 'A' + 10);
        bn *= b;
    }
    // keep sign
    if ((*this) < 0) out *= -1;
    return out;
}

///////////////////////////////////////////////////////////////////////////
Bigint Bigint::changeBase(unsigned int b1, unsigned int b2) const
// convert from base b1 to base b2
// precondition: bigint is correctly expressed in base b1
{
    // convert from b1 to decimal, then from decimal to b2
    return ((*this).baseToDec(b1)).decToBase(b2);
}

///////////////////////////////////////////////////////////////////////////
bool Bigint::baseOk(unsigned int b) const
// returns true if number is correctly expressed in base b
{
    int base;
    base = (b <= 9) ? b + '0' : b + 'A' - 10;

    for (int i = 0; i <= (*this).lastDigitIndex_; ++i)
        if ((*this).vDigits_[i] >= base)
            return false;
    return true;
}

///////////////////////////////////////////////////////////////////////////
Bigint Bigint::factorial() const
{
    Bigint temp(*this);
    for (Bigint i = (*this) - 1; i > 1; --i)
        temp *= i;
    return temp;
}

///////////////////////////////////////////////////////////////////////////
int Bigint::minBase() const
// returns minimum base in which the number can be correctly expressed
{
    int base = 0;

    for (int i = 0; i <= (*this).lastDigitIndex_; ++i) {
        if ((*this).vDigits_[i] > base)
            base = (*this).vDigits_[i];
    }
    if (base > '9') 
        base = base - 'A' + 11;
    else
        base = base - '0' + 1;
    return base;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////
//	MAIN PROGRAM
///////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{
	// redirect input and output
	#ifndef ONLINE_JUDGE 
		cin.rdbuf((new std::ifstream("input"))->rdbuf()); 
		cout.rdbuf((new std::ofstream("output"))->rdbuf()); 
	#endif 


	string line;
	std::getline(cin, line);
	while ((line[0] != '#') && !cin.eof()) {
		// PROCESS
		// obtain the message number
		// 2^1024 contains 309 digits		
		Bigint power(65536, 310);	// 2^16 = 65536
		Bigint m(0, 310);
		for (int i = (int)line.length() - 1; i >= 0; i--) {
			m += power * line[i];
			power *= 256;		// 2^8 = 256
		}
		// (m^256 + crc) % g = 0
		const int g = 34943;
		int r = m % g;
		int crc = 0;
		if (r != 0)
			crc = g - r;

#ifdef DEBUG
		cout << "r " << r << "\t\tm " << m << endl;
#endif

		// SHOW OUTPUT
		// output in hex format, separating bytes with space
		std::ostringstream os;
		os.setf(std::ios::hex, std::ios::basefield);
		os << std::setw(4) << std::setfill('0') << std::ios::uppercase << crc << endl;

		std::istringstream is(os.str());
		string number;
		is >> number;
		// now number is formatted
		cout << number.substr(0,2) << " " << number.substr(2,2) << endl;

		// READ NEXT INPUT
		std::getline(cin, line);
	}
		
#ifdef DEBUG
	cout << START_DEBUG;

	cout << END_DEBUG;
#endif
	
	return 0;
}

/* @END_OF_SOURCE_CODE */

