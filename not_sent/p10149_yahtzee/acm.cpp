/* @JUDGE_ID:  40922FK  10149  C++  */
/* @BEGIN_OF_SOURCE_CODE */    
/**************************************************************************
 Solution to Problem 10149 - Yahtzee
 by: Francisco Dibar
 date: Jul-31-2005
**************************************************************************/

#define DEBUG 
//#define ONLINE_JUDGE
#include <iostream>
#ifndef ONLINE_JUDGE 
	#include <fstream>
#endif 
#include <vector>
#include <algorithm>		// sort
//#include <functional>   // greater<int>()


#define NCATEGORIES	13
#define NDICE			5

#define PTS_5KIND				50
#define PTS_SHORTSTRAIGHT	25
#define PTS_LONGSTRAIGHT	35
#define PTS_FULL				40


using namespace std;

enum { fiveKind, fullHouse, longStraight, shortStraight }; 
///////////////////////////////////////////////////////////////////////////
bool sortVectorIntDesc(vector<int> v, vector<int> s)
// devuelve true si v esta antes que s
{
// comento la generalizacion
//	int size = min(v.size(), s.size());
//	for (int i = 0; i < size; i++) {
	
	for (int i = 0; i < NDICE; i++) {
		if (v[i] > s[i])
			return false;
		else if (v[i] < s[i])
			return true;
	}
	return false;	// son iguales
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

	vector< vector<int> > m(NCATEGORIES);
	// resize m
	for (int i = 0; i < NCATEGORIES; i++)
		m[i].resize(NDICE);

	int d;
	cin >> d;
	while (!cin.eof()) {
		// READ INPUT
		for (int i = 0; i < NCATEGORIES; i++) {
			for (int j = 0; (j < NDICE) && !cin.eof(); j++) {
				m[i][j] = d;
				cin >> d;
			}
		}

		// PROCESS
		// sort m
		for (int i = 1; i < NCATEGORIES; i++)
			//sort(m[i].begin(), m[i].end(), greater<int>());
			sort(m[i].begin(), m[i].end());
		sort(m.begin(), m.end(), sortVectorIntDesc);

		// setear puntos en orden decreciente
		int vecPuntos[NCATEGORIES];

		// SHOW RESULTS
#ifdef DEBUG
		for (int i = 0; i < NCATEGORIES; i++) {
			for (int j = 0; j < NDICE; j++) {
				cout << m[i][j] << " ";
			}
			cout << endl;
		}
#endif 
		cout << endl;
	}
	return 0;
}

/* @END_OF_SOURCE_CODE */

