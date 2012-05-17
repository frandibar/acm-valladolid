
/* @JUDGE_ID:  40922FK  10035  C++  */
    
/******************************************************************************
 Solution to Problem 10035 - Primary Arithmetic
 by: Francisco Dibar
 date: May-30-2004
******************************************************************************/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <queue>

//#define ONLINE_JUDGE 

using namespace std;

////////////////////////////////////////////////////////////////////////////////
int carrys_suma(const string& sA, const string& sB)
// devuelve la cantidad de carrys de la suma de dos enteros representados como string de cualquier longitud
{
	int tot_carrys = 0;
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
		if (carry) tot_carrys++;
		res[i+1] = sum - 10*carry + 48;
	}
	
	return tot_carrys;
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
	string n1, n2;

	cin >> n1 >> n2;
	while (((n1 != "0") || (n2 != "0")) && !cin.eof()) {
		int tot_carrys = carrys_suma(n1, n2);
		if (tot_carrys == 0)
			os_output << "No carry operation." << endl;
		else if (tot_carrys == 1)
			os_output << "1 carry operation." << endl;
		else
			os_output << tot_carrys << " carry operations." << endl;
		cin >> n1 >> n2;
	}
	cout << os_output.str();
	return 0;
}

