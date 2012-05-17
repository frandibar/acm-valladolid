/* @JUDGE_ID:  40922FK  10142  C++  */
    
/**************************************************************************
 Solution to Problem 10142 - Australian Voting
 by: Francisco Dibar
 date: Jul-09-2005
**************************************************************************/
/* @BEGIN_OF_SOURCE_CODE */

#include <iostream>
#include <fstream>
#include <sstream>	// istringstream
#include <string>
#include <vector>

#define MAX_VOTANTES		1000
#define MAX_CANDIDATOS	25
#define VOTOS				0
#define RONDA				1

//#define ONLINE_JUDGE 

using namespace std;

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
	string nombre;
	getline(cin, nombre);	// terminar de leer la linea de casos
	getline(cin, nombre);	// saltear linea en blanco

	// analizar cada caso
	for (int k = 0; k < casos; k++) {
		// CARGAR DATOS
		int candidatos;
		int votantes = 0;

		cin >> candidatos;
		getline(cin, nombre);	// terminar de leer la linea de casos

		vector<string> vec_candidatos(candidatos+1);	
		// empiezo indice en 1!
		// cargar vec_candidatos con los nombres de los mismos
		for (int i = 1; i <= candidatos; i++) {
			getline(cin, vec_candidatos[i]);
		}

		// cargar mat_votos con los votos
		int mat_votos[MAX_VOTANTES][MAX_CANDIDATOS];
		string line;
		getline(cin, line);
		while (!line.empty() && !cin.eof()) {
			istringstream is_input(line);
			for (int m = 0; m < candidatos; m++) {
				is_input >> mat_votos[votantes][m];
			}
			votantes++;
			getline(cin, line);
		}
		
		// PROCESAR
		int mat_votos_acum[MAX_CANDIDATOS][2];	
		// el 2do indice guarda la ronda en que es eliminado
		int lim_votos_ganador;
		// si hay votos pares, se gana con v/2 + 1, sino con (v+1)/2
		if (votantes % 2 == 0)
			lim_votos_ganador = votantes / 2 + 1;
		else
			lim_votos_ganador = (votantes + 1) / 2;

		// inicializar mat_votos_acum
		for (int i = 1; i <= candidatos; i++) {
			mat_votos_acum[i][VOTOS] = 0;
			mat_votos_acum[i][RONDA] = 0;
		}			

		// cargar mat_votos_acum con el primer voto
		int max_votos = 0;
		for (int i = 0; i < votantes; i++) {
			int candidato = mat_votos[i][0];
			mat_votos_acum[candidato][VOTOS]++;
			// calcular el voto maximo
			if (mat_votos_acum[candidato][VOTOS] > max_votos)
				max_votos = mat_votos_acum[candidato][VOTOS];
		}

		bool hay_ganador = (max_votos >= lim_votos_ganador);
		int ronda = 0;
		while (!hay_ganador && (ronda < candidatos)) {
			ronda++;
			// calcular la menor cantidad de votos
			int min_votos = votantes;	// inicializo en el valor maximo
			for (int i = 1; i <= candidatos; i++) {
				// si la cantidad de votos a este candidato es menor a 
				// min_votos y no es un candidato eliminado
				if ((mat_votos_acum[i][VOTOS] < min_votos) && (mat_votos_acum[i][RONDA] == 0))
					min_votos = mat_votos_acum[i][VOTOS];
			}
			// marcar los candidatos con menor cantidad de votos como 
			// eliminados en esta ronda
			for (int i = 1; i <= candidatos; i++) {
				// si la cantidad de votos a este candidato es igual a 
				// min_votos y no es un candidato eliminado
				if ((mat_votos_acum[i][VOTOS] == min_votos) && (mat_votos_acum[i][RONDA] == 0))
					mat_votos_acum[i][RONDA] = ronda;
			}
			// para estos candidatos, recontar sus votos en favor de los 
			// demas candidatos			
			for (int i = 1; i <= candidatos; i++) {
				if (mat_votos_acum[i][RONDA] == ronda)
					// es un candidato eliminado
					// buscar el voto al candidato no eliminado entre los 
					// votos que tenian como primer candidato a este
					for (int j = 0; j < votantes; j++)
						if (mat_votos[j][0] == i) {
							bool seguir = true;
							for (int n = 1; (n < candidatos) && seguir; n++)	// busco desde el 2do
								// si el voto es a un candidato no eliminado 
								// o eliminado en esta ronda
								if ((mat_votos_acum[ mat_votos[j][n] ][RONDA] == 0) || (mat_votos_acum[ mat_votos[j][n] ][RONDA] == ronda)) {
									mat_votos_acum[ mat_votos[j][n] ][VOTOS]++;
									if (mat_votos_acum[ mat_votos[j][n] ][VOTOS] >= lim_votos_ganador)
										hay_ganador = true;
										seguir = false;
									if (mat_votos_acum[ mat_votos[j][n] ][VOTOS] > max_votos)
										max_votos = mat_votos_acum[ mat_votos[j][n] ][VOTOS];
								}
						}
			}
		}

		// recorrer mat_votos_acum y mostrar los candidatos con max_votos
		for (int c = 1; c <= candidatos; c++) 
			if ((mat_votos_acum[c][VOTOS] == max_votos))
				cout << vec_candidatos[c] << endl;

		// agregar una linea en blanco para separar los casos
		if (k < casos-1) cout << endl;
	}
	return 0;
}

/* @END_OF_SOURCE_CODE */

