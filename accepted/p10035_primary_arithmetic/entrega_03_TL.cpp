
/* @JUDGE_ID:  40922FK  10035  C++  */
    
/**************************************************************************
 Solution to Problem 10035 - Primary Arithmetic
 by: Francisco Dibar
 date: Dec-12-2004
**************************************************************************/

//#define ONLINE_JUDGE 
#include <iostream>
#ifndef ONLINE_JUDGE 
	#include <fstream>
#endif 
#include <string>
#include <queue>

using namespace std;

///////////////////////////////////////////////////////////////////////////
int carrys_suma(const string& sA, const string& sB)
// devuelve la cantidad de carrys de la suma de dos enteros representados
// como string de cualquier longitud
{
	int tot_carrys = 0;
	// hacer ambos strings de igual longitud colocando ceros por delante
	string s0(abs(long(sA.length() - sB.length())), '0');
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
		// le resto el offset ascii
		int sum = carry + s1[i] + s2[i] - 96;	
		carry = (sum > 9);
		if (carry) tot_carrys++;
		res[i+1] = sum - 10*carry + 48;
	}
	
	return tot_carrys;
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

	string n1, n2;

	cin >> n1 >> n2;
	while (((n1 != "0") && (n2 != "0")) && !cin.eof()) {
		int tot_carrys = carrys_suma(n1, n2);
		if (tot_carrys == 0)
			cout << "No carry operation." << endl;
		else if (tot_carrys == 1)
			cout << "1 carry operation." << endl;
		else
			cout << tot_carrys << " carry operations." << endl;
		cin >> n1 >> n2;
	}
	return 0;
}
