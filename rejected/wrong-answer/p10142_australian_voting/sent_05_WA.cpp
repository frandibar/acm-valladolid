/* @JUDGE_ID:  40922FK  10142  C++  */
/* @BEGIN_OF_SOURCE_CODE */
/**************************************************************************
 Solution to Problem 10142 - Australian Voting
 by: Francisco Dibar
 date: Aug-19-2006
**************************************************************************/

//#define DEBUG
//#define ONLINE_JUDGE 
#include <iostream>
#ifndef ONLINE_JUDGE 
    #include <fstream>
#endif 
#include <sstream>  // istringstream
#include <string>
#include <vector>

#define START_DEBUG "START DEBUG ********************************************************************\n"
#define END_DEBUG   "END DEBUG **********************************************************************\n"

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

//const int MAX_BALLOTS = 1000;
//const int MAX_CANDIDATES = 25;
const int VOTES = 0;
const int ROUND = 1;

///////////////////////////////////////////////////////////////////////////
int calculateMaxVotes(int ncandidates, 
                      const vector<vector<int> >& mBallots,
                      vector<vector<int> >& mAcumBallots)
{
    // resize mBallots
    for (int i = 1; i <= ncandidates; i++)
        // i indicates candidate number
        // 1st index stores accumulated votes
        // 2nd index stores eliminated round
        mAcumBallots[i].resize(2); 

    int nvotesToWin;
    // with even nballots, win with nballots/2 + 1, else with (nballots+1)/2
    int nballots = (int)mBallots.size();
    if (nballots % 2 == 0)
        nvotesToWin = nballots / 2 + 1;
    else
        nvotesToWin = (nballots + 1) / 2;

#ifdef DEBUG
    cout << nvotesToWin << " votes are needed to win\n";
#endif

    // load mAcumBallots with first vote
    int maxVotes = 0;
    for (int i = 0; i < nballots; i++) {
        int candidate = mBallots[i][0];
        mAcumBallots[candidate][VOTES]++;
        // calculate max vote
        if (mAcumBallots[candidate][VOTES] > maxVotes)
            maxVotes = mAcumBallots[candidate][VOTES];
    }

    bool winner = (maxVotes >= nvotesToWin);
    int round = 0;
    while (!winner && (round < ncandidates)) {
        round++;

#ifdef DEBUG
        // show mAcumBallots
        cout << "mAcumBallots at round " << round << endl;
        for (int i = 1; i <= ncandidates; i++) {
            cout << i << " ";
            for (int j = 0; j < (int)mAcumBallots[i].size(); j++)
                cout << mAcumBallots[i][j] << " ";
            cout << endl;
        }
#endif

        // calculate minor amount of ballots
        int minVotes = nballots;    // initialize to max value
        for (int i = 1; i <= ncandidates; i++) {
            // if votes to this candidate are less than minVotes
            // and cantidate hasn't been eliminated
            if ((mAcumBallots[i][VOTES] < minVotes) && (mAcumBallots[i][ROUND] == 0))
                minVotes = mAcumBallots[i][VOTES];
        }
        // mark candidates with less votes as eliminated this round
        for (int i = 1; i <= ncandidates; i++) {
            // if votes to this candidate are equal to minVotes
            // and cantidate hasn't been eliminated
            if ((mAcumBallots[i][VOTES] == minVotes) && (mAcumBallots[i][ROUND] == 0)) {
                mAcumBallots[i][ROUND] = round;
#ifdef DEBUG
                cout << "candidate " << i << " is eliminated\n";
#endif
            }
        }
        // for the eliminated candidates, recount their votes for non eliminated candidates
        for (int i = 1; i <= ncandidates; ++i) {
            if (mAcumBallots[i][ROUND] == round) {
                // it's an eliminated candidate
                // find non eliminated candidates vote among those ballots
                // that had this candidate in 1st place
                for (int j = 0; j < nballots; ++j) {
                    if (mBallots[j][0] == i) {
                        for (int n = 1; n < ncandidates; ++n) {
                            // search from 2nd
                            // if vote is to a non eliminated candidate or a
                            // candidate eliminated this round
                            int cand = mBallots[j][n];
                            if (mAcumBallots[cand][ROUND] == 0) {
                                mAcumBallots[cand][VOTES]++;
                                if (mAcumBallots[cand][VOTES] > maxVotes)
                                    maxVotes = mAcumBallots[cand][VOTES];
                                break;  // consider only first vote
                            }
                        }
                    }
                }
            }
        }
        winner = (maxVotes >= nvotesToWin);
    }

#ifdef DEBUG
    cout << "there is a winner with " << maxVotes << " votes\n";
#endif
    return maxVotes;
}

///////////////////////////////////////////////////////////////////////////
//  MAIN PROGRAM
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
    string line;
    std::getline(cin, line);    // ignore rest of line
    std::getline(cin, line);    // skip blank line

    for (int k = 0; k < ncases; ++k) {
        // READ INPUT
        int ncandidates;
        cin >> ncandidates;
        std::getline(cin, line);    // ignore rest of line

        vector<string> vCandidates(ncandidates + 1);            
        // load vCandidates with names
        for (int i = 1; i <= ncandidates; ++i) { // start index at 1
            std::getline(cin, vCandidates[i]);
        }

        // read ballots into mBallots
        int nballots = 0;
        vector<vector<int> > mBallots;
        std::getline(cin, line);
        while (!line.empty() && !cin.eof()) {
            std::istringstream is(line);
            vector<int> vBallots(ncandidates);
            for (int m = 0; m < ncandidates; ++m)
                is >> vBallots[m];

            mBallots.push_back(vBallots);
            nballots++;

            std::getline(cin, line);
        }
        
#ifdef DEBUG
        cout << START_DEBUG;
        // show mBallots
        cout << "mBallots" << endl;
        for (int i = 0; i < (int)mBallots.size(); ++i) {
            cout << i << "] ";
            for (int j = 0; j < (int)mBallots[i].size(); ++j)
                cout << mBallots[i][j] << " ";
            cout << endl;
        }
#endif

        // PROCESS
        vector<vector<int> > mAcumBallots(ncandidates + 1);
        // mAcumBallots[i] contains the row corresponding to candidate i
        int maxVotes = calculateMaxVotes(ncandidates, mBallots, mAcumBallots);

#ifdef DEBUG
        // show mAcumBallots
        cout << "mAcumBallots" << endl;
        for (int i = 1; i <= ncandidates; i++) {
            cout << i << " ";
            for (int j = 0; j < (int)mAcumBallots[i].size(); j++)
                cout << mAcumBallots[i][j] << " ";
            cout << vCandidates[i] << endl;
        }
        cout << END_DEBUG;
#endif

        // SHOW OUTPUT
        // traverse mAcumBallots & show candidates with maxVotes
        for (int i = 1; i <= ncandidates; ++i) 
            if ((mAcumBallots[i][VOTES] == maxVotes))
                cout << vCandidates[i] << endl;

        // separate cases with blank line
        if (k < ncases-1) cout << endl;
    }

    return 0;
}

/* @END_OF_SOURCE_CODE */

