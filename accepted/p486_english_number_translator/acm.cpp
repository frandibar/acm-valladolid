
/* @JUDGE_ID:  40922FK  486  C++  */
    
/******************************************************************************
 Solution to Problem 486 - English-Number Translator
 by: Francisco Dibar
 date: May-19-2004
******************************************************************************/

#include <iostream>
#include <queue>
#include <string>
#include <sstream>
#include <map>

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

#define H	100
#define T	1000
#define M	1000000

using namespace std;

typedef map<string, int> map_str_i;

////////////////////////////////////////////////////////////////////////////////
void init_map_palabras(map_str_i& map_palabras)
// inicializa el mapa asociativo con las palabras y sus valores
{
	// el maximo valor a reconocer es 999.999.999.999
	map_palabras.insert(map_str_i::value_type("negative", -1));
	map_palabras.insert(map_str_i::value_type("zero", 0));
	map_palabras.insert(map_str_i::value_type("one", 1));
	map_palabras.insert(map_str_i::value_type("two", 2));
	map_palabras.insert(map_str_i::value_type("three", 3));
	map_palabras.insert(map_str_i::value_type("four", 4));
	map_palabras.insert(map_str_i::value_type("five", 5));
	map_palabras.insert(map_str_i::value_type("six", 6));
	map_palabras.insert(map_str_i::value_type("seven", 7));
	map_palabras.insert(map_str_i::value_type("eight", 8));
	map_palabras.insert(map_str_i::value_type("nine", 9));
	map_palabras.insert(map_str_i::value_type("ten", 10));
	map_palabras.insert(map_str_i::value_type("eleven", 11));
	map_palabras.insert(map_str_i::value_type("twelve", 12));
	map_palabras.insert(map_str_i::value_type("thirteen", 13));
	map_palabras.insert(map_str_i::value_type("fourteen", 14));
	map_palabras.insert(map_str_i::value_type("fifteen", 15));
	map_palabras.insert(map_str_i::value_type("sixteen", 16));
	map_palabras.insert(map_str_i::value_type("seventeen", 17));
	map_palabras.insert(map_str_i::value_type("eighteen", 18));
	map_palabras.insert(map_str_i::value_type("nineteen", 19));
	map_palabras.insert(map_str_i::value_type("twenty", 20));
	map_palabras.insert(map_str_i::value_type("thirty", 30));
	map_palabras.insert(map_str_i::value_type("forty", 40));
	map_palabras.insert(map_str_i::value_type("fifty", 50));
	map_palabras.insert(map_str_i::value_type("sixty", 60));
	map_palabras.insert(map_str_i::value_type("seventy", 70));
	map_palabras.insert(map_str_i::value_type("eighty", 80));
	map_palabras.insert(map_str_i::value_type("ninety", 90));
	map_palabras.insert(map_str_i::value_type("hundred", 100));
	map_palabras.insert(map_str_i::value_type("thousand", 1000));
	map_palabras.insert(map_str_i::value_type("million", 1000000));
}
////////////////////////////////////////////////////////////////////////////////
int64 letra_a_nro(map_str_i& map_palabras, string str_nro)
// devuelve el nro descripto por str_nro
// el maximo valor a reconocer es 999.999.999.999
{
	int64 nro = 0, 
		 pre = 0;
	int signo = 1;
	int miles = 0;
	istringstream ostr_nro(str_nro);

	while (!ostr_nro.eof()) {
		string str_token;
		ostr_nro >> str_token;
		int token = map_palabras[str_token];
		
		if (token == -1) 
			signo = -1;
		else {	
			if (token < H)
				pre += token;
			else {
				if (pre == 0) {
					if (token > miles) {
						nro *= token;
						miles = token;
					} else {
						pre += token;
						miles = token;
					}
				}
				else
					if (token > miles) {
						nro = (nro + pre) * token;
						miles = token;
						pre = 0;
					} else {
						if ((token == H) && (miles == M)) {
							pre *= token;
						} else {
							nro += pre * token;
							pre = 0;
						}
					}
			}
		}
	}
	if (miles == pre)
		return (signo * nro * pre);
	else
		return (signo * (nro + pre));
}

////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//	PROGRAMA PRINCIPAL
////////////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{
	queue<string> que_input;
	map_str_i map_palabras;
	string str_input;

	// leer la entrada
	getline(cin, str_input);	
	while (!cin.eof()) {
		que_input.push(str_input);
		getline(cin, str_input);	
	}		

	init_map_palabras(map_palabras);

	// procesar cada entrada
	while (!que_input.empty()) {
		str_input = que_input.front();
		que_input.pop();
		cout << letra_a_nro(map_palabras, str_input) << endl;
	}

	return 0;
}

