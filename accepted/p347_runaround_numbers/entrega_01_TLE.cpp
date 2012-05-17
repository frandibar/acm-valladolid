
/* @JUDGE_ID:  40922FK  347  C++  */
    
/******************************************************************************
 Solution to Problem 347 - Run, Run, Runaround Numbers
 by: Francisco Dibar
 date: Jun-07-2004
******************************************************************************/

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
//#define ONLINE_JUDGE

using namespace std;

////////////////////////////////////////////////////////////////////////////////
bool valid_run_around_format(const string& sz_num)
// chequear que el nro no tenga ceros ni digitos repetidos
{
	vector<bool> vec_esta(10);		// lo uso para marcar los digitos presentes
											// se incializa en false
	for (int i = 0; i < (int)sz_num.length(); i++) {
		if (sz_num[i] == '0') return false;
		else {
			if (vec_esta[sz_num[i]-'0'])
				return false;
			else 
				vec_esta[sz_num[i]-'0'] = true;
		}
	}
	return true;
}

////////////////////////////////////////////////////////////////////////////////
bool run_around(const string& sz_num)
{
	if (!valid_run_around_format(sz_num)) 
		return false;

	int len = sz_num.length();
	vector<bool> vec_visit(len);
	int not_visited = len;			// cuenta los digitos visitados
	int visit = 0;						// indica el indice del digito visitado
	while (not_visited >= 0) {
		if (vec_visit[visit]) {
		   if ((not_visited > 0) || (visit != 0)) 
		         return false;
		} else {
		   vec_visit[visit] = true;
			visit = (visit + sz_num[visit] - '0') % len;	
		}
		not_visited--;
	}
	return true;
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

	string sz_num;
	cin >> sz_num;
	int case_num = 1;
	while ((sz_num != "0") && (!cin.eof())) {
		// procesar cada nro
		// buscar aquel nro mayor a sz_start que sea run around
		while (!run_around(sz_num))
			sz_num = sumar(sz_num, "1");
		os_output << "Case " << case_num << ": " << sz_num << endl;
		case_num++;
		cin >> sz_num;
	}

	cout << os_output.str();
	return 0;
}

////////////////////////////////////////////////////////////////////////////////
/*

An N-digit runaround number is characterized as follows:

- It is an integer with exactly N digits, each of which is between 1 and 9,
	inclusively.
- The digits form a sequence with each digit telling where the next digit in
	the sequence occurs. This is done by giving the number of digits to the
 	right of the digit where the next digit in the sequence occurs.
  	If necessary, counting wraps around from the rightmost digit back to the
   	leftmost.
- The leftmost digit in the number is the first digit in the sequence, and the
	sequence must return to this digit after all digits in the number have been
 	used exactly once.
- No digit will appear more than once in the number.

*/
////////////////////////////////////////////////////////////////////////////////

