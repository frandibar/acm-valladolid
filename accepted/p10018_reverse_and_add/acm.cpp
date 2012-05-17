
/* @JUDGE_ID:  40922FK  10018  C++  */
    
/******************************************************************************
 Solution to Problem 10018 - Reverse and Add
 by: Francisco Dibar
 date: Jun-03-2004
******************************************************************************/

#include <iostream>
#include <sstream>
#include <fstream>
//#define ONLINE_JUDGE 

using namespace std;

////////////////////////////////////////////////////////////////////////////////
bool palindrome(const string& word)
// devuelve true si la palabra es capicua
{
	long s = word.length();
	for (long i = 0; i < s/2; i++)
		if (word[i] != word[s-i-1]) return false;
	return true;
}

////////////////////////////////////////////////////////////////////////////////
string invertir(const string& word)
// devuelve word invertida
{
	string pal = word;
	long s = word.length();
	for (long i = 0; i < s/2; i++) 
		swap(pal[i], pal[s-i-1]);

	return pal;
}

////////////////////////////////////////////////////////////////////////////////
string sumar(const string& sA, const string& sB)
// devuelve la suma de dos enteros representados como string de cualquier longitud
{
	// hacer ambos strings de igual longitud colocando ceros por delante
	string s0(abs(sA.length() - sB.length()), '0');
	string s1 = sA,
			 s2 = sB;
	if (sA.length() > sB.length()) 
		s2.insert(0, s0);
	else
		s1.insert(0,s0);

	string res(s1.length()+1, '0');
	// efectuar la suma
	int carry = 0;
	for (int i = s1.length()-1; i >= 0; i--) {
		int sum = carry + s1[i] + s2[i] - 96;	// le resto el offset ascii
		carry = (sum > 9);
		res[i+1] = sum - 10*carry + 48;
	}
	res[0] = carry + 48;
	
	// quitar el 0 del comienzo
	if (res[0] == '0') 
		return res.substr(1,res.length());
	else
		return res;
}

////////////////////////////////////////////////////////////////////////////////
//	PROGRAMA PRINCIPAL
////////////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{
	// redireccionar la entrada y salida
	#ifndef ONLINE_JUDGE 
		cin.rdbuf((new ifstream("input.txt"))->rdbuf()); 
		cout.rdbuf((new ofstream("output.txt"))->rdbuf()); 
	#endif 

	ostringstream os_output;
	int bloques;
	cin >> bloques;
	for (int i = 0; (i < bloques) && (!cin.eof()); i++) {
		string sz_nro;
		cin >> sz_nro;
		int inversiones = 0;
		while (!palindrome(sz_nro)) {
			string sz_inv = invertir(sz_nro);
			sz_nro = sumar(sz_inv, sz_nro);
			inversiones++;
		}
		os_output << inversiones << " " << sz_nro << endl;
	}
	cout << os_output.str();
	return 0;
}

