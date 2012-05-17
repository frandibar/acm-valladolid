/* @JUDGE_ID:  40922FK  148  C++  */
/* @BEGIN_OF_SOURCE_CODE */    
/**************************************************************************
 Solution to Problem 148 - Anagram checker
 by: Francisco Dibar
 date: Nov-05-2006
**************************************************************************/

#define DEBUG
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
#include <string>
#include <algorithm>    // sort

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

const char SEPARATOR = '#';


///////////////////////////////////////////////////////////////////////////
bool contains(const string& container, const string& word)
// returns true if all of word's letters are contained in container
// precondition: word and container are sorted    
{
    unsigned int p = container.find(word[0]);
    if (p == string::npos)
        return false;

    for (int i = 1; i < (int)word.length(); ++i) {
        if ((p = container.find(word[i], p+1)) == string::npos)
            return false;
    }
    return true;
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

    string input;
    getline(cin, input);

    vector<string> vDictionary;
    vector<string> vSortedDictionary;
    vector<string> vPhrases;
    vector<string> vSortedPhrases;
    // READ INPUT
    // dictionary
    while (input[0] != SEPARATOR) {
        vDictionary.push_back(input);
        std::sort(input.begin(), input.end());
        // sort input and push in vSortedDictionary
        vSortedDictionary.push_back(input);
        getline(cin, input);
    }
    // phrases
    getline(cin, input);
    while (input[0] != SEPARATOR) {
        vPhrases.push_back(input);
        // sort input and push in vSortedPhrases
        std::sort(input.begin(), input.end());
        // remove spaces at beginning
        vSortedPhrases.push_back(input.begin() + input.find_first_not_of(' '));
        getline(cin, input);
    }

    // PROCESS
    // for each phrase, obtain anagrams
    for (int i = 0; i < (int)vPhrases.size(); ++i) {
        // vFits indicates if word in vDictionary[j] can be a valid anagram in vPhrases[i]
        vector<bool> vFits(vDictionary.size());
        for (int j = 0; j < (int)vDictionary.size(); ++j) {
            vFits[j] = contains(vSortedPhrases[i], vSortedDictionary[j]); 
            //cout << vSortedDictionary[j] << (vFits[j] ? " in " : " not in ") << vSortedPhrases[i] << endl;
        }

        // choose words and try to find a phrase anagram
        // generate al possible combinations of words with vFits = true
        int totalLength = 0;
        for (int u = 0; u < (int)vDictionary.size(); ++u) {
            
        }

    }

    //for (vector<string>::const_iterator i = vPhrases.begin(); i != vPhrases.end(); ++i) {
        //cout << *i << endl;
    //}

		// SHOW OUTPUT

#ifdef DEBUG
    cout << "sorted dictionary" << endl;
    for (vector<string>::iterator i = vSortedDictionary.begin(); i != vSortedDictionary.end(); ++i) {
        cout << *i << endl;
    }
    cout << "sorted phrases" << endl;
    for (vector<string>::iterator i = vSortedPhrases.begin(); i != vSortedPhrases.end(); ++i) {
        cout << *i << endl;
    }
#endif

		
#ifdef DEBUG
	cout << START_DEBUG;

	cout << END_DEBUG;
#endif
	
	return 0;
}

/* @END_OF_SOURCE_CODE */

