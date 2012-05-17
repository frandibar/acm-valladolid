
/* @JUDGE_ID:  40922FK  221  C++  */
    
/******************************************************************************
 Solution to Problem 221 - Urban Elevations
 by: Francisco Dibar
 date: Mar-30-2004
******************************************************************************/

#include <iostream>
#include <list>
#include <queue>
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

using namespace std;

struct edificio {
	int nro;
	int sw_x;
	int sw_y;
	int width;
	int depth;
	int height;
};

struct edificio2d {
	int nro;
	int desde;
	int hasta;
	int altura;
};

struct mapa {
	int nro;
	int cant_edificios;
	list<edificio> lst_edificios;
	list<int> lst_perfiles;
};


////////////////////////////////////////////////////////////////////////////////
void mostrar_edificio(edificio ed)
{
	cout << ed.nro << ": " << ed.sw_x << " " << ed.sw_y << " " << ed.width << " " << ed.depth << " " << ed.height << endl;
}

////////////////////////////////////////////////////////////////////////////////
void mostrar(int y)
{
	cout << y << " ";
}

////////////////////////////////////////////////////////////////////////////////
void mostrar_mapa(mapa map)
{
	cout << map.nro << ": " << map.cant_edificios << endl;
	for_each(map.lst_edificios.begin(), map.lst_edificios.end(), mostrar_edificio);
}

////////////////////////////////////////////////////////////////////////////////
list<edificio2d> armar_perfil(list<edificio2d> lst_edif)
{
	list<edificio2d> lst_aux;

	while (!lst_edif.empty()) {
		edificio2d ed2 = lst_edif.front();	
		lst_edif.pop_front();
		// buscar la posicion en que debe ubicarse el edificio en lst_aux, comenzando por atras
		// i apunta al edificio con quien tengo que comparar el edificio nuevo.
		typedef list<edificio2d>::iterator LI;
		LI i = lst_aux.end(); 
		i--;		// comenzar sw_x el ultimo
		edificio2d& ed1 = *i;
		// mover los edificios de lst_aux sw_x i hasta el final, al comienzo de lst_edificios para reprocesar
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
						ed1.altura = ed2.altura;
						ed2.desde = ed1.hasta;
						lst_edif.push_front(ed2);
					} else {
						// caso 2
						//Creo un nuevo E2' con la parte sobrante y repito el proceso.
						ed2.desde = ed1.hasta;						
						lst_edif.push_front(ed2);	// hasta aca
					}
				} else {
					if (ed2.altura > ed1.altura) {
						// caso 3 
						// Reemplazo E1 por E1' hasta la interseccion. Repito el proceso (Caso 1)
						edificio2d ed0;
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
							edificio2d ed0;
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
							ed1.altura = ed2.altura;
						}
					} else {
						// caso 6
						// Descarto ed2
					}
				} else {
					if (ed2.altura > ed1.altura) {
						// caso 7 
						// Divido E1 en E1' y E1'', y reemplazo E1 por E1', E2 y E1''
						if (ed2.hasta < ed1.hasta) {
							edificio2d ed0;
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
							ed1.hasta = ed2.desde;
							i++;
							lst_aux.insert(i,ed2);
						}
					} else {
						// caso 8
						// Descarto E2
					}
				}
			}
		} else {
			if (ed2.desde > ed1.hasta) {
				// caso 9
				// dejo ed1, creo un nuevo edificio2d con h = 0 entre ed1 y ed2, y luego coloco ed2
				edificio2d ed0;
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
					i++;
					lst_aux.insert(i,ed2);
				} else {
					// caso 11	
					// Reemplazo h1 por h2, y descarto E2
					ed1.hasta = ed2.hasta;
				}
			}
		}
	}

	// mostrar el perfil
/*	for_each(lst_aux.begin(), lst_aux.end(), mostrar_perfil);
	cout << lst_aux.back().hasta << " 0" << endl;
*/	return lst_aux;

}

	
////////////////////////////////////////////////////////////////////////////////
void mostrar_vista(mapa map)
{	
	// resolver el perfil para cada coordenada en y distinta
	typedef list<int>::iterator LI;
	for (LI i = map.lst_perfiles.begin(); i != map.lst_perfiles.end(); i++) {
		const int& e = *i;

	}

}

////////////////////////////////////////////////////////////////////////////////
//	PROGRAMA PRINCIPAL
////////////////////////////////////////////////////////////////////////////////
int main(int argc, char *argv[])
{
	list<mapa> lst_mapas;
	int cant_edificios;
	int mapas = 0;

	// leer los mapas de entrada y agregarlos a la lista lst_mapas
	cin >> cant_edificios;
	while ((cant_edificios != 0) && (!cin.eof())) {
		mapa map;
		vector<int> vec_coord_y;

		map.cant_edificios = cant_edificios;
		map.nro = ++mapas;	// inc y luego asigna
		// leer los edificios del mapa y agregarlos a la lista map.lst_edificios
		for (int i = 1; i <= map.cant_edificios; i++) {
			edificio ed;
			ed.nro = i;
			cin >> ed.sw_x >> ed.sw_y >> ed.width >> ed.depth >> ed.height;
			vec_coord_y.push_back(ed.sw_y);
			map.lst_edificios.push_back(ed);
		}
		// obtener una lista ordenada con las distintas coordenadas en y
		sort(vec_coord_y.begin(), vec_coord_y.end());
		unique_copy(vec_coord_y.begin(), vec_coord_y.end(), back_inserter(map.lst_perfiles));
		
		// mostrar las distintas coordenadas en y
		for_each(map.lst_perfiles.begin(), map.lst_perfiles.end(), mostrar);
		cout << endl;
		
		lst_mapas.push_back(map);
		cin >> cant_edificios;
	}

	// mostrar lo leido
	for_each(lst_mapas.begin(), lst_mapas.end(), mostrar_mapa);

	// resolver la vista de cada mapa
	for_each(lst_mapas.begin(), lst_mapas.end(), mostrar_vista);

	return 0;
}
