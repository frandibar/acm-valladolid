/* @JUDGE_ID:  40922FK  495  C++  */
/* @BEGIN_OF_SOURCE_CODE */    
/**************************************************************************
 Solution to Problem 495 - Fibonacci Freeze
 by: Francisco Dibar
 date: Feb-23-2005
**************************************************************************/

//#define ONLINE_JUDGE 
#include <iostream>
#ifndef ONLINE_JUDGE 
	#include <fstream>
#endif 
#include <vector>

using namespace std;

/**************************************************************************
 BIGINT Library Header
 by: Francisco Dibar
 date: Feb-18-2005
**************************************************************************/

#if !defined(_BIGINT_H__)
#define _BIGINT_H__

#define PLUS	1		// positive sign bit
#define MINUS	-1		// negative sign bit
#define DEFAULT_DIGITS	64

//#include<vector>
#include<string>

//using namespace std;

class bigint {
private:
	vector<char> digits;
	int signbit;
	int lastdigit;		// index of high order digit

protected:
	int compare(const bigint &, const bigint &) const;
	bigint &zero_justify();
	bigint &digit_shift(int);

public:
	bigint(long nro = 0, long size = DEFAULT_DIGITS);
	bigint(const string &, long size = DEFAULT_DIGITS);
	bigint(const bigint &);	// constructor copia

	friend ostream &operator<<(ostream &, const bigint &);
	friend istream &operator>>(istream &, bigint &);

	bigint &operator=(const bigint &);
	bigint operator+(const bigint &) const;
	bigint operator-(const bigint &) const;
	bigint operator-() const;
	bigint operator*(const bigint &) const;
	bigint operator/(const bigint &) const;
	bigint operator%(const bigint &) const;

	bigint &operator+=(const bigint &);
	bigint &operator-=(const bigint &);
	bigint &operator*=(const bigint &);
	bigint &operator/=(const bigint &);

	bool operator==(const bigint &) const;
	bool operator!=(const bigint &) const;
	bool operator<(const bigint &) const;
	bool operator>(const bigint &) const;
	bool operator<=(const bigint &) const;
	bool operator>=(const bigint &) const;

	bigint absolute() const;

	bigint &operator++();	// preincremento
	bigint operator++(int);	// postincremento
	bigint &operator--();	// predecremento
	bigint operator--(int);	// postdecremento

	bool is_palindrome() const;
	bigint reverse() const;
};

#endif

/**************************************************************************
 BIGINT Library Implementation
 by: Francisco Dibar
 date: Feb-17-2005
**************************************************************************/

//#include <iostream>

///////////////////////////////////////////////////////////////////////////
bigint::bigint(const bigint &nro)
{
	digits.resize(nro.lastdigit+1, '0');
	digits = nro.digits;

	signbit = nro.signbit;
	lastdigit = nro.lastdigit;
}

///////////////////////////////////////////////////////////////////////////
bigint::bigint(const string &nro, long size)
// asume nro en formato "-n" o "n", se admiten ceros al comienzo
{
	int offset = nro.find_first_of("123456789");
	// si no encuentra ninguno de los digitos, inicializar en 0
	if (offset == string::npos)
		*this = bigint(0);
	else {
		signbit = (nro[0] == '-') ? MINUS : PLUS;
		lastdigit = nro.length() - 1 - offset;

		digits.resize(lastdigit + 1, '0');
		for (int i = 0; i <= lastdigit; i++)
			digits[lastdigit - i] = nro[i + offset];
	}
}

///////////////////////////////////////////////////////////////////////////
bigint::bigint(long nro, long size)
{
	digits.resize(size, '0');

	// setear signo
	signbit = (nro >= 0) ? PLUS : MINUS;

	// vector inicializa digits en cero
	lastdigit = -1;
	int t = abs(nro);
	while (t > 0) {
		lastdigit++;
		digits[lastdigit] = (t % 10) + '0';
		t /= 10;
	}
	
	if (nro == 0) {
		lastdigit = 0;
		digits[0] = '0';
	}
	digits.resize(lastdigit+1, '0');
}

///////////////////////////////////////////////////////////////////////////
int bigint::compare(const bigint &a, const bigint &b) const
// devuelve PLUS si a < b, MINUS si b < a, y 0 si a = b
{
	if ((a.signbit == MINUS) && (b.signbit == PLUS)) return PLUS;
	if ((a.signbit == PLUS) && (b.signbit == MINUS)) return MINUS;

	if (b.lastdigit > a.lastdigit) return (PLUS * a.signbit);
	if (a.lastdigit > b.lastdigit) return (MINUS * a.signbit);
	// tienen = cant de digitos
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
bool bigint::operator==(const bigint &nro) const
{
	return (compare(*this, nro) == 0); 
}

///////////////////////////////////////////////////////////////////////////
bool bigint::operator!=(const bigint &nro) const
{
	return (compare(*this, nro) != 0); 
}

///////////////////////////////////////////////////////////////////////////
bool bigint::operator<(const bigint &nro) const
{
	return (compare(*this, nro) == 1); 
}

///////////////////////////////////////////////////////////////////////////
bool bigint::operator>(const bigint &nro) const
{
	return (compare(*this, nro) == -1); 
}

///////////////////////////////////////////////////////////////////////////
bool bigint::operator<=(const bigint &nro) const
{
	return (compare(*this, nro) >= 0); 
}

///////////////////////////////////////////////////////////////////////////
bool bigint::operator>=(const bigint &nro) const
{
	return (compare(*this, nro) <= 0); 
}

///////////////////////////////////////////////////////////////////////////
bigint &bigint::operator=(const bigint &nro)
{
	digits.resize(nro.lastdigit+1, '0');
	digits = nro.digits;

	signbit = nro.signbit;
	lastdigit = nro.lastdigit;
	return *this;
}

///////////////////////////////////////////////////////////////////////////
bigint &bigint::operator--()
// operador -- como prefijo (predecremento)
{
	*this -= bigint(1);
	return (*this);
}

///////////////////////////////////////////////////////////////////////////
bigint bigint::operator--(int)
// operador -- como sufijo (postdecremento)
{
	bigint temp = *this;
	*this -= bigint(1);
	return temp;
}

///////////////////////////////////////////////////////////////////////////
bigint &bigint::operator++()
// operador ++ como prefijo (preincremento)
{
	*this += bigint(1);
	return (*this);
}

///////////////////////////////////////////////////////////////////////////
bigint bigint::operator++(int) 
// operador ++ como sufijo (postincremento)
{
	bigint temp = *this;
	*this += bigint(1);
	return temp;
}

///////////////////////////////////////////////////////////////////////////
bigint &bigint::operator+=(const bigint &nro)
{
	bigint temp = nro;
	*this = *this + temp;
	return (*this);
}

///////////////////////////////////////////////////////////////////////////
bigint &bigint::operator-=(const bigint &nro)
{
	bigint temp = nro;
	*this = *this - temp;
	return (*this);
}

///////////////////////////////////////////////////////////////////////////
bigint &bigint::operator*=(const bigint &nro)
{
	bigint temp = nro;
	*this = *this * temp;
	return (*this);
}

///////////////////////////////////////////////////////////////////////////
bigint &bigint::operator/=(const bigint &nro)
{
	bigint temp = nro;
	*this = *this / temp;
	return (*this);
}

///////////////////////////////////////////////////////////////////////////
bigint bigint::operator+(const bigint &nro) const
{
	// a + b siendo b = nro
	bigint res(*this);
	if (signbit == nro.signbit)
		res.signbit = signbit;
	else {
		if (signbit == MINUS){
			// devuelvo b - abs(a)
			return ((bigint)nro - res.absolute());
		} else {
			// devuelvo a - abs(b)
			return (res - (bigint)nro.absolute());
		}
	}
	// efectuo la suma, independientemente del signo
	res.lastdigit = max(lastdigit, nro.lastdigit) + 1;
	res.digits.resize(res.lastdigit + 1, '0');
	int carry = 0;
	for (int i = 0; i <= res.lastdigit; i++) {
		int adigit = (i <= lastdigit) ? digits[i] - '0' : 0;
		int bdigit = (i <= nro.lastdigit) ? nro.digits[i] - '0' : 0;
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
bigint bigint::operator-(const bigint &nro) const
// nro no es const aunque no se modifica, para evitar tener que inicializar 
// una variable auxiliar con el signo contrario
{
	// a - b siendo b = nro
	bigint res(*this);
	if ((signbit == MINUS) || (nro.signbit == MINUS)) {
		bigint temp = -nro;	// (-a) - b = -a + (-b)
		res += nro;				// a - (-b) = a + b
		return res;				// (-a) - (-b) = -a + b = b - a
	}

	if (res < nro) {
		res = nro - res;
		res.signbit = MINUS;
		return res;
	}

	res.lastdigit = max(lastdigit, nro.lastdigit);
	int borrow = 0;
	for (int i = 0; i <= res.lastdigit; i++) {
		int adigit = (i <= nro.lastdigit) ? nro.digits[i] - '0' : 0;
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
bigint bigint::operator*(const bigint &nro) const
{
	bigint res, 
			 row = *this;

	for (int i = 0; i <= nro.lastdigit; i++) {
		for (int j = 1; j <= nro.digits[i]-'0'; j++) 
			res += row;

		row.digit_shift(1);
	}
	res.signbit = signbit * nro.signbit;
   return res.zero_justify();
}

///////////////////////////////////////////////////////////////////////////
bigint bigint::operator/(const bigint &nro) const
{
	// evitar division por cero
	if (nro == 0) return (bigint)0;

	bigint res = *this,	// inicializo para evitar un resize
			 a = *this,
			 b = nro;
	
	res.signbit = signbit * nro.signbit;
	
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
bigint bigint::operator%(const bigint &nro) const
// division modulo, devuelve el resto de dividir por nro
{
	bigint res = *this;
	res /= nro;
	return (*this - (res * nro));
}

///////////////////////////////////////////////////////////////////////////
ostream &operator<<(ostream &os, const bigint &bi) 
{
	string salida;
	if (bi.signbit == MINUS) 
		salida = "-";
	for (int i = bi.lastdigit; i >= 0; i--)
		salida += bi.digits[i];
	return (os << salida);
}

///////////////////////////////////////////////////////////////////////////
istream &operator>>(istream &is, bigint &bi) 
{
	string input;
	is >> input;
	bi = bigint(input);
	return is;
}

///////////////////////////////////////////////////////////////////////////
bigint bigint::absolute() const
// devuelve el valor absoluto del nro 
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
bigint &bigint::digit_shift(int d)
// multiplica por 10^d
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
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
bigint fibonacci(int n, int *max, vector<bigint>& vec_fibo)
// vec_fibo es un vector de la serie precalculada (max valores)
{
	if (n >= *max) {
		// precalcular valores
		vec_fibo.resize(n+1);
		for (int i = *max; i <= n; i++)
			vec_fibo[i] = vec_fibo[i-1] + vec_fibo[i-2];
		*max = n;
	}
	return vec_fibo[n];
}

///////////////////////////////////////////////////////////////////////////
//	PROGRAMA PRINCIPAL
///////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{
	// redireccionar la entrada y salida
	#ifndef ONLINE_JUDGE 
		cin.rdbuf((new ifstream("input.txt"))->rdbuf()); 
		cout.rdbuf((new ofstream("output.txt"))->rdbuf()); 
	#endif 

	int n, 
		 max = 2;		// cant de valores precalculados
	cin >> n;
	vector<bigint> vec_fibo(n);		// valores precalculados

	vec_fibo[0] = 0;
	vec_fibo[1] = 1;

	while (!cin.eof()) {
		cout << fibonacci(n, &max, vec_fibo) << endl;
		cin >> n;
	}
	return 0;
}

/* @END_OF_SOURCE_CODE */

