
/* @JUDGE_ID:  40922FK  136  C++  */
    
/******************************************************************************
 Solution to Problem 136 - Ugly Numbers
 by: Francisco Dibar
 date: Jan-31-2004
******************************************************************************/

#include <iostream>
#include <math.h>
using namespace std;

#define ORDEN_BUSCADO	1500

////////////////////////////////////////////////////////////////////////////////
double next_ugly(double ugly)
{
	int xmax = 0, ymax = 0, zmax = 0;
    double prox_ugly;

	// buscar xmax = min x / 2^x > ugly
	xmax = (int)ceil(log10(ugly)/log10(2)) + 1;

	// buscar ymax = min y / 3^y > ugly
	ymax = (int)ceil(log10(ugly)/log10(3)) + 1;
	
	// buscar zmax = min z / 5^z > ugly
	zmax = (int)ceil(log10(ugly)/log10(5)) + 1;
    
    // prox_ugly = min(xmax, ymax, zmax)
	double pow2 = pow(2,xmax);
	double pow3 = pow(3,ymax);
	double pow5 = pow(5,zmax);
    
	if (pow2 < pow3) 
        ((pow2 < pow5) ? prox_ugly = pow2 : prox_ugly = pow5);
    else 
        ((pow3 < pow5) ? prox_ugly = pow3 : prox_ugly = pow5);

    for (int x = 0; x < xmax; x++) {
        pow2 = pow(2,x); 
		if (pow2 < prox_ugly) {
			for (int y = 0; y < ymax; y++) {
                double pow23 = pow2 * pow(3,y);
				if (pow23 < prox_ugly) {
					for (int z = 0; z < zmax; z++) {
                        double pow235 = pow23 * pow(5,z);
						if ((pow235 > ugly) && (pow235 < prox_ugly))
                            prox_ugly = pow235;
					}
				}
			}
		}
	}

    return prox_ugly;

}

////////////////////////////////////////////////////////////////////////////////
//	PROGRAMA PRINCIPAL
////////////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{
	int u = 1;	// cuenta los ugly encontrados (el 1 es ugly por convencion)
	double prox_ugly = 1;

	while (u < ORDEN_BUSCADO) {
		prox_ugly = next_ugly(prox_ugly);
		u++;
	}
	cout << "The " << ORDEN_BUSCADO << "'th ugly number is " << (long)prox_ugly << endl;
	return 0;
}

