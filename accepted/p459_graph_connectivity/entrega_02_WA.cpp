/* @JUDGE_ID:  40922FK  459  C++  */
/* @BEGIN_OF_SOURCE_CODE */    
/**************************************************************************
 Solution to Problem 459 - Graph Connectivity
 by: Francisco Dibar
 date: Apr-05-2005
**************************************************************************/

//#define ONLINE_JUDGE 
#include <iostream>
#ifndef ONLINE_JUDGE 
	#include <fstream>
#endif 
#include <sstream>

/**************************************************************************
 GRAPH Library Header
 by: Francisco Dibar
 date: Apr-02-2005
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
	// constructor
	Arista(int d, int c) {
		m_iDestino = d;
		m_iCosto = c;
	}
	
	// gets - sets
	int &Destino() { return m_iDestino; }
	int &Costo() { return m_iCosto; }

	// otros
	void procesar() {};
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
	// constructor
	Vertice(string nombre = "") {
		m_sNombre = nombre;
	}

	// gets - sets
	string &Nombre() { return m_sNombre; }
	int &Distancia() { return m_iDistancia; }
	int &Anterior() { return m_iAnterior; }
	int &Extra() { return m_iExtra; }
	list<Arista> &lstAdy() { return m_lstAdy; }
	int cantidadAristas() { return m_lstAdy.size(); }

	// otros
	void procesar();
};

typedef void (*PROC_VERT_VISIT)(void *);
// es un tipo para definir un puntero a una funcion con un argumento
// (puntero). Esta especifica que proceso se realizara con el vertice
// visitado y sera definida por el usuario

///////////////////////////////////////////////////////////////////////////
class Grafo
{
private:
	bool m_bDirigido;
	map<string, int> m_mapVertices;	// relaciona nro con nombre del vertice
	vector<Vertice> m_vecTabla;
	int m_iCantVertices;
	int m_iCantAristas;
	// puntero a la funcion que indica el proceso a realizar en el 
	// vertice visitado
	PROC_VERT_VISIT procVertVisit;

protected:
	bool agregarAristaInterna(int origen, int destino, int costo);
	int agregarVerticeADiccionario(string nombreVertice, bool *noExiste);
	void limpiarDatos();
	bool dijkstra(int vertOrigen);
	void dfs(int start);

	void imprimirCaminoRec(int vertDest);

public:
	// constructor
	Grafo(bool dirigido = false);
	
	// gets
	int cantAristas() { return m_iCantAristas; }
	int cantVertices() { return m_iCantVertices; }

	// recorrer
	void bfs(string start);
	void dfs(string start);
	void caminoMinSinPesos(string vertOrigen);
	void imprimirCamino(string vertDest);
	void mostrar();

	// creacion
	void agregarArista(string origen, string destino, int costo);
	bool agregarVertice(string vertice);

	// otros
	void asignarProceso(PROC_VERT_VISIT fn) { procVertVisit = fn; }
	int maximalConnectedSubgraphs();
	bool conexo() { return (maximalConnectedSubgraphs() == 1); }
	bool existeVertice(string vertice);
};

///////////////////////////////////////////////////////////////////////////

#endif _GRAPH_H__

/**************************************************************************
 GRAPH Library Implementation
 by: Francisco Dibar
 date: Apr-02-2005
**************************************************************************/

#include <iostream>

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
void Grafo::agregarArista(string origen, string destino, int costo = 1)
{
	// agregar los vertices en caso de que no existan
	agregarVertice(origen);
	agregarVertice(destino);

	// obtener los indices de los vertices en la tabla hash
	int orig = m_mapVertices[origen];
	int dest = m_mapVertices[destino];

	agregarAristaInterna(orig, dest, costo);
	if (!m_bDirigido) 
		// agrego dos aristas (ida y vuelta) porque el grafo es no dirigido
		agregarAristaInterna(dest, orig, costo);

}

///////////////////////////////////////////////////////////////////////////
bool Grafo::agregarAristaInterna(int origen, int destino, int costo)
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
bool Grafo::agregarVertice(string nomVertice)
// si el vertice no existe en el grafo, lo agrega y devuelve true
{
	bool noExiste;
	int numeroVert = agregarVerticeADiccionario(nomVertice, &noExiste);
	// agregar el vertice al grafo si no existe
	if (noExiste) {		
		m_vecTabla.push_back(Vertice(nomVertice));
		return true;
	}
	return false;
}

///////////////////////////////////////////////////////////////////////////
int Grafo::agregarVerticeADiccionario(string nombreVertice, bool *noExiste)
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
void Grafo::bfs(string vertDesde)
{
	int nroVertDesde = m_mapVertices[vertDesde];

	// uso m_vecTabla.size() en vez de m_iCantVertices porque si se
	// eliminan vertices, puede ocurrir que nroVertice > m_iCantVertices
	vector<bool> processed(m_vecTabla.size());	
	vector<bool> discovered(m_vecTabla.size());
	vector<int> parent(m_vecTabla.size());

	queue<int> q;
	q.push(nroVertDesde);
	discovered[nroVertDesde] = true;
	while (!q.empty()) {
		int v = q.front();
		q.pop();
		m_vecTabla[v].procesar();
		processed[v] = true;
		// recorrer la lista de aristas del vertice v
		list<Arista>::iterator LI;		// const
		for (LI = m_vecTabla[v].lstAdy().begin(); 
				LI != m_vecTabla[v].lstAdy().end(); LI++) {
			int w = (*LI).Destino();
			if (!discovered[w]) {
				q.push(w);
				discovered[w] = true;
				parent[w] = v;
			}
		}
	}
}

///////////////////////////////////////////////////////////////////////////
void Grafo::caminoMinSinPesos(string vertOrigen)
{
	queue<int> q;

	int nroVertOrigen = m_mapVertices[vertOrigen];
	limpiarDatos();
	m_vecTabla[nroVertOrigen].Distancia() = 0;
	q.push(nroVertOrigen);
	while (!q.empty()) {
		int v = q.front();
		q.pop();
		list<Arista> &lstAdy = m_vecTabla[v].lstAdy();
		list<Arista>::iterator li;
		for (li = lstAdy.begin(); li != lstAdy.end(); ++li) {
			Arista &ar = *li;
			int w = ar.Destino();
			if (m_vecTabla[w].Distancia() == INFINITO) {
				m_vecTabla[w].Distancia() = m_vecTabla[v].Distancia() + 1; 
				m_vecTabla[w].Anterior() = v; 
				q.push(w);
			}
		}
	}
}

///////////////////////////////////////////////////////////////////////////
void Grafo::dfs(string vertDesde)
{
	int nroVertDesde = m_mapVertices[vertDesde];
	dfs(nroVertDesde);
}

///////////////////////////////////////////////////////////////////////////
void Grafo::dfs(int nroVertDesde)
{
	// uso m_vecTabla.size() en vez de m_iCantVertices porque si se
	// eliminan vertices, puede ocurrir que nroVertice > m_iCantVertices
	vector<bool> processed(m_vecTabla.size());	
	vector<bool> discovered(m_vecTabla.size());
	vector<int> parent(m_vecTabla.size());

	discovered[nroVertDesde] = true;
	m_vecTabla[nroVertDesde].procesar();

	list<Arista>::iterator LI;		// const
	for (LI = m_vecTabla[nroVertDesde].lstAdy().begin(); 
			LI != m_vecTabla[nroVertDesde].lstAdy().end(); LI++) {
		int w = (*LI).Destino();
		if (!discovered[w]) {
			parent[w] = nroVertDesde;
			dfs(w);
		} else 
			if (!processed[w])
				m_vecTabla[w].procesar();
	}
	processed[nroVertDesde] = true;
}


///////////////////////////////////////////////////////////////////////////
bool Grafo::dijkstra(int vertOrigen)
{
	return false;
}

///////////////////////////////////////////////////////////////////////////
bool Grafo::existeVertice(string vertice)
{
	map<string, int>::const_iterator iter;
	iter = m_mapVertices.find(vertice);
	return (iter != m_mapVertices.end());
}

///////////////////////////////////////////////////////////////////////////
void Grafo::imprimirCamino(string vertDest)
{
	int nroVertDest = m_mapVertices[vertDest];
	if (m_vecTabla[nroVertDest].Distancia() == INFINITO)
		cout<< m_vecTabla[nroVertDest].Nombre() << " es inalcanzable" << endl;
	else {
		imprimirCaminoRec(nroVertDest);
		cout << "El costo es " << m_vecTabla[nroVertDest].Distancia() << endl;
	}
}

///////////////////////////////////////////////////////////////////////////
void Grafo::imprimirCaminoRec(int vertDest)
{
	if (m_vecTabla[vertDest].Anterior() != VERTICE_NULO) {
		imprimirCaminoRec(m_vecTabla[vertDest].Anterior());
		cout << " a ";
	}
	cout << m_vecTabla[vertDest].Nombre();
}

///////////////////////////////////////////////////////////////////////////
void Grafo::limpiarDatos()
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
int Grafo::maximalConnectedSubgraphs()
// devuelve la maxima cantidad de subgrafos conexos
// obs: devuelve valores != si el grafo es dirigido o no
{
	int max = 0;
	int cantVertVistos = m_iCantVertices;
	vector<bool> vec_vistos(m_vecTabla.size());

	// bfs
	vector<bool> discovered(m_vecTabla.size());

	// REVISAR: que pasa si no existe el vertice i
	for (int i = 0; i < (int)m_vecTabla.size(); i++) {
		if (!discovered[i]) {
			queue<int> q;
			q.push(i);
			discovered[i] = true;
			max++;
			while (!q.empty()) {
				int v = q.front();
				q.pop();
				// recorrer la lista de aristas del vertice v
				list<Arista>::iterator LI;		// const
				for (LI = m_vecTabla[v].lstAdy().begin(); 
						LI != m_vecTabla[v].lstAdy().end(); LI++) {
					int w = (*LI).Destino();
					if (!discovered[w]) {
						q.push(w);
						discovered[w] = true;
					}
				}
			}
		} 
	}

	return max;
}

///////////////////////////////////////////////////////////////////////////
void Grafo::mostrar()
{
	cout << "Grafo " << (m_bDirigido ? "Dirigido" : "no Dirigido") 
		<< ": " << endl << endl;
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
}

///////////////////////////////////////////////////////////////////////////
void Vertice::procesar()
{
	cout << m_sNombre << endl;
}

///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

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

	Grafo g(false);	// grafo no dirigido
	string input;
	char v, w;
	cin >> v;	// ignoro el primer char
	// agregar al grafo todos los vertices de 'A' hasta v
	for (char c = 'A'; c <= v; c++) {
		string vert;
		vert += c;
		g.agregarVertice(vert);
	}
	getline(cin, input);	// ignorar el resto de la linea
	getline(cin, input);
	while (!cin.eof() && !input.empty()) {
		istringstream is(input);
		is >> v >> w;
		string sv, sw;
		sv += v; sw += w;
		g.agregarArista(sv, sw);
		getline(cin, input);
	}
	cout << g.maximalConnectedSubgraphs() << endl;
	return 0;
}

/* @END_OF_SOURCE_CODE */

