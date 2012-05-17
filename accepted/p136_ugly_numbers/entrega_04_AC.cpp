/* @JUDGE_ID:  40922FK  136  C++  */
/* @BEGIN_OF_SOURCE_CODE */    
/******************************************************************************
 Solution to Problem 136 - Ugly Numbers
 by: Francisco Dibar
 date: Dec-17-2005
******************************************************************************/

//#define DEBUG
//#define ONLINE_JUDGE 
#include <iostream>
#ifndef ONLINE_JUDGE 
	#include <fstream>
#endif 
#include <cmath>		// pow, ceil

#define START_DEBUG	"START DEBUG ********************************************************************\n"
#define END_DEBUG	"END DEBUG **********************************************************************\n"

using std::cin;
using std::cout;
using std::endl;


#define ORDER	1500

////////////////////////////////////////////////////////////////////////////////
double next_ugly(double ugly)
// returns next ugly number greater than ugly
// ugly = 2^x.3^y.5^z

// note: using double to avoid converting to long for this problem
{
	int	xmax = 0, 
			ymax = 0, 
			zmax = 0;
	double next;

	// find xmax = min x / 2^x > ugly
	xmax = (int)ceil(log10(ugly) / log10(2)) + 1;

	// find ymax = min y / 3^y > ugly
	ymax = (int)ceil(log10(ugly) / log10(3)) + 1;
	
	// find zmax = min z / 5^z > ugly
	zmax = (int)ceil(log10(ugly) / log10(5)) + 1;
    
    // next = min(xmax, ymax, zmax)
	double pow2 = pow(2, xmax);
	double pow3 = pow(3, ymax);
	double pow5 = pow(5, zmax);
    
	if (pow2 < pow3) 
        ((pow2 < pow5) ? next = pow2 : next = pow5);
    else 
        ((pow3 < pow5) ? next = pow3 : next = pow5);

    for (int x = 0; x < xmax; x++) {
        pow2 = pow(2,x); 
		if (pow2 < next) {
			for (int y = 0; y < ymax; y++) {
                double pow23 = pow2 * pow(3,y);
				if (pow23 < next) {
					for (int z = 0; z < zmax; z++) {
                        double pow235 = pow23 * pow(5,z);
						if ((pow235 > ugly) && (pow235 < next))
                            next = pow235;
					}
				}
			}
		}
	}
	return next;
}

////////////////////////////////////////////////////////////////////////////////
//	MAIN PROGRAM
////////////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{
	// redirect input and output
	#ifndef ONLINE_JUDGE 
		cin.rdbuf((new std::ifstream("input.txt"))->rdbuf()); 
		cout.rdbuf((new std::ofstream("output.txt"))->rdbuf()); 
	#endif 

	// PROCESS, no input
	int u = 1;	// counts found ugly nums (1 is ugly by convention)
	double ugly = 1;

	while (u < ORDER) {
#ifdef DEBUG
		cout << u << "\t" << (long)ugly << endl;
#endif
		ugly = next_ugly(ugly);
		u++;
	}

	// SHOW OUTPUT
	cout << "The " << ORDER << "'th ugly number is " << (long)ugly << "." << endl;

	return 0;
}

/* @END_OF_SOURCE_CODE */