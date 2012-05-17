/**************************************************************************
 GRAPH Library Implementation
 by: Francisco Dibar
 date: Apr-02-2005
**************************************************************************/

#include "grafo.h"
#include <iostream>

#include <list>
#include <map>
#include <queue>
#include <string>
#include <vector>

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
		for (li = lstAdy.begin(); 
				li != lstAdy.end(); ++li) {
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
/*	LimpiarDatos();
//	priority_queue<int, int> pq;
	priority_queue<Vertice, less<Vertice> > pq;
	m_vecTabla[vertOrigen].Distancia() = 0;
	//pq.push(priority_queue<Vertice, less<Vertice> >::value_type(vertOrigen, 0));
	pq.push(m_vecTabla[vertOrigen]);
*/
/*
	int v, w;
	CColaPrioridad cp;
	CElementoCola vrec(VERTICE_NULO);
	CVertice *pVertice = (CVertice *)m_vecTabla->ElementAt(nodoOrigen);

	LimpiarDatos();
	pVertice->Distancia() = 0;
	cp.Insertar(new CElementoCola(nodoOrigen, 0));

	for (int nodosVistos = 0; nodosVistos < m_iCantVertices; nodosVistos++) {
		do {
			if (cp.Vacia())
				return;
			vrec.Destino() = cp.EliminarMin();
			pVertice = (CVertice *)m_vecTabla->ElementAt(vrec.Destino());
		} while (pVertice->Conocido() == false);
		
		v = vrec.Destino();
		pVertice = (CVertice *)m_vecTabla->ElementAt(v);
		pVertice->Conocido() = true;

		CObList *pLista = new CObList;
		// copiar la lista de adyacencia para el vertice v en pLista
		pLista->AddHead(pVertice->ObtenerLista());

		POSITION pos = pLista->GetHeadPosition();
		for ( ; pos != NULL ; pLista->GetNext(pos)) {
			w = ((CArista *)pLista->GetAt(pos))->Destino();
			int cvw = ((CArista *)pLista->GetAt(pos))->Costo();
			CVertice *pVerticeW = (CVertice *)m_vecTabla->ElementAt(w);
			
			if (cvw < 0) {
				cerr << "\nError al hallar el camino minimo, no se aceptan aristas negativas\n";
				return;
			}

			if (pVerticeW->Distancia() > pVertice->Distancia() + cvw) {
				pVerticeW->Distancia() = (pVertice->Distancia() + cvw);
				pVerticeW->Anterior() = v; 
				cp.Insertar(new CElementoCola(w, pVerticeW->Distancia()));
			}
		}
	}
*/	return false;
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
	cout << "Vertices (" << m_iCantVertices << "):" << endl << endl;
	for (int i = 0; i < m_iCantVertices; i++)
		cout << m_vecTabla[i].Nombre() << endl;
		
	cout << endl;
	cout << "Aristas (" << m_iCantAristas << "):" << endl;
	cout << "[Vertice Origen] -> [Vertice Destino]: [Costo]" << endl << endl;

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
