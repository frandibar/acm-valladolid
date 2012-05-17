/* @JUDGE_ID:  40922FK  10003  C++  */
/* @BEGIN_OF_SOURCE_CODE */    
/**************************************************************************
 Solution to Problem 10003 - Cutting Sticks
 by: Francisco Dibar
 date: Dec-17-2005
**************************************************************************/

#define DEBUG
//#define ONLINE_JUDGE 
#include <iostream>
#ifndef ONLINE_JUDGE 
	#include <fstream>
#endif 
#include <vector>

#define START_DEBUG	"START DEBUG ********************************************************************\n"
#define END_DEBUG	"END DEBUG **********************************************************************\n"

#define MAXINT  2147483647

using std::cin;
using std::cout;
using std::endl;
using std::vector;

#ifdef DEBUG
////////////////////////////////////////////////////////////////////////////////
template<class T>
void print_matrix(vector< vector<T> >& m)
{
	for (int i = 0; i < (int)m.size(); i++) {
		for (int j = 0; j < (int)m[i].size(); j++)
			cout << m[i][j] << " ";
		cout << endl;
	}
}
#endif

////////////////////////////////////////////////////////////////////////////////
void dp(int length, const vector<int>& vp, vector< vector<int> >& mat_m)
{
    int n = (int)mat_m.size();
    for (int i = 0; i < n; i++)
        mat_m[i][i] = length;
    
    for (int cuts = 2; cuts <= n; cuts++) {
        for (int i = 0; i < n - cuts + 1; i++) {
            int j = i + cuts - 1;
            mat_m[i][j] = MAXINT;
            for (int k = i; k <= j-1; k++) {
					// REVISAR ACA esta el kit de la cuestion
					int c1 = mat_m[i][k] + length - vp[k];
					int rem = length - vp[j];
					if (rem < vp[k])
						rem = vp[j];
					int c2 = mat_m[k+1][j] + rem;
					int q = std::min(c1, c2);
#ifdef DEBUG
					cout << "cuts: " << cuts << "  i: " << i << "  j: " << j << "  k: " << k << endl;
					cout << "m[" << i << "][" << k << "]: " << mat_m[i][k] << "  m[" << k+1 << "][" << j << "]: " << mat_m[k+1][j] << "  rem: " << rem << endl;
					cout << "c1: " << c1 << "  c2: " << c2 << endl;
#endif
					if (q < mat_m[i][j]) {
						mat_m[i][j] = q;
#ifdef DEBUG
						print_matrix(mat_m);
						cout << endl;
#endif
                }
				}
        }
    }
}


/////////////////////////////////////////////////////////////////////////// 
int calculate_cut(int length, vector<int> vec_sticks)
{
	int n = (int)vec_sticks.size();
	vector< vector<int> > mat_m(n);

	// resize mat_m
	for (int i = 0; i < n; i++)
		mat_m[i].resize(n);

	dp(length, vec_sticks, mat_m);

	return mat_m[0][n-1];
}

///////////////////////////////////////////////////////////////////////////
//	MAIN PROGRAM
///////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{
	// redireccionar la entrada y salida
	#ifndef ONLINE_JUDGE 
		cin.rdbuf((new std::ifstream("input.txt"))->rdbuf()); 
		cout.rdbuf((new std::ofstream("output.txt"))->rdbuf()); 
	#endif 

	int length;
	cin >> length;
	
	while ((length != 0) && !cin.eof()) {
		// READ INPUT
		int ncuts;
		cin >> ncuts;
		vector<int> vec_sticks(ncuts);
		for (int i = 0; i < ncuts; i++) 
			cin >> vec_sticks[i];
			
#ifdef DEBUG
		cout << START_DEBUG;
		// PROCESS
		int cut = calculate_cut(length, vec_sticks);
		cout << END_DEBUG;
#endif
		// SHOW OUTPUT
		cout << "The minimum cutting is " << cut << "." << endl;

		// READ NEXT INPUT
		cin >> length;
	}
		
	return 0;
}

/* @END_OF_SOURCE_CODE */

