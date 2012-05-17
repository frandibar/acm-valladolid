/* @JUDGE_ID:  40922FK  10033  C++  */
    
/******************************************************************************
 Solution to Problem 10033 - Interpreter
 by: Francisco Dibar
 date: Aug-15-2004
******************************************************************************/
/* @BEGIN_OF_SOURCE_CODE */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
//#define ONLINE_JUDGE 

#define HALT		-1

#define REGISTERS	10
#define WORDS		1000

#define MODULO		1000

using namespace std;

////////////////////////////////////////////////////////////////////////////////

int execute(string inst, int address, int vec_registers[], string vec_ram[])
{
	switch (inst[0]) {
		case '1':	if (inst == "100")
							return HALT;
						break;
		case '2':	// 2dn: set register d to n
						vec_registers[inst[1]-'0'] = inst[2]-'0'; 
						break;
		case '3':	// 3dn: add n to register d
						vec_registers[inst[1]-'0'] += inst[2]-'0'; 
						vec_registers[inst[1]-'0'] %= MODULO; 
						break;
		case '4':	// 4dn: multiply register d by n
						vec_registers[inst[1]-'0'] *= inst[2]-'0'; 
						vec_registers[inst[1]-'0'] %= MODULO; 
						break;
		case '5':	// 5ds: set register d to the value of register s
						vec_registers[inst[1]-'0'] = vec_registers[inst[2]-'0']; 
						break;
		case '6':	// 6ds: add the value of register s to register d
						vec_registers[inst[1]-'0'] += vec_registers[inst[2]-'0']; 
						vec_registers[inst[1]-'0'] %= MODULO; 
						break;
		case '7':	// 7ds: multiply register d by the value of register s
						vec_registers[inst[1]-'0'] *= vec_registers[inst[2]-'0']; 
						vec_registers[inst[1]-'0'] %= MODULO; 
						break;
		case '8':	// 8da: set register d to the value in RAM whose address is in register a
						vec_registers[inst[1]-'0'] = atoi(vec_ram[vec_registers[inst[2]-'0']].c_str()); 
						break;
		case '9':	// 9sa: set the value in RAM whose address is in register a to the value of register s
						//vec_ram[vec_registers[inst[2]-'0']] = vec_registers[inst[1]-'0']; 
						char str[3];
						itoa(vec_registers[inst[1]-'0'], str, 10); 
						vec_ram[vec_registers[inst[2]-'0']] = str;
						break;
		case '0':	// 0ds: goto the location in register d unless register s contains 0
						if (vec_registers[inst[2]-'0'] != 0)
							return vec_registers[inst[1]-'0'];
						break;
	}
	return address+1;
}

////////////////////////////////////////////////////////////////////////////////
//	PROGRAMA PRINCIPAL
////////////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{
	// redireccionar la entrada y salida
	#ifndef ONLINE_JUDGE 
		cin.rdbuf((new ifstream("input.txt"))->rdbuf()); 
		cout.rdbuf((new ofstream("output.txt"))->rdbuf()); 
	#endif 

	ostringstream os_output;
	int vec_registers[REGISTERS];
	string vec_ram[WORDS];
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
		getline(cin, inst);
		// leer cada instruccion y volcarla en vec_ram
		while (!inst.empty() && !cin.eof()) {
			vec_ram[address++] = inst;
			getline(cin, inst);
		}
		// ejecutar cada instruccion
		address = 0;
		while (address != HALT) {
			address = execute(vec_ram[address], address, vec_registers, vec_ram);
			executed++;
		}
		os_output << executed << endl;
		if (k < casos - 1) os_output << endl;
	}

	cout << os_output.str();
	return 0;
}

/* @END_OF_SOURCE_CODE */

