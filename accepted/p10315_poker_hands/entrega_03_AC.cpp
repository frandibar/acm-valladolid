/* @JUDGE_ID:  40922FK  10315  C++  */
/* @BEGIN_OF_SOURCE_CODE */    
/**************************************************************************
 Solution to Problem 10315 - Poker Hands
 by: Francisco Dibar
 date: Jul-24-2005
**************************************************************************/

//#define ONLINE_JUDGE 
//#define DEBUG

#include <iostream>
#ifndef ONLINE_JUDGE 
	#include <fstream>
#endif 

#include <string>

#define NCARDS 	52
#define NSUITS  	4
#define NVALUES 	14
#define HAND 	5			// cantidad de cartas repartidas
#define MAX_SHUFFLES 	100
#define TIE 	0
#define WHITE 	1
#define BLACK 	2
#define DATA 	0

using namespace std;

///////////////////////////////////////////////////////////////////////////
class Card {
public:
	char	_value,
			_suit;
	// constructor
	Card() {
		_value = 0;
		_suit = 0;
	}
/*
	Card(string c) {	// c puede contener 2 o 3 digitos		
		_value = c[c.find_first_of("234567890JQKA")];
		_suit = c[c.find_first_of("CDHS")];
	}
*/
	Card(char *c) {	// c puede contener 2 o 3 digitos		
		_value = c[strlen(c)-2];
		_suit = c[strlen(c)-1];
	}

	int cardinal() const {
		if (_value == '0') return 10;
		if (_value <= '9') return _value - '0';
		else
			switch(_value) {
				case 'J': return 11; break;
				case 'Q': return 12; break;
				case 'K': return 13; break;
				case 'A': return 14; break;
			}
		return 0;	// nunca llega aca
	}

	bool after(const Card &c) const {
		return ((_suit > c._suit) || ((_suit == c._suit) && (this->cardinal() > c.cardinal())));
	}

	// sobrecarga de operadores
	friend int operator==(const Card &c1, const Card &c2) {
		return ((c1._value == c2._value) && (c1._suit == c2._suit));
	}
	
	friend int operator>(const Card &c1, const Card &c2){
		return (c1.cardinal() > c2.cardinal());
		}

	friend int operator>=(const Card &c1, const Card &c2){
		return (c1.cardinal() >= c2.cardinal());
		}

	friend istream &operator>>(istream &is, Card &card) {
		//string c;		tira error al terminar!!
		char c[4];
		is >> c;
		card = Card(c);
		return is;
	}

};

///////////////////////////////////////////////////////////////////////////
class Hand {
#ifdef DEBUG
public:
#else
private:
#endif
	enum rankValue {	rvHighCard, rvPair, rvTwoPairs, rvThreeOfKind, rvStraight, 
							rvFlush, rvFullHouse, rvFourOfKind, rvStraightFlush };
	rankValue _rank;
	int _rankInfo[HAND];
	int _ind;
	Card _vecCards[HAND];

protected:
	void sortSuitValue() {
		// ordenar las cartas por suit y luego por valor,
		// en orden descendente
		bool ordered = false;
		while (!ordered) {
			ordered = true;
			for (int i = HAND-1; i > 0; i--) {
				if (_vecCards[i].after(_vecCards[i-1])) {
					// swap
					Card c = _vecCards[i-1];
					_vecCards[i-1] = _vecCards[i];
					_vecCards[i] = c;
					ordered = false;
				}
			}
		}
	}

	void sortValue() {
		// ordenar las cartas por valor,
		// en orden descendente
		bool ordered = false;
		while (!ordered) {
			ordered = true;
			for (int i = HAND-1; i > 0; i--) {
				if (_vecCards[i].cardinal() > (_vecCards[i-1].cardinal())) {
					// swap
					Card c = _vecCards[i-1];
					_vecCards[i-1] = _vecCards[i];
					_vecCards[i] = c;
					ordered = false;
				}
			}
		}
	}

	rankValue setRank() {		
		// analizo por rank descendente, => al encontrar jugada termino
		if (straightFlush()) return rvStraightFlush;
		if (fourOfKind()) return rvFourOfKind;
		if (fullHouse()) return rvFullHouse;
		if (flush()) return rvFlush;
		if (straight()) return rvStraight;
		if (threeOfKind()) return rvThreeOfKind;
		if (twoPairs()) return rvTwoPairs;
		if (pair()) return rvPair;
		if (highCard()) return rvHighCard;
		return rvHighCard;
	}

	bool straightFlush() {
		// check for 5 equal suits
		char suit = _vecCards[0]._suit;
		int i = 1;
		while ((_vecCards[i]._suit == suit) && (i < HAND)) {
			i++;
		}

		if (i == HAND) {
			// suit iguales, analizo escalera
			sortSuitValue();	// ordenar descendentemente
			int j = 0;			
			while ((_vecCards[j].cardinal() == _vecCards[j+1].cardinal() + 1) && (j < HAND-1)) 
				j++;
			if (j == HAND-1) {
				// hay escalera
				_rank = rvStraightFlush;
				_rankInfo[DATA] = 1;
				_rankInfo[DATA+1] = _vecCards[0].cardinal();
				return true;
			}
		}
		return false;
	}

	int *histogram() {
		int *vecValues = new int[NVALUES+1];
		// inicializar vecValues en 0
		for (int i = 1; i <= NVALUES; i++)
			vecValues[i] = 0;

		// histograma
		for (int i = 0; i < HAND; i++)
			vecValues[_vecCards[i].cardinal()]++;
		
		return vecValues;
	}

	bool fourOfKind() {
		int *vecValues = histogram();
		for (int i = 1; i <= NVALUES; i++)
			if (vecValues[i] == 4) {
				_rank = rvFourOfKind;
				_rankInfo[DATA] = 1;
				_rankInfo[DATA+1] = i;
				delete []vecValues;
				return true;
			}
		delete []vecValues;
		return false;
	}

	bool fullHouse() {
		int *vecValues = histogram();
		bool pair = false;
		int terna = 0;
		for (int i = 1; i <= NVALUES; i++) {
			if (vecValues[i] == 2)
				pair = true;
			if (vecValues[i] == 3) 
				terna = i;
		}
		if (pair && terna) {
			_rank = rvFullHouse;
			_rankInfo[DATA] = 1;
			_rankInfo[DATA+1] = terna;
			delete []vecValues;
			return true;
		}
		delete []vecValues;
		return false;
	}

	bool flush() {
		sortSuitValue();
		char suit = _vecCards[0]._suit;
		int i = 0;
		while ((_vecCards[i]._suit == suit) && (i < HAND))
			i++;
		if (i == HAND) {
			_rank = rvFlush;
			_rankInfo[DATA] = HAND;
			for (int i = 1; i <= HAND; i++)
				_rankInfo[DATA+i] = _vecCards[i-1].cardinal();
			return true;
		}
		return false;
	}

	bool straight() {
		sortValue();
		int i = 0;			
		while ((_vecCards[i].cardinal() == _vecCards[i+1].cardinal() + 1) && (i < HAND-1)) 
			i++;
		if (i == HAND-1) {
			// hay escalera
			_rank = rvStraight;
			_rankInfo[DATA] = 1;
			_rankInfo[DATA+1] = _vecCards[0].cardinal();
			return true;
		}
		return false;
	}

	bool threeOfKind() {
		int *vecValues = histogram();

		for (int i = 1; i <= NVALUES; i++)
			if (vecValues[i] == 3) {
				_rank = rvThreeOfKind;
				_rankInfo[DATA] = 1;
				_rankInfo[DATA+1] = i;
				delete []vecValues;
				return true;
			}
		delete []vecValues;
		return false;
	}

	bool twoPairs() {
		int *vecValues = histogram();

		bool onepair = false;
		for (int i = 1; i <= NVALUES; i++) {
			if (vecValues[i] == 1) 
				_rankInfo[DATA+3] = i;

			if (vecValues[i] == 2) {
				if (!onepair) {
					onepair = true;
					_rankInfo[DATA+2] = i;
				} else {
					_rank = rvTwoPairs;
					_rankInfo[DATA] = 3;
					_rankInfo[DATA+1] = i;
					delete []vecValues;
					return true;
				}
			}
		}
		delete []vecValues;
		return false;
	}

	bool pair() {
		int *vecValues = histogram();

		int c = HAND-1;
		bool onepair = false;
		for (int i = 1; i <= NVALUES; i++) {
			if (vecValues[i] == 1) {
				_rankInfo[DATA+c] = i;
				c--;
			}

			if (vecValues[i] == 2) {
				onepair = true;
				_rank = rvPair;
				_rankInfo[DATA] = HAND-1;
				_rankInfo[DATA+1] = i;
			}
		}
		delete []vecValues;
		return onepair;
	}

	bool highCard() {
		int *vecValues = histogram();

		int c = HAND;
		for (int i = 1; i <= NVALUES; i++) {
			if (vecValues[i] > 1) {
				delete []vecValues;
				return false;
			}

			if (vecValues[i] == 1) {
				_rankInfo[DATA+c] = i;
				c--;
			}
		}
		_rank = rvHighCard;
		_rankInfo[DATA] = HAND;
		delete []vecValues;
		return true;
	}

	inline bool ranked() { return (_rankInfo[DATA] != 0); }

public:

	Hand() { 
		_ind = 0; 
		_rankInfo[DATA] = 0;
	}
	
	bool addCard(const Card &c) {
		if (_ind < HAND) {
			_vecCards[_ind++] = c;
			return true;
		}
		return false;
	}

	rankValue rank() { 
		if (!ranked())
			setRank();
		return _rank;
	}

	// sobrecarga de operadores
	friend int operator==(Hand &h1, Hand &h2) {
		if (h1.rank() != h2.rank())
			return false;
		else {			
			int i = 1;
			while ((h1._rankInfo[DATA+i] == h2._rankInfo[DATA+i]) && (i < h1._rankInfo[DATA]))
				i++;
			return (h1._rankInfo[DATA+i] == h2._rankInfo[DATA+i]);				
		}
	}

	friend int operator>(Hand &h1, Hand &h2) {
		if (h1.rank() < h2.rank())
			return false;
		else if (h1.rank() > h2.rank()) 			
			return true;
		else {
			// son iguales, desempatar
			int i = 1;
			while ((h1._rankInfo[i] == h2._rankInfo[i]) && (i < h1._rankInfo[DATA]))
				i++;
			return (h1._rankInfo[i] > h2._rankInfo[i]);				
		}
	}

	friend int operator<(Hand &h1, Hand &h2) {
		return !((h1 > h2) || (h1 == h2));
	}

};

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
	
	Card c;
	cin >> c;
	while (!cin.eof()) {
		Hand white, black;

		// READ INPUT
		// read black cards
		black.addCard(c);
		for (int i = 0; i < HAND-1; i++) {
			cin >> c;
			black.addCard(c);
		}
		// read white cards
		for (int i = 0; i < HAND; i++) {
			cin >> c;
			white.addCard(c);
		}

		// PROCESS
		int winner;
		if (black == white)
			winner = TIE;
		else
			winner = ((black > white) ? BLACK : WHITE);

// DEBUG OUTPUT
#ifdef DEBUG
		cout << "B " << black.rank() << " ";
		for (int i = 0; i < black._rankInfo[0]; i++)
			cout << black._rankInfo[i+1] << " ";
		cout << endl;
		cout << "W " << white.rank() << " ";
		for (int i = 0; i < white._rankInfo[0]; i++)
			cout << white._rankInfo[i+1] << " ";
		cout << endl;
#endif

		// SHOW OUTPUT
		switch(winner) {
		case TIE:
			cout << "Tie." << endl;
			break;
			
		case WHITE:
			cout << "White wins." << endl;
			break;
			
		case BLACK:
			cout << "Black wins." << endl;
			break;
		}
		cin >> c;
	}

	return 0;
}

/* @END_OF_SOURCE_CODE */

