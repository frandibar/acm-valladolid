/* @JUDGE_ID:  40922FK  10016  C++  */
/* @BEGIN_OF_SOURCE_CODE */    
/******************************************************************************
 Solution to Problem 10016 - Flip-Flop the Squarelotron
 by: Francisco Dibar
 date: Aug-13-2006
******************************************************************************/

//#define DEBUG
//#define ONLINE_JUDGE 
#include <iostream>
#ifndef ONLINE_JUDGE 
	#include <fstream>
#endif 
#include <vector>

#ifdef DEBUG
    #define START_DEBUG	"START DEBUG ********************************************************************\n"
    #define END_DEBUG	"END DEBUG **********************************************************************\n"
    // g++-2.95 doesn't support asserts
    #define ASSERT(x,y)   if (!(x)) { std::cerr << "ASSERTION FAILED!: " << y << "\n"; exit(1); }
#endif

using std::cin;
using std::cout;
using std::endl;
using std::vector;


const int UP_DOWN      = 1;
const int LEFT_RIGHT   = 2;
const int DIAGONAL     = 3;
const int INV_DIAGONAL = 4;


////////////////////////////////////////////////////////////////////////////////
int mirror(int i, int move, int N)
// returns index of i's mirror to swap with
// N is the matrix dimension    
{
    int col = i % N,
        row = (i - col) / N;
    // i = row x N + col;
    switch (move) {
        case UP_DOWN:       // (row, col) <-> (N - row - 1, col)
            return (N - row - 1) * N + col;
            break;
        case LEFT_RIGHT:    // (row, col) <-> (row, N - col - 1)
            return row * N + N - col - 1;
            break;
        case DIAGONAL:  // (row, col) <-> (col, row)
            return col * N + row;
            break;
        case INV_DIAGONAL:      // (row, col) <-> (N - col - 1, N - row - 1)
            return (N - col - 1) * N + N - row - 1;
            break;
        default:
            break;
    }
    return -1;
}

////////////////////////////////////////////////////////////////////////////////
void applyMove(vector<int>& vSTron, int aMove, vector<int>& vRings, int N)
{
    // apply transformation on each index of every ring
    int nswaps = (int)vRings.size();
    if (nswaps == 1) return;

    vector<bool> vSwapped(nswaps + 1);  // true indicates index was swapped
                                        // rings start at 1
    int swapped = 0;
    int i = 0; 
    while (swapped < nswaps) {
        int ind = vRings[i++],
            m = mirror(ind, aMove, N);
        if (ind != m) {
            if (!vSwapped[ind]) {        // asking for vSwapped[m] is redundant
                swap(vSTron[ind], vSTron[m]);
                swapped += 2;
                vSwapped[ind] = vSwapped[m] = true;
            }
        } else {
            swapped++;
            vSwapped[ind] = true;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////
void inRing(vector<vector<int> >& vRings, int N)
// indicates the ring each index belongs to
// N is the matrix dimension
{   
    int dim = N*N;
    for (int i = 0; i < dim; i++) {
        int col = i % N,                                   // col = i mod N
        row = (i - col) / N,                               // row = (i - col) / N
        ring = min(min(row, col) + 1, min(N - row, N - col)); // ring = min(row + 1, col + 1, N - row, N - col)
        vRings[ring].push_back(i);    
    }
}

#ifdef DEBUG
#include <string>
////////////////////////////////////////////////////////////////////////////////
std::string getMove(int aMove)
{
    switch (aMove) {
        case UP_DOWN:      return "UP_DOWN";
        case LEFT_RIGHT:   return "LEFT_RIGHT";
        case DIAGONAL:     return "DIAGONAL";
        case INV_DIAGONAL: return "INV_DIAGONAL";
    }
    return "";
}
#endif

///////////////////////////////////////////////////////////////////////////
//	MAIN PROGRAM
///////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{
	// redirect input and output
	#ifndef ONLINE_JUDGE 
		cin.rdbuf((new std::ifstream("input"))->rdbuf()); 
		cout.rdbuf((new std::ofstream("output"))->rdbuf()); 
	#endif 

    int ncases;
    cin >> ncases;
    for (int k = 0; (k < ncases) && (!cin.eof()); ++k) {
        int N;
        cin >> N;
        int dim = N * N;
        vector<int> vSTron(dim);       // NxN unidimensional matrix
        int nrings = (N + 1) / 2;
        vector< vector<int> > vRings(nrings+1);     // en vRings[r][i] stores indexes corresponding to ring r
                                                    // rings start at 1
        // load vRings
        inRing(vRings, N);

        // load matrix
        for (int i = 0; i < dim; ++i)
            cin >> vSTron[i];

#ifdef DEBUG
        cout << START_DEBUG;
        // show matrix
        cout << "outermost ring is ring 1" << endl;
        for (int i = 0; i < dim; ++i) {
            cout << vSTron[i] << " ";
            if ((i+1) % N == 0) cout << endl;
        }
#endif
        // read moves for each ring and apply them
        for (int ring = 1; ring <= nrings; ++ring) {
            int moves;
            cin >> moves;
            for (int m = 0; m < moves; ++m) {
                int move;
                cin >> move;
                applyMove(vSTron, move, vRings[ring], N);
#ifdef DEBUG
                // show matrix
                cout << "After applying move " << getMove(move) << " on ring " << ring << endl;
                for (int i = 0; i < dim; ++i) {
                    cout << vSTron[i] << " ";
                    if ((i+1) % N == 0) cout << endl;
                }
#endif
            }
        }
#ifdef DEBUG
        cout << END_DEBUG;
#endif

        // SHOW OUTPUT
        for (int i = 0; i < dim; ++i) {
            cout << vSTron[i] << " ";
            if ((i+1) % N == 0) cout << endl;
        }
    }

    return 0;
}

