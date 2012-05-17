
/* @JUDGE_ID:  40922FK  177  C++  */
    
/******************************************************************************
 Solution to Problem 177 - Paper Folding
 by: Francisco Dibar
 date: Mar-11-2004
******************************************************************************/

#include <iostream>
#include <queue>
#include <vector>
#include <cmath>

using namespace std;

#define B  ' '
#define H  '_'
#define V  '|'
#define FIN  '^'

enum direccion { U, D, L, R };

////////////////////////////////////////////////////////////////////////////////
//	PROGRAMA PRINCIPAL
////////////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{
	int n;
	queue<int> que_input;
	// leer el input y volcarlo a la cola que_input
	cin >> n;		// 1 <= n <= 13	
	while (n) {
		que_input.push(n);
		cin >> n;
	}
	// resolver para cada valor del input
	while (!que_input.empty()) {
		n = que_input.front();
		que_input.pop();
		
		// resolver pliegue para n
		int dim = (int)pow(2,n);
		direccion *vec = new direccion[dim];
		
		if (!vec) {
			cerr << "memoria insuficiente";
			return -1;
		}
		
		vec[0] = R;
		for (int m = 0; m < n; m++) {
			int desde = (int)pow(2,m)-1;
			for (int i = desde; i >= 0; i--) {
				int j = 2*desde + 1 - i;
				switch(vec[i]) {
					case U:	vec[j] = L; break;
					case R:	vec[j] = U; break;
					case L:	vec[j] = D; break;
					case D:	vec[j] = R; break;
					default: break;
				}
			}
		}
		// hasta aca vec contiene el pliegue, ahora falta dibujarlo
		// dibujar_pliegue(vec, n);

		int off_left = 0, 
			off_up = 0,
			desp_h = 0,
			desp_v = 0,
			max_x = 0, 
			max_y = 0,
			dim_x = 0,	// dim_x = max_x - off_left
			dim_y = 0;	// dim_y = max_y - off_up

		// hacer una recorrida a vec para determinar off_left y off_up, que son el 
		// desplazamiento a derecha y hacia abajo desde donde hay que comenzar para
		// que no se vaya del borde
		// ademas se obtienen dim_x y dim_y que son las dimensiones del dibujo
		// el desplazamiento vertical crece hacia abajo, y el horizontal hacia la derecha
		for (int k = 0; k < dim; k++) {
			if (k < dim-1) {
				switch(vec[k]) {
					case U:	
						desp_v--;
						if (vec[k+1] == L) desp_h--;
						if (vec[k+1] == R) desp_h++;
						break;
					case R:	
						desp_h++; 
						if (vec[k+1] == D) desp_v++;
						break;
					case L:	
						desp_h--; 
						if (vec[k+1] == D) desp_v++;
						break;
					case D:	
						if (vec[k+1] == L) desp_h--;
						if (vec[k+1] == R) desp_h++;
						break;
					default: break;
				}			
			} 
			// guardar el maximo desplazamiento
			if (desp_h < off_left) off_left = desp_h; 
			if (desp_v < off_up) off_up = desp_v; 

			if (desp_h > max_x) max_x = desp_h; 
			if (desp_v > max_y) max_y = desp_v; 
		}

		dim_x = max_x - off_left + 1;
		dim_y = max_y - off_up + 1;

		// declaro la matriz mat de dim_x * dim_y
		vector< vector<char> >mat(dim_x, vector<char>(dim_y));

		// inicializar mat con espacios en blanco
		for (int x = 0; x < dim_x; x++)
			for (int y = 0; y < dim_y; y++)
				mat[x][y] = B;

		// recorro nuevamente vec, pero ahora dibujando en la matriz
		desp_h = -off_left;
		desp_v = -off_up;
		for (int t = 0; t < dim; t++) {
			if (t < dim-1) {
				switch(vec[t]) {
					case U:							
						mat[desp_h][desp_v] = V;
						desp_v--;
						if (vec[t+1] == L) desp_h--;
						if (vec[t+1] == R) desp_h++;
						break;
					case R:	
						mat[desp_h][desp_v] = H;
						desp_h++; 
						if (vec[t+1] == D) desp_v++;
						break;
					case L:	
						mat[desp_h][desp_v] = H;
						desp_h--; 
						if (vec[t+1] == D) desp_v++;
						break;
					case D:	
						mat[desp_h][desp_v] = V;
						if (vec[t+1] == L) desp_h--;
						if (vec[t+1] == R) desp_h++;
						break;
					default: break;
				}			
			} else {
				switch(vec[t]) {
					case U:
					case D:	
						mat[desp_h][desp_v] = V; break;
					case R:
					case L:	
						mat[desp_h][desp_v] = H; break;
					default: break;
				}			
			}
		}
		
		// mostrar el resultado
		for (int y = 0; y < dim_y; y++) {
			for (int x = 0; x < dim_x; x++)
				cout << mat[x][y];
			cout << endl;
		}

		cout << FIN << endl;
		delete []vec;
	}
	return 0;
}

/*//////////////////////////////////////////////////////////////////////////////
Procedimiento:

	El pliege se representa en un vector, donde cada elemento representa un lado.
	las direcciones de cada lado pueden ser U(up),D(down),L(left) y R(right)
	para N pliegues se tienen 2^N lados
	por ejemplo, para 1 pliegue, se tiene RU (siempre empieza con R)
	para 2 plieges, se tiene RULU
	el metodo consiste en resolver sucesivamente cada pliegue. (de n=0 a n=N)
	se empieza con un vector de 1 solo elemento (2^0): R
	luego se recorre el vector en sentido inverso, y se van agregando nuevos lados
	de acuerdo a la siguiente transformacion:
	U -> L
	R -> U
	L -> D
	D -> R
	se tiene entonces para N=1: RU
	para N=2, comienzo a barrer desde atras, la U pasa a L entonces agrego RUL,
	luego la R pasa a U entonces obtengo RULU
	para N=3, hago lo mismo, barro RULU en sentido contrario y agrego LDLU al final,
	con lo que obtengo RULULDLU.

//////////////////////////////////////////////////////////////////////////////*/
