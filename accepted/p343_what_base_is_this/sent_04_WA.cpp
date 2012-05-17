/* @JUDGE_ID:  40922FK  343  C++  */
/* @BEGIN_OF_SOURCE_CODE */    
/**************************************************************************
 Solution to Problem 343 - What Base is This?
 by: Francisco Dibar
 date: Mar-15-2005
**************************************************************************/

//#define ONLINE_JUDGE 
#include <iostream>
#ifndef ONLINE_JUDGE 
	#include <fstream>
#endif 
#include <string>

#define MAX_BASE  36

using namespace std;

///////////////////////////////////////////////////////////////////////////
string dec_a_base(long nro, int b)
// convierte de base decimal a base b
// condicion: b <= MAX_BASE
{
	/* contemplar casos especiales */
	//if (b == 10) return itoa(..);
	if (b < 2) return "0";
	if (nro == 0) return "0";
	if (b > MAX_BASE) return "0";		// Restriccion
	
	long tmp = abs(nro),
		 logb = 0;
	
	string out;
	int offset = 0;
	// mantener el signo
	if (nro < 0) {
		out = "-";
		offset++;
	}
	while (tmp > 0) {
		int resto = tmp % b;
		if (resto <= 9)
			out += resto + '0';
		else
			out += resto - 10 + 'A';
		tmp /= b;
	}
	// invertir out desde la posicion offset en adelante
	for (int i = offset; i < ((int)out.length() - offset) / 2 + offset; i++) {
		char aux = out[i];
		out[i] = out[out.length() + offset - i - 1];
		out[out.length() + offset - i - 1] = aux;
	}
	return out;
}

///////////////////////////////////////////////////////////////////////////
long str_base_a_dec(string nro, int b)
// convierte nro de base b a base decimal
// condicion: b <= MAX_BASE
{
	/* contemplar casos especiales */
	if (b == 10) return atol(nro.c_str());

	// -00..0
	int offset = 0;
	bool cero = true;
	if (nro[0] == '-') 
		offset++;
	for (int i = offset; i < (int)nro.length(); i++)
		if (nro[i] != '0') cero = false;
	if (cero) return 0;

	if (b > MAX_BASE) return 0;		// Restriccion
	
	long out = 0,
		  bn = 1;
	offset = nro.find_first_of("123456789ABCDEFHIJKLMNOPQRSTUVWXYZ");
	if (offset != -1) {
		for (int i = (int)nro.length()-1; i >= offset ; i--) {
			if (nro[i] <= '9') 
				out += bn * (nro[i] - '0');
			else
				out += bn * (nro[i] - 'A' + 10);
			bn *= b;
		}
	}
	// mantener el signo
	if (nro[0] == '-') out *= -1;
	return out;
}

///////////////////////////////////////////////////////////////////////////
bool base_ok(string nro, int b)
// devuelve true si el nro esta correctamente expresado en base b
{
	int base;
	base = (b <= 9) ? b + '0' : b + 'A' - 10;

	for (int i = 0; i < (int)nro.length(); i++)
		if (nro[i] >= base)
			return false;
	return true;
}

///////////////////////////////////////////////////////////////////////////
int base_min(string nro)
// devuelve la minima base en la cual el nro esta correctamente expresado
{
	int base = 0;

	for (int i = 0; i < (int)nro.length(); i++) {
		if (nro[i] > base)
			base = nro[i];
	}
	if (base > '9') 
		base = base - 'A' + 11;
	else
		base = base - '0' + 1;
	
	if (base == 1) 
		return 2;
	else
		return base;
}

///////////////////////////////////////////////////////////////////////////
string cambio_base(string nro, int b1, int b2)
// convierte nro de base b1 a base b2
// condicion: el nro esta correctamente expresado en base b1
{
	// convierto de b1 a base decimal, y luego de decimal a b2
	return (dec_a_base(str_base_a_dec(nro, b1), b2));
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

	string x, y;

	cin >> x >> y;
	while (!cin.eof()) {
		// eliminar los ceros de adelante a x e y
		int off = x.find_first_not_of("-0");
		if (off == -1) x = "0";
		else x = ((x[0] == '-') ? "-" : "") + x.substr(off, (int)x.length()-off);
		
		off = y.find_first_not_of("-0");
		if (off == -1) y = "0";
		else y = ((y[0] == '-') ? "-" : "") + y.substr(off, (int)y.length()-off);
		
		int bx = base_min(x);
		int by = base_min(y);
		string dx = cambio_base(x, bx, 10);
		string dy = cambio_base(y, by, 10);

		while ((dx != dy) && (bx <= MAX_BASE) && (by <= MAX_BASE)) {
			if (atol(dx.c_str()) < atol(dy.c_str())) {
				bx++;
				dx = cambio_base(x, bx, 10);
			} else {
				by++;
				dy = cambio_base(y, by, 10);
			}
		}
		if ((bx > MAX_BASE) || (by > MAX_BASE))
			cout << x << " is not equal to " << y << " in any base 2.." << MAX_BASE << endl;
		else
			cout << x << " (base " << bx << ") = " << y << " (base " << by << ")" << endl;

		cin >> x >> y;
	}
	return 0;
}

/* @END_OF_SOURCE_CODE */

