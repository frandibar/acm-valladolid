/* @JUDGE_ID:  40922FK  10180  C++  */
/* @BEGIN_OF_SOURCE_CODE */    
/**************************************************************************
 Solution to Problem 10180 - Rope Crisis in Ropeland!
 by: Francisco Dibar
 date: Nov-22-2005
**************************************************************************/

//#define DEBUG
//#define ONLINE_JUDGE 
#include <iostream>
#ifndef ONLINE_JUDGE 
	#include <fstream>
#endif 
#include <cmath>	// sqrt, fabs
#include <iomanip>	// setprecision
#include <cstdlib>	// min, max

#define START_DEBUG	"START DEBUG ********************************************************************\n"
#define END_DEBUG	"END DEBUG **********************************************************************\n"

#define EPSILON	0.0001
#define PI			3.1415926535897932384626433832795

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
double rope_length(point2d p, point2d q, double r)
{
	// c = center of circle (always (0,0))
	// determine if the line between p and q intersects the circle
	// that is, if the distance (d) from c to pq (at point s) is less than r,
	// then if s lies in the box determined by p and q, there is an 
	// intersection, so must calculate ta and tb, points of the 
	// circle such that pta and qtb are tangent to the circle.
	// then calculate the shortest perimeter from t1 to t2
	// 
	// if d > r || not point_in_box
	// 	return dist(p,q)
	// else
	// 	return dist(p,t1) + dist(p,t2) + dist(t1,t2,circ)

	line pq;
	points_to_line(p, q, &pq);

	point2d c, pclose;
	c.x = c.y = 0.0;		// center of circle
	closest_point(c, pq, &pclose);
	double dd = square_distance(pclose, c);
	double rr = r*r;

	if ((dd > rr) || !point_in_box(pclose, p, q) )
		return sqrt(square_distance(p, q));
	else {
		// return dist(p,t1) + dist(p,t2) + dist(t1,t2,circ)

		// find t1, t2
		double dpc2 = square_distance(p, c);
		double dpta = sqrt(fabs(dpc2 - rr));	// fabs to prevent -
    	// points of circle where tangent lines intersect	
        point2d ta1, tb1, ta2, tb2;	
		// t1
		double alfa, beta, anglea, angleb;
		if (fabs(p.x) > EPSILON)
			alfa = atan(p.y / p.x);
		else
			if (p.y > 0)
				alfa = PI / 2.0;
			else
				alfa = 1.5 * PI;		// 3pi/2
		beta = asin(dpta / sqrt(dpc2));
		anglea = alfa + beta;
		angleb = alfa - beta;
		ta1.x = r * cos(anglea);
		ta1.y = r * sin(anglea);
		ta2.x = r * cos(angleb);
		ta2.y = r * sin(angleb);

		// t2
		double dqc2 = square_distance(q, c);
		double dqtb = sqrt(fabs(dqc2 - rr));	// fabs to prevent -
		if (fabs(q.x) > EPSILON)
			alfa = atan(q.y / q.x);
		else
			if (q.y > 0)	// just interested in the sign
				alfa = PI / 2.0;
			else
				alfa = 1.5 * PI;		// 3pi/2
		beta = asin(dqtb / sqrt(dqc2));
		anglea = alfa + beta;
		angleb = alfa - beta;
		tb1.x = r * cos(anglea);
		tb1.y = r * sin(anglea);
		tb2.x = r * cos(angleb);
		tb2.y = r * sin(angleb);

		// calculate the perimeter from t1 to t2 (choose min)
		line lt;
		points_to_line(ta1, tb1, &lt);
		closest_point(c, lt, &pclose);
		double d = sqrt(square_distance(pclose, c));
		double angle = acos(d / r);
		double perim1 = 2 * angle * r;

		points_to_line(ta1, tb2, &lt);
		closest_point(c, lt, &pclose);
		d = sqrt(square_distance(pclose, c));
		angle = acos(d / r);
		double perim2 = 2 * angle * r;
		double perim = min(perim1, perim2);

		points_to_line(tb1, ta1, &lt);
		closest_point(c, lt, &pclose);
		d = sqrt(square_distance(pclose, c));
		angle = acos(d / r);
		perim1 = 2 * angle * r;
		perim = min(perim1, perim);

		points_to_line(tb1, ta2, &lt);
		closest_point(c, lt, &pclose);
		d = sqrt(square_distance(pclose, c));
		angle = acos(d / r);
		perim1 = 2 * angle * r;
		perim = min(perim1, perim);

		return dpta + dqtb + perim;
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

	int cases;
	cin >> cases;

	for (int k = 0; k < cases; k++) {
		
		// READ INPUT
		point2d p1, p2;
		double r;
		cin >> p1.x >> p1.y >> p2.x >> p2.y >> r;

		// PROCESS
		double res = rope_length(p1, p2, r);

		// SHOW OUTPUT
		cout.setf(ios::fixed);
		cout.precision(3);
		cout << res << endl;
	}
		
#ifdef DEBUG
	cout << START_DEBUG;

	cout << END_DEBUG;
#endif
	
	return 0;
}

/* @END_OF_SOURCE_CODE */

