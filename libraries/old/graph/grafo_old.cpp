/**************************************************************************
 GRAPH Library Implementation
 by: Francisco Dibar
 date: Mar-20-2005
**************************************************************************/

#include "grafo.h"
#include <iostream>
#include <list>
#include <vector>
#include <map>
#include <string>

#define TAMANO_DEFAULT 50
#define INFINITO 2147483644 // maxint
#define VERTICE_NULO -1

////////////////////////////////////////////////////////////////////////////////
Grafo::Grafo()
{
	m_iCantVertices = 0;
	m_vecTabla.resize(TAMANO_DEFAULT);
}

////////////////////////////////////////////////////////////////////////////////
bool Grafo::ExisteVertice(string vertice)
{
	map<string, int>::const_iterator res;
	res = m_mapVertices.find(vertice);
	return (res == m_mapVertices.end());
}

/*
////////////////////////////////////////////////////////////////////////////////
void Grafo::AgregarArista(string origen, string destino, int costo)
{
	// agregar los vertices en caso de que no existan
	AgregarVertice(origen);
	AgregarVertice(destino);

	// obtener los indices de los vertices en la tabla hash
	int orig = AgregarVerticeADiccionario(origen);
	int dest = AgregarVerticeADiccionario(destino);
	
	AgregarAristaInterna(orig, dest, costo);
	if (!m_bDirigido) 
		// agrego dos aristas porque el grafo es no dirigido
		AgregarAristaInterna(dest, orig, costo);

}

////////////////////////////////////////////////////////////////////////////////
void Grafo::EliminarArista(string origen, string destino)
{
	// obtener los indices de los vertices en la tabla hash
	int orig = AgregarVerticeADiccionario(origen);
	int dest = AgregarVerticeADiccionario(destino);
	
	// agrego dos aristas porque el grafo es no dirigido
	EliminarAristaInterna(orig, dest);
	EliminarAristaInterna(dest, orig);
}
*/

/*
////////////////////////////////////////////////////////////////////////////////
void Grafo::AgregarVertice(string vertice)
// si el vertice no existe en el grafo, lo agrega
{
	int numeroVert = AgregarVerticeADiccionario(vertice);
	// agregar el vertice al grafo (lista de adyacencia)
	if (m_vecTabla->ElementAt(numeroVert) == NULL) {
		CVertice *pVert = new CVertice(vertice);
		m_vecTabla->ElementAt(numeroVert) = pVert;
	}
}

////////////////////////////////////////////////////////////////////////////////
void Grafo::AgregarAristaInterna(int origen, int destino, int costo)
{
	// si la arista ya existe, se modifica el costo, si no existe, se agrega
	CArista *pSig = NULL;
	CObList *pLista = ((CVertice *)m_vecTabla->ElementAt(origen))->ObtenerLista();
	POSITION pos = pLista->GetHeadPosition();
	bool encontrada = false;

	while (pos != NULL && !encontrada) {
		pSig = (CArista *)pLista->GetNext(pos);
		if (pSig->Destino() == destino) {
			// ya existe
			pSig->Costo() = costo;
			encontrada = true;
		}
	}
	if (pos == NULL && !encontrada) {
		// no existe
		pLista->AddTail(new CArista(destino, costo));
	}
}

////////////////////////////////////////////////////////////////////////////////
void Grafo::EliminarAristaInterna(int origen, int destino)
{
	CArista *pAct = NULL;
	CObList *pLista = ((CVertice *)m_vecTabla->ElementAt(origen))->ObtenerLista();
	bool encontrada = false;

	for (int i = 0; i < pLista->GetCount() && !encontrada; i++) {
		pAct = (CArista *)pLista->GetAt(pLista->FindIndex(i));
		if (pAct->Destino() == destino) {
			pLista->RemoveAt(pLista->FindIndex(i));
			encontrada = true;
		}
	}
}
*/
////////////////////////////////////////////////////////////////////////////////
int Grafo::AgregarVerticeADiccionario(string nombreVertice)
// si nombreVertice ya existe, devuelve su numero interno, 
// sino lo agrega al diccionario
{
	// no se permiten claves duplicadas, si ya existe, no lo inserta
	m_mapVertices.insert(nombreVertice, m_iCantVertices+1);
	m_iCantVertices = m_mapVertices.size();
	return m_mapVertices[nombreVertice];
}
/*
////////////////////////////////////////////////////////////////////////////////
void Grafo::Mostrar()
{
	CArista *pSig = NULL;
	CVertice *pVertice = NULL;
	CObList *pLista = NULL;
	POSITION pos = NULL;
	
	cout << "\nGrafo: \n\n";
	cout << "[Vertice Origen]: [Vertice Final] ([Costo])\n";
	for (int i = 0; i < m_iCantVertices; i++) {
		pVertice = (CVertice *)m_vecTabla->ElementAt(i);
		pLista = ((CVertice *)m_vecTabla->ElementAt(i))->ObtenerLista();
		pos = pLista->GetHeadPosition();		

		cout << endl << pVertice->Nombre() << ": ";
		while (pos != NULL) {
			pSig = (CArista *)pLista->GetNext(pos);
			cout << NombreVertice(pSig->Destino()) << " (" << pSig->Costo() << ") ";
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
string Grafo::NombreVertice(int indice)
{
	if (indice < 0 || indice >= m_iCantVertices) {
		cerr << "\nError al obtener el nombre del vertice\nNumero de indice fuera de rango\n";
		return "";
	}
	return ((CVertice *)m_vecTabla->ElementAt(indice))->Nombre();
}

////////////////////////////////////////////////////////////////////////////////
void Grafo::Dijkstra(int nodoOrigen)
{
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
}

////////////////////////////////////////////////////////////////////////////////
void Grafo::LimpiarDatos()
{
	CVertice *pV = NULL;
	
	for (int i = 0; i < m_iCantVertices; i++) {
		pV = ObtenerVertice(i);
		pV->Distancia() = INFINITO;
		pV->Anterior() = VERTICE_NULO;
	}
}

////////////////////////////////////////////////////////////////////////////////
void Grafo::MostrarTablaCaminoMinimo()
{
	CVertice *pVertice = NULL;
	
	cout << "\nCamino Minimo: \n\n";
	cout << "[Vertice Origen]: [Distancia] ([Vertice Anterior])\n";
	for (int i = 0; i < m_iCantVertices; i++) {
		pVertice = (CVertice *)m_vecTabla->ElementAt(i);

		cout << endl << pVertice->Nombre() << ":\t";
		if (pVertice->Distancia() != INFINITO)
			cout << pVertice->Distancia() << "\t(";
		else
			cout << "INF\t(";
		if (pVertice->Anterior() != VERTICE_NULO)
			cout << NombreVertice(pVertice->Anterior());
		else
			cout << "-";
		cout << ") ";
	}
	cout << endl;
}

////////////////////////////////////////////////////////////////////////////////
int Grafo::ObtenerDistancia(string nombreVertice) 
{
	int vertice = AgregarVerticeADiccionario(nombreVertice);
	return ((CVertice *)m_vecTabla->ElementAt(vertice))->Distancia();
}

////////////////////////////////////////////////////////////////////////////////
string Grafo::ObtenerAnterior(string nombreVertice)
{
	int vertice = AgregarVerticeADiccionario(nombreVertice);
	CVertice *pVertice = (CVertice *)m_vecTabla->ElementAt(vertice);
	if (pVertice->Anterior() != VERTICE_NULO)
		return NombreVertice(((CVertice *)m_vecTabla->ElementAt(vertice))->Anterior());
	else
		return "-";
}

////////////////////////////////////////////////////////////////////////////////
int Grafo::NumeroVertice(string vertice)
{
	return AgregarVerticeADiccionario(vertice);
}

////////////////////////////////////////////////////////////////////////////////
void Grafo::MostrarCaminoMinimo(string destino)
{
	if (!ExisteVertice(destino)) {
		cout << endl << destino << " no es un vertice del grafo\n";
		return;
	}
	int vertice = AgregarVerticeADiccionario(destino);
	CVertice *pVertice = (CVertice *)m_vecTabla->ElementAt(vertice);

	if (pVertice->Distancia() == INFINITO) {
		cout << endl << destino << " es inalcanzable\n";
		return;
	}
	if (pVertice->Anterior() != VERTICE_NULO) {
		string destAnterior = NombreVertice(pVertice->Anterior());
		MostrarCaminoMinimo(destAnterior);
		cout << " a ";
	}
	cout << destino << "(" << pVertice->Distancia() << ")";
}

////////////////////////////////////////////////////////////////////////////////
void Grafo::EncontrarPtosArticulacion()
{
	if (m_iCantVertices == 0)
		return;

	// inicializar todos los m_bConocido de los vertices en false
	for (int i = 0; i < m_iCantVertices; i++) 
		((CVertice *)m_vecTabla->ElementAt(i))->Conocido() = false;

	BuscarArticulacion(0, 0);
	MostrarPtosArticulacion();
}

////////////////////////////////////////////////////////////////////////////////
void Grafo::AsignarNrosDFS(int vertice, int nro)
// no se utiliza
{
	CVertice *pVerticeV = (CVertice *)m_vecTabla->ElementAt(vertice);
	pVerticeV->NroDFS() = nro;
	pVerticeV->Conocido() = true;

	CArista *pSig = NULL;
	CObList *pLista = pVerticeV->ObtenerLista();
	POSITION pos = pLista->GetHeadPosition();

	while (pos != NULL) {
		pSig = (CArista *)pLista->GetNext(pos);
		CVertice *pVerticeW = (CVertice *)m_vecTabla->ElementAt(pSig->Destino());
		if (pVerticeW->Conocido() == false)
			AsignarNrosDFS(pSig->Destino(), nro + 1);
	}
}

////////////////////////////////////////////////////////////////////////////////
void Grafo::BuscarArticulacion(int vertice, int contador)
{
	CVertice *pVerticeV = (CVertice *)m_vecTabla->ElementAt(vertice);
	pVerticeV->NroDFS() = contador;
	pVerticeV->Conocido() = true;
	pVerticeV->Inferior() = pVerticeV->NroDFS();

	CArista *pSig = NULL;
	CObList *pLista = pVerticeV->ObtenerLista();
	POSITION pos = pLista->GetHeadPosition();

	while (pos != NULL) {
		pSig = (CArista *)pLista->GetNext(pos);
		CVertice *pVerticeW = (CVertice *)m_vecTabla->ElementAt(pSig->Destino());
		if (pVerticeW->Conocido() == false) {
			pVerticeV->Padre() = vertice;
			BuscarArticulacion(pSig->Destino(), contador + 1);
			if (pVerticeW->Inferior() >= pVerticeV->NroDFS())
				pVerticeV->PtoArticulacion() = true;
			
			if (pVerticeV->Inferior() > pVerticeW->Inferior()) 
				pVerticeV->Inferior() =	pVerticeW->Inferior();  
		} else {
			if (pVerticeV->Padre() != pSig->Destino()) {
				if (pVerticeV->Inferior() > pVerticeW->NroDFS()) 
					pVerticeV->Inferior() =	pVerticeW->NroDFS();  
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
void Grafo::MostrarPtosArticulacion()
{
	CVertice *pVertice = NULL;
	
	cout << "\nPuntos de Articulacion: \n\n";
	for (int i = 0; i < m_iCantVertices; i++) {
		pVertice = (CVertice *)m_vecTabla->ElementAt(i);
		if (pVertice->PtoArticulacion() == true)
			cout << pVertice->Nombre() << endl;
	}
}
*/