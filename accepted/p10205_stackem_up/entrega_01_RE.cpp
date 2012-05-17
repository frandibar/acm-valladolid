/* @JUDGE_ID:  40922FK  10205  C++  */
/* @BEGIN_OF_SOURCE_CODE */    
/**************************************************************************
 Solution to Problem 10205 - Stack'em up
 by: Francisco Dibar
 date: Feb-18-2005
**************************************************************************/

//#define ONLINE_JUDGE 
#include <iostream>
#ifndef ONLINE_JUDGE 
	#include <fstream>
#endif 

#include <string>
#include <vector>

using namespace std;

///////////////////////////////////////////////////////////////////////////
class carta {
public:
	int valor,
		palo;
	// constructor
	carta(int valor = 0, int palo = 0) {};
};

///////////////////////////////////////////////////////////////////////////
class mazo_cartas {
private:
	string vec_nom_palos[4];
	string vec_nom_valores[13];
	int vec_orden[52];

public:
	carta mazo[52];

	mazo_cartas();
	void cargar_nombres();
	void cargar_cartas();
	void ordenar();
	void mezclar(const vector<int>&);
	string nombre_carta(const carta&); 
	string nombre_carta(int); 
};

///////////////////////////////////////////////////////////////////////////
void mazo_cartas::mezclar(const vector<int>& vec_mezcla)
{
	int vec_aux[52];
	// inicializar aux
	for (int j = 0; j < 52; j++) 
		vec_aux[j] = vec_orden[j];

	for (int i = 0; i < 52; i++)
		// -1 porque indice empieza en 1
		vec_orden[i] = vec_aux[vec_mezcla[i]-1];	
}

///////////////////////////////////////////////////////////////////////////
void mazo_cartas::ordenar()
{
	for (int i = 0; i < 52; i++)
		vec_orden[i] = i;
}

///////////////////////////////////////////////////////////////////////////
void mazo_cartas::cargar_cartas()
{
	for (int p = 0; p < 4; p++) {
		for (int v = 0; v < 13; v++) {
			int orden = 13*p + v;
			mazo[orden].palo = p;
			mazo[orden].valor = v;
		}
	}
}

///////////////////////////////////////////////////////////////////////////
mazo_cartas::mazo_cartas()		// constructor
{
	cargar_nombres();
	cargar_cartas();
	ordenar();
}

///////////////////////////////////////////////////////////////////////////
inline string mazo_cartas::nombre_carta(const carta& c)
{
	return (vec_nom_valores[c.valor] + " of " + vec_nom_palos[c.palo]);
}

///////////////////////////////////////////////////////////////////////////
inline string mazo_cartas::nombre_carta(int pos)
// devuelve la carta en la posicion pos
{
	int ord = vec_orden[pos];
	return (vec_nom_valores[mazo[ord].valor] + " of " + vec_nom_palos[mazo[ord].palo]);
}

///////////////////////////////////////////////////////////////////////////
void mazo_cartas::cargar_nombres()
{
	// nombres de palos
	vec_nom_palos[0] = "Clubs";
	vec_nom_palos[1] = "Diamonds";
	vec_nom_palos[2] = "Hearts";
	vec_nom_palos[3] = "Spades";

	// nombres de valores
	vec_nom_valores[0] = "2";
	vec_nom_valores[1] = "3";
	vec_nom_valores[2] = "4";
	vec_nom_valores[3] = "5";
	vec_nom_valores[4] = "6";
	vec_nom_valores[5] = "7";
	vec_nom_valores[6] = "8";
	vec_nom_valores[7] = "9";
	vec_nom_valores[8] = "10";
	vec_nom_valores[9] = "Jack";
	vec_nom_valores[10] = "Queen";
	vec_nom_valores[11] = "King";
	vec_nom_valores[12] = "Ace";
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
	for (int k = 0; (k < casos) && (!cin.eof()); k++) {
		int mezclas;
		cin >> mezclas;
		// leer las mezclas conocidas
		vector< vector<int> > mat_shuffles(mezclas);
		for (int i = 0; i < mezclas; i++) {
			mat_shuffles[i].resize(52);
			for (int j = 0; (j < 52) && (!cin.eof()); j++)
				cin >> mat_shuffles[i][j];
		}

		mazo_cartas mazo;

		// leer las mezclas efectuadas y ejecutarlas
		int mezcla;
		cin >> mezcla;
		while (!cin.eof()) {
			mazo.mezclar(mat_shuffles[mezcla-1]);
			cin >> mezcla;
		}
		// mostrar el mazo
		for (int c = 0; c < 52; c++) 
			cout << mazo.nombre_carta(c) << endl;
	}

	return 0;
}

/* @END_OF_SOURCE_CODE */

