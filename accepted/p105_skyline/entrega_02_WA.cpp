
/* @JUDGE_ID:  40922FK  105  C++  */
    
/******************************************************************************
 Solution to Problem 105 - The Skyline problem
 by: Francisco Dibar
 date: Jan-24-2004
******************************************************************************/

#include <iostream>		// para leer el archivo de texto

#define MAX_COORDENADA		10000
#define MAX_EDIFICIOS		5000

using namespace std;

////////////////////////////////////////////////////////////////////////////////
class CPerfilCiudad {
private:
	int *m_pPerfil;
	int m_iTamanio;			// contiene el tamaño del perfil (de 0 a m_iTamanio-1)

public:
	CPerfilCiudad(int tam = MAX_COORDENADA) { 
		m_iTamanio = tam;
		m_pPerfil = new int[m_iTamanio];
		Borrar(); 
	}					
	~CPerfilCiudad() { delete []m_pPerfil; }
	void Borrar() { 
		for (int i = 0; i < m_iTamanio; i++) 
				m_pPerfil[i] = 0; 
	}
	void AgregarEdificio(int l, int h, int r) {
		for (int i = l; i < r; i++) 
			if (m_pPerfil[i] < h)
				m_pPerfil[i] = h;
	}
	int ObtenerCoordenadaMax() { return m_iTamanio-1; }
	int *ObtenerPerfil(int *elem) {
	// devuelve un array con el perfil de la ciudad, y el tamaño del mismo en elem
		int cambiosAltura = 0;
		int *pPerfil = new int[2*m_iTamanio]; // para m_iTamanio cambios de altura, tengo 2*m_iTamanio posiciones en el perfil
		if (!pPerfil) {		// error: memoria insuficiente
			cerr << "\nNo hay suficiente memoria para obtener el perfil de la ciudad.\n";
			return 0;	
		}

		for (int i = 1; i < m_iTamanio; i++) {
			if (m_pPerfil[i] != m_pPerfil[i-1]) {		// si hay variacion de altura															
				pPerfil[2*cambiosAltura] = i;			// guardo el indice izq  
				pPerfil[2*cambiosAltura + 1] = m_pPerfil[i];	// guardo la nueva altura
				cambiosAltura++;
			}		
		}
		*elem = 2*cambiosAltura - 1;
		return pPerfil;
	}
};

////////////////////////////////////////////////////////////////////////////////
int CargarEdificios(CPerfilCiudad *pPerfil)
{
	int x1, h, x2;
	cin >> x1 >> h >> x2;
	int edificios = 1;
	while (!cin.eof() && (edificios < MAX_EDIFICIOS)) {
		// verificar que no se exceda el limite permitido
		if ((x1 >= MAX_COORDENADA) || (x2 >= MAX_COORDENADA)) {
			cerr << "Error por limite excedido de coordenada (0 - " << MAX_COORDENADA << ")";
			return -1;
		}
		pPerfil->AgregarEdificio(x1, h, x2);
		cin >> x1 >> h >> x2;
	}   
	return 0;
}

////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//	PROGRAMA PRINCIPAL
////////////////////////////////////////////////////////////////////////////////

// si todos los edificios estan contiguos, y tienen distinta altura con sus vecinos
// entonces habra MAX_EDIFICIOS alturas distintas, por lo que se necesita un vector
// de dimension 2*MAX_EDIFICIOS para contener el perfil

////////////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{
	CPerfilCiudad perfilCiudad;
	int *pPerfil = 0;
	int TamPerfil = 0;

	if (CargarEdificios(&perfilCiudad) == -1)
		return -1; 

	if (pPerfil) delete []pPerfil;	// si ya existe, eliminarlo					
	pPerfil = perfilCiudad.ObtenerPerfil(&TamPerfil);
	cout << "\n("; 
	for (int i = 0; i < TamPerfil; i++)
		cout << pPerfil[i] << ",";
	cout << "0)\n";

	if (pPerfil) delete []pPerfil;
	pPerfil = 0;

	return 0;
}

