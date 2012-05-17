/* @JUDGE_ID:  40922FK  850  C++  */
/* @BEGIN_OF_SOURCE_CODE */    
/**************************************************************************
 Solution to Problem 850 - Crypt Kicker II
 by: Francisco Dibar
 date: Aug-08-2005
**************************************************************************/

//#define ONLINE_JUDGE 
#include <iostream>
#ifndef ONLINE_JUDGE 
	#include <fstream>
#endif 
#include <string>
#include <queue>

#define FRASE	"the quick brown fox jumps over the lazy dog"

using namespace std;

///////////////////////////////////////////////////////////////////////////
bool knownfrase(const string& s, string& str_enc)
// return true if s is the encrypted frase, str_enc returns with the
// encryption scheme
{
	string frase = FRASE;
#ifdef WIN32
	if (	(s.length() != frase.length()) ||
#else
	if (	(s.length() != frase.length()+1) ||
#endif
			(s[2] != s[28] || s[28]	!= s[33]) ||
			(s[1] != s[32]) ||
			(s[12] != s[17] || s[17] != s[26] || s[26] != s[41]) ||
			(s[11] != s[29]) ||
			(s[0] != s[31]) ||
			(s[5] != s[21]) ||
			(	s[3] != ' ' || s[9] != ' ' || 
				s[15] != ' ' || s[19] != ' ' || 
				s[25] != ' ' || s[30] != ' ' || 
				s[34] != ' ' || s[39] != ' ') ) 
		return false;
	
	bool valid = true;
#ifdef WIN32
	for (int i = 0; i < (int)s.length() && valid; i++) {	
#else
	for (int i = 0; i < (int)s.length()-1 && valid; i++) {	
#endif	
		// s.length = frase.length (sino sale antes)
		if (s[i] != ' ')
			if ((str_enc[frase[i]-'a'] != '0') && (str_enc[frase[i]-'a'] != s[i]))
				valid = false;
			else
				str_enc[frase[i]-'a'] = s[i];
	}

	if (!valid)	
		str_enc = "00000000000000000000000000";

	return valid;
}

///////////////////////////////////////////////////////////////////////////
string unencrypt(const string& s, const string& str_enc)
// return string s unencrypted
{
	string u = s;
#ifdef WIN32
	for (int i = 0; i < (int)s.length(); i++) {
#else
	for (int i = 0; i < (int)s.length()-1; i++) {
#endif	
		if (u[i] != ' ')
			// REVISAR!: se puede optimizar reordenando
			// str_enc y evitar el find
			u[i] = str_enc.find(s[i]) + 'a';
	}
	return u;
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

	int cases;
	cin >> cases;

	string line;
	getline(cin, line);	// finish reading line
	getline(cin, line);	// ignore blank line
	for (int k = 0; k < cases; k++) {
		getline(cin, line);
		bool foundfrase = false;
		queue<string> q;
		string str_enc = "00000000000000000000000000";
#ifdef WIN32
		while (!cin.eof() && !line.empty()) {
#else
		while (!cin.eof() && (line.length() > 1)) {
#endif	
			if (!foundfrase)
				if (!knownfrase(line, str_enc))
					q.push(line);
				else {
					foundfrase = true;
					// process each line in q
					while (!q.empty()) {
						string l = q.front();
						q.pop();
						cout << unencrypt(l, str_enc) << endl;
					}
					cout << FRASE << endl;
				}
			else {
				cout << unencrypt(line, str_enc) << endl;				
			}
			getline(cin, line);
		}
		if (!foundfrase)
			cout << "No solution." << endl;

		if (k < cases-1) cout << endl;
	}

	return 0;
}

/* @END_OF_SOURCE_CODE */

