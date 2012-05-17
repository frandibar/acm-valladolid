
/* @JUDGE_ID:  40922FK  10070  C++  */
    
/******************************************************************************
 Solution to Problem 10070 - Leap Year or Not Leap Year and ...
 by: Francisco Dibar
 date: May-29-2004
******************************************************************************/

#include <iostream>
#include <fstream>
#include <sstream>
//#define ONLINE_JUDGE 

#define ORDINARY	"This is an ordinary year."
#define LEAP		"This is leap year."
#define HULUCULU	"This is huluculu festival year."
#define BULUCULU	"This is buluculu festival year."

using namespace std;

////////////////////////////////////////////////////////////////////////////////
inline bool leap_year(int year)
{
	if (!(year % 4))
		if (!(year % 400))
			return true;
		else
			if (year % 100)
				return true;
	return false;			
}

////////////////////////////////////////////////////////////////////////////////
inline void year_type(int year, bool *leap, bool *hulu, bool *bulu)
{
	*leap = leap_year(year);
	*hulu = (year % 15 == 0);
	*bulu = (leap && (year % 55 == 0));
}

////////////////////////////////////////////////////////////////////////////////
//	PROGRAMA PRINCIPAL
////////////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{
	// redireccionar la entrada y salida
	#ifndef ONLINE_JUDGE 
		cin.rdbuf((new ifstream("input.txt"))->rdbuf()); 
		cout.rdbuf((new ofstream("output.txt"))->rdbuf()); 
	#endif 

	ostringstream os_output;
	int year;

	cin >> year;
	while (!cin.eof()) {
		bool leap, hulu, bulu;
		year_type(year, &leap, &hulu, &bulu);
		if (leap) os_output << LEAP << endl;
		if (hulu) os_output << HULUCULU << endl;
		if (bulu) os_output << BULUCULU << endl;
		if (!leap && !hulu && !bulu) os_output << ORDINARY << endl;
		cin >> year;
		if (!cin.eof()) os_output << endl;
	}
	cout << os_output.str();
	return 0;
}

