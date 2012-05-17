/* @JUDGE_ID:  40922FK  10259  C++  */
/* @BEGIN_OF_SOURCE_CODE */    
/**************************************************************************
 Solution to Problem 10259 - The Priest Mathematician
 by: Francisco Dibar
 date: Jul-29-2006
**************************************************************************/

//#define DEBUG
//#define ONLINE_JUDGE 
#include <iostream>
#ifndef ONLINE_JUDGE 
	#include <fstream>
#endif 
#include <vector>
#include <string>

#ifdef DEBUG
    #define START_DEBUG	"START DEBUG ********************************************************************\n"
    #define END_DEBUG	"END DEBUG **********************************************************************\n"
    // g++-2.95 doesn't support asserts
    #define ASSERT(x,y)   if (!(x)) { std::cerr << "ASSERTION FAILED!: " << y << "\n"; exit(1); }
#endif

using std::cin;
using std::cout;
using std::endl;

using std::vector;
using std::string;
using std::ostream;
using std::istream;

/**************************************************************************
 BIGINT Library Header
 by: Francisco Dibar
 date: Dec-30-2005
 uses: vector, string
**************************************************************************/

const int PLUS  = 1;	    	// positive sign bit
const int MINUS = -1;	        // negative sign bit
const int DEFAULT_DIGITS = 64;

///////////////////////////////////////////////////////////////////////////
class bigint {
private:

	vector<char> digits;
	int signbit;
	int lastdigit;		// index of high order digit

protected:

	int compare(const bigint&, const bigint&) const;
	bigint& zero_justify();
	bigint& digit_shift(int);

	bigint dec_to_base(int) const;
	bigint base_to_dec(int) const;

public:

	// constructors
	bigint(long num = 0, long size = DEFAULT_DIGITS);
	bigint(const string&, long size = DEFAULT_DIGITS);
	bigint(const bigint&);	// copy constructor

	// overloaded operators
	bigint& operator=(const bigint&);
	bigint operator+(const bigint&) const;
	bigint operator-(const bigint&) const;
	bigint operator-() const;
	bigint operator*(const bigint&) const;
	bigint operator/(const bigint&) const;
	bigint operator%(const bigint&) const;
	int operator%(int) const;
	bigint operator^(const bigint&) const;

	bigint& operator+=(const bigint&);
	bigint& operator-=(const bigint&);
	bigint& operator*=(const bigint&);
	bigint& operator/=(const bigint&);
	bigint& operator^=(const bigint&);

	friend std::ostream &operator<<(std::ostream&, const bigint&);
	friend std::istream &operator>>(std::istream&, bigint&);

	// comparison operators
	inline bool operator==(const bigint&) const;
	inline bool operator!=(const bigint&) const;
	inline bool operator<(const bigint&) const;
	inline bool operator>(const bigint&) const;
	inline bool operator<=(const bigint&) const;
	inline bool operator>=(const bigint&) const;

	inline bigint &operator++();		// preincrement
	inline bigint operator++(int);	// postincrement
	inline bigint &operator--();		// predecrement
	inline bigint operator--(int);	// postdecrement

	bigint absolute() const;

	bool base_ok(int base) const;
	int min_base() const;
	bigint cambio_base(int, int) const;
	bigint cambio_base(int base) const { return dec_to_base(base); }
	
	int to_int() const;

	bool is_palindrome() const;
	bigint reverse() const;
};


/**************************************************************************
 BIGINT Library Implementation
 by: Francisco Dibar
 date: Dec-30-2005
**************************************************************************/

///////////////////////////////////////////////////////////////////////////
bigint::bigint(const bigint& num)
{
	digits.resize(num.lastdigit+1, '0');
	digits = num.digits;

	signbit = num.signbit;
	lastdigit = num.lastdigit;
}

///////////////////////////////////////////////////////////////////////////
bigint::bigint(const string& num, long size)
// asumes num format is "-n" o "n", no 0's at beginning
{
	// accept any base
	int offset = num.find_first_of("123456789ABCDEFGHIJKLMNOPQRSTUVWXY");
	// if none of those digits are found, initialize with 0
	if (offset == (int)string::npos)
		*this = bigint(0);
	else {
		signbit = (num[0] == '-') ? MINUS : PLUS;
		lastdigit = num.length() - 1 - offset;

		digits.resize(lastdigit + 1, '0');
		for (int i = 0; i <= lastdigit; i++)
			digits[lastdigit - i] = num[i + offset];
	}
}

///////////////////////////////////////////////////////////////////////////
bigint::bigint(long num, long size)
{
	digits.resize(size, '0');

	// set sign
	signbit = (num >= 0) ? PLUS : MINUS;

	// vector inicializes digits with 0
	lastdigit = -1;
	int t = abs(num);
	while (t > 0) {
		lastdigit++;
		digits[lastdigit] = (t % 10) + '0';
		t /= 10;
	}
	
	if (num == 0) {
		lastdigit = 0;
		digits[0] = '0';
	}
	digits.resize(lastdigit + 1, '0');
}

///////////////////////////////////////////////////////////////////////////
int bigint::compare(const bigint& a, const bigint& b) const
// returns PLUS if a < b, MINUS if b < a, 0 if a = b
{
	if ((a.signbit == MINUS) && (b.signbit == PLUS)) return PLUS;
	if ((a.signbit == PLUS) && (b.signbit == MINUS)) return MINUS;

	if (b.lastdigit > a.lastdigit) return (PLUS * a.signbit);
	if (a.lastdigit > b.lastdigit) return (MINUS * a.signbit);
	// = amount of digits
	for (int i = a.lastdigit; i >= 0; i--) {
		if (a.digits[i] > b.digits[i])
			return (MINUS * a.signbit);
		if (b.digits[i] > a.digits[i])
			return (PLUS * a.signbit);
	}
	// a = b
	return 0;
}

///////////////////////////////////////////////////////////////////////////
inline bool bigint::operator==(const bigint& num) const
{
	return (compare(*this, num) == 0); 
}

///////////////////////////////////////////////////////////////////////////
inline bool bigint::operator!=(const bigint& num) const
{
	return (compare(*this, num) != 0); 
}

///////////////////////////////////////////////////////////////////////////
inline bool bigint::operator<(const bigint& num) const
{
	return (compare(*this, num) == 1); 
}

///////////////////////////////////////////////////////////////////////////
inline bool bigint::operator>(const bigint& num) const
{
	return (compare(*this, num) == -1); 
}

///////////////////////////////////////////////////////////////////////////
inline bool bigint::operator<=(const bigint& num) const
{
	return (compare(*this, num) >= 0); 
}

///////////////////////////////////////////////////////////////////////////
inline bool bigint::operator>=(const bigint& num) const
{
	return (compare(*this, num) <= 0); 
}

///////////////////////////////////////////////////////////////////////////
bigint& bigint::operator=(const bigint& num)
{
	digits.resize(num.lastdigit+1, '0');
	digits = num.digits;

	signbit = num.signbit;
	lastdigit = num.lastdigit;
	return *this;
}

///////////////////////////////////////////////////////////////////////////
inline bigint &bigint::operator--()
// operator -- as prefix (predecrement)
{
	*this -= bigint(1);
	return (*this);
}

///////////////////////////////////////////////////////////////////////////
inline bigint bigint::operator--(int)
// operator -- as sufix (postdecrement)
{
	bigint temp = *this;
	*this -= bigint(1);
	return temp;
}

///////////////////////////////////////////////////////////////////////////
inline bigint &bigint::operator++()
// operator ++ as prefix (preincrement)
{
	*this += bigint(1);
	return (*this);
}

///////////////////////////////////////////////////////////////////////////
inline bigint bigint::operator++(int) 
// operator ++ as sufix (postincrement)
{
	bigint temp = *this;
	*this += bigint(1);
	return temp;
}

///////////////////////////////////////////////////////////////////////////
bigint &bigint::operator+=(const bigint& num)
{
	bigint temp = num;
	*this = *this + temp;
	return (*this);
}

///////////////////////////////////////////////////////////////////////////
bigint &bigint::operator-=(const bigint& num)
{
	bigint temp = num;
	*this = *this - temp;
	return (*this);
}

///////////////////////////////////////////////////////////////////////////
bigint &bigint::operator*=(const bigint& num)
{
	bigint temp = num;
	*this = *this * temp;
	return (*this);

	/* REVISAR, optimizar para no hacer copia de bigint
	bigint res, 
			 row = *this;

	for (int i = 0; i <= num.lastdigit; i++) {
		int maxj = num.digits[i] - '0';
		for (int j = 1; j <= maxj; j++) 
			res += row;

		row.digit_shift(1);
	}
	res.signbit = signbit * num.signbit;
   return res.zero_justify();
*/
}

///////////////////////////////////////////////////////////////////////////
bigint &bigint::operator/=(const bigint& num)
{
	bigint temp = num;
	*this = *this / temp;
	return (*this);
}

///////////////////////////////////////////////////////////////////////////
bigint bigint::operator+(const bigint& num) const
{
	// a + b with b = num
	bigint res(*this);
	if (signbit == num.signbit)
		res.signbit = signbit;
	else {
		if (signbit == MINUS){
			// return b - abs(a)
			return ((bigint)num - res.absolute());
		} else {
			// return a - abs(b)
			return (res - (bigint)num.absolute());
		}
	}
	// do the sum, independent of the sign
	res.lastdigit = std::max(lastdigit, num.lastdigit) + 1;
	res.digits.resize(res.lastdigit + 1, '0');
	int carry = 0;
	for (int i = 0; i <= res.lastdigit; i++) {
		int adigit = (i <= lastdigit) ? digits[i] - '0' : 0;
		int bdigit = (i <= num.lastdigit) ? num.digits[i] - '0' : 0;
		int sum = carry + adigit + bdigit;
		res.digits[i] = (sum % 10) + '0';
		carry = sum / 10;
	}
	return res.zero_justify();
}

///////////////////////////////////////////////////////////////////////////
bigint bigint::operator-() const
// unary operator, change sign
{
	bigint temp(*this);
	temp.signbit *= MINUS;
	return temp;
}

///////////////////////////////////////////////////////////////////////////
bigint bigint::operator-(const bigint& num) const
// num isn't const although it isn't modified, to avoid inicializing
// an auxiliary variable with the sign changed
{
	// a - b with b = num
	bigint res(*this);
	if ((signbit == MINUS) || (num.signbit == MINUS)) {
		bigint temp = -num;	// (-a) - b = -a + (-b)
		res += num;				// a - (-b) = a + b
		return res;				// (-a) - (-b) = -a + b = b - a
	}

	if (res < num) {
		res = num - res;
		res.signbit = MINUS;
		return res;
	}

	res.lastdigit = std::max(lastdigit, num.lastdigit);
	int borrow = 0;
	for (int i = 0; i <= res.lastdigit; i++) {
		int adigit = (i <= num.lastdigit) ? num.digits[i] - '0' : 0;
		int v = (res.digits[i] - '0' - borrow - adigit);
		if (res.digits[i] > '0')
			borrow = 0;
		if (v < 0) {
			v += 10;
			borrow = 1;
		}
		res.digits[i] = (v % 10) + '0';
	}
	return res.zero_justify();
}

///////////////////////////////////////////////////////////////////////////
bigint bigint::operator*(const bigint& num) const
{
	bigint res, 
			 row = *this;

	for (int i = 0; i <= num.lastdigit; i++) {
		int maxj = num.digits[i] - '0';
		for (int j = 1; j <= maxj; j++) 
			res += row;

		row.digit_shift(1);
	}
	res.signbit = signbit * num.signbit;
   return res.zero_justify();
}

///////////////////////////////////////////////////////////////////////////
bigint bigint::operator/(const bigint& num) const
{
	// evitar division por cero
	if (num == 0) return (bigint)0;

	bigint res = *this,	// inicializo para evitar un resize
			 a = *this,
			 b = num;
	
	res.signbit = signbit * num.signbit;
	
	a.signbit = PLUS;
	b.signbit = PLUS;

	res.lastdigit = lastdigit;

	bigint row;					// represent shifted row
	for (int i = lastdigit; i >= 0; i--) {
		row.digit_shift(1);
		row.digits[0] = digits[i];
		res.digits[i] = '0';
		while (row >= b) {
			res.digits[i] ++;
			row -= b;
		}
	}	
	return res.zero_justify();
}

///////////////////////////////////////////////////////////////////////////
bigint bigint::operator^(const bigint& num) const
// a^n = a^(n/2) * a^(n/2) * a^(n mod 2)
{
	/* special cases */
	if (*this == 1) return 1;	// 1^n = 1 (no importa el signo de n) (*1)
	if (*this == 0) return 0;	// 0^n no esta definido
	if (num < 0) return 0;		// se devuelve entero (evaluo luego de (*1))
	if (num == 0) return 1;
	if (num == 1) return *this;

	/* see Algorithms from Sedgewick page 46 */
	/* method: convert num N to binary and sweep from left to right
	   starting with 1 in accumulator AC. At each step power AC to 2
	   and multiply by x when there is a 1 in the binary 
	   representation of N
	*/

	bigint base2 = num.cambio_base(2),
			 acum = 1;

	for (int i = base2.lastdigit; i >= 0; i--) {
		acum *= acum;					// REVISAR: aca hay cuello de botella
		if (base2.digits[i] == '1') 
			acum *= (*this);
	}
	return acum;
}

///////////////////////////////////////////////////////////////////////////
bigint bigint::operator%(const bigint& num) const
{
	bigint res = *this;
	res /= num;
	return (*this - (res * num));
}

///////////////////////////////////////////////////////////////////////////
int bigint::operator%(int num) const
{
	bigint res = *this;
	res /= (bigint)num;
	return (*this - (res * num)).to_int();
}

///////////////////////////////////////////////////////////////////////////
ostream &operator<<(ostream& os, const bigint& bi) 
{
	string salida;
	if (bi.signbit == MINUS) 
		salida = "-";
	for (int i = bi.lastdigit; i >= 0; i--)
		salida += bi.digits[i];
	return (os << salida);
}

///////////////////////////////////////////////////////////////////////////
istream &operator>>(istream& is, bigint& bi) 
{
	string input;
	is >> input;
	bi = bigint(input);
	return is;
}

///////////////////////////////////////////////////////////////////////////
bigint bigint::absolute() const
{
	bigint temp(*this);
	temp.signbit = PLUS;
	return temp;
}

///////////////////////////////////////////////////////////////////////////
bigint &bigint::zero_justify()
{
	while ((lastdigit > 0) && (digits[lastdigit] == '0'))
		lastdigit--;

	if ((lastdigit == 0) && (digits[0] == '0'))
		signbit = PLUS;		/* hack to avoid -0 */

	return *this;
}

///////////////////////////////////////////////////////////////////////////
bigint& bigint::digit_shift(int d)
// multiply by 10^d
{
	if ((lastdigit == 0) && (digits[0] == '0')) 
		return *this;

	// REVISAR: estoy haciendo resize con cada shift. optimizar
	digits.resize(lastdigit + d + 1);
	for (int i = lastdigit; i >= 0; i--)
		digits[i+d] = digits[i];

	for (int j = 0; j < d; j++)
		digits[j] = '0';

	lastdigit += d;
	return *this;
}

///////////////////////////////////////////////////////////////////////////
bool bigint::is_palindrome() const
{
	int i = 0;
	while (i <= (lastdigit / 2)) {
		if (digits[i] != digits[lastdigit - i])
			return false;
		i++;
	}
	return true;
}

///////////////////////////////////////////////////////////////////////////
bigint bigint::reverse() const
{
	bigint temp(*this);
	for (int i = 0; (i <= lastdigit); i++) {
		temp.digits[i]= digits[lastdigit - i];
	}
	return temp;
}

///////////////////////////////////////////////////////////////////////////
int bigint::to_int() const
// note: if bigint doesn't fit in int, returns crap
{
	int out = 0,
		weight = 1;
	
	for (int i = 0; i <= lastdigit; i++) {
		out += weight * (digits[i] - '0');
		weight *= 10;
	}
	return out;
}

///////////////////////////////////////////////////////////////////////////
bigint bigint::dec_to_base(int b) const
// convert from base b to decimal
// condition: b <= 36
{
	/* special cases */
	if (b == 10) return (*this);
	if (b < 2) return bigint(0);
	if (*this == 0) return bigint(0);
	if (b > 36) return bigint(0);		// restriction
	
	bigint tmp = (*this).absolute(),
			 logb = 0,
			 out = 0;
	
	// find integer log in base b, to calculate array size
	while (tmp >= b) {
		tmp /= b;
		logb++;
	}
	tmp = (*this).absolute();
	out.digits.resize((logb+1).to_int(), '0');

	// vector initializes digits with 0
	out.lastdigit = -1;
	while (tmp > 0) {
		out.lastdigit++;
		bigint resto = tmp % b;
		int iresto = resto.to_int();
		//out.digits[out.lastdigit] = resto.to_int() + '0';
		if (iresto <= 9)
			out.digits[out.lastdigit] = iresto + '0';
		else
			out.digits[out.lastdigit] = iresto - 10 + 'A';
		tmp /= b;
	}
	// keep sign
	if ((*this) < 0) out *= -1;
	return out;
}

///////////////////////////////////////////////////////////////////////////
bigint bigint::base_to_dec(int b) const
// convert from base b to decimal
// condition: b <= 36
{
	/* special cases */
	if (b == 10) return (*this);
	if ((*this) == 0) return bigint(0);
	if (b > 36) return bigint(0);		// restriction
	
	bigint out = 0,
			 bn = 1;
	
	for (int i = 0; i <= (*this).lastdigit; i++) {
		if ((*this).digits[i] <= '9') 
			out += bn * ((*this).digits[i] - '0');
		else
			out += bn * ((*this).digits[i] - 'A' + 10);
		bn *= b;
	}
	// keep sign
	if ((*this) < 0) out *= -1;
	return out;
}

///////////////////////////////////////////////////////////////////////////
bigint bigint::cambio_base(int b1, int b2) const
// convert from base b1 to base b2
// condition: num is correctly expressed in base b1
{
	// convert from b1 to decimal, then from decimal to b2
	return ((*this).base_to_dec(b1)).dec_to_base(b2);
}

///////////////////////////////////////////////////////////////////////////
bool bigint::base_ok(int b) const
// devuelve true si el num esta correctamente expresado en base b
{
	int base;
	base = (b <= 9) ? b + '0' : b + 'A' - 10;

	for (int i = 0; i <= (*this).lastdigit; i++)
		if ((*this).digits[i] >= base)
			return false;
	return true;
}

///////////////////////////////////////////////////////////////////////////
int bigint::min_base() const
// returns minimum base in which the number can be correctly expressed
{
	int base = 0;

	for (int i = 0; i <= (*this).lastdigit; i++) {
		if ((*this).digits[i] > base)
			base = (*this).digits[i];
	}
	if (base > '9') 
		base = base - 'A' + 11;
	else
		base = base - '0' + 1;
	return base;
}

///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

const int MAX = 10000;

// global variables storing amount of precalculated values
int nCalcHanoi = 0;
int nCalcPriest = 0;

bigint vHanoi[MAX];   // MAX space isn't really needed
bigint vPriest[MAX];  // stores # of moves for hanoi with 4 needles
// vPriest[k] = m, with k = # of discs means that m moves are necessary to solve it

///////////////////////////////////////////////////////////////////////////
void init()
// initialize array of precalculated values
{
    nCalcHanoi = 3;
    vHanoi[1] = 1;
    vHanoi[2] = 3;
    vHanoi[3] = 7;

    nCalcPriest = 3;
    vPriest[1] = 1;
    vPriest[2] = 3;
    vPriest[3] = 5;
}

////////////////////////////////////////////////////////////////////////////////
void precomputeHanoi(int n)
// precondition: init() has been executed
// calculate values so as to be able to obtain H(n)
{
    // H(n) = 2.H(n-1) + 1
    for (int i = nCalcHanoi+1; i <= n; ++i) {
        vHanoi[i] = vHanoi[i-1] * 2 + bigint(1);
        nCalcHanoi++;
    }
}

////////////////////////////////////////////////////////////////////////////////
void precomputePriest(int n)
// precondition: init() has been executed
// calculate values so as to be able to obtain P(n)
{
    // P(n) = min(2.P(n-k) + H(k)) for k = 0..n
    for (int i = nCalcPriest+1; i <= n; ++i) {
        bigint min = vPriest[i-1] * 2;
        min += vHanoi[1];
        for (int j = 1; (j <= i-1) && (vHanoi[j] < min); ++j) {
            // start loop with j=1 (redundant) to guarantee vHanoi[j] exists
            // calculate only needed hanoi values
            while (vHanoi[nCalcHanoi] < min)
                precomputeHanoi(nCalcHanoi+1);

            bigint temp = vPriest[i-j] * 2;
            temp += vHanoi[j];
            if (temp < min)
                min = temp;
        }
        vPriest[i] = min;
        nCalcPriest++;
    }
}

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

    init();

	int n;
	cin >> n;
    while (!cin.eof()) {
		// PROCESS AND SHOW OUTPUT
        precomputePriest(n);
        cout << vPriest[n] << endl;
		// READ NEXT INPUT
        cin >> n;
	}
		
#ifdef DEBUG
	cout << START_DEBUG;
    for (int i = 1; i <= nCalcPriest; ++i)
        cout << "Priest(" << i << ") =\t" <<  vPriest[i] << endl;
	cout << END_DEBUG;
#endif
	
	return 0;
}

/* @END_OF_SOURCE_CODE */

