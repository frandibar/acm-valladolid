//
// acm.cpp
//
// fecha y hora de comienzo:	02/01/04 07:00 pm
// fecha y hora de finalizac:	03/01/04 09:46 pm
// demora:						h
// observaciones: una misma cadena puede dar resultados distintos.

#include <fstream.h>	// manejo de archivos
#include <crtdbg.h>		// lagunas de memoria
#include <conio.h>		// para interceptar una tecla presionada	
#include <afx.h>		// para interceptar una tecla presionada	
#include <string.h>		// manejo de strings
#include "cadn.h"

#define FIN_INPUT	'*'

int main(int argc, char* argv[])
{{
/*	if (argc != 2) {
		cerr << "Uso: acm archivo_entrada";
		return -1;
	}
	// abrir el archivo de entrada
	ifstream is(argv[1], ios::in|ios::nocreate);
*/	ifstream is("input.txt");
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

	CString linea;
	char *p_linea = linea.GetBuffer(MAX_LEN);
	
	// recorrer el archivo de entrada
	is.getline(p_linea, MAX_LEN);		// leer la linea
	while (!is.eof() && (p_linea[0] != FIN_INPUT)) {
		linea.ReleaseBuffer();
		CAdn adn(linea);
		linea = adn.Proteina();
		p_linea = linea.GetBuffer(MAX_LEN);
		os.write(p_linea, strlen(p_linea));
		os.put('\n');
		is.getline(p_linea, MAX_LEN);		// leer la linea
	}
	linea.ReleaseBuffer();
	os.close();
	is.close();
}
	// verificar si hay lagunas de memoria (hay lagunas por el simple hecho de declarar un cstring)
	if (_CrtDumpMemoryLeaks()) {
		cerr << "Hay lagunas de memoria\n";
		_getch();
	} else {
		cerr << "OK: No hay lagunas de memoria\n";
		_getch();
	}

	return 0;
}

