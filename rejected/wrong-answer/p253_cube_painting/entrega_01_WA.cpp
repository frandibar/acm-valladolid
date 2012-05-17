
/* @JUDGE_ID:  40922FK  253  C++  */
    
/******************************************************************************
 Solution to Problem 253 - Cube painting
 by: Francisco Dibar
 date: Apr-05-2004
******************************************************************************/

#include <iostream>
#include <list>
#include <string>
#include <algorithm>
#include <map>

#define F	"FALSE"
#define T	"TRUE"

#define xi	0
#define xd	1
#define yi	2
#define yd	3
#define zi	4
#define zd	5

using namespace std;

////////////////////////////////////////////////////////////////////////////////
string rotar(string cubo, int eje)
{
	//					012345
	// estado inicial: "WOBRYG"
	string aux;
	switch (eje) {
	case xi:
		// estado final "RWOBYG"
		aux = cubo[3] + cubo.substr(0,3) + cubo.substr(4,2); 
		break;
	case xd:
		// estado final "OBRWYG"
		aux = cubo.substr(1,3) + cubo[0] + cubo.substr(4,2); 
		break;
	case yi:
		// estado final "GOYRWB"
		// escribo cubo.substr() en vez de cubo[] al menos una vez para que lo interprete bien
		aux = cubo.substr(5,1) + cubo[1] + cubo[4] + cubo[3] + cubo[0] + cubo[2];  
		break;
	case yd:
		// estado final "YOGRBW"
		aux = cubo.substr(4,1) + cubo[1] + cubo[5] + cubo[3] + cubo[2] + cubo[0];  
		break;
	case zi:
		// estado final "WYBGRO"
		aux = cubo.substr(0,1) + cubo[4] + cubo[2] + cubo[5] + cubo[3] + cubo[1];  
		break;
	case zd:
		// estado final "WGBYOR"
		aux = cubo.substr(0,1) + cubo[5] + cubo[2] + cubo[4] + cubo[1] + cubo[3];  
		break;
	default:
		break;
	}
	return aux;
}

////////////////////////////////////////////////////////////////////////////////
bool transformacion_posible(string antes, string despues)
{
	list<string> lst_falta_revisar;
	map<string, int> map_vistos;

	string proximo = antes;
	lst_falta_revisar.push_back(antes);
	while ((!lst_falta_revisar.empty()) && (proximo != despues)) {
		proximo = lst_falta_revisar.front();
		lst_falta_revisar.pop_front();
		map_vistos[proximo] = true;
		for (int e = xi; (e <= zd) && (proximo != despues); e++) {
			proximo = rotar(proximo, e);
			// si proximo no esta en map_vistos, agregarlo a lst_falta_revisar
			if (map_vistos.find(proximo) == map_vistos.end())
				lst_falta_revisar.push_back(proximo);
		}
	}

	if (proximo == despues)
		return true;
	else
		return false;
}

////////////////////////////////////////////////////////////////////////////////
void analizar_cubo(string input)
{
	string antes, despues;
	antes = input.substr(0,6);
	despues = input.substr(6,6);

	// la primera forma para determinar es contar las ocurrencias de cada color
	// antes y despues.	
	if ((count(antes.begin(), antes.end(),'r') != count(despues.begin(), despues.end(),'r')) ||
		(count(antes.begin(), antes.end(),'g') != count(despues.begin(), despues.end(),'g')) ||
		(count(antes.begin(), antes.end(),'b') != count(despues.begin(), despues.end(),'b')))
		cout << F << endl;
	else
		if (transformacion_posible(antes, despues))
			cout << T << endl;
		else
			cout << F << endl;
}

////////////////////////////////////////////////////////////////////////////////
//	PROGRAMA PRINCIPAL
////////////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{
	// leer la entrada
	string input;
	list<string> lst_input;

	cin >> input;
	while (!cin.eof()) {
		lst_input.push_back(input);
		cin >> input;
	}

	// analizar cada entrada
	for_each(lst_input.begin(), lst_input.end(), analizar_cubo);

	return 0;
}

