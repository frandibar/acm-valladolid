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

#define INVALID_CELL	-2
#define NOT_SET		-1
#define NO_SOLUTION	-1

#define ROWS		8
#define ROWS_EXT	16		// extended for diagonals
#define COLS		11
#define INPUT		12

#define ROW_A	6
#define ROW_I	6		// = ROW_A
#define ROW_D	9		// = ROW_A + 4
#define ROW_E	9		// = ROW_E

#define IN_A	0	// index of input for row A
#define IN_E	4	// index of input for diag E
#define IN_I	8	// index of input for diag I

#define START_DEBUG	"START DEBUG ********************************************************************\n"
#define END_DEBUG	"END DEBUG **********************************************************************\n"

using std::cin;
using std::cout;
using std::endl;

int mat_star[ROWS_EXT][COLS];	

///////////////////////////////////////////////////////////////////////////
void show_star()
{
	for (int i = ROW_A-3; i < ROW_D+4; i++) {
		for (int j = 0; j < COLS; j++) {
			if (mat_star[i][j] != INVALID_CELL)
				cout << mat_star[i][j] << " ";
			else
				cout << "  ";
		}
		cout << endl;
	}
}

///////////////////////////////////////////////////////////////////////////
bool verify_input(const int vec_input[])
{
	// determine the maximum value for each row/diag
	// and check if it corresponds to input value
	// check row A
	int vec_max[INPUT];

	// check rows A to D
	for (int i = ROW_A; i <= ROW_D; i++) {	
		int maxval = 0;
		for (int j = 0; j < COLS; j++) {
			maxval = std::max(mat_star[i][j], maxval);
		}
		vec_max[i - ROW_A] = maxval;
	}

	// check diagonals E to H
	int ind_in = IN_E - 1;
	for (int d = ROW_E; d < ROWS_EXT; d += 2) {
		ind_in++;
		int col = 0;
		int maxval = 0;
		for (int i = d; (i >= 0) && (col < COLS); i--) {	
			if (mat_star[i][col] == INVALID_CELL)
				col++;
			if ((col < COLS) && (mat_star[i][col] != INVALID_CELL)) {
				maxval = std::max(mat_star[i][col], maxval);
				if ((i + col) % 2 != 0) {
					col++;
					if (col < COLS)
						maxval = std::max(mat_star[i][col], maxval);
				}
			}
		}
		vec_max[ind_in] = maxval;
	}

	// check diagonals I to K
	ind_in = IN_I - 1;
	for (int d = ROW_I; d >= 0; d -= 2) {
		ind_in++;
		int col = 0;
		int maxval = 0;
		for (int i = d; (i < ROWS_EXT) && (col < COLS); i++) {	
			if (mat_star[i][col] == INVALID_CELL)
				col++;
			if ((col < COLS) && (mat_star[i][col] != INVALID_CELL)) {
				maxval = std::max(mat_star[i][col], maxval);
				if ((i + col) % 2 == 0) {
					col++;
					if (col < COLS)
						maxval = std::max(mat_star[i][col], maxval);
				}
			}
		}
		vec_max[ind_in] = maxval;
	}


	// compare vec_max with vec_input
	// if they differ, then return false
	for (int i = 0; i < INPUT; i++) {
		if (vec_max[i] != vec_input[i])
			return false;
	}
	return true;
}

///////////////////////////////////////////////////////////////////////////
int sum_star()
{
	int sum = 0;
	for (int i = 0; i < ROWS_EXT; i++) {
		for (int j = 0; j < COLS; j++) {
			if ((mat_star[i][j] != INVALID_CELL) && (mat_star[i][j] != NOT_SET))
				sum += mat_star[i][j];
		}
	}
	return sum;
}

///////////////////////////////////////////////////////////////////////////
int calc_max(const int vec_input[])
{	
	// fill rows A to D (2 to 5)
	int ind_in = IN_A;
	for (int i = ROW_A; i <= ROW_D; i++) {	
		for (int j = 0; j < COLS; j++) {
			if (mat_star[i][j] != INVALID_CELL) {
				mat_star[i][j] = vec_input[ind_in];
			}
		}
		ind_in++;
	}

	// fill diagonals E to H
	ind_in = IN_E - 1;
	for (int d = ROW_E; d < ROWS_EXT; d += 2) {
		ind_in++;
		int col = 0;
		for (int i = d; (i >= 0) && (col < COLS); i--) {	
			if (mat_star[i][col] == INVALID_CELL)
				col++;
			if ((col < COLS) && (mat_star[i][col] != INVALID_CELL)) {
				if (mat_star[i][col] != NOT_SET)
					mat_star[i][col] = std::min(mat_star[i][col], vec_input[ind_in]);
				else
					mat_star[i][col] = vec_input[ind_in];
				if ((i + col) % 2 != 0) {
					col++;
					if (col < COLS) {
						if (mat_star[i][col] != NOT_SET)
							mat_star[i][col] = std::min(mat_star[i][col], vec_input[ind_in]);
						else
							mat_star[i][col] = vec_input[ind_in];
					}
				}
			}
		}
	}

	// fill antidiagonals I to K
	ind_in = IN_I - 1;
	for (int d = ROW_I; d >= 0; d -= 2) {
		ind_in++;
		int col = 0;
		for (int i = d; (i < ROWS_EXT) && (col < COLS); i++) {	
			if (mat_star[i][col] == INVALID_CELL)
				col++;
			if ((col < COLS) && (mat_star[i][col] != INVALID_CELL)) {
				if (mat_star[i][col] != NOT_SET)
					mat_star[i][col] = std::min(mat_star[i][col], vec_input[ind_in]);
				else
					mat_star[i][col] = vec_input[ind_in];
				if ((i + col) % 2 == 0) {
					col++;
					if (col < COLS) {
						if (mat_star[i][col] != NOT_SET)
							mat_star[i][col] = std::min(mat_star[i][col], vec_input[ind_in]);
						else
							mat_star[i][col] = vec_input[ind_in];
					}
				}
			}
		}
	}

	// verify valid input
	if (!verify_input(vec_input))
		return NO_SOLUTION;

	return sum_star();
}

///////////////////////////////////////////////////////////////////////////
int calc_min(const int vec_input[], bool maxconf)
{
	if (!maxconf)
		if (calc_max(vec_input) == NO_SOLUTION)
			return NO_SOLUTION;

	
	// rows A to D
	for (int i = ROW_A; i <= ROW_D; i++) {
		bool maxset = false;
		for (int j = 0; j < COLS; j++) {
			if (mat_star[i][j] == INVALID_CELL)
				continue;
			if (mat_star[i][j] != vec_input[i - ROW_A]) {
				// not row's max, set to 0 if not other diag's max
				int diag = i + j;
				int in;
				switch(diag) {
					case 9:
					case 10:	in = IN_E; break;					
					case 11:
					case 12:	in = IN_E+1; break;	// F
					case 13: 
					case 14:	in = IN_E+2; break;	// G
					case 15: 
					case 16:	in = IN_E+3; break;	// H
					default: in = -1; break;	// not in diag
				}
				bool setzero = false;
				if (in == -1)
					setzero = true;
				else if (mat_star[i][j] != vec_input[in])
					setzero = true;	// not diag's max
				if (setzero) {
					int antidiag = j - i;
					switch(antidiag) {
						case -6:
						case -5:	in = IN_I; break;					
						case -4:
						case -3:	in = IN_I+1; break;	// J
						case -2: 
						case -1:	in = IN_I+2; break;	// K
						case  0: 
						case  1:	in = IN_I+3; break;	// L
						default: in = -1; break;	// not in antidiag
					}
					if (in != -1) {
						if (mat_star[i][j] != vec_input[in]) {
							mat_star[i][j] = 0; // not antidiag's max, set to 0
						}
					} else
						mat_star[i][j] = 0;
				}
			} else
				if (maxset)
					mat_star[i][j] = 0;
				else
					maxset = true;
		}
	}

#ifdef DEBUG
		show_star();
#endif
	
	// diags E to H
	int ind_in = IN_E - 1;
	for (int d = ROW_E; d < ROWS_EXT; d += 2) {
		ind_in++;
		int col = 0;
		bool maxset = false;
		for (int i = d; (i >= 0) && (col < COLS); i--) {	
			if (mat_star[i][col] == INVALID_CELL)
				col++;
			if ((col < COLS) && (mat_star[i][col] != INVALID_CELL)) {
				if (mat_star[i][col] != vec_input[ind_in]) {
					// not diags's max, set to 0 if not other row/diag's max
					bool setzero = true;
					if ((i >= ROW_A) && (i <= ROW_E)) {
						if (mat_star[i][col] == vec_input[i - ROW_A])
							// row's max, don't set to 0
							setzero = false;
					}
					if (setzero) {
						int antidiag = col - i;
						int in;
						switch(antidiag) {
							case -6:
							case -5:	in = IN_I; break;					
							case -4:
							case -3:	in = IN_I+1; break;	// J
							case -2: 
							case -1:	in = IN_I+2; break;	// K
							case  0: 
							case  1:	in = IN_I+3; break;	// L
							default: in = -1; break;	// not in antidiag
						}
						if (in != -1) {
							if (mat_star[i][col] != vec_input[in]) {
								mat_star[i][col] = 0; // not antidiag's max, set to 0
							}
						} else
							mat_star[i][col] = 0;
					}
				} else
					if (maxset)
						mat_star[i][col] = 0;
					else
						maxset = true;
				if ((i + col) % 2 != 0) {
					col++;
					if ((col < COLS) && (mat_star[i][col] != INVALID_CELL)) {
						if (mat_star[i][col] != vec_input[ind_in]) {
							// not diags's max, set to 0 if not other row/diag's max
							bool setzero = true;
							if ((i >= ROW_A) && (i <= ROW_E)) {
								if (mat_star[i][col] == vec_input[i - ROW_A])
									// row's max, don't set to 0
									setzero = false;
							}
							if (setzero) {
								int antidiag = col - i;
								int in;
								switch(antidiag) {
									case -6:
									case -5:	in = IN_I; break;					
									case -4:
									case -3:	in = IN_I+1; break;	// J
									case -2: 
									case -1:	in = IN_I+2; break;	// K
									case  0: 
									case  1:	in = IN_I+3; break;	// L
									default: in = -1; break;	// not in antidiag
								}
								if (in != -1) {
									if (mat_star[i][col] != vec_input[in]) {
										mat_star[i][col] = 0; // not antidiag's max, set to 0
									}
								} else
									mat_star[i][col] = 0;
							}
						} else
							if (maxset)
								mat_star[i][col] = 0;
							else
								maxset = true;
					}
				}
			}
		}
	}

#ifdef DEBUG
		show_star();
#endif

	// antidiags I to L
	ind_in = IN_I - 1;
	for (int d = ROW_I; d >= 0; d -= 2) {
		ind_in++;
		int col = 0;
		bool maxset = false;
		for (int i = d; (i < ROWS_EXT) && (col < COLS); i++) {	
			if (mat_star[i][col] == INVALID_CELL)
				col++;
			if ((col < COLS) && (mat_star[i][col] != INVALID_CELL)) {
				if (mat_star[i][col] != vec_input[ind_in]) {
					// not diags's max, set to 0 if not other row/diag's max
					bool setzero = true;
					if ((i >= ROW_A) && (i <= ROW_E)) {
						if (mat_star[i][col] == vec_input[i - ROW_A])
							// row's max, don't set to 0
							setzero = false;
					}
					if (setzero) {
						int diag = col + i;
						int in;
						switch(diag) {
							case 9:
							case 10:	in = IN_E; break;					
							case 11:
							case 12:	in = IN_E+1; break;	// F
							case 13: 
							case 14:	in = IN_E+2; break;	// G
							case 15: 
							case 16:	in = IN_E+3; break;	// H
							default: in = -1; break;	// not in diag
						}
						if (in != -1) {
							if (mat_star[i][col] != vec_input[in]) {
								mat_star[i][col] = 0; // not diag's max, set to 0
							}
						} else
							mat_star[i][col] = 0;
					}
				} else
					if (maxset)
						mat_star[i][col] = 0;
					else
						maxset = true;
				if ((i + col) % 2 == 0) {
					col++;
					if ((col < COLS) && (mat_star[i][col] != INVALID_CELL)) {
						if (mat_star[i][col] != vec_input[ind_in]) {
							// not diags's max, set to 0 if not other row/diag's max
							bool setzero = true;
							if ((i >= ROW_A) && (i <= ROW_E)) {
								if (mat_star[i][col] == vec_input[i - ROW_A])
									// row's max, don't set to 0
									setzero = false;
							}
							if (setzero) {
								int diag = col + i;
								int in;
								switch(diag) {
									case 9:
									case 10:	in = IN_E; break;					
									case 11:
									case 12:	in = IN_E+1; break;	// F
									case 13: 
									case 14:	in = IN_E+2; break;	// G
									case 15: 
									case 16:	in = IN_E+3; break;	// H
									default: in = -1; break;	// not in diag
								}
								if (in != -1) {
									if (mat_star[i][col] != vec_input[in]) {
										mat_star[i][col] = 0; // not diag's max, set to 0
									}
								} else
									mat_star[i][col] = 0;
							}
						} else
							if (maxset)
								mat_star[i][col] = 0;
							else
								maxset = true;
					}
				}
			}
		}
	}

	return sum_star();
}

///////////////////////////////////////////////////////////////////////////
void init_star()
// sets cells in mat_star as INVALID_CELL or NOT_SET
{
	// set all cells to NOT_SET
	for (int i = 0; i < ROWS_EXT; i++)
		for (int j = 0; j < COLS; j++) 
			mat_star[i][j] = NOT_SET;

	// set to INVALID_CELL those rows above and below the star
	for (int i = 0; i < ROW_A-2; i++)
		for (int j = 0; j < COLS; j++) 
			mat_star[i][j] = INVALID_CELL;

	for (int i = ROW_D+3; i < ROWS_EXT; i++)
		for (int j = 0; j < COLS; j++) 
			mat_star[i][j] = INVALID_CELL;

	// first star row
	mat_star[ROW_A-2][0] = INVALID_CELL;
	mat_star[ROW_A-2][1] = INVALID_CELL;
	mat_star[ROW_A-2][2] = INVALID_CELL;
	mat_star[ROW_A-2][3] = INVALID_CELL;
	mat_star[ROW_A-2][4] = INVALID_CELL;
	mat_star[ROW_A-2][6] = INVALID_CELL;
	mat_star[ROW_A-2][7] = INVALID_CELL;
	mat_star[ROW_A-2][8] = INVALID_CELL;
	mat_star[ROW_A-2][9] = INVALID_CELL;
	mat_star[ROW_A-2][10] = INVALID_CELL;

	// second star row
	mat_star[ROW_A-1][0] = INVALID_CELL;
	mat_star[ROW_A-1][1] = INVALID_CELL;
	mat_star[ROW_A-1][2] = INVALID_CELL;
	mat_star[ROW_A-1][3] = INVALID_CELL;
	mat_star[ROW_A-1][7] = INVALID_CELL;
	mat_star[ROW_A-1][8] = INVALID_CELL;
	mat_star[ROW_A-1][9] = INVALID_CELL;
	mat_star[ROW_A-1][10] = INVALID_CELL;

	// before last star row
	mat_star[ROW_D+1][0] = INVALID_CELL;
	mat_star[ROW_D+1][1] = INVALID_CELL;
	mat_star[ROW_D+1][2] = INVALID_CELL;
	mat_star[ROW_D+1][3] = INVALID_CELL;
	mat_star[ROW_D+1][7] = INVALID_CELL;
	mat_star[ROW_D+1][8] = INVALID_CELL;
	mat_star[ROW_D+1][9] = INVALID_CELL;
	mat_star[ROW_D+1][10] = INVALID_CELL;

	// last star row
	mat_star[ROW_D+2][0] = INVALID_CELL;
	mat_star[ROW_D+2][1] = INVALID_CELL;
	mat_star[ROW_D+2][2] = INVALID_CELL;
	mat_star[ROW_D+2][3] = INVALID_CELL;
	mat_star[ROW_D+2][4] = INVALID_CELL;
	mat_star[ROW_D+2][6] = INVALID_CELL;
	mat_star[ROW_D+2][7] = INVALID_CELL;
	mat_star[ROW_D+2][8] = INVALID_CELL;
	mat_star[ROW_D+2][9] = INVALID_CELL;
	mat_star[ROW_D+2][10] = INVALID_CELL;

	// exceptions left and right borders
	mat_star[ROW_A+1][0] = INVALID_CELL;
	mat_star[ROW_A+2][0] = INVALID_CELL;

	mat_star[ROW_A+1][10] = INVALID_CELL;
	mat_star[ROW_A+2][10] = INVALID_CELL;
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

	int vec_input[INPUT];
	
	cin >> vec_input[0];
	while (!cin.eof()) {
		// READ INPUT
		for (int i = 1; i < 12; i++)
			cin >> vec_input[i];

		// PROCESS
		init_star();
		int maxsum = calc_max(vec_input);

#ifdef DEBUG
		cout << START_DEBUG;
		show_star();
#endif

		int minsum;
		if (maxsum != NO_SOLUTION)
			minsum = calc_min(vec_input, true);
		
#ifdef DEBUG
		show_star();
		cout << END_DEBUG;
#endif

		// SHOW OUTPUT
		if ((maxsum != NO_SOLUTION))
			cout << minsum << " " << maxsum << endl;
		else
			cout << "NO SOLUTION" << endl;


		// READ NEXT INPUT
		cin >> vec_input[0];
	}
		
	
	return 0;
}

/* @END_OF_SOURCE_CODE */

