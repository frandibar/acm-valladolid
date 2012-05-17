
/* @JUDGE_ID:  40922FK  197  C++  */
    
/******************************************************************************
 Solution to Problem 197 - Cube
 by: Francisco Dibar
 date: Mar-15-2004
******************************************************************************/

#include <iostream>
#include <string>
#include <list>
#include <algorithm>

#define LADO	3
#define DIM		27	// LADO*LADO*LADO

#define DEC		-1
#define INC		1

#define V		'.'

#define PIEZA_A		'a'
#define PIEZA_B		'b'
#define PIEZA_C		'c'
#define PIEZA_D		'd'
#define PIEZA_E		'e'
#define PIEZA_F		'f'
#define PIEZA_G		'g'

#define CUBITOS_PIEZA_A		4
#define CUBITOS_PIEZA_B		3
#define CUBITOS_PIEZA_C		4
#define CUBITOS_PIEZA_D		4
#define CUBITOS_PIEZA_E		4
#define CUBITOS_PIEZA_F		4
#define CUBITOS_PIEZA_G		4

using namespace std;
enum ejes { X, Y, Z };

////////////////////////////////////////////////////////////////////////////////
int cubitos(char pieza) {
	switch (pieza) {
		case PIEZA_A: return CUBITOS_PIEZA_A; break;
		case PIEZA_B: return CUBITOS_PIEZA_B; break;
		case PIEZA_C: return CUBITOS_PIEZA_C; break;
		case PIEZA_D: return CUBITOS_PIEZA_D; break;
		case PIEZA_E: return CUBITOS_PIEZA_E; break;
		case PIEZA_F: return CUBITOS_PIEZA_F; break;
		case PIEZA_G: return CUBITOS_PIEZA_G; break;
		default: return 0; break;
	}
}	

////////////////////////////////////////////////////////////////////////////////
string trasladar(string cubo, ejes e, int inc, char pieza)
{
	string nuevo = cubo;
	int i;
	switch (e) {
	case X:
		switch (inc) {
		case -1:
			for (i = 0; i < DIM; i++) 
				if ((i - 2) % LADO != 0) 
					nuevo[i] = cubo[i + 1];
				else
					nuevo[i] = V;
			break;

		case 1:
			for (i = 0; i < DIM; i++) 
				if (i % LADO != 0) 
					nuevo[i] = cubo[i - 1];
				else
					nuevo[i] = V;
			break;

		default:
			break;
		}
		break;

	case Y:
		switch (inc) {
		case -1:
			for (i = 0*LADO; i < 2*LADO; i++) 
				nuevo[i] = cubo[i + LADO];
			for (i = 2*LADO; i < 3*LADO; i++) 
				nuevo[i] = V;
			for (i = 3*LADO; i < 5*LADO; i++) 
				nuevo[i] = cubo[i + LADO];
			for (i = 5*LADO; i < 6*LADO; i++) 
				nuevo[i] = V;
			for (i = 6*LADO; i < 8*LADO; i++) 
				nuevo[i] = cubo[i + LADO];
			for (i = 8*LADO; i < 9*LADO; i++) 
				nuevo[i] = V;
			break;

		case 1:
			for (i = 0*LADO; i < 1*LADO; i++) 
				nuevo[i] = V;
			for (i = 1*LADO; i < 3*LADO; i++) 
				nuevo[i] = cubo[i - LADO];
			for (i = 3*LADO; i < 4*LADO; i++) 
				nuevo[i] = V;
			for (i = 4*LADO; i < 6*LADO; i++) 
				nuevo[i] = cubo[i - LADO];
			for (i = 6*LADO; i < 7*LADO; i++) 
				nuevo[i] = V;
			for (i = 7*LADO; i < 9*LADO; i++) 
				nuevo[i] = cubo[i - LADO];
			break;

		default:
			break;
		}
		break;

	case Z:
		int i;
		switch (inc) {
		case -1:
			for (i = 0*LADO; i < 3*LADO; i++) 
				nuevo[i] = V;
			for (i = 3*LADO; i < 9*LADO; i++) 
				nuevo[i] = cubo[i - 3*LADO];
			break;

		case 1:
			for (i = 0*LADO; i < 6*LADO; i++) 
				nuevo[i] = cubo[i + 3*LADO];
			for (i = 6*LADO; i < 9*LADO; i++) 
				nuevo[i] = V;
			break;

		default:
			break;
		}
		break;

	default:
		break;
	}
	// chequear que la pieza no sale del cubo
	if (count(nuevo.begin(), nuevo.end(), pieza) == cubitos(pieza))
		return nuevo;
	else
		return "";
}

////////////////////////////////////////////////////////////////////////////////
string rotar(string cubo, ejes e)
{
	string nuevo = cubo;
	
	switch (e) {
	case X:
		nuevo.replace(0*LADO, LADO, cubo.substr(6,LADO));
		nuevo.replace(1*LADO, LADO, cubo.substr(15,LADO));
		nuevo.replace(2*LADO, LADO, cubo.substr(24,LADO));
		nuevo.replace(3*LADO, LADO, cubo.substr(3,LADO));
		//nuevo.replace(4*LADO, LADO, cubo.substr(12,LADO));	se mantiene igual
		nuevo.replace(5*LADO, LADO, cubo.substr(21,LADO));
		nuevo.replace(6*LADO, LADO, cubo.substr(0,LADO));
		nuevo.replace(7*LADO, LADO, cubo.substr(9,LADO));
		nuevo.replace(8*LADO, LADO, cubo.substr(18,LADO));
		break;

	case Y:
		nuevo[0] = cubo[18];
		nuevo[1] = cubo[9];
		nuevo[2] = cubo[0];
		nuevo[3] = cubo[21];
		nuevo[4] = cubo[12];
		nuevo[5] = cubo[3];
		nuevo[6] = cubo[24];
		nuevo[7] = cubo[15];
		nuevo[8] = cubo[6];
		nuevo[9] = cubo[19];
		nuevo[10] = cubo[10];
		nuevo[11] = cubo[1];
		nuevo[12] = cubo[22];
		nuevo[13] = cubo[13];
		nuevo[14] = cubo[4];
		nuevo[15] = cubo[25];
		nuevo[16] = cubo[16];
		nuevo[17] = cubo[7];
		nuevo[18] = cubo[20];
		nuevo[19] = cubo[11];
		nuevo[20] = cubo[2];
		nuevo[21] = cubo[23];
		nuevo[22] = cubo[14];
		nuevo[23] = cubo[5];
		nuevo[24] = cubo[26];
		nuevo[25] = cubo[17];
		nuevo[26] = cubo[8];
		break;

	case Z:
		nuevo[0] = cubo[2];
		nuevo[1] = cubo[5];
		nuevo[2] = cubo[8];
		nuevo[3] = cubo[1];
		nuevo[4] = cubo[4];
		nuevo[5] = cubo[7];
		nuevo[6] = cubo[0];
		nuevo[7] = cubo[3];
		nuevo[8] = cubo[6];
		nuevo[9] = cubo[11];
		nuevo[10] = cubo[14];
		nuevo[11] = cubo[17];
		nuevo[12] = cubo[10];
		nuevo[13] = cubo[13];
		nuevo[14] = cubo[16];
		nuevo[15] = cubo[9];
		nuevo[16] = cubo[12];
		nuevo[17] = cubo[15];
		nuevo[18] = cubo[20];
		nuevo[19] = cubo[23];
		nuevo[20] = cubo[26];
		nuevo[21] = cubo[19];
		nuevo[22] = cubo[22];
		nuevo[23] = cubo[25];
		nuevo[24] = cubo[18];
		nuevo[25] = cubo[21];
		nuevo[26] = cubo[24];
		break;
	
	default:
		break;
	}
	return nuevo;
}

////////////////////////////////////////////////////////////////////////////////
string rotar(string cubo, ejes e, int n)
{
	for (int i=0; i<n; i++)
		cubo = rotar(cubo, e);
	return cubo;
}


////////////////////////////////////////////////////////////////////////////////
//	PROGRAMA PRINCIPAL
////////////////////////////////////////////////////////////////////////////////
void print(const string& s)
{
	cout << s << endl;
}
int main(int argc, char *argv[])
{
	char pieza;
	cin >> pieza;
	
	string cubo;
	switch (pieza) {
		case PIEZA_A: cubo = "aa.a..a....................";	break;
		case PIEZA_B: cubo = "bb.b.......................";	break;
		case PIEZA_C: cubo = "c..cc.c....................";	break;
		case PIEZA_D: cubo = ".d.dd.d....................";	break;
		case PIEZA_E: cubo = "ee.e.....e.................";	break;
		case PIEZA_F: cubo = "ff.f........f..............";	break;
		case PIEZA_G: cubo = "gg.g......g................";	break;
		default: return 0; break;
	}

	list<string> lst_posiciones;
	list<string> lst_faltantes;
	
	lst_faltantes.push_back(cubo);
	while (!lst_faltantes.empty()) {
		cubo = lst_faltantes.front();
		lst_faltantes.pop_front();
		if (count(lst_posiciones.begin(), lst_posiciones.end(), cubo) == 0)
			lst_posiciones.push_back(cubo);
		
		string nuevo = trasladar(cubo,X,DEC,pieza);
		if ((nuevo != "") && (count(lst_posiciones.begin(), lst_posiciones.end(), nuevo) == 0)) 
			lst_faltantes.push_back(nuevo);

		nuevo = trasladar(cubo,X,INC,pieza);
		if ((nuevo != "") && ( count(lst_posiciones.begin(), lst_posiciones.end(), nuevo) == 0))  
			lst_faltantes.push_back(nuevo);

		nuevo = trasladar(cubo,Y,DEC,pieza);
		if ((nuevo != "") && ( count(lst_posiciones.begin(), lst_posiciones.end(), nuevo) == 0))  
			lst_faltantes.push_back(nuevo);

		nuevo = trasladar(cubo,Y,INC,pieza);
		if ((nuevo != "") && ( count(lst_posiciones.begin(), lst_posiciones.end(), nuevo) == 0))  
			lst_faltantes.push_back(nuevo);

		nuevo = trasladar(cubo,Z,DEC,pieza);
		if ((nuevo != "") && ( count(lst_posiciones.begin(), lst_posiciones.end(), nuevo) == 0))  
			lst_faltantes.push_back(nuevo);

		nuevo = trasladar(cubo,Z,INC,pieza);
		if ((nuevo != "") && ( count(lst_posiciones.begin(), lst_posiciones.end(), nuevo) == 0))  
			lst_faltantes.push_back(nuevo);
		
		for (int i = 0; i < 4; i++) {
			nuevo = rotar(cubo,X,i);
			if ((nuevo != "") && ( count(lst_posiciones.begin(), lst_posiciones.end(), nuevo) == 0))  
				lst_faltantes.push_back(nuevo);

			nuevo = rotar(cubo,Y,i);
			if ((nuevo != "") && ( count(lst_posiciones.begin(), lst_posiciones.end(), nuevo) == 0))  
				lst_faltantes.push_back(nuevo);

			nuevo = rotar(cubo,Z,i);
			if ((nuevo != "") && ( count(lst_posiciones.begin(), lst_posiciones.end(), nuevo) == 0))  
				lst_faltantes.push_back(nuevo);
		}
	}

	for_each(lst_posiciones.begin(), lst_posiciones.end(), print);

	return 0;
}

