/**************************************************************************
 BIGINT Library Header
 by: Francisco Dibar
 date: Mar-20-2005
**************************************************************************/

#if !defined(_GRAPH_H__)
#define _GRAPH_H__

#include <iostream>
#include <list>
#include <vector>
#include <map>
#include <string>

////////////////////////////////////////////////////////////////////////////////

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

////////////////////////////////////////////////////////////////////////////////

class Vertice
{
private:
	string m_sNombre;			// nombre real del vertice
	list<Arista> m_lstAdy;	// lista de adyacencia, se insertan las aristas
	int m_iDistancia;			// costo (despues de ejecutar el algoritmo)
	int m_iAnterior;			// vertice anterior en el camino minimo
	int m_iExtra;				// variable extra usada por los algoritmos
/*
	bool m_bConocido;
	bool m_bPtoArticulacion;
	int m_iNroDFS;			// utilizadas para obtener el punto de articulacion
	int m_iInferior;
	int m_iPadre;
*/
public:
	Vertice(string nombre) {
		m_sNombre = nombre;
	}

	/* devuelven las variables miembro */
	string &Nombre() { return m_sNombre; }
	int &Distancia() { return m_iDistancia; }
	int &Anterior() { return m_iAnterior; }

//	list<Arista> ObtenerLista() { return m_lAdy; }
/*
	bool &Conocido() { return m_bConocido; }
	bool &PtoArticulacion() { return m_bPtoArticulacion; }
	int &NroDFS() { return m_iNroDFS; }
	int &Inferior() { return m_iInferior; }
	int &Padre() { return m_iPadre; }
*/
};

////////////////////////////////////////////////////////////////////////////////

class Grafo
{
private:
	bool m_bDirigido;
	map<int, string> m_mapVertices;	// relaciona nro con nombre del vertice
	vector<vertice> m_vecTabla;
	int m_iCantVertices;

protected:
	int AgregarVerticeADiccionario(string nombreVertice);
/*
	void AgregarAristaInterna(int origen, int destino, int costo);
	void EliminarAristaInterna(int origen, int destino);
	void LimpiarDatos();
	void AsignarNrosDFS(int vertice, int nro);
	void BuscarArticulacion(int vertice, int contador);
*/
public:
	Grafo();

	bool ExisteVertice(string vertice);
/*
	void AgregarVertice(string vertice);
	void AgregarArista(string origen, string destino, int costo);
	void EliminarArista(string origen, string destino);
	void Mostrar();
	void MostrarTablaCaminoMinimo();
	int CantVertices() { return m_iCantVertices; }
	string NombreVertice(int);
	void Dijkstra(string nodoOrigen) {
		Dijkstra(AgregarVerticeADiccionario(nodoOrigen));
	}
	void Dijkstra(int nodoOrigen);
	Vertice *ObtenerVertice(int i) { return m_vecTabla[i]; }
	int ObtenerDistancia(string vertice);
	string ObtenerAnterior(string vertice);
	int NumeroVertice(string vertice);
	void MostrarCaminoMinimo(string destino);
	void EncontrarPtosArticulacion();
	void MostrarPtosArticulacion();
*/
};

////////////////////////////////////////////////////////////////////////////////

#endif _GRAPH_H__
