/* @JUDGE_ID:  40922FK  10245  C++  */
/* @BEGIN_OF_SOURCE_CODE */    
/**************************************************************************
 Solution to Problem 10245 - The Closest Pair Problem
 by: Francisco Dibar
 date: Dec-05-2005
**************************************************************************/

//#define DEBUG
//#define ONLINE_JUDGE 
#include <iostream>
#ifndef ONLINE_JUDGE 
	#include <fstream>
#endif 

#define START_DEBUG	"START DEBUG ********************************************************************\n"
#define END_DEBUG	"END DEBUG **********************************************************************\n"

#include <vector>
#include <cmath>		// sqrt
#include <algorithm>	// sort
#include <functional>	// binary_function
#include <iomanip>		// fixed

#define EPSILON	0.00001

#define LIMIT	10000


using std::cin;
using std::cout;
using std::endl;
using std::vector;

///////////////////////////////////////////////////////////////////////////
// Author: fdibar
// Date: dec 01, 2005
// Uses: vector, cmath, algorithm
// #define EPSILON 0.0001
// Multidimensional point class
template <unsigned int T>
class point_t {
protected:
    vector<double> _vec_coords;

public:
	point_t() : _vec_coords(T, 0) {}    // constructor

	// constructors
	// constructor from a vector
	point_t(const vector<double>& v_coords) : _vec_coords(T, 0) {	
		for (unsigned int i = 0; i < T; i++)
			_vec_coords[i] = v_coords[i];
	}    
	// copy constructor
	point_t(const point_t& p) : _vec_coords(T, 0) {		
		for (unsigned int i = 0; i < T; i++)
			_vec_coords[i] = p._vec_coords[i];
	}

	inline unsigned int getT() const { return T; }
	inline double& coord(int coord) { return _vec_coords[coord]; }
	inline const double& coord(int coord) const { return _vec_coords[coord]; }
    
	double square_modulus() const {
		double m = 0;
		for (unsigned int i = 0; i < T; i++)
			m += _vec_coords[i] * _vec_coords[i];
		return m;
	}
	inline double modulus() const { return sqrt(square_modulus()); }
	
	double square_distance(const point_t& p) const {
		double m = 0;
		for (unsigned int i = 0; i < T; i++) {
			double s = _vec_coords[i] - p._vec_coords[i];
			m += s * s;
		}
		return m;
	}
	inline double distance(const point_t& p) const { return sqrt(square_distance(p)); }
    
	friend std::ostream& operator<<(std::ostream& os, const point_t<T>& p) {
		os << "(";
		for (unsigned int i = 0; i < (T - 1); i++)
			os << p._vec_coords[i] << ",";
		os << p._vec_coords[T - 1] << ")";
		return os;
	}    

	// binary conmutative operatiors
	friend point_t<T> operator+(const point_t<T>& p, const point_t<T>& q);
	friend point_t<T> operator-(const point_t<T>& p, const point_t<T>& q);

	bool operator==(const point_t<T>& p) const {
		for (unsigned int i = 0; i < T; i++) {
			if ( fabs(_vec_coords[i] - p._vec_coords[i]) > EPSILON )
				return false;
		}
		return true;
	}

	inline bool operator!=(const point_t<T>& p) const { 
		return !((*this) == p); 
	}

	point_t<T> operator-() const {		// unary -
		point_t<T> tmp = (*this);
		for (int i = 0; i < T; i++)
			tmp._vec_coords[i] = -tmp._vec_coords[i];
		return tmp;
	}
	const point_t<T>& operator+=(const point_t<T>& p) {
		for (int i = 0; i < T; i++)
			_vec_coords[i] += _vec_coords[i];
		return (*this);
	}


};

///////////////////////////////////////////////////////////////////////////
template <unsigned int T>
class point : public point_t<T> {
public:
};

///////////////////////////////////////////////////////////////////////////
template <unsigned int T>
point<T> operator+(const point<T>& p, const point<T>& q)
{
	point<T> tmp = p;
	for (int i = 0; i < T; i++)
		tmp.coord(i) += q.coord(i);
	return tmp;
}

///////////////////////////////////////////////////////////////////////////
template <unsigned int T>
point<T> operator-(const point<T>& p, const point<T>& q)
{
	point<T> tmp = p;
	for (int i = 0; i < T; i++)
		tmp._vec_coords[i] -= q._vec_coords[i];
	return tmp;
}

///////////////////////////////////////////////////////////////////////////
// template to provide constructor for a point of 1 dimension
template <>     
class point<1> : public point_t<1> {
public:
	point(double x) {       // constructor
        _vec_coords[0] = x;
	}
	inline const double& x() const { return _vec_coords[0]; }
	inline double& x() { return _vec_coords[0]; }
};

///////////////////////////////////////////////////////////////////////////
// template to provide constructor for a point of 2 dimensions
template<>
class point<2> : public point_t<2> {
public:
	// constructors
	point() {}
	point(double x, double y) {
		_vec_coords[0] = x;
		_vec_coords[1] = y;
	}

	inline const double& x() const { return _vec_coords[0]; }
	inline double& x() { return _vec_coords[0]; }
	inline const double& y() const { return _vec_coords[1]; }
	inline double& y() { return _vec_coords[1]; }

	void rotate(double alfa);

	// revisar!! deberia usar el de la clase base
	point<2> operator-() const {		// unary -
		point<2> tmp = (*this);
		for (int i = 0; i < 2; i++)
			tmp._vec_coords[i] = -tmp._vec_coords[i];
		return tmp;
	}
	const point<2>& operator+=(const point<2>& p) {
		for (int i = 0; i < 2; i++)
			_vec_coords[i] += p._vec_coords[i];
		return (*this);
	}
	
};

///////////////////////////////////////////////////////////////////////////
void point<2>::rotate(double alfa) {
	double r = modulus();
	if (r > EPSILON) {
		double beta = asin(_vec_coords[1] / r);
		_vec_coords[0] = r * cos(alfa + beta);
		_vec_coords[1] = r * sin(alfa + beta);
	} else {
		_vec_coords[0] = 0;
		_vec_coords[1] = 0;
	}
}

///////////////////////////////////////////////////////////////////////////
// template to provide constructor for a point of 3 dimensions
template<>
class point<3> : public point_t<3> {
public:
	point() {}
	point(double x, double y, double z) {
		_vec_coords[0] = x;
		_vec_coords[1] = y;
		_vec_coords[2] = z;
	}
	inline const double& x() const { return _vec_coords[0]; }
	inline double& x() { return _vec_coords[0]; }
	inline const double& y() const { return _vec_coords[1]; }
	inline double& y() { return _vec_coords[1]; }
	inline const double& z() const { return _vec_coords[2]; }
	inline double& z() { return _vec_coords[2]; }
};


///////////////////////////////////////////////////////////////////////////
double signed_triangle_area(const point<2>& a, const point<2>& b, const point<2>& c) 
{
	return  ( (a.x() * b.y() - a.y() * b.x() + a.y() * c.x() 
				- a.x() * c.y() + b.x() * c.y() - c.x() * b.y()) / 2.0);
}


///////////////////////////////////////////////////////////////////////////
double triangle_area(const point<2>& a, const point<2>& b, const point<2>& c)
{
	return fabs(signed_triangle_area(a, b, c));
}

///////////////////////////////////////////////////////////////////////////
bool ccw(const point<2>& a, const point<2>& b, const point<2>& c)
// returns true if a, b, c are in counter clockwise order
{
	return (signed_triangle_area(a, b, c) > EPSILON);
}
	
///////////////////////////////////////////////////////////////////////////
bool cw(const point<2>& a, const point<2>& b, const point<2>& c)
// returns true if a, b, c are in clockwise order
{
	return (signed_triangle_area(a, b, c) < -EPSILON);
}

///////////////////////////////////////////////////////////////////////////
bool collinear(const point<2>& a, const point<2>& b, const point<2>& c)
{
	return (fabs(signed_triangle_area(a, b, c)) <= EPSILON);
}

/////////////////////////////////////////////////////////////////////////// 
bool leftlower(const point<2>& p1, const point<2>& p2)
{
	if (p1.x() < p2.x()) return true;
	if (p1.x() > p2.x()) return false;
	
	if (p1.y() < p2.y()) return true;
	if (p1.y() > p2.y()) return false;

	return false;	// p1 == p2
}

/////////////////////////////////////////////////////////////////////////// 
bool lowerleft(const point<2>& p1, const point<2>& p2)
{
	if (p1.y() < p2.y()) return true;
	if (p1.y() > p2.y()) return false;
	
	if (p1.x() < p2.x()) return true;
	if (p1.x() > p2.x()) return false;

	return false;	// p1 == p2
}

///////////////////////////////////////////////////////////////////////////
bool point_in_box(const point<2>& s, const point<2>& p, const point<2>& q)
// returns true if s is in box delimited by p and q
{
	return ( (s.x() >= std::min(p.x(), q.x())) && (s.x() <= std::max(p.x(), q.x())) &&
			 (s.y() >= std::min(p.y(), q.y())) && (s.y() <= std::max(p.y(), q.y())) );
}



///////////////////////////////////////////////////////////////////////////
//	PROGRAMA PRINCIPAL
///////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{
	// redireccionar la entrada y salida
	#ifndef ONLINE_JUDGE 
		cin.rdbuf((new std::ifstream("input.txt"))->rdbuf()); 
		cout.rdbuf((new std::ofstream("output.txt"))->rdbuf()); 
	#endif 

	cout.setf(std::ios::fixed);
	cout.precision(4);
	
	int n;
	cin >> n;
	while ((n != 0) && !cin.eof()) {
		vector< point<2> > vec_points(n);
		// READ INPUT
		for (int i = 0; i < n; i++)
			cin >> vec_points[i].x() >> vec_points[i].y();

		double mindistance2 = 0;
		if (n > 1) {
			// PROCESS
			// n(n-1)/2 comparations
			mindistance2 = vec_points[0].square_distance(vec_points[1]);
			for (int i = 0; i < n; i++) {
				for (int j = i+1; j < n; j++) {
					double dist2 = vec_points[i].square_distance(vec_points[j]);
					if (dist2 < mindistance2)
						mindistance2 = dist2;
				}
			}
		}			
		// SHOW OUTPUT
		double dist = sqrt(mindistance2);
		if (dist >= LIMIT)
			cout << "INFINITY" << endl;
		else
			cout << dist << endl;

		// READ NEXT INPUT
		cin >> n;
	}
		
#ifdef DEBUG
	cout << START_DEBUG;

	cout << END_DEBUG;
#endif
	
	return 0;
}

/* @END_OF_SOURCE_CODE */

