/* @JUDGE_ID:  40922FK  10033  C++  */
    
/*************************************************************************
 Solution to Problem 10033 - Interpreter
 by: Francisco Dibar
 date: Jul-12-2005
**************************************************************************/
/* @BEGIN_OF_SOURCE_CODE */

#include <iostream>
#ifndef ONLINE_JUDGE 
	#include <fstream>
#endif 
#include <string>
#include <sstream>
//#define ONLINE_JUDGE 

#define HALT		-1

#define REGISTERS	10
#define WORDS		1010

#define MODULO		1000

using namespace std;

////////////////////////////////////////////////////////////////////////////////
void reverse(char s[])
{
	int c, i, j;
	for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}

////////////////////////////////////////////////////////////////////////////////
void itoa(int n, char s[])
{
	int i, sign;

	if ((sign = n) < 0)
		n = -n;
	i = 0;
	do {
		s[i++] = n % 10 + '0';
	} while ((n /= 10) > 0);
	if (sign < 0)
		s[i++] = '-';
	s[i] = '\0';
	reverse(s);
}

///////////////////////////////////////////////////////////////////////////
int execute(string inst, int address, int vec_registers[], 
				string vec_ram[])
{
	switch (inst[0]) {
		case '1':	
			if (inst == "100") return HALT;
			break;

		case '2':	
			// 2dn: set register d to n
			vec_registers[inst[1]-'0'] = inst[2]-'0'; 
			break;

		case '3':	
			
			// 3dn: add n to register d
			vec_registers[inst[1]-'0'] += inst[2]-'0'; 
			vec_registers[inst[1]-'0'] %= MODULO; 
			break;
		
		case '4':	
			
			// 4dn: multiply register d by n
			vec_registers[inst[1]-'0'] *= inst[2]-'0'; 
			vec_registers[inst[1]-'0'] %= MODULO; 
			break;

		case '5':	
			// 5ds: set register d to the value of register s
			vec_registers[inst[1]-'0'] = vec_registers[inst[2]-'0']; 
			break;

		case '6':	
			// 6ds: add the value of register s to register d
			vec_registers[inst[1]-'0'] += vec_registers[inst[2]-'0']; 
			vec_registers[inst[1]-'0'] %= MODULO; 
			break;

		case '7':	
			// 7ds: multiply register d by the value of register s
			vec_registers[inst[1]-'0'] *= vec_registers[inst[2]-'0']; 
			vec_registers[inst[1]-'0'] %= MODULO; 
			break;

		case '8':	
			// 8da: set register d to the value in RAM 
			//whose address is in register a
			vec_registers[inst[1]-'0'] = atoi(vec_ram[vec_registers[inst[2]-'0']].c_str()); 
			break;

		case '9':	
			// 9sa: set the value in RAM whose address is in register a 
			// to the value of register s
			// vec_ram[vec_registers[inst[2]-'0']] = 
			//		vec_registers[inst[1]-'0']; 
			char str[3];
			itoa(vec_registers[inst[1]-'0'], str); 
			vec_ram[vec_registers[inst[2]-'0']] = str;
			break;

		case '0':	
			// 0ds: goto the location in register d unless 
			// register s contains 0
			if (vec_registers[inst[2]-'0'] != 0)
				return vec_registers[inst[1]-'0'];
			break;
	}
	return address + 1;
}

//////////////////////////////////////////////////////////////////////////
//	PROGRAMA PRINCIPAL
//////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{
	// redireccionar la entrada y salida
	#ifndef ONLINE_JUDGE 
		cin.rdbuf((new ifstream("input.txt"))->rdbuf()); 
		cout.rdbuf((new ofstream("output.txt"))->rdbuf()); 
	#endif 

	int vec_registers[REGISTERS];		// registros
	string vec_ram[WORDS];	// guardo las instrucciones
	string inst;

	int casos;
	cin >> casos;
	getline(cin, inst);	// terminar de leer la linea de los casos
	getline(cin, inst);	// saltear la linea en blanco

	for (int k = 0; k < casos; k++) {

		// inicializar vec_ram en 0
		for (int i = 0; i < WORDS; i++)
			vec_ram[i] = "000";

		// inicializar vec_registers en 0
		for (int j = 0; j < REGISTERS; j++)
			vec_registers[j] = 0;

		int executed = 0;
		int address = 0;
		inst = "";
		getline(cin, inst);
		// saltear lineas en blanco de mas
		while (inst.size() <= 1 && !cin.eof())
			getline(cin, inst);
		// leer cada instruccion y volcarla en vec_ram
		while (inst.size() > 1 && !cin.eof()) {
			// evitar espacios al principio y al final
			istringstream is(inst);
			is >> inst;
			vec_ram[address++] = inst;
			getline(cin, inst);
		}
		// ejecutar cada instruccion
		address = 0;
		while (address != HALT) {
			address = execute(vec_ram[address], address, vec_registers, vec_ram);
			executed++;
		}
		cout << executed << endl;
		if (k < casos - 1) cout << endl;
	}

	return 0;
}

/* @END_OF_SOURCE_CODE */

