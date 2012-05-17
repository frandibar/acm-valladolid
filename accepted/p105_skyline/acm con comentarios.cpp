
/* @JUDGE_ID:  40922FK  105  C++  */
    
/******************************************************************************
 Solution to Problem 105 - The Skyline problem
 by: Francisco Dibar
 date: Mar-24-2004
******************************************************************************/

#include <iostream>
#include <list>
#include <algorithm>

// The base types 
#ifdef WIN32 
  typedef __int8            int8; 
  typedef __int16           int16; 
  typedef __int32           int32; 
  typedef __int64           int64; 
  typedef unsigned __int8   uint8; 
  typedef unsigned __int16  uint16; 
  typedef unsigned __int32  uint32; 
  typedef unsigned __int64  uint64; 
#else 
  typedef char                    int8; 
  typedef short                   int16; 
  typedef long                    int32; 
  typedef long long int           int64; 
  typedef unsigned char           uint8; 
  typedef unsigned short          uint16; 
  typedef unsigned long           uint32; 
  typedef unsigned long long int  uint64; 
#endif 


#define MAX_COORDENADA		10000
#define MAX_EDIFICIOS		5000

using namespace std;

struct edificio {
	int desde;
	int altura;
	int hasta;
};

////////////////////////////////////////////////////////////////////////////////
void mostrar_perfil(edificio ed)
{
	cout << ed.desde << "," << ed.altura << ",";
}

////////////////////////////////////////////////////////////////////////////////
void mostrar_edificio(edificio ed)
{
	cout << ed.desde << "\t" << ed.altura << "\t" << ed.hasta << endl;
}

////////////////////////////////////////////////////////////////////////////////
//	PROGRAMA PRINCIPAL
////////////////////////////////////////////////////////////////////////////////
int main(int argc, char *argv[])
{
	list<edificio> lst_edif;
	list<edificio> lst_aux;
	edificio ed;

	// leer los edificios de entrada y agregarlos a la lista lst_edif
	while (!cin.eof()) {
		cin >> ed.desde >> ed.altura >> ed.hasta;
		lst_edif.push_back(ed);
	}

	lst_edif.pop_back();	// descartar el ultimo edificio ingresado (que no es un edificio)
	
	ed = lst_edif.front();
	lst_edif.pop_front();
	lst_aux.push_back(ed);	// volcar el primer edificio

	while (!lst_edif.empty()) {
		edificio ed2 = lst_edif.front();	
		lst_edif.pop_front();
		// buscar la posicion en que debe ubicarse el edificio en lst_aux, comenzando por atras
		// i apunta al edificio con quien tengo que comparar el edificio nuevo.
		typedef list<edificio>::iterator LI;
		LI i = lst_aux.end(); 
		i--;		// comenzar desde el ultimo
		edificio& ed1 = *i;
		// mover los edificios de lst_aux desde i hasta el final, al comienzo de lst_edificios para reprocesar
		int reprocesar = 0;
		while ((ed2.desde < ed1.desde) && (i != lst_aux.begin())) {
			reprocesar++;
			lst_edif.push_front(*i);
			i--;
			ed1 = *i;
		}
		while (reprocesar > 0) {
			lst_aux.pop_back();
			reprocesar--;
		}
		ed1 = *i;

		// comparar ed2 con ed1, y determinar a que caso corresponde
		if (ed2.desde < ed1.hasta) {
			if (ed2.hasta > ed1.hasta) {
				if (ed2.desde == ed1.desde) {
					if (ed2.altura > ed1.altura) {
						// caso 1 
						// Reemplazo a1 por a2 en el intervalo de interseccion, creo un nuevo ed0' con d0' = h1 y repito el proceso.
cout << "caso 1" << endl;
mostrar_edificio(ed1);mostrar_edificio(ed2);
						ed1.altura = ed2.altura;
						ed2.desde = ed1.hasta;
						lst_edif.push_front(ed2);
					} else {
						// caso 2
						//Creo un nuevo E2' con la parte sobrante y repito el proceso.
cout << "caso 2" << endl;
mostrar_edificio(ed1);mostrar_edificio(ed2);
						ed2.desde = ed1.hasta;						
						lst_edif.push_front(ed2);	// hasta aca
					}
				} else {
					if (ed2.altura > ed1.altura) {
						// caso 3 
						// Reemplazo E1 por E1' hasta la interseccion. Repito el proceso (Caso 1)
cout << "caso 3" << endl;
mostrar_edificio(ed1);mostrar_edificio(ed2);
						edificio ed0;
						ed0.desde = ed2.desde;
						ed0.altura = ed2.altura;
						ed0.hasta = ed1.hasta;
						ed1.hasta = ed2.desde;
						ed2.desde = ed0.hasta;
						lst_edif.push_front(ed2);
						i++;
						lst_aux.insert(i,ed0);
					} else {
						// caso 4
						// Creo un nuevo E2' con la parte sobrante y repito el proceso.
cout << "caso 4" << endl;
mostrar_edificio(ed1);mostrar_edificio(ed2);
						ed2.desde = ed1.hasta;						
						lst_edif.push_front(ed2);	// hasta aca
					}
				}
			} else {
				if (ed2.desde == ed1.desde) {
					if (ed2.altura > ed1.altura) {
						if (ed2.hasta < ed1.hasta) {
							// caso 5 
							// Reemplazo E1 por E2, y agrego E1' desde la interseccion.
cout << "caso 5" << endl;
mostrar_edificio(ed1);mostrar_edificio(ed2);
							edificio ed0;
							ed0.desde = ed2.hasta;		
							ed0.altura = ed1.altura;
							ed0.hasta = ed1.hasta;
							i++;
							lst_aux.insert(i,ed0);
							ed1.altura = ed2.altura;
							ed1.hasta = ed2.hasta;
						} else {
							// caso 5B 
							// Reemplazo E1 por E2
cout << "caso 5B" << endl;
mostrar_edificio(ed1);mostrar_edificio(ed2);
							ed1.altura = ed2.altura;
						}
					} else {
						// caso 6
						// Descarto ed2
cout << "caso 6" << endl;
mostrar_edificio(ed1);mostrar_edificio(ed2);
					}
				} else {
					if (ed2.altura > ed1.altura) {
						// caso 7 
						// Divido E1 en E1' y E1'', y reemplazo E1 por E1', E2 y E1''
						if (ed2.hasta < ed1.hasta) {
cout << "caso 7" << endl;
mostrar_edificio(ed1);mostrar_edificio(ed2);
							edificio ed0;
							ed0.desde = ed2.hasta;		
							ed0.altura = ed1.altura;
							ed0.hasta = ed1.hasta;
							
							ed1.hasta = ed2.desde;
							i++;
							lst_aux.insert(i,ed2);
							lst_aux.insert(i,ed0);
						} else {
						// caso 7B 
						// Reemplazo E1 por E1' hasta la interseccion, y luego proceso nuevamente E2
cout << "caso 7B" << endl;
mostrar_edificio(ed1);mostrar_edificio(ed2);
							ed1.hasta = ed2.desde;
							i++;
							lst_aux.insert(i,ed2);
						}
					} else {
						// caso 8
						// Descarto E2
cout << "caso 8" << endl;
mostrar_edificio(ed1);mostrar_edificio(ed2);
					}
				}
			}

		} else {
			if (ed2.desde > ed1.hasta) {
				// caso 9
				// dejo ed1, creo un nuevo edificio con h = 0 entre ed1 y ed2, y luego coloco ed2
cout << "caso 9" << endl;
mostrar_edificio(ed1);mostrar_edificio(ed2);
				edificio ed0;
				ed0.desde = ed1.hasta;
				ed0.altura = 0;
				ed0.hasta = ed2.desde;
				i++;
				lst_aux.insert(i,ed0);
				lst_aux.insert(i,ed2);
			} else {
				if (ed2.altura != ed1.altura) {
					// caso 10
					// Dejo E1 y coloco a continuacion E2
cout << "caso 10" << endl;
mostrar_edificio(ed1);mostrar_edificio(ed2);
					i++;
					lst_aux.insert(i,ed2);
				} else {
					// caso 11	
					// Reemplazo h1 por h2, y descarto E2
cout << "caso 11" << endl;
mostrar_edificio(ed1);mostrar_edificio(ed2);
					ed1.hasta = ed2.hasta;
				}
			}
		}
	}

cout << endl;
	for_each(lst_aux.begin(), lst_aux.end(), mostrar_edificio);

	// mostrar el perfil
	cout << endl << "(";
	for_each(lst_aux.begin(), lst_aux.end(), mostrar_perfil);
	cout << lst_aux.back().hasta << ",0)" << endl;

	return 0;
}

