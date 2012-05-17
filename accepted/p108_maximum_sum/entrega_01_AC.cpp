/* @JUDGE_ID:  40922FK  108  C++  */
/* @BEGIN_OF_SOURCE_CODE */    
/**************************************************************************
 Solution to Problem 108 - Maximum Sum
 by: Francisco Dibar
 date: Dec-08-2005
**************************************************************************/

//#define DEBUG
//#define ONLINE_JUDGE 
#include <iostream>
#ifndef ONLINE_JUDGE 
	#include <fstream>
#endif 
#include <vector>

#define START_DEBUG	"START DEBUG ********************************************************************\n"
#define END_DEBUG	"END DEBUG **********************************************************************\n"

using std::cin;
using std::cout;
using std::endl;
using std::vector;
//using std::pair;

/*
///////////////////////////////////////////////////////////////////////////
pair<long, pair<int, int> > secmax(vector<int>& vec)
// devuelve la suma, y los indices de la subsecuencia maxima
{
	int i = 0;
	while ((vec[i] < 0) && (i < (int)vec.size()))
		i++;

	int from, to, left;
	int suma, max;

	from = to = left = i;
	suma = max = 0;
	while (i < (int)vec.size()) {
		suma += vec[i];
		if (suma > max) {
			max = suma;
			from = left;
			to = i;
		} else if (suma < 0) {
			suma = 0;
			left = i+1;
		}
		i++;
	}
	return std::make_pair(max, std::make_pair(from, to));
}
*/

///////////////////////////////////////////////////////////////////////////
int secmax(const vector<int>& vec)
// returns the maximum subsecuence
{
#ifdef DEBUG
	cout << "vec ";
	for (int j = 0; j < (int)vec.size(); j++)
		cout << vec[j] << " ";
	cout << endl;
#endif

	int i = 0;
	int from, to, left;
	int sum, maxsum;

	maxsum = vec[0];
	// advance i to first positive number
	while ((vec[i] < 0) && (i < (int)vec.size())) {
		if (vec[i] > maxsum)
			maxsum = vec[i];
		i++;
	}

	if (i == (int)vec.size())
		sum = maxsum;	// maxsum < 0
	else
		sum = 0;

	from = to = left = i;
	while (i < (int)vec.size()) {
		sum += vec[i];
		if (sum > maxsum) {
			maxsum = sum;
			from = left;
			to = i;
		} else if (sum < 0) {
			sum = 0;
			left = i+1;
		}
		i++;
	}
#ifdef DEBUG
	cout << "from col " << from << " to col " << to << " sums " << maxsum << endl;
#endif

	return maxsum;
}

///////////////////////////////////////////////////////////////////////////
int max_sum(vector< vector<int> >& mat)
{
	int dim = (int)mat.size();
	vector< vector<int> > mat_colsum(dim);

	// initialize mat_colsum
	
	// each row is the accumulated sum of the rows above (below)
	for (int i = 0; i < dim; i++) {
		mat_colsum[i].resize(dim);
		mat_colsum[0][i] = mat[0][i];
	}
	// mat_colsum[i][j] = sum(i,{0,i}) mat[i][j]
	for (int i = 1; i < dim; i++) {
		for (int j = 0; j < dim; j++)
			mat_colsum[i][j] = mat_colsum[i-1][j] + mat[i][j];
	}

#ifdef DEBUG
	// show mat_colsum
	cout << START_DEBUG;
	for (int i = 0; i < dim; i++) {
		for (int j = 0; j < dim; j++)
			cout << mat_colsum[i][j] << " ";
		cout << endl;
	}
#endif

	// for each possible group of rows, obtain max sum in 1 dimension
	// i and j are rows
	int maxsum = mat[0][0];
	for (int i = 0; i < dim; i++) {
		for (int j = i; j < dim; j++) {
			vector<int> v(dim);
			if (i == 0) {
				for (int k = 0; k < dim; k++)
					v[k] = mat_colsum[j][k];
			} else if (j == i) {
				for (int k = 0; k < dim; k++)
					v[k] = mat[j][k];
			} else {
				for (int k = 0; k < dim; k++)
					v[k] = mat_colsum[j][k] - mat_colsum[i-1][k];
			}
#ifdef DEBUG
			cout << "row " << i << " to row " << j << ": ";
#endif
			int sum = secmax(v);
			if (sum > maxsum)
				maxsum = sum;
		}
	}
#ifdef DEBUG
	cout << END_DEBUG;
#endif
	return maxsum;
}

///////////////////////////////////////////////////////////////////////////
//	PROGRAMA PRINCIPAL
///////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{
	// redireccionar la entrada y salida
	#ifndef ONLINE_JUDGE 
		cin.rdbuf((new std::ifstream("input.txt"))->rdbuf()); 
		cout.rdbuf((new std::ofstream("output.txt"))->rdbuf()); 
	#endif 

	int dim;
	cin >> dim;

	if (dim <= 0) return 0;

	// READ INPUT
	// initialize mat
	vector< vector<int> > mat(dim);
	for (int i = 0; i < dim; i++) {
		mat[i].resize(dim);
		for (int j = 0; j < dim; j++)
			cin >> mat[i][j];
	}

	// PROCESS
	int sum = max_sum(mat);

	// SHOW OUTPUT
	cout << sum << endl;

#ifdef DEBUG
	cout << START_DEBUG;

	cout << END_DEBUG;
#endif

	return 0;
}


/* @END_OF_SOURCE_CODE */

