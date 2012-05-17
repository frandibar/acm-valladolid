/* @JUDGE_ID:  40922FK  10494  C++  */
/* @BEGIN_OF_SOURCE_CODE */    
/**************************************************************************
 Solution to Problem 10494 - If we were Child Again
 by: Francisco Dibar
 date: Dec-28-2005
**************************************************************************/

//#define DEBUG
//#define ONLINE_JUDGE 
#include <iostream>
#ifndef ONLINE_JUDGE 
	#include <fstream>
#endif 
#include <vector>
#include <string>

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
 BIGINT Library Header
 by: Francisco Dibar
 date: Dec-17-2005
 uses: vector, string
**************************************************************************/

#define PLUS	1		// positive sign bit
#define MINUS	-1		// negative sign bit
#define DEFAULT_DIGITS	64

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
	int base_min() const;
	bigint cambio_base(int, int) const;
	bigint cambio_base(int base) const { return dec_to_base(base); }
	
	int to_int() const;

	bool is_palindrome() const;
	bigint reverse() const;
};


/**************************************************************************
 BIGINT Library Implementation
 by: Francisco Dibar
 date: Dec-17-2005
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
	// si no encuentra ninguno de los digitos, inicializar en 0
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
// operator ++ como sufix (postincrement)
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
	// a + b siendo b = num
	bigint res(*this);
	if (signbit == num.signbit)
		res.signbit = signbit;
	else {
		if (signbit == MINUS){
			// devuelvo b - abs(a)
			return ((bigint)num - res.absolute());
		} else {
			// devuelvo a - abs(b)
			return (res - (bigint)num.absolute());
		}
	}
	// efectuo la suma, independientemente del signo
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
// operador unario, cambia el signo
{
	bigint temp(*this);
	temp.signbit *= MINUS;
	return temp;
}

///////////////////////////////////////////////////////////////////////////
bigint bigint::operator-(const bigint& num) const
// num no es const aunque no se modifica, para evitar tener que inicializar 
// una variable auxiliar con el signo contrario
{
	// a - b siendo b = num
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
	/* contemplar casos especiales */
	if (*this == 1) return 1;	// 1^n = 1 (no importa el signo de n) (*1)
	if (*this == 0) return 0;	// 0^n no esta definido
	if (num < 0) return 0;		// se devuelve entero (evaluo luego de (*1))
	if (num == 0) return 1;
	if (num == 1) return *this;

	/* ver Algorithms de Sedgewick pag. 46 */
	/* metodo: convertir el num N a binario y recorrerlo de izquierda
	   a derecha empezando con 1 en el acumulador AC. A cada paso 
		se eleva el AC al cuadrado y se multiplica por x cuando
		hay un 1 en la representacion binaria de N */

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
// division modulo, devuelve el resto de dividir por num
{
	bigint res = *this;
	res /= num;
	return (*this - (res * num));
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
// devuelve el valor absoluto del num 
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
// si el valor de bigint no entra en un int, devuelve basura
{
	int out = 0,
		peso = 1;
	
	for (int i = 0; i <= lastdigit; i++) {
		out += peso * (digits[i] - '0');
		peso *= 10;
	}
	return out;
}

///////////////////////////////////////////////////////////////////////////
bigint bigint::dec_to_base(int b) const
// convierte de base decimal a base b
// condicion: b <= 36
{
	/* contemplar casos especiales */
	if (b == 10) return (*this);
	if (b < 2) return bigint(0);
	if (*this == 0) return bigint(0);
	if (b > 36) return bigint(0);		// Restriccion
	
	bigint tmp = (*this).absolute(),
			 logb = 0,
			 out = 0;
	
	// hallar el log entero en base b, para calcular el tamaño del array
	while (tmp >= b) {
		tmp /= b;
		logb++;
	}
	tmp = (*this).absolute();
	out.digits.resize((logb+1).to_int(), '0');

	// vector inicializa digits en cero
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
	// mantener el signo
	if ((*this) < 0) out *= -1;
	return out;
}

///////////////////////////////////////////////////////////////////////////
bigint bigint::base_to_dec(int b) const
// convierte de base b a base decimal
// condicion: b <= 36
{
	/* contemplar casos especiales */
	if (b == 10) return (*this);
	if ((*this) == 0) return bigint(0);
	if (b > 36) return bigint(0);		// Restriccion
	
	bigint out = 0,
			 bn = 1;
	
	for (int i = 0; i <= (*this).lastdigit; i++) {
		if ((*this).digits[i] <= '9') 
			out += bn * ((*this).digits[i] - '0');
		else
			out += bn * ((*this).digits[i] - 'A' + 10);
		bn *= b;
	}
	// mantener el signo
	if ((*this) < 0) out *= -1;
	return out;
}

///////////////////////////////////////////////////////////////////////////
bigint bigint::cambio_base(int b1, int b2) const
// convierte de base b1 a base b2
// condicion: el num esta correctamente expresado en base b1
{
	// convierto de b1 a base decimal, y luego de decimal a b1
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
int bigint::base_min() const
// devuelve la minima base en la cual el num esta correctamente expresado
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
//	MAIN PROGRAM
///////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{
	// redirect input and output
	#ifndef ONLINE_JUDGE 
		cin.rdbuf((new std::ifstream("input.txt"))->rdbuf()); 
		cout.rdbuf((new std::ofstream("output.txt"))->rdbuf()); 
	#endif 

	bigint x, y;
	char op;
	cin >> x >> op >> y;
	while (!cin.eof()) {		
		if (op == '/')
			cout << x / y << endl;
		else if (op == '%')
			cout << x % y << endl;
		cin >> x >> op >> y;
	}

#ifdef DEBUG
	cout << START_DEBUG;

	cout << END_DEBUG;
#endif

	return 0;
}

/* @END_OF_SOURCE_CODE */

