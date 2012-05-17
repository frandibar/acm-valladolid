// EN LINUX DEVUELVE RUN TIME ERROR: SEGMENTATION FAULT
/* @JUDGE_ID:  40922FK  493  C++  */
    
/******************************************************************************
 Solution to Problem 493 - Rational Spiral
 by: Francisco Dibar
 date: May-12-2004
******************************************************************************/

#include <iostream>
#include <queue>
#include <vector>
#include <set>

#define N		100000
#define SUBE	1
#define BAJA	-1

typedef long INTn;		// definir el tamaño de entero

using namespace std;

////////////////////////////////////////////////////////////////////////////////
struct racional {
	INTn num, 
		  den;
};

////////////////////////////////////////////////////////////////////////////////
INTn gcd(INTn u, INTn v)
// devuelve el maximo comun divisor entre u y v
{
	INTn t;
	while (v != 0) {
		t = u % v; 
		u = v;
		v = t;
	}
	return u;
}

////////////////////////////////////////////////////////////////////////////////
void mostrar(vector<racional>& vec_racionales, INTn indice)
// mostrar en pantalla el nro racional
{
//	racional r = vec_racionales.at(indice);
	racional r = vec_racionales[indice];
	cout << r.num << " / " << r.den << endl;
}

////////////////////////////////////////////////////////////////////////////////
void armar_serie(vector<INTn>& vec, INTn base, INTn desde)
{
	// el armado consiste en una fase creciente hasta el maximo valor alcanzado mas uno, 
	// una repeticion del maximo que se va incrementando cada vez
	// una fase decreciente hasta el mismo valor maximo de signo negativo
	// otra repeticion del maximo que se va incrementando cada vez
		INTn i = desde;
		while (i < (INTn) vec.size()) {		
			INTn inc = SUBE;
			INTn ultimo = vec[i-1];
			
			// volcar la fase creciente
			INTn k = ultimo;
			while (k < (-ultimo + 1)) {
				vec[i] = vec[i-1] + inc;
				i++;
				k += inc;
			}

			// repetir la base	
			for (INTn r = 0; r <= base; r++)
				vec[i++] = k;
			base++;

			// volcar la fase decreciente
			inc = BAJA;
			k = ultimo = vec[i-1];
			while (k > (-ultimo)) {
				vec[i] = vec[i-1] + inc;
				i++;
				k += inc;
			}
			// repetir la base	
			for (INTn r = 0; r <= base; r++)
				vec[i++] = k;
			base++;
		}
}

////////////////////////////////////////////////////////////////////////////////
void calcular_racionales(vector<racional>& vec_racionales, INTn n)
// volcar en vec_racionales n racionales
{
	set<double, less<double> > set_racionales;	// lo utilizo para evitar repeticiones
	vector<INTn> vec_num(n);
	vector<INTn> vec_den(n);

	// armar vec_num y vec_den, ambas ondas son similares, pero una presenta un desfasaje respecto de la otra
	vec_num[0] = 0;
	armar_serie(vec_num, 0, 1);
	vec_den[0] = 0;
	vec_den[1] = 0;
	armar_serie(vec_den, 1, 2);

	// a partir de vec_num y vec_den, armo los nros racionales, los divido por su mcd y los inserto en set_racionales,
	// si no estaban presentes, los agrego a vec_racionales
	for (INTn i = 0; i < (INTn)vec_num.size(); i++) {
		racional r;
		r.num = vec_num[i];
		r.den = vec_den[i];
		if (r.den != 0) {
			// obtener la minima expresion
			INTn mcd = gcd(r.num, r.den);
			r.num /= mcd;
			r.den /= mcd;
			// pasar el signo del denominador al numerador
			if (r.den < 0) {
				r.den = -r.den;
				r.num = -r.num;
			}
			// si numerador y denominador son negativos, hacerlos positivos
			if ((r.num < 0) && (r.den < 0)) {
				r.num = -r.num;
				r.den = -r.den;
			}
			// evitar las los denominadores distintos para el numerador = 0;
			if (r.num == 0)
				r.den = 1;
			
			// REVISAR: depende de la precision de double, que pueden considerar dos nros distintos como iguales
			// insertarlos en el set y verificar si ya existia
			double dr = (double)r.num / (double)r.den;
			pair< set<double, less<double> >::const_iterator, bool > p;
			p = set_racionales.insert(dr);
			if (p.second)	// indica si se inserto, o sea no estaba repetido
				vec_racionales.push_back(r);
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
//	PROGRAMA PRINCIPAL
////////////////////////////////////////////////////////////////////////////////

INTn main(INTn argc, char *argv[])
{
	vector<racional> vec_racionales;

	// generar el vector de racionales
	calcular_racionales(vec_racionales, N);

	queue<INTn> que_input;
	// leer la entrada
	INTn in;
	cin >> in;
	while (!cin.eof()) {
		que_input.push(in);
		cin >> in;
	}

	// mostrar la salida
	while (!que_input.empty()) {
			mostrar(vec_racionales, que_input.front());
		que_input.pop();
	}
	return 0;
}

