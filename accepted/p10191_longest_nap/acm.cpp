/* @JUDGE_ID:  40922FK  10191  C++  */
/* @BEGIN_OF_SOURCE_CODE */    
/**************************************************************************
 Solution to Problem 10191 - Longest Nap
 by: Francisco Dibar
 date: Aug-17-2005
**************************************************************************/

//#define DEBUG
//#define ONLINE_JUDGE 
#include <iostream>
#ifndef ONLINE_JUDGE 
	#include <fstream>
#endif 
#include <string>
#include <vector>
#include <sstream>

#define NMINUTES	480	// 480 = 8x60

#define START_DEBUG	"START DEBUG ********************************************************************\n"
#define END_DEBUG		"END DEBUG **********************************************************************\n"
	
using namespace std;

///////////////////////////////////////////////////////////////////////////
int timeIndex(const string& time)
{
	// 10:00 corresponds to 0
	// 10:01 corresponds to 1
	// 18:00 corresponds to 480
	int i = (time[1]-'0')*60 + (time[3]-'0')*10 + time[4]-'0';
	return i;
}

///////////////////////////////////////////////////////////////////////////
string timeFromIndex(int index)
{
	// 0 corresponds to 10:00
	// 1 corresponds to 10:01
	// 480 corresponds to 18:00
	
	//if (index > NMINUTES)
	//	return "";
	
	int h = index / 60;
	int m = index % 60;

	string time = "10:00";
	time[1] = h + '0';
	if (m > 9)
		time[3] = m / 10 + '0';
	time[4] = m % 10 + '0';
	
	return time;
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

	int tasks;
	cin >> tasks;
	int day = 0;
	// READ INPUT
	while (!cin.eof()) {
		day++;
		string line;
		getline(cin, line);	// ignore rest of line
		vector<bool> vecAgenda(NMINUTES);
		for (int i = 0; i < tasks; i++) {
			getline(cin, line);
			istringstream is(line);
			string starttime, endtime;
			is >> starttime >> endtime;
			
			int from = timeIndex(starttime);
			int to = timeIndex(endtime);
			vecAgenda[from] = true;		// avoid problems when from = to
			for (int j = from; j < to; j++)
				vecAgenda[j] = true;
		}

		// PROCESS		
		int maxnap = 0;
		int nap = 0;
		int maxistart = 0;
		int istart = -1;
		for (int i = 0; i < NMINUTES; i++) {
			while (!vecAgenda[i] && (i < NMINUTES)) {
				i++;
				nap++;
			}
			if (nap > maxnap) {
				maxnap = nap;
				maxistart = istart + 1;
			}
			if (vecAgenda[i]) {
				nap = 0;
				istart = i;
			}
		}

		// SHOW OUTPUT
		int hours = maxnap / 60;
		int minutes = maxnap % 60;
		string start = timeFromIndex(maxistart);		
		cout << "Day #" << day << ": the longest nap starts at " << start << " and will last for ";
		if (hours > 0)
			cout << hours << " hours and " << minutes << " minutes." << endl;
		else
			cout << minutes << " minutes." << endl;

#ifdef DEBUG
		cout << START_DEBUG;
		cout << maxnap << " minutes" << endl;
		cout << "starts at " << maxistart << endl;
		for (int i = 0; i < NMINUTES; i++)
			cout << i << "\t" << vecAgenda[i] << endl;
		cout << END_DEBUG;
#endif
	
		cin >> tasks;
	}
		
	return 0;
}

/* @END_OF_SOURCE_CODE */

