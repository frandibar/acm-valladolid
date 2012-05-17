/* @JUDGE_ID:  40922FK  10473  C++  */
/* @BEGIN_OF_SOURCE_CODE */    
/**************************************************************************
 Solution to Problem 10473 - Simple Base Conversion
 by: Francisco Dibar
 date: Mar-14-2005
**************************************************************************/

//#define ONLINE_JUDGE 
#include <iostream>
#ifndef ONLINE_JUDGE 
	#include <fstream>
#endif 
#include <string>

using namespace std;

///////////////////////////////////////////////////////////////////////////
string dec_a_base(long nro, int b)
// convierte de base decimal a base b
// condicion: b <= 16
{
	/* contemplar casos especiales */
	//if (b == 10) return itoa(..);
	if (b < 2) return "0";
	if (nro == 0) {
		if (b == 16)
			return "0x0";
		return "0";
	}
	if (b > 16) return "0";		// Restriccion
	
	long tmp = abs(nro),
		 logb = 0;
	
	string out;
	int offset = 0;
	// mantener el signo
	if (nro < 0) {
		out = "-";
		offset++;
	}
	if (b == 16) {
		out += "0x";
		offset += 2;
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
// condicion: b <= 16
{
	/* contemplar casos especiales */
	if (b == 10) return atol(nro.c_str());

	// -0x0..0
	int offset = 0;
	bool cero = true;
	if (nro[0] == '-') 
		offset++;
	for (int i = offset; i < (int)nro.length(); i++)
		if (nro[i] != '0') cero = false;
	if (cero) return 0;

	if (b > 16) return 0;		// Restriccion
	
	long out = 0,
		  bn = 1;
	offset = nro.find_first_of("123456789ABCDEF");
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
//	PROGRAMA PRINCIPAL
///////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{
	// redireccionar la entrada y salida
	#ifndef ONLINE_JUDGE 
		cin.rdbuf((new ifstream("input.txt"))->rdbuf()); 
		cout.rdbuf((new ofstream("output.txt"))->rdbuf()); 
	#endif 

	string snro;
	long nro;
	bool es_hexa;

	do {
		cin >> snro;
		// si es negativo terminar (evitar -0..0 y -0x0..0)
		if (snro[0] == '-') {
			// determinar si es hexa
			if (snro.length() > 3 && snro.substr(1, 2) == "0x") {
				es_hexa = true;
				bool cero = true;
				for (int i = 3; i < (int)snro.length(); i++)
					if (snro[i] != '0') cero = false;
				if (cero) 
					snro = "0x0";
				else
					return 0;	// es negativo hexa, no procesar
			} else if (atol(snro.c_str()) == 0)
				snro = "0";
			else
				return 0;	// es negativo dec, no procesar
		}
		if (snro.length() > 2 && snro.substr(0, 2) == "0x") {
			nro = str_base_a_dec(snro, 16);
			es_hexa = true;
		} else {
			nro = atol(snro.c_str());
			es_hexa = false;
		}
		if (es_hexa)	// mostrar en decimal
			cout << nro << endl;
		else		// mostrar en hexa
			//la sig inst no sirve porque devuelve las letras en minuscula
			//cout << hex << "0x" << nro << endl;
			cout << dec_a_base(nro, 16) << endl;

	} while (!cin.eof() && (nro >= 0)); 

	return 0;
}

/* @END_OF_SOURCE_CODE */

