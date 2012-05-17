//
// p1_wacmian.cpp
//
// fecha y hora de comienzo:	24/12/03 7:30 pm
// fecha y hora de finalizac:	24/12/03 8:40 pm
// demora:						1 h
// observaciones: es un problema muy sencillo. la demora se debio al uso del lenguaje

#include <iostream.h>
#include <fstream.h>	// manejo de archivos
#include <string.h>		// funcion strlen
#include <stdlib.h>		// funcion itoa

#define CERO		'%'
#define UNO			')'
#define DOS			'~'
#define TRES		'@'
#define CUATRO		'?'
#define CINCO		'\\'
#define MENOS_UNO	'$'
#define FIN_INPUT	'#'	

char *descifrar(char *nro_wac)
{
	char *nro_dec = new char(10);
	int dec = 0;
	int pot = 0;
	for (int i=strlen(nro_wac)-1; i >= 0; i--) {
		int nro;
		switch (nro_wac[i]) {
			case CERO:		nro = 0;	break;
			case UNO:		nro = 1;	break;
			case DOS:		nro = 2;	break;
			case TRES:		nro = 3;	break;
			case CUATRO:	nro = 4;	break;
			case CINCO:		nro = 5;	break;
			case MENOS_UNO: nro = -1;	break;
		}
		(i == strlen(nro_wac)-1 ? pot = 1 : pot *=6);
		dec += pot*nro;
	}
	itoa(dec,nro_dec,10);	// convertir a string
	return nro_dec;
}

int main(int argc, char* argv[])
{
/*	if (argc != 2) {
		cerr << "Uso: p1_wacmian archivo_entrada";
		return -1;
	}
*/	// abrir el archivo de entrada
//	ifstream is(argv[1], ios::in|ios::nocreate);
	ifstream is("input.txt");
	if (!is) {
		cerr << "No se puede abrir el archivo\n";
		return -1;
	}

	// abrir el archivo de salida
	ofstream os("salida.txt");
	if (!os) {
		cerr << "No se puede abrir el archivo\n";
		return -1;
	}

	char *nro_wac = new char(10);
	char *nro_dec = new char(10);
	// recorrer el archivo de entrada
	is.getline(nro_wac,10);		// leer la linea
	while ((!is.eof()) && (nro_wac[0] != FIN_INPUT)) {
		nro_dec = descifrar(nro_wac);
		os.write(nro_dec,strlen(nro_dec));
		os.put('\n');
		is.getline(nro_wac,10);		// leer la linea
	}
/*	delete nro_wac; 
	delete nro_dec;
*/	
	return 0;
}
