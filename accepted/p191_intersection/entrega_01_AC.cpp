
/* @JUDGE_ID:  40922FK  191  C++  */
    
/******************************************************************************
 Solution to Problem 191 - Intersection
 by: Francisco Dibar
 date: Mar-13-2004
******************************************************************************/

#include <iostream>
#include <queue>

using namespace std;
/*
////////////////////////////////////////////////////////////////////////////////
template<class T>const T& max(const T& a, const T& b)
{
	return (a < b) ? b : a;
}

////////////////////////////////////////////////////////////////////////////////
template<class T>const T& min(const T& a, const T& b)
{
	return (a < b) ? a : b;
}
*/
////////////////////////////////////////////////////////////////////////////////
//	PROGRAMA PRINCIPAL
////////////////////////////////////////////////////////////////////////////////

struct linea {
	int xstart, ystart, xend, yend;
};

struct rect {
	int xleft, ytop, xright, ybottom;
};

struct coord {
	linea l;
	rect r;
};

int main(int argc, char *argv[])
{
	int n;		// cantidad de casos

	queue<coord>que_input;
	cin >> n;
	coord caso;
	// leer los n casos
	for (int i = 0; i < n; i++) {
		cin >> caso.l.xstart >> caso.l.ystart >> caso.l.xend >> caso.l.yend >> caso.r.xleft >> caso.r.ytop >> caso.r.xright >> caso.r.ybottom;
		que_input.push(caso);
	}
	
	while (!que_input.empty()) {
		caso = que_input.front();
		que_input.pop();	// descartar el valor leido
		
		linea l;
		rect r;

		int xa, xb, ya, yb;
		// identificar las coordenadas izq y der, sup e inf
		l.xstart = min(caso.l.xstart, caso.l.xend);
		l.xend = max(caso.l.xstart, caso.l.xend);
		l.ystart = min(caso.l.ystart, caso.l.yend);
		l.yend = max(caso.l.ystart, caso.l.yend);

		r.xleft = min(caso.r.xleft, caso.r.xright);
		r.xright = max(caso.r.xleft, caso.r.xright);
		r.ybottom = min(caso.r.ybottom, caso.r.ytop);
		r.ytop = max(caso.r.ybottom, caso.r.ytop);

		// ahora con las coordenadas ordenadas, busco la interseccion en X y Y entre
		// la linea y el cuadrado
		xa = max(l.xstart, r.xleft);
		xb = min(l.xend, r.xright);

		ya = max(l.ystart, r.ybottom);
		yb = min(l.yend, r.ytop);

		if ((xa > xb) || (ya > yb))
			// no hay interseccion
			cout << "F" << endl;
		else {
			double m, b, y_xa, y_xb;
			// y = m.x + b 
			if (l.xend != l.xstart) {
				m = (caso.l.yend - caso.l.ystart) / (caso.l.xend - caso.l.xstart);
				// b = y - m.x 
				b = caso.l.ystart - m * caso.l.xstart;
				y_xa = m * xa + b;
				y_xb = m * xb + b;
			} else {
				// es un punto o una recta vertical
				y_xa = max(ya, l.ystart);
				y_xb = min(yb, l.yend);
			}
			if ((y_xa <= yb && y_xa >= ya) || (y_xb <= yb && y_xb >= ya) || (y_xa <= ya && y_xb >= yb)) 
				// hay interseccion
				cout << "T" << endl;
			else 
				// no hay interseccion
				cout << "F" << endl;
		}
	}
	return 0;
}

