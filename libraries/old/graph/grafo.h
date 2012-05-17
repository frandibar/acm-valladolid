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
