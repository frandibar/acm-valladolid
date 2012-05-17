/* @JUDGE_ID:  40922FK  758  C++  */
/* @BEGIN_OF_SOURCE_CODE */    
/**************************************************************************
 Solution to Problem 758 - The Same Game
 by: Francisco Dibar
 date: Nov-05-2006
**************************************************************************/

//#define DEBUG
//#define ONLINE_JUDGE 

#ifdef DEBUG
    #define START_DEBUG	"**************************** START DEBUG *****************************\n"
    #define END_DEBUG	"***************************** END DEBUG ******************************\n"
    // g++-2.95 doesn't support asserts
    #define ASSERT(x,y)   if (!(x)) { std::cerr << "ASSERTION FAILED!: " << y << "\n"; exit(1); }
#endif

#include <iostream>
#ifndef ONLINE_JUDGE 
	#include <fstream>
#endif 
#include <vector>
#include <queue>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::queue;

const int NROWS = 10;
const int NCOLS = 15;

const char RED   = 'R';
const char GREEN = 'G';
const char BLUE  = 'B';
const char CLEAR = '.';

////////////////////////////////////////////////////////////////////////////////
int floodfill(vector<vector<char> >& grid, int xi, int yi, char search, char replaceWith)
// returns the number of painted points
// xi: initial row, yi: initial column
{
	if (grid[xi][yi] != search) return 0;

	queue<pair<int, int> > qMissing;
	qMissing.push(make_pair(xi, yi));
	int npainted = 0;
	while (!qMissing.empty()) {
		pair<int, int> pos;
		pos = qMissing.front();
		qMissing.pop();
		// it can ocurr that I push 2 times the same thing
		if (grid[pos.first][pos.second] == search) {
			grid[pos.first][pos.second] = replaceWith;
			npainted++;
			if (pos.first-1 >= 0) {
				if (grid[pos.first-1][pos.second] == search)
					qMissing.push(make_pair(pos.first-1, pos.second));
			}
			if (pos.first+1 < (int)grid.size()) {
				if (grid[pos.first+1][pos.second] == search)
					qMissing.push(make_pair(pos.first+1, pos.second));
			}

			if (pos.second-1 >= 0) {
				if (grid[pos.first][pos.second-1] == search)
					qMissing.push(make_pair(pos.first, pos.second-1));
			}

			if (pos.second+1 < (int)grid[0].size()) {
				if (grid[pos.first][pos.second+1] == search)
					qMissing.push(make_pair(pos.first, pos.second+1));
			}
		}
	}
	return npainted;
}

///////////////////////////////////////////////////////////////////////////
void shiftLeft(vector<vector<char> >& mBoard)
{
    // TODO

}

///////////////////////////////////////////////////////////////////////////
void shiftDown(vector<vector<char> >& mBoard)
{
    // TODO
    for (int j = 0; j < NCOLS; ++j) {
        for (int i = NROWS - 1; i >= 0; --i)
            if (mBoard[i][j] == CLEAR) {
                // find first cell above not clear
                for (int k = i-1; k >= 0; --k)
                    if (mBoard[k][j] != CLEAR)
                        mBoard[i][j] = mBoard[k][j];

            }
    }

}

///////////////////////////////////////////////////////////////////////////
void applyMove(vector<vector<char> >& mBoard, int x, int y)
{
    floodfill(mBoard, x, y, mBoard[x][y], CLEAR);
    // shift balls
    shiftDown(mBoard);
    shiftLeft(mBoard);
}

///////////////////////////////////////////////////////////////////////////
bool checkForBigClusters(vector<vector<char> >& mBoard)
// returns true if there are any big clusters    
{
    // floodfill with the same color, just to count cluster size
    for (int i = 0; i < NROWS; ++i)
        for (int j = 0; j < NROWS; ++j)
            if (floodfill(mBoard, i, j, mBoard[i][j], mBoard[i][j]) > 1)
                return true;

    return false;
}

///////////////////////////////////////////////////////////////////////////
//	MAIN PROGRAM
///////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{
#ifndef ONLINE_JUDGE 
	// redirect input and output
    cin.rdbuf((new std::ifstream("input"))->rdbuf()); 
    cout.rdbuf((new std::ofstream("output"))->rdbuf()); 
#endif 

	int ncases;
	cin >> ncases;

    vector<vector<char> > mBoard(NROWS);
    for (vector<vector<char> >::iterator i = mBoard.begin(); i != mBoard.end(); ++i)
        mBoard.resize(NCOLS);

	for (int k = 0; k < ncases; ++k) {

		// READ INPUT
        for (int i = 0; i < NROWS; ++i)
            for (int j = 0; j < NCOLS; ++j)
                cin >> mBoard[i][j];

        // PROCESS
        int nballs = NROWS * NCOLS;
        bool bigClusters = true;
        int score = 0;
        int nmoves = 0;

        // game ends if no more balls are left, or no big cluster exists                    
        while (nballs > 0 && bigClusters) {
            // find next move
            // for each row, col apply floodfill on mTemp, then apply move on mBoard
            vector<vector<char> > mTemp(mBoard);
            int maxCluster = 1;
            int x = 0, y = 0;
            for (int i = NROWS - 1; i >= 0; --i) {
                for (int j = 0; j < NCOLS; ++j) {
                    int cluster = floodfill(mTemp, i, j, mTemp[i][j], CLEAR);
                    // choose leftmost, then bottommost
                    if ((cluster > maxCluster) || 
                       ((cluster == maxCluster) && (j < i))) {
                        maxCluster = cluster;
                        x = i;
                        y = j;
                    }
                }
            }
            // SHOW OUTPUT
            char color = mBoard[x][y];
            int points = (maxCluster-2) * (maxCluster-2);
            cout << "Move " << nmoves << " at (" << x << "," << y << "): removed " << maxCluster << " balls of color " << color << ", got " << points << " points." << endl;

            nballs -= maxCluster;
            score += points;
            applyMove(mBoard, x, y);
            bigClusters = checkForBigClusters(mBoard);
        }

        // SHOW OUTPUT
        cout << "Final score: " << score << ", with " << nballs << " balls remaining." << endl;
	}
		
#ifdef DEBUG
	cout << START_DEBUG;

	cout << END_DEBUG;
#endif
	
	return 0;
}

/* @END_OF_SOURCE_CODE */

