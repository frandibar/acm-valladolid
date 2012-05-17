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
//#define ONLINE_JUDGE 

#define HALT		-1

#define REGISTERS	10
#define WORDS		1000

#define MODULO		1000

using namespace std;
/*
////////////////////////////////////////////////////////////////////////////////
int getline(char *line, int max)
{
	if (fgets(line, max, stdin) == NULL)
		return 0;
	else
		return strlen(line);
}
*/
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
int execute(char *inst, int address, int *vec_registers, 
				char vec_ram[][3])
{
	switch (inst[0]) {
		case '1':	
			if (inst[2] == '0' && inst[3] == '0') return HALT;
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
			vec_registers[inst[1]-'0'] = atoi(vec_ram[vec_registers[inst[2]-'0']]); 
			break;

		case '9':	
			// 9sa: set the value in RAM whose address is in register a 
			// to the value of register s
			// vec_ram[vec_registers[inst[2]-'0']] = 
			//		vec_registers[inst[1]-'0']; 
			char str[3];
			itoa(vec_registers[inst[1]-'0'], str); 
			vec_ram[vec_registers[inst[2]-'0']][0] = str[0];
			vec_ram[vec_registers[inst[2]-'0']][1] = str[1];
			vec_ram[vec_registers[inst[2]-'0']][2] = str[2];
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
	char vec_ram[WORDS][3];		// guardo las instrucciones
	char line[80];
	char inst[3];

	int casos;
	cin >> casos;
	cin.getline(line, 80, '\n');	// terminar de leer la linea de los casos
	cin.getline(line, 80, '\n');	// saltear la linea en blanco

	for (int k = 0; k < casos; k++) {
		// inicializar vec_ram en 0
		for (int i = 0; i < WORDS; i++) {
			vec_ram[i][0] = '0';
			vec_ram[i][1] = '0';
			vec_ram[i][2] = '0';
		}
		
		// inicializar vec_registers en 0
		for (int j = 0; j < REGISTERS; j++)
			vec_registers[j] = 0;

		int executed = 0;
		int address = 0;
		cin.getline(line, 80, '\n');
		// saltear lineas en blanco de mas
		while (strlen(line) == 0)
			cin.getline(line, 80, '\n');
		// leer cada instruccion y volcarla en vec_ram
		// evitar espacios al principio y al final
		while (!cin.eof() && (strlen(line) > 0) && (address < WORDS)) {
			sscanf(line, "%3s", inst);
			vec_ram[address][0] = inst[0];
			vec_ram[address][1] = inst[1];
			vec_ram[address][2] = inst[2];
			address++;
			cin.getline(line, 80, '\n');
		}
		// ejecutar cada instruccion
		address = 0;
		while ((address != HALT) && (address < WORDS)) {
//		cout << "address " << address << " " << vec_ram[address] << endl;
			address = execute(vec_ram[address], address, vec_registers, vec_ram);
			executed++;
		}
		cout << executed << endl;
		if (k < casos - 1) cout << endl;
	}

	return 0;
}

/* @END_OF_SOURCE_CODE */

