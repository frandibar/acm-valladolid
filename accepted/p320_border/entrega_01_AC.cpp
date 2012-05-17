
/* @JUDGE_ID:  40922FK  320  C++  */
    
/******************************************************************************
 Solution to Problem 320 - Border
 by: Francisco Dibar
 date: Apr-04-2004
******************************************************************************/

#include <iostream>
#include <list>
#include <string>
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


#define DIMX	32
#define DIMY	32

#define X				'X'
#define FIN_CAMINO		'.'		// REVISAR: no se controla el fin de camino

using namespace std;

////////////////////////////////////////////////////////////////////////////////
class bitmap {
private:
	int m_iNro;
	int m_iX0;
	int m_iY0;
	string m_sCamino;

public:

	char vec_bitmap[DIMX][DIMY];		// REVISAR: esta desprolijo, hacerlo privado
	bitmap() { 
		// inicializar vec_bitmap con "."
		for (int y = DIMY-1; y >= 0; y--) 
			for (int x = 0; x < DIMX; x++) 
				vec_bitmap[x][y] = '.';
	}
	int &nro() { return m_iNro; }
	int &x0() { return m_iX0; }
	int &y0() { return m_iY0; }
	string &camino() { return m_sCamino; }
	
};


////////////////////////////////////////////////////////////////////////////////
void mostrar_bmp(bitmap bmp)
{
	cout << "Bitmap #" << bmp.nro() << endl;
	for (int y = DIMY-1; y >= 0; y--) {
		for (int x = 0; x < DIMX; x++) 
			cout << bmp.vec_bitmap[x][y];
		cout << endl;
	}
	cout << endl;
}

////////////////////////////////////////////////////////////////////////////////
void procesar_bmp(bitmap bmp)
{
	// recorrer el string camino y colocar una X en la parte externa del camino

	int x = bmp.x0();
	int y = bmp.y0();

	for (int i = 0; i < bmp.camino().length(); i++) {
		char dir = bmp.camino().c_str()[i];
		switch (dir) {
		case 'N' :
			bmp.vec_bitmap[x][y] = X;
			y++;
			break;
		case 'S' :
			bmp.vec_bitmap[x-1][y-1] = X;
			y--;
			break;
		case 'E' :
			bmp.vec_bitmap[x][y-1] = X;
			x++;
			break;
		case 'W' :
			bmp.vec_bitmap[x-1][y] = X;
			x--;
			break;
		default:
			break;
		}

	}
	// REVISAR: al salir de esta funcion, bmp se mantiene intacto, pasar como referencia
	mostrar_bmp(bmp);
}

////////////////////////////////////////////////////////////////////////////////
//	PROGRAMA PRINCIPAL
////////////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{
	list<bitmap> lst_bitmaps;
	int cant_casos;

	cin >> cant_casos;
	// leer la entrada y guardar cada mapa en lst_bitmaps
	for (int caso = 1; (caso <= cant_casos) && (!cin.eof()); caso++) {
		bitmap bmp;
		bmp.nro() = caso;
		cin >> bmp.x0() >> bmp.y0();
		cin >> bmp.camino();
		lst_bitmaps.push_back(bmp);
	}

	// procesar cada mapa
	for_each(lst_bitmaps.begin(), lst_bitmaps.end(), procesar_bmp);

	return 0;
}

