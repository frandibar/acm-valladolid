/* @JUDGE_ID:  40922FK  10131  C++  */
/* @BEGIN_OF_SOURCE_CODE */    
/**************************************************************************
 Solution to Problem 10131 - Is Bigger Smarter?
 by: Francisco Dibar
 date: Dec-13-2005
**************************************************************************/

//#define DEBUG
//#define ONLINE_JUDGE 
#include <iostream>
#ifndef ONLINE_JUDGE 
	#include <fstream>
#endif 
#include <vector>
#include <algorithm>		// sort

#define START_DEBUG	"START DEBUG ********************************************************************\n"
#define END_DEBUG	"END DEBUG **********************************************************************\n"

#define UP		1
#define LEFT	2
#define UPLEFT	3

using std::cin;
using std::cout;
using std::endl;
using std::vector;

///////////////////////////////////////////////////////////////////////////
class elefant {
public:
	int num;
	int size;
	int iq;

	elefant() {};	// constructor
	elefant(const elefant& e) {	// copy constructor
		num = e.num;
		size = e.size;
		iq = e.iq;
	}
};

///////////////////////////////////////////////////////////////////////////
inline bool sort_size_asc(const elefant& a, const elefant& b)
// returns true if a.size > b.size
{
	return (a.size > b.size);
}

///////////////////////////////////////////////////////////////////////////
inline bool sort_iq_desc(const elefant& a, const elefant& b)
// returns true if a.iq < b.iq
{
	return (a.iq < b.iq);
}


////////////////////////////////////////////////////////////////////////////////
void reconstruct_path(const vector< vector<int> >& mp, const vector<elefant>& vs, vector<elefant>& vr)
// returns vr with the path
{
	// reconstruct path
	int i = (int)mp.size()-1;
	int j = (int)mp[0].size()-1;
	while ((i > 0) && (j > 0)) {
		if (mp[i][j] == UPLEFT) {
			vr.push_back(vs[i-1]);	// s[i] = t[j]
			i--;
			j--;
		} else if (mp[i][j] == UP)
			i--;
		else
			j--;
	}
}

////////////////////////////////////////////////////////////////////////////////
bool find_previous(const vector< vector<int> >& mp, int i, int j, const vector<elefant>& vs, elefant* prev)
{
	// find in mp an UPLEFT
	while ((i > 0) && (j > 0)) {
		if (mp[i][j] == UPLEFT)
			break;
		else if (mp[i][j] == UP)
			i--;
		else
			j--;
	}
	if (mp[i][j] == UPLEFT) {
		*prev = vs[i-1];
		return true;
	}
	return false;
}

////////////////////////////////////////////////////////////////////////////////
void lcs(const vector<elefant>& vs, const vector<elefant>& vt, vector<elefant>& vr)
// returns vector r with the lcs
{
	vector< vector<int> > mc;	
	vector< vector<int> > mp;	// contains the path
	// it's possible to avoid using mp, and reconstruct the path on each step.

	mc.resize((int)vs.size() + 1);
	mp.resize((int)vs.size() + 1);
	for (int i = 0; i < (int)vs.size() + 1; i++) {
		mc[i].resize((int)vt.size() + 1, 0);
		mp[i].resize((int)vt.size() + 1, 0);
	}

	// fill matrix m
	elefant prev;
	for (int i = 1; i < (int)mc.size(); i++) {
		for (int j = 1; j < (int)mc[i].size(); j++) {
			// find previous elefant and validate order
			bool found = find_previous(mp, i, j-1, vs, &prev);
			if ( (vs[i-1].num == vt[j-1].num) && 
				(!found || ((vs[i-1].size < prev.size) && (vs[i-1].iq > prev.iq))) ) {
				mc[i][j] = mc[i-1][j-1] + 1;
				mp[i][j] = UPLEFT;
			} else if (mc[i-1][j] >= mc[i][j-1]) {
					mc[i][j] = mc[i-1][j]; 
					mp[i][j] = UP;
			} else {
					mc[i][j] = mc[i][j-1]; 
					mp[i][j] = LEFT;
			}
		}           
	}

#ifdef DEBUG
	// show matric mc
	// show labels first row
	cout << endl << "    ";
	for (int i = 0; i < (int)vt.size(); i++)
		cout << vt[i].num << " ";
	cout << endl;

	for (i = 0; i < (int)mc.size(); i++) {
		// show vertical labels
		if (i > 0)
			cout << vs[i-1].num << " ";
		else
			cout << "  ";
		for (int j = 0; j < (int)mc[i].size(); j++) {
			cout << mc[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;

	// show path matrix
	cout << "    ";
	for (int i = 0; i < (int)vt.size(); i++)
		cout << vt[i].num << " ";
	cout << endl;

	for (i = 0; i < (int)mp.size(); i++) {
		// show vertical labels
		if (i > 0)
			cout << vs[i-1].num << " ";
		else
			cout << "  ";
		for (int j = 0; j < (int)mp[i].size(); j++) {
            cout << mp[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
#endif

	reconstruct_path(mp, vs, vr);
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

	vector<elefant> vec_elefants_ss;

	// READ INPUT
	int number = 0;
	elefant e;
	cin >> e.size;
	while (!cin.eof()) {
		number++;
		cin >> e.iq;
		e.num = number;
		vec_elefants_ss.push_back(e);
		cin >> e.size;
	}

	// PROCESS	
	vector<elefant> vec_elefants_siq = vec_elefants_ss;

#ifdef DEBUG
	cout << START_DEBUG;
	for (int i = 0; i < (int)vec_elefants_ss.size(); i++) {
		cout << vec_elefants_ss[i].num << " " << vec_elefants_ss[i].size << " " << vec_elefants_ss[i].iq << endl;
		cout << vec_elefants_siq[i].num << " " << vec_elefants_siq[i].size << " " << vec_elefants_siq[i].iq << endl;
		cout << endl;
	}
#endif

	// sort vec_elefants_ss by size asc, iq desc
	std::sort(vec_elefants_ss.begin(), vec_elefants_ss.end(), sort_size_asc);

	// sort vec_elefants_siq by iq desc, size asc
	std::sort(vec_elefants_siq.begin(), vec_elefants_siq.end(), sort_iq_desc);

#ifdef DEBUG
	for (int i = 0; i < (int)vec_elefants_ss.size(); i++) {
		cout << vec_elefants_ss[i].num << " " << vec_elefants_ss[i].size << " " << vec_elefants_ss[i].iq << endl;
	}
	cout << endl;
	for (int i = 0; i < (int)vec_elefants_siq.size(); i++) {
		cout << vec_elefants_siq[i].num << " " << vec_elefants_siq[i].size << " " << vec_elefants_siq[i].iq << endl;
	}
#endif

	vector<elefant> vec_lcs;
	lcs(vec_elefants_ss, vec_elefants_siq, vec_lcs);

	// SHOW OUTPUT
	cout << (int)vec_lcs.size() << endl;
	for (int i = 0; i < (int)vec_lcs.size(); i++)
		cout << vec_lcs[i].num << endl;

#ifdef DEBUG
	cout << START_DEBUG;

	cout << END_DEBUG;
#endif

	return 0;
}

/* @END_OF_SOURCE_CODE */

