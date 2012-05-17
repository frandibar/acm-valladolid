/* @JUDGE_ID:  40922FK  10195  C++  */
/* @BEGIN_OF_SOURCE_CODE */    
/**************************************************************************
 Solution to Problem 10195 - The Knights of the Round Table
 by: Francisco Dibar
 date: Nov-24-2005
**************************************************************************/

//#define DEBUG
//#define ONLINE_JUDGE 
#include <iostream>
#ifndef ONLINE_JUDGE 
	#include <fstream>
#endif 
#include <cmath>	// sqrt
#include <iomanip>	// setprecision
#include <algorithm>	// min, max

#define START_DEBUG	"START DEBUG ********************************************************************\n"
#define END_DEBUG	"END DEBUG **********************************************************************\n"

#define EPSILON	0.0001
#define PI		3.14159265

using namespace std;

typedef struct {
	double x, y;
} point2d;

typedef struct {
	// ax + by + c = 0
	double a, b, c;
} line;	

///////////////////////////////////////////////////////////////////////////
bool point_in_box(point2d s, point2d p, point2d q)
{
	point2d	p2,		// lower left corner
				q2;		// upper right corner
	p2.x = min(p.x, q.x);
	p2.y = min(p.y, q.y);
	q2.x = max(p.x, q.x);
	q2.y = max(p.y, q.y);

	if ( (s.x >= p2.x) && (q2.x >= s.x) &&
		  (s.y >= p2.y) && (q2.x >= s.x) )
	   return true;
	else
		return false;
}

///////////////////////////////////////////////////////////////////////////
void points_to_line(point2d p1, point2d p2, line *l)
// establish a canonical representation by insisting that y=1 if y!=0.
// otherwise, set x=1
{
	if (p1.x == p2.x) {
		// vertical line 1.x=k
		l->a = 1;
		l->b = 0;
		l->c = -p1.x;
	} else {
		l->b = 1;
		l->a = -(p1.y - p2.y) / (p1.x - p2.x);	// slope
		l->c = -(l->a * p1.x) - (l->b * p1.y);
	}
}

///////////////////////////////////////////////////////////////////////////
double square_distance(point2d p1, point2d p2)
// returns square distance between p1 and p2
{
	return ((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

///////////////////////////////////////////////////////////////////////////
void point_and_slope_to_line(point2d p, double m, line *l)
{
	l->a = -m;
	l->b = 1;
	l->c = -(l->a * p.x) - (l->b * p.y);
}

///////////////////////////////////////////////////////////////////////////
bool parallelQ(line l1, line l2)
{
	return ( (fabs(l1.a - l2.a) <= EPSILON) &&
			 (fabs(l1.b - l2.b) <= EPSILON) );
}

///////////////////////////////////////////////////////////////////////////
bool same_lineQ(line l1, line l2)
{
	return (parallelQ(l1, l2) && (fabs(l1.c - l2.c) <= EPSILON) );
}

///////////////////////////////////////////////////////////////////////////
bool intersection_point(line l1, line l2, point2d *p)
{
	if (same_lineQ(l1, l2)) {
		p->x = p->y = 0.0;
		return true;
	}
	if (parallelQ(l1,l2) == true) {
		return false;
	}

	p->x = (l2.b * l1.c - l1.b * l2.c) / (l2.a * l1.b - l1.a * l2.b);
	if (fabs(l1.b) > EPSILON)	// test for vertical line
		p->y = - (l1.a * p->x + l1.c) / l1.b;
	else
		p->y = - (l2.a * p->x + l2.c) / l2.b;
	
	return true;
}

///////////////////////////////////////////////////////////////////////////
void closest_point(point2d p, line l, point2d *cp)
{
	if (fabs(l.b) <= EPSILON) {		// vertical line
		cp->x = -l.c;
		cp->y = p.y;
		return;
	}

	if (fabs(l.a) <= EPSILON) {		// horizontal line
		cp->x = p.x;
		cp->y = -l.c;
		return;
	}
	// line with slope
	line perp;	// perpendicular to l through (x,y)
	point_and_slope_to_line(p, 1/l.a, &perp);
	intersection_point(l, perp, cp);
}	


///////////////////////////////////////////////////////////////////////////
double radius(double a, double b, double c)
// returns the radius of the maximum circle inside triangle with
// sides a, b and c
{
	// cos ca = (a^2 + c^2 - b^2) / (2ac)
	double ca;	// angle between sides c and a
	ca = acos((a*a + c*c - b*b) / (2*a*c));
	// side a lies along x axis, from p to q
	point2d p, q;
	p.x = 0.0;
	p.y = 0.0;
	q.x = a;
	q.y = 0.0;

	line 	pb,	// line from p with angle ca/2
			qc;	// line from q with angle ab/2
	point2d w, z;
	w.x = a;
	w.y = a * tan(ca / 2.0);
	points_to_line(p, w, &pb);

	// angle between sides a and b
	double ab = acos((a*a + b*b - c*c) / (2*a*b));
	z.x = 0;
	z.y = a * tan(ab / 2.0);
	points_to_line(q, z, &qc);

	point2d pc;
	intersection_point(pb, qc, &pc);	
	return pc.y;
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

	double a, b, c;
	cin >> a >> b >> c;
	while (!cin.eof()) {
		// PROCESS
		double r = radius(a, b, c);
		// SHOW OUTPUT
		cout.setf(ios::fixed);
		cout.precision(3);
		cout << "The radius of the round table is: " << r << endl;
		
		// READ NEXT INPUT
		cin >> a >> b >> c;
	}
		
#ifdef DEBUG
	cout << START_DEBUG;

	cout << END_DEBUG;
#endif
	
	return 0;
}

/* @END_OF_SOURCE_CODE */

