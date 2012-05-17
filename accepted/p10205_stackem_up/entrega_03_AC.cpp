/* @JUDGE_ID:  40922FK  10205  C++  */
/* @BEGIN_OF_SOURCE_CODE */    
/**************************************************************************
 Solution to Problem 10205 - Stack'em up
 by: Francisco Dibar
 date: Dec-26-2005
**************************************************************************/

//#define DEBUG
//#define ONLINE_JUDGE 
#include <iostream>
#ifndef ONLINE_JUDGE 
	#include <fstream>
#endif 
#include <sstream>
#include <string>
#include <vector>

#define START_DEBUG	"START DEBUG ********************************************************************\n"
#define END_DEBUG	"END DEBUG **********************************************************************\n"

#define NCARDS 			52
#define NSUITS  			4
#define NVALUES 			13
#define MAX_SHUFFLES 	100

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;

///////////////////////////////////////////////////////////////////////////
class card {
public:
	int value,
		 suit;
	// constructor
	card(int value = 0, int suit = 0) {};
};

///////////////////////////////////////////////////////////////////////////
class deck {
private:
	vector<string> vec_suit_names;
	vector<string> vec_value_names;
	vector<int> vec_ordered;

public:
	// member variable
	vector<card> vec_deck;

	deck();	// constructor
	void load_names();
	void load_cards();
	void order();
	void shuffle(const vector<int>&);
	string card_name(const card&); 
	string card_name(int); 
};

///////////////////////////////////////////////////////////////////////////
void deck::shuffle(const vector<int>& vec_shuffle)
{
	vector<int> vec_aux(NCARDS);
	// initialize aux
	for (int j = 0; j < NCARDS; j++) 
		vec_aux[j] = vec_ordered[j];

	for (int i = 0; i < NCARDS; i++)
		// -1 because index starts at 1
		vec_ordered[i] = vec_aux[vec_shuffle[i]-1];	
}

///////////////////////////////////////////////////////////////////////////
void deck::order()
{
	for (int i = 0; i < NCARDS; i++)
		vec_ordered[i] = i;
}

///////////////////////////////////////////////////////////////////////////
void deck::load_cards()
{
	for (int p = 0; p < NSUITS; p++) {
		for (int v = 0; v < NVALUES; v++) {
			int order = NVALUES * p + v;
			vec_deck[order].suit = p;
			vec_deck[order].value = v;
		}
	}
}

///////////////////////////////////////////////////////////////////////////
deck::deck()		// constructor
{
	vec_suit_names.resize(NSUITS);
	vec_value_names.resize(NVALUES);
	vec_ordered.resize(NCARDS);
	vec_deck.resize(NCARDS);

	load_names();
	load_cards();
	order();
}

///////////////////////////////////////////////////////////////////////////
inline string deck::card_name(const card& c)
{
	return (vec_value_names[c.value] + " of " + vec_suit_names[c.suit]);
}

///////////////////////////////////////////////////////////////////////////
inline string deck::card_name(int pos)
// devuelve la card en la posicion pos
{
	int ord = vec_ordered[pos];
	return (vec_value_names[vec_deck[ord].value] + " of " + vec_suit_names[vec_deck[ord].suit]);
}

///////////////////////////////////////////////////////////////////////////
void deck::load_names()
{
	// suit names
	vec_suit_names[0] = "Clubs";
	vec_suit_names[1] = "Diamonds";
	vec_suit_names[2] = "Hearts";
	vec_suit_names[3] = "Spades";

	// value names
	vec_value_names[0] = "2";
	vec_value_names[1] = "3";
	vec_value_names[2] = "4";
	vec_value_names[3] = "5";
	vec_value_names[4] = "6";
	vec_value_names[5] = "7";
	vec_value_names[6] = "8";
	vec_value_names[7] = "9";
	vec_value_names[8] = "10";
	vec_value_names[9] = "Jack";
	vec_value_names[10] = "Queen";
	vec_value_names[11] = "King";
	vec_value_names[12] = "Ace";
}

///////////////////////////////////////////////////////////////////////////
//	MAIN PROGRAM
///////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{
	// redirect input and output
	#ifndef ONLINE_JUDGE 
		cin.rdbuf((new std::ifstream("input.txt"))->rdbuf()); 
		cout.rdbuf((new std::ofstream("output.txt"))->rdbuf()); 
	#endif 
	
	int cases;
	cin >> cases;
	for (int k = 0; (k < cases) && (!cin.eof()); k++) {
		// READ INPUT & PROCESS
		int shuffles;
		cin >> shuffles;
		// read known shuffles
		vector< vector<int> > mat_shuffles(MAX_SHUFFLES);
		for (int i = 0; i < shuffles; i++) {
			mat_shuffles[i].resize(NCARDS);
			for (int j = 0; (j < NCARDS) && (!cin.eof()); j++)
				cin >> mat_shuffles[i][j];
		}

		deck mydeck;

		// read and execute shuffles
		string line;
		std::getline(cin, line);	// ignore rest of previous line
		std::getline(cin, line);
		std::istringstream is(line);
		int shuffle;
		is >> shuffle;
		// read until blank line
		while (!is.fail()) {
			mydeck.shuffle(mat_shuffles[shuffle-1]);
			std::getline(cin, line);
			is.clear();
			is.str(line);
			is >> shuffle;
		}
		
		// SHOW OUTPUT
		// show deck of cards
		for (int c = 0; c < NCARDS; c++) 
			cout << mydeck.card_name(c) << endl;

		if (k < (cases - 1)) cout << endl; 
	}

#ifdef DEBUG
	cout << START_DEBUG;

	cout << END_DEBUG;
#endif

	return 0;
}

/* @END_OF_SOURCE_CODE */

