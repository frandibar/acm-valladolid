//
// p2_cd_titles.cpp
//
// fecha y hora de comienzo:	28/12/03 4:10 pm
// fecha y hora de finalizac:	28/12/03 5:10 pm
// demora:						1 h
// observaciones: es un problema muy sencillo.

#include <iostream.h>
#include <fstream.h>	// manejo de archivos
#include <string.h>		// funcion strlen
#include <stdlib.h>		// funcion itoa

#define FIN_INPUT	'#'	

char mat_salida[36][50];

void init_mat_salida()
{
	for (int i=0; i < 36; i++)
		for (int j=0; j < 36; j++)
			mat_salida[i][j]=' ';
}

void hacer_vertical(char *title, int col)
{
	for (int i=0; i < strlen(title); i++) 
		mat_salida[i][col] = title[i];
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

	char *title = new char(36);
	init_mat_salida();
	// recorrer el archivo de entrada
	int cont_entrada = 0;		// cuenta las lineas de entrada (max = 50)
	is.getline(title,100);		// leer la linea
	while ((!is.eof()) && (title[0] != FIN_INPUT) && cont_entrada <= 50) {
		hacer_vertical(title, cont_entrada);
		cont_entrada++;
		is.getline(title,100);		// leer la linea
	}		
	char separador_horiz[2*50];
	
	for (int k=0; k < 2*cont_entrada; k++)
		separador_horiz[k]='-';
	
	os.write(separador_horiz, 2*cont_entrada);			
	os.put('\n');			
	for (int i=0; i < 36; i++) {
		char linea_sal[2*50+1] = {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
								' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
								' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
								' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
								' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
								' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
								' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
								' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
								' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
								' ',' ',' ',' ',' ',' ',' ',' ',' ',' '};
		for (int j=0; j < cont_entrada; j++) {
			linea_sal[2*j] = mat_salida[i][j];
			linea_sal[2*j+1] = '|';		// separador
		}			
		os.write(linea_sal,strlen(linea_sal));			
		os.put('\n');
	}
	os.write(separador_horiz, 2*cont_entrada);			
	os.put('\n');
	os.close;
	return 0;
}
