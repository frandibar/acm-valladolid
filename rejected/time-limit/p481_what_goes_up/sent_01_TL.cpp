
/* @JUDGE_ID:  40922FK  481  C++  */
    
/******************************************************************************
 Solution to Problem 481 - What Goes Up
 by: Francisco Dibar
 date: May-05-2004
******************************************************************************/

#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>		// sort, binary_search 

#define SEPARADOR '-'

using namespace std;

typedef set<int, less<int> > SET_int;

////////////////////////////////////////////////////////////////////////////////
int hallar_sm(SET_int& set_alturas, map<int,int>& map_sm, int altura)
{
	// recorrer set_alturas en orden descendente, obtener la sm maxima de aquellas set_alturas[k] > altura;
	// obtener k tal que set_altura[k] > altura
	typedef SET_int::reverse_iterator SET_int_rit;
	SET_int_rit ri = set_alturas.rbegin();
	int sec_max = 0;
	while ((ri != set_alturas.rend()) && (*ri > altura)) {
		if (map_sm[*ri] > sec_max)
			sec_max = map_sm[*ri];
		ri++;
	}
	// agregar la altura en set_alturas (si ya existe se ignora, y se mantienen ordenadas de menor a mayor)
	set_alturas.insert(altura);
	return sec_max;
}

////////////////////////////////////////////////////////////////////////////////
//	PROGRAMA PRINCIPAL
////////////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{
	vector<int> vec_input;
	int i;
	cin >> i;
	// leer la entrada
	while (!cin.eof()) {
		vec_input.push_back(i);
		cin >> i;
	}

	// buscar la secuencia maxima (sm)
	// recorro de atras para adelante
	map<int, int> map_sm;		// guarda la secuencia maxima de la altura
										// clave: altura, valor: sm
	set<int, less<int> > set_alturas;		// guarda las alturas presentes, de manera ordenada y sin repeticiones. sirve para buscar la sm para cada altura en map_sm

	// verificar si la secuencia es nula
	if (vec_input.size() == 0) {
		cout << "0" << endl << SEPARADOR << endl;
		return 0;
	}
	int secuencia_max = 0;
	int ultima_h = vec_input[vec_input.size()-1];
	map_sm[ultima_h] = 1;		// el ultimo tiene sm = 1
	set_alturas.insert(ultima_h);
	for (int j = vec_input.size()-2; j >= 0; j--) {
		// buscar la sm del vec_input[k] con altura(k) > altura(j) y k > j
		// para todas las alturas mayores a la actual, busco la mayor sm		
		int altura = vec_input[j];
		int sm = hallar_sm(set_alturas, map_sm, altura);
		// actualizo la sm para esa altura, y guardo la secuencia maxima
		if (map_sm[altura] < sm + 1) {
			map_sm[altura] = sm + 1;
		if (map_sm[altura] > secuencia_max)
			secuencia_max = map_sm[altura];
		}
	}

	// obtener los indices de los elementos que conforman la sm

	// mostrar la suma maxima y los elementos
	cout << secuencia_max << endl;
	cout << SEPARADOR << endl;

	vector<int> vec_indices_sm;
	// recorrer vec_input, y buscar la sm de ese elemento en map_sm, y agregar k a vec_indices_sm si coincide con el orden buscado
	int orden = secuencia_max;
	int prox = (*set_alturas.begin())-1;	// defino prox como la menor altura presente
	for (int k = 0; k < (int)vec_input.size(); k++)
		if ((map_sm[vec_input[k]] == orden) && (vec_input[k] > prox)) {
			vec_indices_sm.push_back(k);
			prox = vec_input[k];
			orden--;
			cout << vec_input[k] << endl;
		}

	return 0;
}

