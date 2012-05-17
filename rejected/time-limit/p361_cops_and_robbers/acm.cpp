/* @JUDGE_ID:  40922FK  361  C++  */
/* @BEGIN_OF_SOURCE_CODE */    
/**************************************************************************
 Solution to Problem 361 - Cops and Robbers
 by: Francisco Dibar
 date: Dec-04-2005
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
#include <functional>	// binary_function


#define START_DEBUG	"START DEBUG ********************************************************************\n"
#define END_DEBUG	"END DEBUG **********************************************************************\n"

#define EPSILON	0.00001

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
			double s = _vec_coords[i] - p.coord(i);
			m += s * s;
		}
		return m;
	}
	inline double distance(const point_t& p) const { return sqrt(square_distance(p)); }
    
	bool operator==(const point_t& p) const {
		for (unsigned int i = 0; i < T; i++) {
			if ( fabs(_vec_coords[i] - p._vec_coords[i]) > EPSILON )
				return false;
		}
		return true;
	}
	inline bool operator!=(const point_t& p) const { return !((*this) == p); }

	friend std::ostream& operator<<(std::ostream& os, const point_t<T>& p) {
		os << "(";
		for (unsigned int i = 0; i < (T - 1); i++)
			os << p._vec_coords[i] << ",";
		os << p._vec_coords[T - 1] << ")";
		return os;
	}    
};

///////////////////////////////////////////////////////////////////////////
template <unsigned int T>
class point : public point_t<T> {};

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
	point() {}
	point(double x, double y) {
		_vec_coords[0] = x;
		_vec_coords[1] = y;
	}
	inline const double& x() const { return _vec_coords[0]; }
	inline double& x() { return _vec_coords[0]; }
	inline const double& y() const { return _vec_coords[1]; }
	inline double& y() { return _vec_coords[1]; }
};


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
// Author: fdibar
// Date: dec 01, 2005
// Uses: point
// 2-3 dimensional line class

template <unsigned int T>
class line_t {
public:
	// ax + by + cz + d = 0
	double a, b, c, d;
	line_t() {		// constructor
		a = b = c = d = 0;
	}	
};

///////////////////////////////////////////////////////////////////////////
template <unsigned int T>
class line : public line_t<T> {
public:
	line(const line<T>& ln) {		// copy constructor
		(*this).a = ln.a;
		(*this).b = ln.b;
		(*this).c = ln.c;
		(*this).d = ln.d;
	}

};

///////////////////////////////////////////////////////////////////////////
// template to provide constructor for a line in 2d
template <>     
class line<2> : public line_t<2> {
public:

	// constructor from 2 points
	// if p1=p2 then creates a vertical line at p1.x!
	line(const point<2>& p1, const point<2>& p2) {
		if (p1.x() == p2.x()) {
			// vertical line 1.x=k
			a = 1;
			b = c = 0;
			d = -p1.x();
		} else {
			b = 1;
			a = -(p1.y() - p2.y()) / (p1.x() - p2.x());	// slope
			d = -(a * p1.x()) - (b * p1.y());
			c = 0;
		}
	}
	// constructor from point and slope
	line(const point<2>& p, double slope) {
		a = -slope;
		b = 1;
		d = -(a * p.x()) - (b * p.y());
		c = 0;
	}
	inline bool parallelQ(const line<2>& ln) const {
		return ( (fabs(a - ln.a) <= EPSILON) &&
				   (fabs(b - ln.b) <= EPSILON) );
	}
	inline bool operator==(const line<2>& ln) const {
		return (parallelQ(ln) && (fabs(d - ln.d) <= EPSILON) );
	}
	bool intersection_point(const line<2>& ln, point<2>& p) const {
		// returns true if an intersection with line exists, 
		// and p as the intersection point
		if ((*this) == ln) {
			p.x() = p.y() = 0.0;
			return true;
		}
		if (parallelQ(ln))
			return false;

		p.x() = (ln.b * d - b * ln.d) / (ln.a * b - a * ln.b);
		if (fabs(b) > EPSILON)	// test for vertical line
			p.y() = - (a * p.x() + d) / b;
		else
			p.y() = - (ln.a * p.x() + ln.d) / ln.b;

		return true;
	}

};

///////////////////////////////////////////////////////////////////////////
// template to provide constructor for a line in 3d
template <>     
class line<3> : public line_t<3> {
	// TO DO
};
    

///////////////////////////////////////////////////////////////////////////
point<2> closest_point(const point<2>& p, line<2>& ln)
{
	point<2> cp;
	if (fabs(ln.b) <= EPSILON) {		// vertical line
		cp.x() = -ln.d;
		cp.y() = p.y();
		return cp;
	}

	if (fabs(ln.a) <= EPSILON) {		// horizontal line
		cp.x() = p.x();
		cp.y() = -ln.d;
		return cp;
	}
	// line with slope
	line<2> perp(p, (double)1/ln.a);	// perpendicular to l through (x,y)
	ln.intersection_point(perp, cp);
	return cp;
}	

///////////////////////////////////////////////////////////////////////////
bool smaller_angle(const point<2>& first_point, const point<2>& p1, const point<2>& p2) 
{
	if (collinear(first_point, p1, p2))
		return (first_point.square_distance(p1) > first_point.square_distance(p2));

	return (!ccw(first_point, p1, p2));
}

//////////////////////////////////////////////////////////////////////////
class less_angle_cmp : public std::binary_function<point<2>, point<2>, bool> {
// functor class
private:
	point<2> _reference;

public:
	less_angle_cmp(const point<2>& rp) : _reference(rp) {}	// constructor

	bool operator()(const point<2>& p1, const point<2>& p2) {
		if (collinear(_reference, p1, p2))
			return (_reference.square_distance(p1) > _reference.square_distance(p2));

		return (ccw(_reference, p1, p2));
	}
};


//////////////////////////////////////////////////////////////////////////
// Author: fdibar
// Date: dec 01, 2005
// Uses: vector, point
class triangle;
class polygon {
private:
	int _n;
public:
	vector< point<2> > vec_points;

protected:
	polygon make_convex_hull(bool exclude_perimetral_points = true) {
		// Graham's scan algorithm
		// al points in vec_points are ordered counterclockwise
		polygon hull = (*this);
		if (_n <= 3) {		// all points are on hull
			if (_n == 3) {
				// order counterclockwise
				if (!ccw(hull.vec_points[0], hull.vec_points[1], hull.vec_points[2]))
					std::swap(hull.vec_points[1], hull.vec_points[2]);
			}
			return hull;
		}

		hull.sort_and_remove_duplicate_points();
		point<2> first_point = hull.vec_points[0];
		hull.sort_points_by_angle(first_point);
		if (exclude_perimetral_points)
			hull.remove_points_with_same_angle(first_point);

		vector< point<2> > s;
		s.push_back(first_point);
		s.push_back(hull.vec_points[1]);
		s.push_back(hull.vec_points[2]);
		for (int i = 3; i < _n; i++) {
			// if (exclude_perimetral_points) discard if not ccw, 
			// else discard if not ccw and not collineal
			while ( !ccw(s[s.size()-2], s[s.size()-1], hull.vec_points[i]) &&
				   (!exclude_perimetral_points && !collinear(s[s.size()-2], s[s.size()-1], hull.vec_points[i])) )
				s.pop_back();

			s.push_back(hull.vec_points[i]);
		}
		hull.vec_points = s;
		hull._n = (unsigned int)s.size();
		return hull;
	}

public:

	polygon(int n = 3) { 
		vec_points.resize(n+1);	// extra space for sentinel
	}
	polygon(const vector< point<2> >& v) {
		_n = (unsigned int)v.size();
		vec_points = v;
		vec_points.resize((int)vec_points.size() + 1);
	}
	polygon(const polygon& p) {		// copy constructor
		_n = p._n;
		vec_points.resize(_n+1);
		for (int i = 0; i < _n; i++)
			vec_points[i] = p.vec_points[i];
	}
	inline int get_n() const { return _n; }
	inline void set_n(unsigned int newn) { 
		_n = newn; 
		vec_points.resize(_n+1);	// extra space for sentinel
	}

	void remove_points_with_same_angle(const point<2>& first_point) {
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
				if (hole != i)
					vec_points[hole] = vec_points[i];
			}
		}
	}

	void sort_and_remove_duplicate_points() {
		// removes duplicated points
		std::sort(vec_points.begin(), vec_points.begin() + _n, leftlower);
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

	inline void sort_points_by_angle(const point<2>& first_point) {
		std::sort(vec_points.begin()+1, vec_points.begin()+_n, less_angle_cmp(first_point));
	}

	polygon convex_hull(bool exclude_perimetral_points, double* perimeter) {
		polygon hull = make_convex_hull(exclude_perimetral_points);

		*perimeter = 0;
		// sum each segment of the convex hull
		for (int i = 1; i < hull._n; i++)
			(*perimeter) += hull.vec_points[i].distance(hull.vec_points[i-1]);
		(*perimeter) += hull.vec_points[0].distance(hull.vec_points[hull._n-1]);

		return hull;
	}

	polygon convex_hull(bool exclude_perimetral_points = true) {
		return make_convex_hull(exclude_perimetral_points);
	}

	double perimeter() {
		// better use convex_hull(perimeter) to avoid calculating
		// the convex_hull twice!!
		polygon hull = convex_hull();

		double perim = 0;
		// sum each segment of the convex hull
		for (int i = 1; i < hull._n; i++)
			perim += hull.vec_points[i].distance(hull.vec_points[i-1]);
		perim += hull.vec_points[0].distance(hull.vec_points[hull._n-1]);

		return perim;
	}
/*
	bool earQ(int i, int j, int k)
	{
		triangle t(vec_points[i], vec_points[k], vec_points[k]);
		if (cw(vec_points[i], vec_points[j], vec_points[k]))
			return false;
		
		for (int m = 0; m < _n; m++) {
			if ((m != i) && (m != j) && (m != k))
				if (t.contains(vec_points[m]))
					return false;
		}
		return true;
	}
*/
};

///////////////////////////////////////////////////////////////////////////
class triangle: public polygon {
public:
	triangle() : polygon(3) {};
	triangle(const vector< point<2> >& v) : polygon(v) {}
	triangle(const triangle& t) : polygon(t) {}		// copy constructor
	triangle(const point<2>& p1, const point<2>& p2, const point<2>& p3) {
		(*this).set_n(3);
		vec_points[0] = p1;
		vec_points[1] = p2;
		vec_points[2] = p3;
	}
	bool contains(const point<2>& p) const {
		// assumes points are in counterclockwise order!!
		for (int i = 0; i < 3; i++) {
			if (cw(vec_points[i], vec_points[(i+1)%3], p))
				return false;
		}
		return true;
	}
};
/*
///////////////////////////////////////////////////////////////////////////
bool earQ(const point<2>& p1, const point<2>& p2, const point<2>& p3, polygon& poly)
{
	triangle t(p1, p2, p3);
	if (cw(p1, p2, p3))
		return false;
	
	for (int i = 0; i < poly.get_n(); i++) {
		if (
	}
	return true;
}
*/
///////////////////////////////////////////////////////////////////////////
bool earQ(int i, int j, int k, const polygon& p)
{
	triangle t(p.vec_points[i], p.vec_points[k], p.vec_points[k]);
	if (cw(p.vec_points[i], p.vec_points[j], p.vec_points[k]))
		return false;
	
	for (int m = 0; m < p.get_n(); m++) {
		if ((m != i) && (m != j) && (m != k))
			if (t.contains(p.vec_points[m]))
				return false;
	}
	return true;
}


///////////////////////////////////////////////////////////////////////////
class triangulation {
private:
	vector<triangle> vec_triangles;

public:
	triangulation(int n) {
		vec_triangles.resize(n);
	}
	triangulation(const polygon& p) {
		int n = p.get_n();
		vector<int> vleft(n),	// left neighbor indices
						vright(n);	// rigth neighbor indices
		for (int j = 0; j < n; j++) {
			vleft[j] = ((j-1) + n) % n;
			vright[j] = ((j+1) + n) % n;
		}
		int i = n - 1;
		while ((int)vec_triangles.size() < (n-2)) {
			i = vright[i];
			if (earQ(vleft[i], i, vright[i], p)) {
				triangle t(p.vec_points[vleft[i]], p.vec_points[i], p.vec_points[vright[i]]);
				vec_triangles.push_back(t);
				vleft[vright[i]] = vleft[i];
				vright[vleft[i]] = vright[i];
			}
		}
	}
	bool contains(const point<2> p) const {
		for (int i = 0; i < (int)vec_triangles.size(); i++) {
			if (vec_triangles[i].contains(p))
				return true;
		}
		return false;
	}
};


///////////////////////////////////////////////////////////////////////////
// Author: fdibar
// Date: dec 01, 2005
// Uses: point
// Multidimensional segment class

template <unsigned int T>
class segment_t {
public:
    point<T> p1, p2;	// endpoints
};

///////////////////////////////////////////////////////////////////////////
template <unsigned int T>
class segment : public segment_t<T> {};

///////////////////////////////////////////////////////////////////////////
// template to provide constructor for a points of 2 dimensions
template <>     
class segment<2> : public segment_t<2> {
public:
	segment() {};
	segment(const point<2>& p, const point<2>& q) {
		p1 = p;
		p2 = q;
	}
	bool intersectsQ(const segment<2>& s) const {
		line<2>	ln1(p1, p2),
					ln2(s.p1, s.p2);

		if (ln1 == ln2)
			return (point_in_box(p1, s.p1, s.p2) ||
					point_in_box(p2, s.p1, s.p2) ||
					point_in_box(s.p1, p1, p2) ||
					point_in_box(s.p1, p1, p2) );
		
		if (ln1.parallelQ(ln2)) 
			return false;
		
		point<2> p;		// intersection point
		ln1.intersection_point(ln2, p);
		return (point_in_box(p, p1, p2) && point_in_box(p, s.p1, s.p2) );
	}
	bool intersectsQ(const point<2>& p) const {
		segment<2> s(p, p);
		return intersectsQ(s);
	}

};

///////////////////////////////////////////////////////////////////////////
// template to provide constructor for a points of 2 dimensions
template <>     
class segment<3> : public segment_t<3> {
	// TO DO
};



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

	int k = 0;	// dataset
	
	int c, r, o;	// cops, robbers, other citizens
	cin >> c >> r >> o;
	while (((c != 0) || (r != 0) || (o != 0)) && !cin.eof()) {
		k++;
		// READ INPUT
		vector< point<2> > vec_cops(c);
		vector< point<2> > vec_robs(r);
		vector< point<2> > vec_others(o);
		
		for (int i = 0; i < c; i++)
			cin >> vec_cops[i].x() >> vec_cops[i].y();

		for (int i = 0; i < r; i++)
			cin >> vec_robs[i].x() >> vec_robs[i].y();
		
		for (int i = 0; i < o; i++)
			cin >> vec_others[i].x() >> vec_others[i].y();
		
		// PROCESS
		polygon p_cops(vec_cops);
		polygon p_robs(vec_robs);

		polygon ph_cops = p_cops.convex_hull();
		polygon ph_robs = p_robs.convex_hull();

		triangulation t_cops(ph_cops);
		triangulation t_robs(ph_robs);

		// SHOW OUTPUT
		cout << "Data set " << k << ":" << endl;
		// process each citizen
		// if citizen is between 2 cops/robbers or in same place, 
		// consider safe/robbed
		for (int i = 0; i < o; i++) {
			cout << "     Citizen at " << vec_others[i];
			bool res = false;
			// cops
			if (ph_cops.get_n() >= 3) {
				if (t_cops.contains(vec_others[i])) {
					cout << " is safe." << endl;
					res = true;
				}
			} else {
				if (c == 2) {
					segment<2> seg(ph_cops.vec_points[0], ph_cops.vec_points[1]);
					if (seg.intersectsQ(vec_others[i])) {
						cout << " is safe." << endl;
						res = true;
					}
				} else if (c == 1)
					if (ph_cops.vec_points[0] == vec_others[i]) {
						cout << " is safe." << endl;
						res = true;
				}
			}
			if (!res) {
				// robbers
				if (ph_robs.get_n() >= 3) {
					if (t_robs.contains(vec_others[i])) {
						cout << " is robbed." << endl;
						res = true;
					}
				} else if (r == 2) {
					segment<2> seg(ph_robs.vec_points[0], ph_robs.vec_points[1]);
					if (seg.intersectsQ(vec_others[i])) {
						cout << " is robbed." << endl;
						res = true;
					}
				} else if (r == 1) {
					if (ph_robs.vec_points[0] == vec_others[i]) {
						cout << " is robbed." << endl;
						res = true;
					}
				}
			}
			if (!res)
				cout << " is neither." << endl;
		}

		// READ NEXT INPUT
		cin >> c >> r >> o;
		if ((c != 0) || (r != 0) || (o != 0))
			cout << endl;
	}
		
#ifdef DEBUG
	cout << START_DEBUG;

	cout << END_DEBUG;
#endif
	
	return 0;
}

/* @END_OF_SOURCE_CODE */

