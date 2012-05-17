/* @JUDGE_ID:  40922FK  10010  C++  */
    
/**************************************************************************
 Solution to Problem 10010 - Where's Waldorf
 by: Francisco Dibar
 date: Feb-06-2005
**************************************************************************/
/* @BEGIN_OF_SOURCE_CODE */

//#define ONLINE_JUDGE 
#include <iostream>
#ifndef ONLINE_JUDGE 
	#include <fstream>
#endif 
#include <string>
#include <vector>

#define MAX_PALABRAS	20
#define FILA	0
#define COL		1

#define dH		0
#define dV		1
#define dD		2
#define dA		3

using namespace std;

struct coordenada {
	int fila, col;
};

///////////////////////////////////////////////////////////////////////////
string reverse(const string s)
{
	string srev(s);
	for (int i = 0; i < (int)s.length(); i++)
		srev[i] = s[s.length()-1-i];
	return srev;
}

///////////////////////////////////////////////////////////////////////////
coordenada encontrar_palabra(const string palabra, 
					const vector<string>& vec_crucigrama, 
					int sentido, int filas, int columnas)
{	
	coordenada coord;
	bool found = false;
	int f = 0, c = 0;
	// buscar la palabra
	// segun el sentido, la primera occurrencia puede ser la buscada o no
	switch(sentido) {
		int fact, cact;

		case dH:
			while ((f < (int)vec_crucigrama.size()) && !found) {
				c = vec_crucigrama[f].find(palabra);	// busco desde adelante
				if (c >= 0) // fracaso da -1
					found = true;
				else
					f++;
			}
			break;

		case dV:
			// debo seguir buscando hasta encontrar la de mas arriba
			c = (int)vec_crucigrama.size();
			for (int fi = 0; fi < (int)vec_crucigrama.size(); fi++) {
				int cact = vec_crucigrama[fi].find(palabra);
				if (cact >= 0) { // fracaso da -1
					// lo encontro, quedarme con el menor
					found = true;
					if (cact < c) {
							c = cact;
							f = fi;
					}
				}
			}
			break;

		case dD:
			// debo seguir buscando hasta encontrar la de mas arriba
			f = filas + 1; 
			c = columnas + 1;
			for (int d = 0; d < (int)vec_crucigrama.size(); d++) {
				int pos = vec_crucigrama[d].rfind(palabra);	// desde la der
				if (pos >= 0) { // fracaso da -1
					// lo encontro, quedarme con la buscada
					found = true;
					// convertir a coordenadas rect. para poder comparar
					if (d < filas) {
						fact = d - pos;
						cact = pos;
					} else {
						fact = filas - pos - 1;
						cact = d - fact;
					}
					if ((fact < f) || ((fact == f) && (cact < c))) {
						f = fact;
						c = cact;
					}
				}
			}
			break;

		case dA:
			// debo seguir buscando hasta encontrar la de mas arriba
			f = filas + 1; 
			c = columnas + 1;
			for (int d = 0; d < (int)vec_crucigrama.size(); d++) {
				int pos = vec_crucigrama[d].find(palabra);	// desde la izq
				if (pos >= 0) { // fracaso da -1
					// lo encontro, quedarme con la buscada
					found = true;
					// convertir a coordenadas rect. para poder comparar
					if (d < columnas) {
						fact = d - pos;
						cact = pos;
					} else {
						fact = columnas - pos - 1;
						cact = d - fact;
					}
					// ahora debo rotar estas coord en sentido horario
					int aux = fact;
					fact = cact;
					cact = columnas - aux - 1;

					if ((fact < f) || ((fact == f) && (cact < c))) {
						f = fact;
						c = cact;
					}
				}
			}
			break;
	}	
	// expresar el resultado con los indices comenzando en 1
	if (found) {
		if (sentido == dV) {
			// swapear las coordenadas
			coord.fila = c + 1;
			coord.col = f + 1;
		} else {
			coord.fila = f + 1;
			coord.col = c + 1;
		}
	} else {
		coord.fila = 0;
		coord.col = 0;
	}
	return coord;
}

///////////////////////////////////////////////////////////////////////////
coordenada mas_arriba_e_izq(coordenada coord1, coordenada coord2)
// devuelve aquella coordenada mas arriba y a la izquierda
{
	if ((!coord1.fila && !coord1.col) && (coord2.fila || !coord2.col))
		// coord1 es nula y coord2 valida
		return coord2;
	else if ((!coord2.fila && !coord2.col) && (coord1.fila || !coord1.col))
		// coord1 es valida y coord2 nula
		return coord1;
	else
		if (coord1.fila < coord2.fila)
			// coord1 mas arriba
			return coord1;
		else if (coord1.fila > coord2.fila)
			// coord2 mas arriba
			return coord2;
		else // coord1.fila == coord2.fila
			if (coord1.col < coord2.col)
				// coord1 mas a la izquierda
				return coord1;
			else
				// coord2 mas a la izquierda
				return coord2;
}

///////////////////////////////////////////////////////////////////////////
void armar_crucigramas(vector<string>& vec_crucigramaH,
						vector<string>& vec_crucigramaV, 
						vector<string>& vec_crucigramaD, 
						vector<string>& vec_crucigramaA, int filas, int columnas)
{
		// n: itera filas, m: itera cols
		// armar el crucigrama vertical
		for (int m = 0; m < columnas; m++) 
			for (int n = 0; n < filas; n++) 
				vec_crucigramaV[m] += vec_crucigramaH[n][m];

		// armar el crucigrama diagonal (/)
		for (int m = 0; m < columnas; m++) 
			for (int n = 0; n < filas; n++) 
				vec_crucigramaD[m+n] += vec_crucigramaH[n][m];

		// armar el crucigrama antidiagonal (\)
		// se arma de la misma forma que la diagonal
		// pero girando la matriz 90 grados antihorario
		// para eso genero primero la matriz rotada vec_crucigramaHRot
		vector<string> vec_crucigramaHRot(columnas);
		for (int n = 0; n < filas; n++) 
			for (int m = 0; m < columnas; m++) 
				vec_crucigramaHRot[columnas-m-1] += vec_crucigramaH[n][m];

		for (int m = 0; m < filas; m++) // intercambio filas por columnas
			for (int n = 0; n < columnas; n++) 
				vec_crucigramaA[m+n] += vec_crucigramaHRot[n][m];

}

///////////////////////////////////////////////////////////////////////////
void convertir_a_mayusculas(string& str)
{
	for (int i = 0; i < (int)str.length(); i++) 
		str[i] = toupper(str[i]);
}

///////////////////////////////////////////////////////////////////////////
coordenada coordenadas_palabra(string palabra, 
						vector<string>& vec_crucigramaH, 
						vector<string>& vec_crucigramaV,
						vector<string>& vec_crucigramaD, 
						vector<string>& vec_crucigramaA, int filas, int columnas)
{
	coordenada coord, coord1, coord2, coord_aux;

	convertir_a_mayusculas(palabra);
	string pal_invertida(reverse(palabra));
	bool capicua = (palabra == pal_invertida);
	
	// buscar horizontalmente
	// => , ||
	//		  \/					 
	coord1 = encontrar_palabra(palabra, vec_crucigramaH, dH, filas, columnas);
	if (!capicua) {
		coord2 = encontrar_palabra(pal_invertida, vec_crucigramaH, dH, filas, columnas);
		if ((coord2.fila > 0) && (coord2.col > 0))
			// modificar coord2 para que apunte al principio de la palabra
			coord2.col += pal_invertida.length() - 1;
		// quedarse con aquella mas arriba y a la izquierda
		coord = mas_arriba_e_izq(coord1, coord2);
	} else {
		coord.fila = coord1.fila;
		coord.col = coord1.col;
	}

	// buscar verticalmente
	// || , => 
	//	\/					 
	coord1 = encontrar_palabra(palabra, vec_crucigramaV, dV, filas, columnas);
	if (!capicua) {
		coord2 = encontrar_palabra(pal_invertida, vec_crucigramaV, dV, filas, columnas);
		if ((coord2.fila > 0) && (coord2.col > 0))
			// modificar coord2 para que apunte al principio de la palabra
			coord2.fila += pal_invertida.length() - 1;
		coord_aux = mas_arriba_e_izq(coord1, coord2);
	} else {
		coord_aux.fila = coord1.fila;
		coord_aux.col = coord1.col;
	}
	coord = mas_arriba_e_izq(coord, coord_aux);

	// buscar diagonalmente
	//  _		de izq a der
	//	 /|
	coord1 = encontrar_palabra(palabra, vec_crucigramaD, dD, filas, columnas);
	if (!capicua) {
		coord2 = encontrar_palabra(pal_invertida, vec_crucigramaD, dD, filas, columnas);
		// modificar coord2 para que apunte al principio de la palabra
		if ((coord2.fila > 0) && (coord2.col > 0)) {
			coord2.fila -= pal_invertida.length() - 1;
			coord2.col += pal_invertida.length() - 1;
		}
		coord_aux = mas_arriba_e_izq(coord1, coord2);
	} else {
		// devolver la coord del final de la palabra ya que es capicua
		coord_aux.fila = coord1.fila - pal_invertida.length() + 1;
		coord_aux.col = coord1.col + pal_invertida.length() - 1;;
	}
	coord = mas_arriba_e_izq(coord, coord_aux);
	
	// buscar antidiagonalmente
	// _\|		de der a izq
	coord1 = encontrar_palabra(palabra, vec_crucigramaA, dA, filas, columnas);
	if (!capicua) {
		coord2 = encontrar_palabra(pal_invertida, vec_crucigramaA, dA, filas, columnas);
		if ((coord2.fila > 0) && (coord2.col > 0)) {
			// modificar coord2 para que apunte al principio de la palabra
			coord2.fila += pal_invertida.length() - 1;
			coord2.col += pal_invertida.length() - 1;
		}
		coord_aux = mas_arriba_e_izq(coord1, coord2);
	} else {
		coord_aux.fila = coord1.fila;
		coord_aux.col = coord1.col;
	}
	coord = mas_arriba_e_izq(coord, coord_aux);
	
	return coord;
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

	int casos;
	cin >> casos;

	for (int k = 0; k < casos; k++) {
		int filas, columnas, cant_palabras;
		// leer las filas y columnas del crucigrama
		cin >> filas >> columnas;

		// cargar el crucigrama horizontal
		vector<string> vec_crucigramaH(filas);
		for (int n = 0; n < filas; n++) {
			cin >> vec_crucigramaH[n];
			convertir_a_mayusculas(vec_crucigramaH[n]);
		}
		
		// uso 3 crucigramas auxiliares: vertical, diagonal y antidiag
		vector<string> vec_crucigramaV(columnas);
		vector<string> vec_crucigramaD(filas + columnas);
		vector<string> vec_crucigramaA(filas + columnas);
		armar_crucigramas(vec_crucigramaH, vec_crucigramaV, 
								vec_crucigramaD, vec_crucigramaA, 
								filas, columnas);

		// leer la cantidad de palabras a buscar
		cin >> cant_palabras;
		
		// leer cada palabra y buscarla
		int vec_posiciones[MAX_PALABRAS][2];
		string palabra;
		for (int p = 0; p < cant_palabras; p++) {
			cin >> palabra;
			coordenada coord = coordenadas_palabra(palabra, 
									vec_crucigramaH, vec_crucigramaV,
									vec_crucigramaD, vec_crucigramaA, filas, columnas);
			
			// guardar el resultado en vec_posiciones
			vec_posiciones[p][FILA] = coord.fila;
			vec_posiciones[p][COL] = coord.col;
		}

		// mostrar la salida
		for (int s = 0; s < cant_palabras; s++)
			cout << vec_posiciones[s][FILA] << " " << vec_posiciones[s][COL] << endl;
	}
	return 0;
}

/* @END_OF_SOURCE_CODE */

