/* @JUDGE_ID:  40922FK  10159  C++  */
/* @BEGIN_OF_SOURCE_CODE */    
/**************************************************************************
 Solution to Problem 10159 - Star
 by: Francisco Dibar
 date: Nov-10-2005
**************************************************************************/

#define DEBUG
//#define ONLINE_JUDGE 
#include <iostream>
#ifndef ONLINE_JUDGE 
	#include <fstream>
#endif 
#include <vector>
#include <string>

#define INVALID_CELL	-2
#define NOT_SET		-1

#define DIM			11

#define START_DEBUG	"START DEBUG ********************************************************************\n"
#define END_DEBUG	"END DEBUG **********************************************************************\n"

using namespace std;

int vec_hex[11][11];	

///////////////////////////////////////////////////////////////////////////
int calc_min(vector<int>& vec_input)
{

	return -1;
}

///////////////////////////////////////////////////////////////////////////
int calc_max(vector<int>& vec_input)
{
	// init vec_hex
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
			vec_hex[i][j] = NOT_SET;

	

	return -1;
}

///////////////////////////////////////////////////////////////////////////
void show_star(bool hexagonal)
{
	for (int i = 0; i < DIM; i++) {
		if (hexagonal) {
			string s(i, ' ');
			cout << s;
		}
		for (int j = 0; j < DIM; j++) {
			if (vec_hex[i][j] == INVALID_CELL)
				cout << ". ";
			else
				cout << vec_hex[i][j] << " ";
		}
		cout << endl;
	}
}

///////////////////////////////////////////////////////////////////////////
void init_star()
{
	for (int i = 0; i < DIM; i++)
		for (int j = 0; j < DIM; j++) 
			if (((i-j) % 3) == 0)
				vec_hex[i][j] = INVALID_CELL;
			else
				// leave out borders of star
				if ( (i+j <= 4) || (i+j >= 16) || 
					  ((j == 0) && ((i > 5) && (i < 10))) || 
					  ((i == 0) && ((j > 5) && (j < 10))) || 
					  ((j == 10) && ((i > 0) && (i < 5))) || 
					  ((i == 10) && ((j > 0) && (j < 5))) ||
					  ((i+j == 5) && (i*j != 0)) ||
					  ((i+j == 15) && (i != 10) && (j != 10)) )
					vec_hex[i][j] = INVALID_CELL;
				else		
					vec_hex[i][j] = NOT_SET;
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

	vector<int> vec_input(12);
//	vector<vector<int> > vec_hex(12);
	
	cin >> vec_input[0];
	while (!cin.eof()) {
		// READ INPUT
		for (int i = 1; i < 12; i++)
			cin >> vec_input[i];

		// PROCESS
		init_star();
		int min = calc_min(vec_input);
/*		int max = calc_max(vec_input);
		
		// SHOW OUTPUT
		if (max != -1 && max != -1)
			cout << min << " " << max << endl;
		else
			cout << "NO SOLUTION" << endl;
*/
		// READ NEXT INPUT
		cin >> vec_input[0];
	}
		
#ifdef DEBUG
	cout << START_DEBUG;
	show_star(true);
	cout << endl << endl;
	show_star(false);
	cout << END_DEBUG;
#endif
	
	return 0;
}

/* @END_OF_SOURCE_CODE */

