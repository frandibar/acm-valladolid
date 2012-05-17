/* @JUDGE_ID:  40922FK  346  C++  */
    
/**************************************************************************
 Solution to Problem 346 - Getting Chorded
 by: Francisco Dibar
 date: Dec-29-2004
**************************************************************************/
/* @BEGIN_OF_SOURCE_CODE */

//#define ONLINE_JUDGE 
#include <iostream>
#ifndef ONLINE_JUDGE 
	#include <fstream>
#endif 
#include <string>

using namespace std;
/*
	Codificacion empleada

			0	Ab
			1	A
		Bb	2	A#
			3	B
			4	
			5	C
		Db	6	C#
			7	D
		Eb	8	D#
			9	E
			10	
			11	F
		Gb	12	F#
			13	G
		Ab	14	G#

		Mayores					Menores													

		C	E	G					C	D#	G											
		C#	F	G#					C#	E	G#										
		D	F#	A					D	F	A
		D#	G	A#					D#	F#	A#	
		E	G#	B					E	G	B		
		F	A	C					F	G#	C	
		F#	A#	C#					F#	A	C#	
		G	B	D					G	A#	D
		G#	C	D#					G#	B	D#	
		A	C#	E					A	C	E
		A#	D	F					A#	C#	F
		B	D#	F#					B	D	F#
*/
// la siguiente matriz guarda los acordes mayores codificados
int mat_mayor[][2] = {	{0,0},
								{6,9},		// A=1	C#=6	E=9	
								{7,11},
								{8,12},
								{0,0},
								{9,13},
								{11,14},
								{12,1},
								{13,2},
								{14,3},
								{0,0},
								{1,5},
								{2,6},
								{3,7},
								{5,8}};

// la siguiente matriz guarda los acordes mayores codificados
int mat_menor[][2] = {	{0,0},
								{5,9},
								{6,11},
								{7,12},
								{0,0},
								{8,13},
								{9,14},
								{11,1},
								{12,2},
								{13,3},
								{0,0},
								{14,5},
								{1,6},
								{2,7},
								{3,8}};

///////////////////////////////////////////////////////////////////////////
//	PROGRAMA PRINCIPAL
///////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{
	// redireccionar la entrada y salida
	#ifndef ONLINE_JUDGE 
		cin.rdbuf((new ifstream("input.txt"))->rdbuf()); 
		cout.rdbuf((new ofstream("output.txt"))->rdbuf()); 
	#endif 

	string note, note1, note2, note3;
	int nota, n1, n2, n3;
	cin >> note1 >> note2 >> note3;
	while (!cin.eof()) {

		// convertir la nota a nro
		// si es #, sumo 1, si es b, resto 1. luego resto el offset (2 'A')
		// para obtener valores de 0 a 14
		n1 = 2 * toupper(note1[0]) + 
			(note1[1] == '#' ? 1 : (note1[1] == 'b' ? -1 : 0)) - 2 * 'A' + 1;
		
		n2 = 2 * toupper(note2[0]) + 
			(note2[1] == '#' ? 1 : (note2[1] == 'b' ? -1 : 0)) - 2 * 'A' + 1;
		
		n3 = 2 * toupper(note3[0]) + 
			(note3[1] == '#' ? 1 : (note3[1] == 'b' ? -1 : 0)) - 2 * 'A' + 1;
		
		// contemplar el caso Cb = B, porque la cuenta sino da mal
		if ((note1 == "Cb") || (note1 == "cb")) n1 = 3;
		if ((note2 == "Cb") || (note2 == "cb")) n2 = 3;
		if ((note3 == "Cb") || (note3 == "cb")) n3 = 3;

		// contemplar el caso B# = C, porque la cuenta sino da mal
		if ((note1 == "B#") || (note1 == "b#")) n1 = 5;
		if ((note2 == "B#") || (note2 == "b#")) n2 = 5;
		if ((note3 == "B#") || (note3 == "b#")) n3 = 5;

		// contemplar el caso Fb = E, porque la cuenta sino da mal
		if ((note1 == "Fb") || (note1 == "fb")) n1 = 9;
		if ((note2 == "Fb") || (note2 == "fb")) n2 = 9;
		if ((note3 == "Fb") || (note3 == "fb")) n3 = 9;

		// contemplar el caso E# = F, porque la cuenta sino da mal
		if ((note1 == "E#") || (note1 == "e#")) n1 = 11;
		if ((note2 == "E#") || (note2 == "e#")) n2 = 11;
		if ((note3 == "E#") || (note3 == "e#")) n3 = 11;

		// contemplar el caso Ab = G#
		if (n1 == 0) n1 = 14;
		if (n2 == 0) n2 = 14;
		if (n3 == 0) n3 = 14;

		bool mayor = false, 
			  menor = false;
		if (((mat_mayor[n1][0] == n2) && (mat_mayor[n1][1] == n3)) ||
			((mat_mayor[n1][0] == n3) && (mat_mayor[n1][1] == n2))) { 
			mayor = true;
			nota = n1;
		} else if (((mat_mayor[n2][0] == n1) && (mat_mayor[n2][1] == n3)) ||
					 ((mat_mayor[n2][0] == n3) && (mat_mayor[n2][1] == n1))) {
						mayor = true;
						nota = n2;
		} else if (((mat_mayor[n3][0] == n1) && (mat_mayor[n3][1] == n2)) ||
					 ((mat_mayor[n3][0] == n2) && (mat_mayor[n3][1] == n1))) {
						mayor = true;
						nota = n3;
		} else if (((mat_menor[n1][0] == n2) && (mat_menor[n1][1] == n3)) ||
		 			 ((mat_menor[n1][0] == n3) && (mat_menor[n1][1] == n2))) { 
						menor = true;
						nota = n1;
		} else if (((mat_menor[n2][0] == n1) && (mat_menor[n2][1] == n3)) ||
					 ((mat_menor[n2][0] == n3) && (mat_menor[n2][1] == n1))) {
						menor = true;
						nota = n2;
		} else if (((mat_menor[n3][0] == n1) && (mat_menor[n3][1] == n2)) ||
					 ((mat_menor[n3][0] == n2) && (mat_menor[n3][1] == n1))) {
						menor = true;
						nota = n3;
		}
		if (mayor || menor) {		
			switch (nota) {
				case 1: note = "A";	break;
				case 2: note = "A#";	break;
				case 3: note = "B";	break;
				case 5: note = "C";	break;
				case 6: note = "C#";	break;
				case 7: note = "D";	break;
				case 8: note = "D#";	break;
				case 9: note = "E";	break;
				case 11: note = "F";	break;
				case 12: note = "F#";break;
				case 13: note = "G";	break;
				case 14: note = "G#";break;
			}
			if (mayor)
				cout << note1 << " " << note2 << " " << note3 << " is a " 
						<< note << " Major chord." << endl;
			else if (menor)
				cout << note1 << " " << note2 << " " << note3 << " is a " 
						<< note << " Minor chord." << endl;
		} else
			cout << note1 << " " << note2 << " " << note3 
					<< " is unrecognized." << endl;

		cin >> note1 >> note2 >> note3;
	}

	return 0;
}

/* @END_OF_SOURCE_CODE */

