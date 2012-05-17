/* @JUDGE_ID:  40922FK  10167++  */
/* @BEGIN_OF_SOURCE_CODE */    
/**************************************************************************
 Solution to Problem 10167 Birtday Cake
 by: Francisco Dibar
 date: Nov-25-2005
**************************************************************************/

//#define DEBUG
//#define ONLINE_JUDGE 
#include <iostream>
#ifndef ONLINE_JUDGE 
	#include <fstream>
#endif 
#include <vector>
#include <cmath>		// sqrt, fabs

#define START_DEBUG	"START DEBUG ********************************************************************\n"
#define END_DEBUG	"END DEBUG **********************************************************************\n"

#define MAX_COORD 	500
#define MIN_COORD 	-500
#define RADIUS		100
#define EPSILON	0.00001

using namespace std;

///////////////////////////////////////////////////////////////////////////
// Author: fdibar
// Date: NOV 26, 2005
// Uses: vector, cmath, algorithm
// #define EPSILON 0.0001
// Multidimensional point class
class point {	
private:
	int _dim;		// dimensions
	vector<double> _vec_coords;

public:
	point() {	// default coords:2
		_dim = 2;
		_vec_coords.resize(_dim);
	}
	point(unsigned int dim) { 
		_dim = dim;
		_vec_coords.resize(_dim);
	}
	point(double x, double y) {
		_dim = 2;
		_vec_coords.resize(_dim);
	}
	point(double x, double y, double z) {
		_dim = 3;
		_vec_coords.resize(_dim);
	}
//	inline double& x() { return (_dim > 0 ? _vec_coords[0] : 0); }	// error
	// no out of bounds check!
	inline double& x() { return _vec_coords[0]; }
	inline double& y() { return _vec_coords[1]; }
	inline double& z() { return _vec_coords[2]; }
	inline double get_coord(int i) { return (_dim >= i ? _vec_coords[i-1] : 0); }
	bool set_coord(int i, double value) { 
		if (_dim >= i) {
			_vec_coords[i-1] = value;
			return true;
		} else return false; 
	}

	inline unsigned int get_dim() { return _dim; }

	double square_modulus() {
		double m = 0;
		for (int i = 0; i < _dim; i++)
			m += _vec_coords[i] * _vec_coords[i];
		return m;
	}
	inline double modulus() { return sqrt(square_modulus()); }

	bool operator==(const point& p) const {
		if (_dim != p._dim)
			return false;
		
		for (int i = 0; i < _dim; i++) {
			if ( fabs(_vec_coords[i] - p._vec_coords[i]) > EPSILON )
				return false;
		}
		return true;
	}
	inline bool operator!=(const point& p) const { return !((*this) == p); }

};

///////////////////////////////////////////////////////////////////////////
double signed_triangle_area(point& a, point& b, point& c)
{
	// assumes a, b and c are all of same dimensions!
	return  ( (a.x() * b.y() - a.y() * b.x() + a.y() * c.x() 
				- a.x() * c.y() + b.x() * c.y() - c.x() * b.y()) / 2.0);
}

///////////////////////////////////////////////////////////////////////////
double triangle_area(point a, point b, point c)
{
	return fabs(signed_triangle_area(a, b, c));
}


///////////////////////////////////////////////////////////////////////////
void cut_cake(vector<point>& v, int *A, int *B)
// returns A and B where Ax + By = 0, and all points in v are divided in 2
{
	for (int i = 0; i < (int)v.size(); i++) {
		point p, q;
		if (v[i].x() != 0) {
			*A = 1 - v[i].y();	// line across circle passing over point
			*B = v[i].x();
			// obtain points p, q at the border of cake where line = pq
			// p.x = sqrt(RADIUS^2 / (1 + B^2/A^2))
			p.x() = sqrt( (double)RADIUS * RADIUS / (double)( 1 + (double)(*B)*(*B) / (double)((*A)*(*A)) ) );
			if ((*A) != 0)
				p.y() = - (double)(*B)/(*A) * p.x();
			else
				p.y() = 0;
		} else {
			*A = -1 * v[i].y();	// line across circle passing over point
			*B = v[i].x() - 1;
			p.x() = sqrt( (double)RADIUS * RADIUS / (double)( 1 + (double)(*B)*(*B) / (double)((*A)*(*A)) ) );
			if ((*A) != 0)
				p.y() = - (double)(*B)/(*A) * p.x();
			else {
				*B = 0;
				return;	// point lies at {0,0}, no solution exists
			}
		}

		q.x() = -1 * p.x();
		q.y() = -1 * p.y();
		
		// calculate signed area between p, q and c where c is a cherry
		// if + then side1++, else (-) side2++
		int side1, side2;
		side1 = side2 = 0;
		for (int j = 0; j < (int)v.size(); j++) {
			double area = signed_triangle_area(p, q, v[j]);
			if (area > 0 + EPSILON)
				side1++;
			else if (area < 0 - EPSILON)
				side2++;
			else {
				// cut passes over a cherry
				side1 = -1;	// make side1 != side2
				side2 = -2;
				break;
			}
		}
		if (side1 == side2)
			return;	// OK
	}
}

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

	int cherries;
	cin >> cherries;
	while (cherries != 0) {

		// READ INPUT
		int ncherries = 2 * cherries;
		vector<point> vec_cherries(ncherries);
		for (int i = 0; i < ncherries; i++)
			cin >> vec_cherries[i].x() >> vec_cherries[i].y();

		// PROCESS
		int A, B;	// Ax + By = 0
		cut_cake(vec_cherries, &A, &B);

		// SHOW OUTPUT
		cout << A << " " << B << endl;

		cin >> cherries;
	}
		
#ifdef DEBUG
	cout << START_DEBUG;

	cout << END_DEBUG;
#endif
	
	return 0;
}

/* @END_OF_SOURCE_CODE */

