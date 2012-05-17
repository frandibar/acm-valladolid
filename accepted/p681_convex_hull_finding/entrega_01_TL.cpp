/* @JUDGE_ID:  40922FK  681  C++  */
/* @BEGIN_OF_SOURCE_CODE */    
/**************************************************************************
 Solution to Problem 681 - Convex Hull Finding
 by: Francisco Dibar
 date: Nov-28-2005
**************************************************************************/

//#define DEBUG
//#define ONLINE_JUDGE 
#include <iostream>
#ifndef ONLINE_JUDGE 
	#include <fstream>
#endif 
#include <vector>
#include <cmath>
#include <algorithm>

#define START_DEBUG	"START DEBUG ********************************************************************\n"
#define END_DEBUG	"END DEBUG **********************************************************************\n"

#define EPSILON	0.00001
#define SEPARATOR	-1

using namespace std;

///////////////////////////////////////////////////////////////////////////
// Author: fdibar
// Date: nov 26, 2005
// Uses: vector, cmath, algorithm
// #define EPSILON 0.0001
// Multidimensional point class
class point {	
private:
	unsigned int _dim;		// dimensions
	vector<double> _vec_coords;

public:
	point(unsigned int dim = 2) { 
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
	point(const point& p) {		// copy constructor
		_dim = p._dim;
		_vec_coords.resize(_dim);
		for (unsigned int i = 0; i < _dim; i++)
			_vec_coords[i] = p._vec_coords[i];
	}
//	inline double& x() { return (_dim > 0 ? _vec_coords[0] : 0); }	// error
	// no out of bounds check!
	inline double& x() { return _vec_coords[0]; }
	inline double& y() { return _vec_coords[1]; }
	inline double& z() { return _vec_coords[2]; }
	inline double get_coord(unsigned int i) const { return (_dim > i ? _vec_coords[i] : 0); }
	bool set_coord(unsigned int i, double value) { 
		if (_dim >= i) {
			_vec_coords[i-1] = value;
			return true;
		} else return false; 
	}

	inline unsigned int get_dim() { return _dim; }

	double square_modulus() {
		double m = 0;
		for (unsigned int i = 0; i < _dim; i++)
			m += _vec_coords[i] * _vec_coords[i];
		return m;
	}
	inline double modulus() { return sqrt(square_modulus()); }
	double square_distance(point& p) {
		double m = 0;
		for (unsigned int i = 0; i < _dim; i++) {
			double s = _vec_coords[i] - p.get_coord(i);
			m += s * s;
		}
		return m;
	}
	inline double distance(point& p) { return sqrt(square_distance(p)); }

	bool operator==(const point& p) const {
		if (_dim != p._dim)
			return false;
		
		for (unsigned int i = 0; i < _dim; i++) {
			if ( fabs(_vec_coords[i] - p._vec_coords[i]) > EPSILON )
				return false;
		}
		return true;
	}
	inline bool operator!=(const point& p) const { return !((*this) == p); }
	friend ostream& operator<<(ostream& os, point& p) {
		os << "(";
		for (unsigned int i = 0; i < (p._dim - 1); i++)
			os << p._vec_coords[i] << ",";
		os << p._vec_coords[p._dim - 1] << ")";
		return os;
	}
};

///////////////////////////////////////////////////////////////////////////
double signed_triangle_area(point& a, point& b, point& c)
// valid for 2D only!
{
	// assumes a, b and c are all of same dimensions!
	return  ( (a.x() * b.y() - a.y() * b.x() + a.y() * c.x() 
				- a.x() * c.y() + b.x() * c.y() - c.x() * b.y()) / 2.0);
}

///////////////////////////////////////////////////////////////////////////
double triangle_area(point& a, point& b, point& c)
{
	return fabs(signed_triangle_area(a, b, c));
}

///////////////////////////////////////////////////////////////////////////
bool ccw(point& a, point& b, point& c)
// returns true if a, b, c are in counter clockwise order
{
	return (signed_triangle_area(a, b, c) > EPSILON);
}
	
///////////////////////////////////////////////////////////////////////////
bool cw(point& a, point& b, point& c)
// returns true if a, b, c are in clockwise order
{
	return (signed_triangle_area(a, b, c) < EPSILON);
}

///////////////////////////////////////////////////////////////////////////
bool collinear(point& a, point& b, point& c)
{
	return (fabs(signed_triangle_area(a, b, c)) <= EPSILON);
}

/////////////////////////////////////////////////////////////////////////// 
bool leftlower(const point& p1, const point& p2)
// valid for 2D only!!
{
	//if (p1.x() < p2.x()) return true;
	//if (p1.x() > p2.x()) return false;
	if (p1.get_coord(0) < p2.get_coord(0)) return true;
	if (p1.get_coord(0) > p2.get_coord(0)) return false;
	
	//if (p1.y() < p2.y()) return true;
	//if (p1.y() > p2.y()) return false;
	if (p1.get_coord(1) < p2.get_coord(1)) return true;
	if (p1.get_coord(1) > p2.get_coord(1)) return false;

	return false;	// p1 == p2
}

/////////////////////////////////////////////////////////////////////////// 
bool lowerleft(point& p1, point& p2)
// valid for 2D only!!
{
	if (p1.y() < p2.y()) return true;
	if (p1.y() > p2.y()) return false;
	
	if (p1.x() < p2.x()) return true;
	if (p1.x() > p2.x()) return false;

	return false;	// p1 == p2
}

///////////////////////////////////////////////////////////////////////////
bool point_in_box(point& s, point& p, point& q)
{
	return ( (s.x() >= min(p.x(), q.x())) && (s.x() <= max(p.x(), q.x())) &&
			 (s.y() >= min(p.y(), q.y())) && (s.y() >= max(p.y(), q.y())) );
}

///////////////////////////////////////////////////////////////////////////
// Author: fdibar
// Date: nov 26, 2005
// Uses: point
// Multidimensional line class
class line {
public:
	// ax + by + c = 0
	double a, b, c;

	line() { a = b = c = 0; }
	line(point& p1, point& p2) {
		if (p1.x() == p2.x()) {
			// vertical line 1.x=k
			a = 1;
			b = 0;
			c = -p1.x();
		} else {
			b = 1;
			a = -(p1.y() - p2.y()) / (p1.x() - p2.x());	// slope
			c = -(a * p1.x()) - (b * p1.y());
		}
	}
	line(point p, double slope) {
		a = -slope;
		b = 1;
		c = -(a * p.x()) - (b * p.y());
	}
	line(const line& l) {		// copy constructor
		a = l.a;
		b = l.b;
		c = l.c;
	}
	inline bool parallelQ(line& l) {
		return ( (fabs(a - l.a) <= EPSILON) &&
				   (fabs(b - l.b) <= EPSILON) );
	}
	inline bool operator==(line& l) {
		return (parallelQ(l) && (fabs(c - l.c) <= EPSILON) );
	}
	bool intersection_point(line& l, point& p) {
		if ((*this) == l) {
			p.x() = p.y() = 0.0;
			return true;
		}
		if (parallelQ(l))
			return false;

		p.x() = (l.b * c - b * l.c) / (l.a * b - a * l.b);
		if (fabs(b) > EPSILON)	// test for vertical line
			p.y() = - (a * p.x() + c) / b;
		else
			p.y() = - (l.a * p.x() + l.c) / l.b;

		return true;
	}
};


///////////////////////////////////////////////////////////////////////////
point closest_point(point& p, line& l)
{
	point cp;
	if (fabs(l.b) <= EPSILON) {		// vertical line
		cp.x() = -l.c;
		cp.y() = p.y();
		return cp;
	}

	if (fabs(l.a) <= EPSILON) {		// horizontal line
		cp.x() = p.x();
		cp.y() = -l.c;
		return cp;
	}
	// line with slope
	line perp(p, 1/l.a);	// perpendicular to l through (x,y)
	l.intersection_point(perp, cp);
	return cp;
}	

///////////////////////////////////////////////////////////////////////////
bool smaller_angle(point& first_point, point& p1, point& p2) 
{
	if (collinear(first_point, p1, p2))
		if ( first_point.square_distance(p1) <= first_point.square_distance(p2) )
			return false;
		else
			return true;

	if (ccw(first_point, p1, p2))
		return false;
	else
		return true;
}
/*
//////////////////////////////////////////////////////////////////////////
class less_angle_cmp : public std::binary_function<point, point, bool> {
// functor class
private:
	point _reference;
public:
	less_angle_cmp(const point& rp) : _reference(rp) {}

	bool operator()(const point& p1, const point& p2) {
		if (collinear(_reference, p1, p2))
			return (_reference.square_distance(p1) > _reference.square_distance(p2);

		return (!ccw(_reference, p1, p2));
	}
};
*/

//////////////////////////////////////////////////////////////////////////
// Author: fdibar
// Date: nov 26, 2005
// Uses: vector, point
class polygon {
private:
	int _n;

public:
	vector<point> vec_points;

protected:
	void selection_sort_poly(point& first_point) {
		for (int i = 1; i < _n; i++) {
			int min = i;
			for (int j = i+1; j < _n; j++) {
				if (smaller_angle(first_point, vec_points[min], vec_points[j]))
					min = j;
			}
			swap(vec_points[i], vec_points[min]);
		}
	}

	// REVISAR: no funciona!
	void insertion_sort_poly(point& first_point) {
		for (int i = 2; i < _n; i++) {
			int j = i;
			while ((j > 1) && (!smaller_angle(first_point, vec_points[j-1], vec_points[j]))) {
				swap(vec_points[j], vec_points[j-1]);
				cout << "after swap: " << first_point << vec_points[j] << vec_points[j-1] << endl;
				j--;
			}
		}
	}

	int partition_poly(vector<point>& v, int lo, int hi, point& first_point)
	// returns the index of partition, used with quicksort
	{
		int p = hi;	// p pivot element index
		int firsthigh = lo;	// divider position for pivot
		for (int i = lo; i < hi; i++) {
			if (smaller_angle(first_point, v[i], v[p])) {
				swap(v[i], v[firsthigh]);
				firsthigh++;
			}
		}
		swap(v[p], v[firsthigh]);
		return firsthigh;
	}

	// REVISAR: no funciona!
	void quicksort_poly(vector<point>& v, int lo, int hi, point& first_point)
	{
		if ((hi - lo) > 0) {
			int p = partition_poly(v, lo, hi, first_point);	// index of partition
			quicksort_poly(v, lo, p-1, first_point);
			quicksort_poly(v, p+1, hi, first_point);
		}
	}


public:

	polygon(int n = 3) { 
		vec_points.resize(n+1);	// extra space for sentinel
	}
	polygon(vector<point>& v) {
		_n = v.size();
		vec_points = v;
		vec_points.resize((int)vec_points.size() + 1);
	}
	polygon(const polygon& p) {		// copy constructor
		_n = p._n;
		vec_points.resize(_n+1);
		for (int i = 0; i < _n; i++)
			vec_points[i] = p.vec_points[i];
	}
	inline int get_n() { return _n; }
	inline int set_n(unsigned int newn) { 
		_n = newn; 
		vec_points.resize(_n+1);	// extra space for sentinel
	}

	void remove_points_with_same_angle(point& first_point) {
		// asumes points are in leftlower order.
		int oldn = _n;	// num of points before deletion
		int hole = 1;	// index marked for potential deletion
		for (int i = 2; i < oldn; i++) { 
			if ( collinear(first_point, vec_points[hole], vec_points[i]) ) {
				// leave the farthest point
				if (first_point.square_distance(vec_points[hole]) < first_point.square_distance(vec_points[i]))
					vec_points[hole] = vec_points[i];
				_n--;
			} else {
				hole++;
				vec_points[hole] = vec_points[i];
			}
		}
	}

	void sort_and_remove_duplicate_points() {
		// removes duplicated points
		sort(vec_points.begin(), vec_points.begin() + _n, leftlower);
		int oldn = _n;	// num of points before deletion
		int hole = 1;	// index marked for potential deletion
		for (int i = 1; i < (oldn - 1); i++) { 
			if ( vec_points[hole-1] == vec_points[i] )
				_n--;
			else {
				vec_points[hole] = vec_points[i];
				hole++;
			}
		}
		vec_points[hole] = vec_points[oldn - 1];
	}

	inline void sort_points_by_angle(point& first_point) {
		selection_sort_poly(first_point);
	}

	polygon convex_hull() {
		// Graham's scan algorithm
		polygon hull(_n);
		if (_n <= 3) {	// all points on hull
			hull = (*this);
			return hull;
		}

		sort_and_remove_duplicate_points();
		point first_point = vec_points[0];
		sort_points_by_angle(first_point);
		remove_points_with_same_angle(first_point);

		vector<point> s;
		s.push_back(first_point);
		s.push_back(vec_points[1]);
		s.push_back(vec_points[2]);
		for (int i = 3; i < _n; i++) {
			while (!ccw(s[s.size()-2], s[s.size()-1], vec_points[i]))
				s.pop_back();
			s.push_back(vec_points[i]);
		}
		hull.vec_points = s;
		hull._n = s.size();
		return hull;
	}

	double perimeter() {
		polygon hull = convex_hull();

		double perim = 0;
		// sum each segment of the convex hull
		for (int i = 1; i < hull._n; i++)
			perim += hull.vec_points[i].distance(hull.vec_points[i-1]);
		perim += hull.vec_points[0].distance(hull.vec_points[hull._n-1]);

		return perim;
	}

};

///////////////////////////////////////////////////////////////////////////
// Author: fdibar
// Date: nov 26, 2005
// Uses: point
// Multidimensional segment class
class segment {
public:
	point p1, p2;	// endpoints

	segment() {};
	segment(point& p, point& q) {
		p1 = p;
		p2 = q;
	}
	bool intersectsQ(segment& s) {
		line	l1(p1, p2),
				l2(s.p1, s.p2);

		if (l1 == l2)
			return (point_in_box(p1, s.p1, s.p2) ||
					point_in_box(p2, s.p1, s.p2) ||
					point_in_box(s.p1, p1, p2) ||
					point_in_box(s.p1, p1, p2) );
		
		if (l1.parallelQ(l2)) 
			return false;
		
		point p;		// intersection point
		l1.intersection_point(l2, p);
		return (point_in_box(p, p1, p2) && point_in_box(p, s.p1, s.p2) );
	}
};


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

	int cases;
	cin >> cases;
	cout << cases << endl;
	for (int k = 0; k < cases; k++) {
		// READ INPUT
		int npoints;
		cin >> npoints;
		vector<point> vec_points(npoints);
		for (int j = 0; j < npoints; j++) {
			cin >> vec_points[j].x() >> vec_points[j].y();
		}

		// PROCESS
		polygon p(vec_points);
		polygon hull = p.convex_hull();
				
		// SHOW OUTPUT
		int npts = hull.get_n();
		cout << npts + 1 << endl;

		// start by point most to the bottom left, find it
		double bottom, left;
		left = hull.vec_points[0].x();
		bottom = hull.vec_points[0].y();
		int s = 0;	// starting index
		for (int j = 1; j < hull.get_n(); j++) {
			if (hull.vec_points[j].y() < bottom) {
				s = j;
				left = hull.vec_points[j].x();
				bottom = hull.vec_points[j].y();
			} else if (hull.vec_points[j].y() == bottom) {
				if (hull.vec_points[j].x() < left) {
					s = j;
					left = hull.vec_points[j].x();
				}
			}
		}

		for (int i = 0; i <= npts; i++) {
			int ind = (i + s) % npts;
			cout << hull.vec_points[ind].x() << " " << hull.vec_points[ind].y() << endl;
		}

		if (k < (cases - 1)) {
			cin >> npoints;	// read separator, ignore
			cout << SEPARATOR << endl;
		}
	}
		
#ifdef DEBUG
	cout << START_DEBUG;

	cout << END_DEBUG;
#endif
	
	return 0;
}

/* @END_OF_SOURCE_CODE */

