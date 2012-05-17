
/* @JUDGE_ID:  40922FK  106  C++  */
    
/******************************************************************************
 Solution to Problem 495 - Fibonacci Freeze
 by: Francisco Dibar
 date: May-13-2004
******************************************************************************/

#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <cmath>		// pow

#define MAX_DIGITOS		1046		// es la cantidad de digitos de fibonacci(5000)
#define DIG_X_CELDA		9
#define MAX_CELDAS		MAX_DIGITOS / DIG_X_CELDA

typedef unsigned long INTn;

using namespace std;

////////////////////////////////////////////////////////////////////////////////
// definicion de clase de enteros de precision multiple
class entero_mp {
private:
	int dig_x_celda;
	int celdas;
	vector<INTn> vec_int;

public:
	entero_mp() { 
		dig_x_celda = DIG_X_CELDA;
		celdas = 0;
//		vec_int.reserve(MAX_CELDAS);
	}
	entero_mp(const string& str_int);
	string mostrar();
	entero_mp operator+(const entero_mp&);
};

////////////////////////////////////////////////////////////////////////////////
entero_mp::entero_mp(const string& str_int)
{
	// armar el entero a partir del string str_int		
	dig_x_celda = DIG_X_CELDA;
	int i, ai;

	// tomar de a dig_x_celda digitos y volcarlos en una celda
	for (i = 0; i < (int)(str_int.length() / dig_x_celda); i++) {
		ai = atoi(str_int.substr(str_int.length() - dig_x_celda * (i+1), dig_x_celda).c_str());
		vec_int.push_back(ai);
	}
	// la ultima celda puede contener menos digitos
	if ((int)str_int.length() > (dig_x_celda * i)) {
		// volcar el resto	
		ai = atoi(str_int.substr(0, str_int.length() - dig_x_celda * i).c_str());
		vec_int.push_back(ai);
	}
}

////////////////////////////////////////////////////////////////////////////////
string entero_mp::mostrar()
// devolver un string con el nro
{
	string s_nro = "";
	string ceros(dig_x_celda,'0');
	
	char *celda = new char[dig_x_celda];
	s_nro += itoa(vec_int[(int)vec_int.size()-1], celda, 10);
	for (int i = (int)vec_int.size()-2; i >= 0; i--) {
			// anteponer al nro los ceros correspondientes
			string s_celda = ceros + itoa(vec_int[i], celda, 10);
			s_nro += s_celda.substr(s_celda.length()-dig_x_celda, dig_x_celda);
	}
	return s_nro;
}

////////////////////////////////////////////////////////////////////////////////
entero_mp entero_mp::operator+(const entero_mp& n2)
{
	entero_mp mpi1;
	entero_mp mpi2 = n2;

	mpi1.vec_int = vec_int;
	mpi1.celdas = celdas;
	mpi1.dig_x_celda = dig_x_celda;

	// chequear que tengan igual cantidad de digitos por celda
	if (mpi1.dig_x_celda != mpi2.dig_x_celda) return 0;

	// considerar la misma cantidad de ceros
	if (mpi1.vec_int.size() > mpi2.vec_int.size()) 
		while (mpi1.vec_int.size() != mpi2.vec_int.size()) 
			mpi2.vec_int.push_back(0);
	else
		while (mpi1.vec_int.size() != mpi2.vec_int.size()) 
			mpi1.vec_int.push_back(0);

	entero_mp res;
	res.dig_x_celda = dig_x_celda;

	// efectuar la suma
	int carry = 0;
	int max_celda = (int)pow(10, mpi1.dig_x_celda) - 1;
	for (int i = 0; i < (int)mpi1.vec_int.size(); i++) {
		int sum = carry + mpi1.vec_int[i] + mpi2.vec_int[i];	
		carry = (sum > max_celda);
		res.vec_int.push_back(sum - (max_celda + 1) * carry);
	}
	// agregar una celda mas al resultado
	if (carry) 
		res.vec_int.push_back(carry);
	
	res.celdas = vec_int.size();	
	return res;
}

////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
void generar_tabla(vector<entero_mp>& vec_fibo, int max)
// genera una tabla con los primeros max nros de fibonacci
{
	vec_fibo[0] = entero_mp("0");
	vec_fibo[1] = entero_mp("1");
	for (int j = 2; j < max; j++) 
		vec_fibo[j] = vec_fibo[j-1] + vec_fibo[j-2]; 
}


////////////////////////////////////////////////////////////////////////////////
//	PROGRAMA PRINCIPAL
////////////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{
	queue<int> que_input;
	int input;
	int max = 0;
	// leer las entradas y almacenar el maximo leido
	cin >> input;
	while (!cin.eof()) {
		que_input.push(input);
		if (input > max) max = input;
		cin >> input;
	}
	
	vector<entero_mp> vec_fibo(max+1);
	generar_tabla(vec_fibo, max+1);
// procesar las entradas
	while (!que_input.empty()) {
		input = que_input.front();
		que_input.pop();
		cout << "The Fibonacci number for " << input << " is " << vec_fibo[input].mostrar() << endl;
	}
	return 0;
}

