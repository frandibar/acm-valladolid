/* @JUDGE_ID:  40922FK  10037  C++  */
/* @BEGIN_OF_SOURCE_CODE */    
/**************************************************************************
 Solution to Problem 10037 - Bridge
 by: Francisco Dibar
 date: Jul-30-2006
**************************************************************************/

//#define DEBUG
//#define ONLINE_JUDGE 
#include <iostream>
#ifndef ONLINE_JUDGE 
    #include <fstream>
#endif 
#include <vector>
#include <algorithm>        // sort

#ifdef DEBUG
    #define START_DEBUG "START DEBUG ********************************************************************\n"
    #define END_DEBUG   "END DEBUG **********************************************************************\n"
#endif

using std::cin;
using std::cout;
using std::vector;

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

    for (int k = 0; k < ncases; k++) {

        // READ INPUT
        int npeople;
        cin >> npeople;
        vector<int> vTimes(npeople);
        for (int i = 0; i < npeople; i++)
            cin >> vTimes[i];

        // PROCESS
        std::sort(vTimes.begin(), vTimes.end());    // ascending order
        // calculate time
        int totTime = 0;
        if (npeople == 1)
            totTime = vTimes[0];
        else if (npeople == 2)
            totTime = vTimes[0] + vTimes[1];
        else if (npeople > 2) {
            int ntrips = 2 * npeople - 3;
            int m, n;
            if (npeople % 2 == 0) {     // even
                m = ntrips / 4;
                n = 2 * m + 1;
            } else {
                m = ntrips / 4 + 1;
                n = 2 * m - 1;
            }
            totTime = m * vTimes[0] + n * vTimes[1];
            for (int i = npeople-1; i > 1; i -= 2)
                totTime += vTimes[i];
        }

        // SHOW OUTPUT
        cout << totTime << endl;
        // show trips
        if (npeople == 0)
            cout << endl;
        else if (npeople == 1)
            cout << vTimes[0] << endl;
        else {
            int i;
            for (i = npeople-1; i > 2; i -= 2) {
                cout << vTimes[0] << " " << vTimes[1] << endl;
                cout << vTimes[0] << endl;
                cout << vTimes[i-1] << " " << vTimes[i] << endl;
                cout << vTimes[1] << endl;
            }
            cout << vTimes[0] << " " << vTimes[1] << endl;
            if (npeople % 2 != 0) { // odd
                cout << vTimes[0] << endl;
                cout << vTimes[0] << " " << vTimes[i] << endl;
            }
        }

        if (k < ncases-1)
            cout << endl;
    }
        
#ifdef DEBUG
    cout << START_DEBUG;

    cout << END_DEBUG;
#endif

    return 0;
}

/* @END_OF_SOURCE_CODE */


/* 

    Metodo de resolucion:

    El esquema siempre es el siguiente
 
    viajes = 2.n - 3 con n la cantidad de personas y n > 2
           = (n-1) + (n-2) verificar con un ejemplo, donde siempre vuelve el mismo
    tiempo = M.a + N.b + tiempo[n-2.k] + .. + tiempo[n-2] + tiempo[n]
             con tiempo[0] <= ... <= tiempo[n]
 
    si viajes es par
        M = viajes \ 4      (\ division entera)
        N = 2.M + 1
    sino
        M = viajes \ 4  + 1 (\ division entera)
        N = 2.(viajes \ 4) + 1 = 2.M - 1
 
    sea a <= b <= c <= d <= e
    tiempo = 2a + 3b + c + e

    ejemplo:
    -> a b  (menores)
    <- a    (siempre se alterna a con b para volver)
    -> d e  (mayores)
    <- b
    ------- (se repite el patron anterior con los del medio)
    -> a b  (pares terminan aca)
    <- a
    -> a c  (impares terminan aca)

*/

