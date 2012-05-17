
/* @JUDGE_ID:  40922FK  338  C++  */
    
/******************************************************************************
 Solution to Problem 338 - Long Multiplication
 by: Francisco Dibar
 date: Apr-24-2004
******************************************************************************/

#include <iostream>
#include <algorithm>	// for each, max
#include <string>		// cin >> string, cout << string
#include <list>
#include <vector>	
#include <stdlib.h>		// _atoi64

// The base types 

#ifdef WIN32 
  typedef __int8            int8; 
  typedef __int16           int16; 
  typedef __int32           int32; 
  typedef __int64           int64; 
  typedef unsigned __int8   uint8; 
  typedef unsigned __int16  uint16; 
  typedef unsigned __int32  uint32; 
  typedef unsigned __int64  uint64; 
#else 
  typedef char                    int8; 
  typedef short                   int16; 
  typedef long                    int32; 
  typedef long long int           int64; 
  typedef unsigned char           uint8; 
  typedef unsigned short          uint16; 
  typedef unsigned long           uint32; 
  typedef unsigned long long int  uint64; 
#endif 

#define MAX_DIGIT		10
#define MAX_LEN			MAX_DIGIT * 2 + 1
#define MAX_SEPARADOR	"--------------------"		// son 2*MAX_DIGIT ESPACIOS
#define MAX_CEROS		"00000000000000000000"		// puedo reemplazarlo en codigo
#define MAX_SANGRIA		"                    "		// por: string max(MAX_DIGIT * 2,'0')

using namespace std;

struct entrada {
	string sx;
	string sy;
};

/*	// en windows
////////////////////////////////////////////////////////////////////////////////
template<class T>const T& max(const T& a, const T& b)
{
	return (a < b) ? b : a;
}
*/

////////////////////////////////////////////////////////////////////////////////
void reverse(char s[])
{
	int c, i, j;
	for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}

////////////////////////////////////////////////////////////////////////////////
void itoa(int n, char s[])
{
	int i, sign;

	if ((sign = n) < 0)
		n = -n;
	i = 0;
	do {
		s[i++] = n % 10 + '0';
	} while ((n /= 10) > 0);
	if (sign < 0)
		s[i++] = '-';
	s[i] = '\0';
	reverse(s);
}

////////////////////////////////////////////////////////////////////////////////
string invertir(string str)
{
	for (int i = 0, j = str.length() - 1; i < j; i++, j--) {
		char aux = str[i];
		str[i] = str[j];
		str[j] = aux;
	}
	return str;
}

////////////////////////////////////////////////////////////////////////////////
int suma_digito(vector<string>& v_smult, int posicion)
// devuelve la suma de los digitos de la posicion posicion
{
	int suma = 0;
	for (int i = 0; i < v_smult.size(); i++) {
		// leer el digito en la posicion posicion, convertirlo a int y sumarlo
		string s = v_smult[i].substr(posicion,1);
		int si = atoi(s.c_str());
		suma += si;
	}
	return suma;
}

////////////////////////////////////////////////////////////////////////////////
string sumar(vector<string>& v_smult)
{
	string res = "";

	// calcular el resultado
	int digitos = v_smult[0].length();
	int suma_dig = 0;
	int carry = 0;
	char ssuma_dig[MAX_LEN];
	for (int i = digitos - 1; i > 0; i--) {
		suma_dig = suma_digito(v_smult, i);
		suma_dig += carry;
		carry = int(suma_dig / 10);
		suma_dig %= 10;
		itoa(suma_dig, ssuma_dig);
		res += ssuma_dig;
	}
	// para i = 0, agrego el carry si hace falta
	suma_dig = suma_digito(v_smult, 0);
	suma_dig += carry;
	carry = int(suma_dig / 10);
	suma_dig %= 10;
	itoa(suma_dig, ssuma_dig);
	res += ssuma_dig;
	if (carry > 0) {
		char scarry[1];
		itoa(carry, scarry);
		res += scarry;
	}
	// el resultado esta en orden invertido, entonces lo invertimos
	res = invertir(res);
	return res;
}

////////////////////////////////////////////////////////////////////////////////
string multiplicar(string sx, string cy)
// sx es un numero de n digitos, y cy es un solo digito
{
	string resultado = "";
	int y, carry = 0;
	y = atoi(cy.c_str());
	for (int i = 0; i < sx.length(); i++) {
		int x, res;
		string d = sx.substr(sx.length() - i - 1, 1);
		x = atoi(d.c_str());
		res = x * y + carry;
		
		carry = int(res / 10);
		res %= 10;
		char dig[1];
		itoa(res, dig);
		resultado += dig;	// agrego el digito al final
	}		
	
	if (carry > 0) {
		char scarry[1];
		itoa(carry, scarry);
		resultado += scarry;
	}

	resultado = invertir(resultado);
	return resultado;
}

////////////////////////////////////////////////////////////////////////////////
void efectuar_multiplicacion(entrada& in)
{
	vector<string> v_multip(in.sy.length());
	// generar el vector v_multiplicaciones con las multiplicaciones parciales
	int max_len = 0;
	for (int i = in.sy.length()-1; i >= 0; i--) {
		string c;
		c += in.sy[i];
		v_multip[in.sy.length()-1-i] = multiplicar(in.sx, c);
		int aux = v_multip[in.sy.length()-1-i].length() + in.sy.length()-1-i;
		if (aux > max_len) max_len = aux;
	}
	
	// una vez obtenido max_len, agrego los ceros a izquierda y derecha para poder sumar
	vector<string> v_0_multip(in.sy.length());
	// v_0_multip es igual a v_multip pero con ceros a derecha y a izquierda
	string ceros_der = "";
	for (int j = 0; j < v_0_multip.size(); j++) {
		string max_ceros = MAX_CEROS;
		string mult = v_multip[j];
		//v_multiplicaciones[j] = max_ceros.substr(0, max_len - v_multiplicaciones[j].length() - j) + v_multiplicaciones[j] + ceros_der;
		mult = max_ceros.substr(0, max_len - mult.length() - j) + mult + ceros_der;
		v_0_multip[j] = mult;
		ceros_der += "0";
	}	

	// obtener el resultado
	string resultado = sumar(v_0_multip);	

	// SALIDA //

	// mostrar los multiplicandos y el primer separador
	int tot_dig = resultado.size();
	string max_sangria = MAX_SANGRIA;
	string sum1 = max_sangria.substr(0,tot_dig - in.sx.length()) + in.sx;
	string sum2 = max_sangria.substr(0,tot_dig - in.sy.length()) + in.sy;
	// el primer separador debe tener igual cantidad de digitos que el maximo entre x e y
	string max_sep = MAX_SEPARADOR;
	int digitos = max(in.sx.length(), in.sy.length());
	string separador1 = max_sep.substr(0, digitos); 
	separador1 = max_sangria.substr(0,tot_dig - separador1.length()) + separador1;
	cout << sum1 << endl << sum2 << endl << separador1 << endl;

	

	// una vez que tengo la longitud del resultado, agrego la sangria a izquierda y derecha
	string sangria_izq, sangria_der = "";
	vector<string> v_f_multip(in.sy.length());
	// generar el vector v_smultiplicaciones con los sumandos con el formato
	for (int i = 0; (i < in.sy.length()) && (in.sy.length() > 1); i++) {
		sangria_izq = max_sangria.substr(0,tot_dig - v_multip[i].length() - i);
		v_f_multip[i] = sangria_izq + v_multip[i] + sangria_der;
		cout << v_f_multip[i] << endl;
		sangria_der += " ";
	}

	// mostrar los sumandos y el segundo separador
	if (v_multip.size() > 1) {
		string separador2 = max_sep.substr(0, resultado.length()); 
		cout << separador2 << endl;
	}
	cout << resultado << endl << endl;

}

////////////////////////////////////////////////////////////////////////////////
//	PROGRAMA PRINCIPAL
////////////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{
	entrada in;
	list<entrada> lst_input;	
	cin >> in.sx;
	
	// leer la entrada
	while (!cin.eof() && (in.sx != "0")) {
		cin >> in.sy;
		lst_input.push_back(in);
		cin >> in.sx;
	}
	
	// procesar cada entrada
	for_each(lst_input.begin(), lst_input.end(), efectuar_multiplicacion);

	return 0;
}


