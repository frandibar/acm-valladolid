
/* @JUDGE_ID:  40922FK  460  C++  */
    
/******************************************************************************
 Solution to Problem 460 - Overlapping Rectangles
 by: Francisco Dibar
 date: Jun-03-2004
******************************************************************************/

#include <iostream>
#include <sstream>
#include <fstream>
//#define ONLINE_JUDGE 

#define X1_LL  0
#define X1_UR  2
#define X2_LL  1
#define X2_UR  3

#define Y1_LL  0
#define Y1_UR  2
#define Y2_LL  1
#define Y2_UR  3

#define NO_OVERLAP  "No Overlap"

using namespace std;

////////////////////////////////////////////////////////////////////////////////
inline void swap(int* x, int* y)
{
	int aux;
	aux = *y;
	*y = *x;
	*x = aux;
}

////////////////////////////////////////////////////////////////////////////////
inline void sort4(int *vec, int *vec_ind)
// ordenar el vector de 4 elementos vec ascendentemente, 
// y aplica el mismo ordenamiento a vec_ind
{
	// sea el vector {a, b, c, d}
	// orden de comparaciones y swaps: a-b, c-d, b-c, a-b, c-d, b-c
	if (vec[0] > vec[1]) {
		swap(vec, vec+1);
		swap(vec_ind, vec_ind+1);
	}
	if (vec[2] > vec[3]) {
		swap(vec+2, vec+3);
		swap(vec_ind+2, vec_ind+3);
	}
	if (vec[1] > vec[2]) {
		swap(vec+1, vec+2);
		swap(vec_ind+1, vec_ind+2);
	}
	if (vec[0] > vec[1]) {
		swap(vec, vec+1);
		swap(vec_ind, vec_ind+1);
	}
	if (vec[2] > vec[3]) {
		swap(vec+2, vec+3);
		swap(vec_ind+2, vec_ind+3);
	}
	if (vec[1] > vec[2]) {
		swap(vec+1, vec+2);
		swap(vec_ind+1, vec_ind+2);
	}
}

////////////////////////////////////////////////////////////////////////////////
struct box {
	int xll, yll, 
    	xur, yur;
};
                
////////////////////////////////////////////////////////////////////////////////
bool overlap(const box& b1, const box& b2, box& bint)
{
	int vec_coords[4];

	int vec_labels[] = { X1_LL, X1_UR, X2_LL, X2_UR };

	vec_coords[0] = b1.xll;
	vec_coords[1] = b1.xur;
	vec_coords[2] = b2.xll;
	vec_coords[3] = b2.xur;

	// ordenar el vector ascendentemente
	sort4(vec_coords, vec_labels);

	// la interseccion esta dada por los elementos centrales de vec_coordenadas, salvo que las etiquetas
	// no se alternen entre uno y otro rectangulo. ej. X1_LL, X1_UR, X2_LL, X2_UR -> no hay interseccion
	// me doy cuenta si estan alternados si la suma de los elementos del
 	// medio de vec_labels es par
	if ((vec_labels[0] + vec_labels[1]) % 2 == 0)
		return false;
	else {
		// copiar las coordenadas de x en bint y analizar el eje y
		bint.xll = vec_coords[1];
		bint.xur = vec_coords[2];
  		
		vec_coords[0] = b1.yll;
		vec_coords[1] = b1.yur;
		vec_coords[2] = b2.yll;
      vec_coords[3] = b2.yur;

		vec_labels[0] = Y1_LL;
		vec_labels[1] = Y1_UR;
		vec_labels[2] = Y2_LL;
      vec_labels[3] = Y2_UR;

		sort4(vec_coords, vec_labels);

		if ((vec_labels[0] + vec_labels[1]) % 2 == 0)
			return false;
		else {
			bint.yll = vec_coords[1];
			bint.yur = vec_coords[2];
			return true;
		}
	}
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
	int bloques;
	cin >> bloques;
    
   for (int i = 0; (i < bloques) && (!cin.eof()); i++) {
		box b1, b2, bint;
		cin >> b1.xll >> b1.yll >> b1.xur >> b1.yur;
		cin >> b2.xll >> b2.yll >> b2.xur >> b2.yur;
		if (overlap(b1, b2, bint))        
		os_output << bint.xll << " " << bint.yll << " " << bint.xur << " " << bint.yur << endl;
		else 
       	os_output << NO_OVERLAP << endl;
		if (i < bloques-1) os_output << endl;
   }       
   cout << os_output.str();
	return 0;
}

