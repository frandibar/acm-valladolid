/* @JUDGE_ID:  40922FK  10004  C++  */
/* @BEGIN_OF_SOURCE_CODE */    
/**************************************************************************
 Solution to Problem 10004 - Bicoloring
 by: Francisco Dibar
 date: Mar-01-2005
**************************************************************************/

//#define ONLINE_JUDGE 
#include <iostream>
#ifndef ONLINE_JUDGE 
	#include <fstream>
#endif 

#define NOT_SET	0
#define RED			1
#define BLUE		2

using namespace std;

/**************************************************************************
 GRAPH Library Header
 by: Francisco Dibar
 date: Mar-20-2005
**************************************************************************/

#if !defined(_GRAPH_H__)
#define _GRAPH_H__

#include <list>
#include <map>
#include <string>
#include <vector>

using namespace std;

///////////////////////////////////////////////////////////////////////////
class Arista 
{
private:
	int m_iDestino;		// el primer vertice esta implicito
	int m_iCosto;

public:
	Arista(int d, int c) {
		m_iDestino = d;
		m_iCosto = c;
	}

	int &Destino() { return m_iDestino; }
	int &Costo() { return m_iCosto; }
};

///////////////////////////////////////////////////////////////////////////
class Vertice
{
private:
	string m_sNombre;			// nombre real del vertice
	list<Arista> m_lstAdy;	// lista de adyacencia, se insertan las aristas
	int m_iDistancia;			// costo (despues de ejecutar el algoritmo)
	int m_iAnterior;			// vertice anterior en el camino minimo
	int m_iExtra;				// variable extra usada por los algoritmos

public:
	Vertice() { m_sNombre = ""; }
	Vertice(string nombre) {
		m_sNombre = nombre;
	}

	/* devuelven las variables miembro */
	string &Nombre() { return m_sNombre; }
	int &Distancia() { return m_iDistancia; }
	int &Anterior() { return m_iAnterior; }
	int &Extra() { return m_iExtra; }
	list<Arista> &lstAdy() { return m_lstAdy; }
};

///////////////////////////////////////////////////////////////////////////
class Grafo
{
private:
	bool m_bDirigido;
	map<string, int> m_mapVertices;	// relaciona nro con nombre del vertice
	vector<Vertice> m_vecTabla;
	int m_iCantVertices;
	int m_iCantAristas;

protected:
	bool AgregarAristaInterna(int origen, int destino, int costo);
	int AgregarVerticeADiccionario(string nombreVertice, bool *noExiste);
	void LimpiarDatos();

	void ImprimirCaminoRec(int vertDest);

public:
	Grafo(bool dirigido = false);
	int CantAristas() { return m_iCantAristas; }
	int CantVertices() { return m_iCantVertices; }

	void ImprimirCamino(int vertDest);
	void CaminoMinSinPesos(int vertOrigen);
	void Mostrar();

	void AgregarArista(string origen, string destino, int costo);
	bool AgregarVertice(string vertice);

	bool ExisteVertice(string vertice);

	bool Bicolorable();		// para este problema

};

///////////////////////////////////////////////////////////////////////////

#endif _GRAPH_H__


/**************************************************************************
 GRAPH Library Implementation
 by: Francisco Dibar
 date: Mar-20-2005
**************************************************************************/

//#include "grafo.h"
//#include <iostream>

//#include <list>
//#include <map>
#include <queue>
//#include <string>
//#include <vector>

#define INFINITO		715827882	//  2147483647 / 3  //  maxint/3
#define VERTICE_NULO -1

using namespace std;

///////////////////////////////////////////////////////////////////////////
Grafo::Grafo(bool dirigido)
{
	m_bDirigido = dirigido;
	m_iCantVertices = 0;
	m_iCantAristas = 0;
}

///////////////////////////////////////////////////////////////////////////
void Grafo::AgregarArista(string origen, string destino, int costo = 1)
{
	// agregar los vertices en caso de que no existan
	AgregarVertice(origen);
	AgregarVertice(destino);

	// obtener los indices de los vertices en la tabla hash
	int orig = m_mapVertices[origen];
	int dest = m_mapVertices[destino];

	AgregarAristaInterna(orig, dest, costo);
	if (!m_bDirigido) 
		// agrego dos aristas (ida y vuelta) porque el grafo es no dirigido
		AgregarAristaInterna(dest, orig, costo);

}

///////////////////////////////////////////////////////////////////////////
bool Grafo::AgregarAristaInterna(int origen, int destino, int costo)
// si la arista ya existe, se modifica el costo, si no existe, se agrega
// y se devuelve true
{
	list<Arista>::iterator li;
	bool encontrado = false;

	// buscar la arista recorriendo toda la lista
	for (li = m_vecTabla[origen].lstAdy().begin(); 
					!encontrado && (li != m_vecTabla[origen].lstAdy().end()); ++li) {
		Arista &ar = *li;
		if (ar.Destino() == destino) {
			ar.Costo() = costo;
			encontrado = true;
		}
	}
	if (!encontrado) {
		// agregar la arista
		(m_vecTabla[origen].lstAdy()).push_back(Arista(destino, costo));
		m_iCantAristas++;
		return true;
	}
	return false;
}

///////////////////////////////////////////////////////////////////////////
bool Grafo::AgregarVertice(string nomVertice)
// si el vertice no existe en el grafo, lo agrega y devuelve true
{
	bool noExiste;
	int numeroVert = AgregarVerticeADiccionario(nomVertice, &noExiste);
	// agregar el vertice al grafo si no existe
	if (noExiste) {		
		m_vecTabla.push_back(Vertice(nomVertice));
		return true;
	}
	return false;
}

///////////////////////////////////////////////////////////////////////////
int Grafo::AgregarVerticeADiccionario(string nombreVertice, bool *noExiste)
// si nombreVertice ya existe, devuelve su numero interno, 
// sino lo agrega al diccionario
{
	// no se permiten claves duplicadas, si ya existe, no lo inserta
	typedef map<string, int>::iterator mi;
	pair<mi, bool> res; 
	// insert devuelve el par(iterador, bool) con bool = true si se inserto
	// y false si ya existia.
	// iterador apunta al elemento insertado
	res = m_mapVertices.insert(map<string, int>::value_type(nombreVertice, m_iCantVertices));
	if (res.second) {	// indica si se agrego o no
		m_iCantVertices++;
		*noExiste = true;
	} else
		*noExiste = false;
	
	return m_mapVertices[nombreVertice];
}

///////////////////////////////////////////////////////////////////////////
void Grafo::CaminoMinSinPesos(int vertOrigen)
{
	queue<int> que;

	LimpiarDatos();
	m_vecTabla[vertOrigen].Distancia() = 0;
	que.push(vertOrigen);
	while (!que.empty()) {
		int v = que.front();
		que.pop();
		list<Arista> &lstAdy = m_vecTabla[v].lstAdy();
		list<Arista>::iterator li;
		for (li = lstAdy.begin(); li != lstAdy.end(); ++li) {
			Arista &ar = *li;
			int w = ar.Destino();
			if (m_vecTabla[w].Distancia() == INFINITO) {
				m_vecTabla[w].Distancia() = m_vecTabla[v].Distancia() + 1; 
				m_vecTabla[w].Anterior() = v; 
				que.push(w);
			}
		}
	}
}

///////////////////////////////////////////////////////////////////////////
bool Grafo::ExisteVertice(string vertice)
{
	map<string, int>::const_iterator iter;
	iter = m_mapVertices.find(vertice);
	return (iter == m_mapVertices.end());
}

///////////////////////////////////////////////////////////////////////////
void Grafo::ImprimirCamino(int vertDest)
{
	if (m_vecTabla[vertDest].Distancia() == INFINITO)
		cout<< m_vecTabla[vertDest].Nombre() << " es inalcanzable" << endl;
	else {
		ImprimirCaminoRec(vertDest);
		cout << "El costo es " << m_vecTabla[vertDest].Distancia() << endl;
	}
}

///////////////////////////////////////////////////////////////////////////
void Grafo::ImprimirCaminoRec(int vertDest)
{
	if (m_vecTabla[vertDest].Anterior() != VERTICE_NULO) {
		ImprimirCaminoRec(m_vecTabla[vertDest].Anterior());
		cout << " a ";
	}
	cout << m_vecTabla[vertDest].Nombre();
}

///////////////////////////////////////////////////////////////////////////
void Grafo::LimpiarDatos()
// inicializa la tabla de camino minimo
{
	vector<Vertice>::iterator vi;
	for (vi = m_vecTabla.begin(); vi != m_vecTabla.end(); ++vi) {
		Vertice &vert = *vi;
		vert.Distancia() = 0;
		vert.Anterior() = VERTICE_NULO;
		vert.Extra() = 0;
	}
}

///////////////////////////////////////////////////////////////////////////
void Grafo::Mostrar()
{
	cout << "Grafo " << (m_bDirigido ? "Dirigido" : "no Dirigido") << ": " << endl << endl;
	cout << "[Vertice Origen] -> [Vertice Destino]: [Costo]" << endl;
	for (int i = 0; i < m_iCantVertices; i++) {
		Vertice &vert = m_vecTabla[i];
		list<Arista> &ar = vert.lstAdy();

		list<Arista>::iterator li;
		for (li = ar.begin(); li != ar.end(); ++li)
			cout << vert.Nombre() << "\t->\t" 
					<< m_vecTabla[(*li).Destino()].Nombre() 
					<< ":\t" << (*li).Costo() << endl;
		
	}

	cout << endl;
	cout << "[Vertice]: [Extra]" << endl;
	for (int i = 0; i < m_iCantVertices; i++) 
		cout << m_vecTabla[i].Nombre() << ":\t" << m_vecTabla[i].Extra() << endl;
	cout << endl;
}


///////////////////////////////////////////////////////////////////////////
bool Grafo::Bicolorable()
{
	// uso la variable miembro Extra del vertice para guardar el color
	// similar al algoritmo CaminoMinSinPesos
	queue<int> que;

	LimpiarDatos();
	m_vecTabla[0].Extra() = RED;
	m_vecTabla[0].Distancia() = 0;
	que.push(0);
	vector<bool> vec_procesados(m_iCantVertices);
	while (!que.empty()) {
		int v = que.front();
		que.pop();
		list<Arista> &lstAdy = m_vecTabla[v].lstAdy();
		list<Arista>::iterator li;
		for (li = lstAdy.begin(); li != lstAdy.end(); ++li) {
			Arista &ar = *li;
			int w = ar.Destino();
			int colorv = m_vecTabla[v].Extra();
			// analizo el vertice si no fue procesado aun
			if (!vec_procesados[w]) {
				m_vecTabla[w].Distancia() = m_vecTabla[v].Distancia() + 1; 
				if (m_vecTabla[w].Extra() == colorv)
					return false;
				else {
					m_vecTabla[w].Extra() = (colorv == RED ? BLUE : RED); 
					que.push(w);
				}
			}
		}
		vec_procesados[v] = true;
	}
	return true;
}

///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////


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

	int cant_vertices;
	cin >> cant_vertices;
	while ((cant_vertices != 0) && !cin.eof()) {
		Grafo g;
		int cant_aristas;
		cin >> cant_aristas;
		for (int i = 0; i < cant_aristas; i++) {
			string origen, destino;
			cin >> origen >> destino;
			g.AgregarArista(origen, destino);
		}
		if (g.Bicolorable())
			cout << "BICOLORABLE." << endl;
		else
			cout << "NOT BICOLORABLE." << endl;
		//g.Mostrar();
		cin >> cant_vertices;
	}

	return 0;
}

/* @END_OF_SOURCE_CODE */

