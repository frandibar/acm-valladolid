/* @JUDGE_ID:  40922FK  575  C++  */
/* @BEGIN_OF_SOURCE_CODE */    
/**************************************************************************
 Solution to Problem 575 - Skew Binary
 by: Francisco Dibar
 date: Mar-10-2005
**************************************************************************/

//#define ONLINE_JUDGE 
#include <iostream>
#ifndef ONLINE_JUDGE 
	#include <fstream>
#endif 

using namespace std;

/**************************************************************************
 BIGINT Library Header
 by: Francisco Dibar
 date: Mar-10-2005
**************************************************************************/

#if !defined(_BIGINT_H__)
#define _BIGINT_H__

#define PLUS	1		// positive sign bit
#define MINUS	-1		// negative sign bit
#define DEFAULT_DIGITS	64

#include<vector>
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

	bigint dec_a_base(int) const;
	bigint base_a_dec(int) const;

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
	bigint operator^(const bigint &) const;

	bigint &operator+=(const bigint &);
	bigint &operator-=(const bigint &);
	bigint &operator*=(const bigint &);
	bigint &operator/=(const bigint &);
	bigint &operator^=(const bigint &);

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

	bigint cambio_base(int, int) const;
	bigint cambio_base(int b) const { return dec_a_base(b); }
	int to_int() const;

	bool is_palindrome() const;
	bigint reverse() const;
	long skew() const;
};

#endif

/**************************************************************************
 BIGINT Library Implementation
 by: Francisco Dibar
 date: Mar-10-2005
**************************************************************************/

//#include <iostream>
//#include <string>
//#include <vector>

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

	/* REVISAR, optimizar para no hacer copia de bigint
	bigint res, 
			 row = *this;

	for (int i = 0; i <= nro.lastdigit; i++) {
		int maxj = nro.digits[i] - '0';
		for (int j = 1; j <= maxj; j++) 
			res += row;

		row.digit_shift(1);
	}
	res.signbit = signbit * nro.signbit;
   return res.zero_justify();
*/
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
		int maxj = nro.digits[i] - '0';
		for (int j = 1; j <= maxj; j++) 
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
bigint bigint::operator^(const bigint &nro) const
// a^n = a^(n/2) * a^(n/2) * a^(n mod 2)
{
	/* contemplar casos especiales */
	if (*this == 1) return 1;	// 1^n = 1 (no importa el signo de n) (*1)
	if (*this == 0) return 0;	// 0^n no esta definido
	if (nro < 0) return 0;		// se devuelve entero (luego de (*1))
	if (nro == 0) return 1;
	if (nro == 1) return *this;

	/* ver Algorithms de Sedgewick pag. 46 */
	/* metodo: convertir el nro N a binario y recorrerlo de izquierda
	   a derecha empezando con 1 en el acumulador AC. A cada paso 
		se eleva el AC al cuadrado y se multiplica por x cuando
		hay un 1 en la representacion binaria de N */

	bigint base2 = nro.cambio_base(2),
			 acum = 1;

	for (int i = base2.lastdigit; i >= 0; i--) {
		acum *= acum;		// REVISAR: aca hay cuello de botella
		if (base2.digits[i] == '1') 
			acum *= (*this);
	}
	return acum;
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
bigint bigint::dec_a_base(int b) const
// convierte de base decimal a base b
// condicion: b <= 10
{
	/* contemplar casos especiales */
	if (b == 10) return (*this);
	if (b < 2) return bigint(0);
	if (*this == 0) return bigint(0);
	if (b > 10) return bigint(0);		// Restriccion
	
	bigint tmp = *this,
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
		out.digits[out.lastdigit] = resto.to_int() + '0';
		tmp /= b;
	}
	return out;
}

///////////////////////////////////////////////////////////////////////////
bigint bigint::base_a_dec(int b) const
// convierte de base b a base decimal
// condicion: b <= 10
{
	/* contemplar casos especiales */
	if (b == 10) return (*this);
	if (*this == 0) return bigint(0);
	if (b > 10) return bigint(0);		// Restriccion
	
	bigint out = 0,
			 bn = 1;
	
	for (int i = 0; i <= (*this).lastdigit; i++) {
		out += bn * ((*this).digits[i] - '0');
		bn *= b;
	}
	return out;
}

///////////////////////////////////////////////////////////////////////////
bigint bigint::cambio_base(int b1, int b2) const
// convierte de base b1 a base b2
{
	// convierto de b1 a base decimal, y luego de decimal a b1
	return ((*this).base_a_dec(b1)).dec_a_base(b2);
}

///////////////////////////////////////////////////////////////////////////
long bigint::skew() const
{
	long out = 0,
		  bn = 1;
	
	for (int i = 0; i <= (*this).lastdigit; i++) {
		out += bn * ((*this).digits[i] - '0');
		bn = (bn + 1) * 2 - 1;
	}
	return out;

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

	bigint n;
	cin >> n;
	while (!cin.eof() && (n != 0)) {
		cout << n.skew() << endl;
		cin >> n;
	}
	return 0;
}

/* @END_OF_SOURCE_CODE */

