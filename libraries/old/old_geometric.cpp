#include <vector>
#include <cmath>
#include <algorithm>

#define EPSILON	0.00001

using namespace std;

///////////////////////////////////////////////////////////////////////////
// Author: fdibar
// Date: nov 26, 2005
// Uses: vector, cmath, algorithm
// #define EPSILON 0.0001
// Multidimensional point class
class point {	
private:
	int _dim;		// dimensions
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
		for (int i = 0; i < _dim; i++)
			_vec_coords[i] = p._vec_coords[i];
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
	double square_distance(point& p) {
		double m = 0;
		for (int i = 0; i < _dim; i++)
			m += (_vec_coords[i] - p.get_coord(i)) * (_vec_coords[i] - p.get_coord(i));
		return m;
	}
	inline double distance(point& p) { return sqrt(square_distance(p)); }

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
int leftlower(point& p1, point& p2)
// uses int to be able to use as sorting order
{
	if (p1.x() < p2.x()) return (-1);
	if (p1.x() > p2.x()) return 1;
	
	if (p1.y() < p2.y()) return (-1);
	if (p1.y() < p2.y()) return 1;

	return 0;	// p1 == p2
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
int smaller_angle(point& first_point, point& p1, point& p2) {
	// uses int to be able to use as sorting order
	if (collinear(first_point, p1, p2))
		if ( first_point.square_distance(p1) <= first_point.square_distance(p2) )
			return (-1);
		else
			return 1;

	if (ccw(first_point, p1, p2))
		return (-1);
	else
		return 1;
}


///////////////////////////////////////////////////////////////////////////
template <class T>
int partition_poly(vector<T> v, int l, int h, point& first_point)
// returns the index of partition, used with quicksort
{
	int p = h;	// p pivot element index
	int firsthigh = l;	// divider position for pivot
	for (int i = l; i < h; i++) {
		if (smaller_angle(first_point, v[i], v[p])) {
			swap(v[i], v[firsthigh]);
			firsthigh++;
		}
	}
	swap(v[p], v[firsthigh]);
	return 0;
}

///////////////////////////////////////////////////////////////////////////
template <class T>
void quicksort_poly(vector<T> v, int l, int h, point& first_point)
{
	if ((h - l) > 0) {
		int p = partition_poly(v, l, h, first_point);	// index of partition
		quicksort_poly(v, l, p-1, first_point);
		quicksort_poly(v, p+1, h, first_point);
	}
}


//////////////////////////////////////////////////////////////////////////
// Author: fdibar
// Date: nov 26, 2005
// Uses: vector, point
class polygon {
private:
	int _n;

public:
	vector<point> vec_points;

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
	
	void sort_and_remove_duplicate_points() {
		// removes duplicated points
		sort(vec_points.begin(), vec_points.end(), leftlower);
		int oldn = _n;	// num of points before deletion
		int hole = 1;	// index marked for potential deletion
		for (int i = 0; i < (oldn - 1); i++) { 
			if ( vec_points[hole-1] == vec_points[i] )
				_n--;
			else {
				vec_points[hole] = vec_points[1];
				hole += 1;
			}
		}
		vec_points[hole] = vec_points[oldn - 1];
	}

	inline void sort_points_by_angle(point& first_point) {
		quicksort_poly(vec_points, 0, (int)vec_points.size(), first_point);
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

		//sort(vec_points.begin(), vec_points.end(), smaller_angle);
		sort_points_by_angle(first_point);

		hull.vec_points[0] = first_point;
		hull.vec_points[1] = vec_points[1];
		vec_points[_n] = first_point;	// sentinel for wrap around
		int top = 1;
		int i = 2;

		while (i <= _n) {
			if (!ccw(hull.vec_points[top-1],  hull.vec_points[top], vec_points[i]))
				top -= 1;	// top not on hull
			else {
				top += 1;
				hull.vec_points[top] = vec_points[i];
				i += 1;
			}
		}
		hull._n = top;
		return hull;
	}

	double perimeter() {
		polygon hull = convex_hull();
		double perim = 0;
		for (int i = 1; i < hull._n; i++)
			perim += hull.vec_points[i].square_distance(hull.vec_points[i-1]);
		return sqrt(perim);
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

// DRIVER TO TEST CLASSES
int main(int argc, char *argv[])
{
	// redireccionar la entrada y salida
	#ifndef ONLINE_JUDGE 
		cin.rdbuf((new ifstream("input.txt"))->rdbuf()); 
		cout.rdbuf((new ofstream("output.txt"))->rdbuf()); 
	#endif 

	int cases;
	cin >> cases;

	for (int k = 0; k < cases; k++) {
		// READ INPUT
		// number of points n
		// followed by n points
		int npoints;
		cin >> npoints;
		vector<point> vec_points(npoints);
		for (int j = 0; j < npoints; j++) {
			cin >> vec_points[j].x() >> vec_points[j].y();
		}

		// PROCESS
		// show convex hull
		polygon p(vec_points);
		p.convex_hull();
		cout << "convex hull" << endl;
		for (int j = 0; j < p._n; j++) {
			cout << p.vec_points[j].x() << " " << p.vec_points[j].y() << endl;
		}
		
	}
}
