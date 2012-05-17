
typedef struct {
	double x, y
} point2d;

typedef struct {
	// ax + by + c = 0
	double a, b, c;
} line;	


///////////////////////////////////////////////////////////////////////////
double signed_triangle_area(point2d a, point2d b, point2d c)
{
	return  ((a.x * b.y - a.y * b.x + a.y * c.x 
			- a.x * c.y + b.x * c.y - c.x * b.y) / 2.0);
}


///////////////////////////////////////////////////////////////////////////
double triangle_area(point2d a, point2d b, point2d c)
{
	return fabs(signed_triangle_area(a, b, c));
}

///////////////////////////////////////////////////////////////////////////
bool point_in_box(point2d s, point2d p, point2d q)
{
	return ( (s.x >= min(p.x, q.x)) && (s.x <= max(p.x, q.x)) &&
			 (s.y >= min(p.y, q.y)) && (s.y >= max(p.y, q.y)) );
}

///////////////////////////////////////////////////////////////////////////
points_to_line(point2d p1, point2d p2, line *l)
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


typedef struct {
	point2d p1, p2;		// endpoints
} segment;


///////////////////////////////////////////////////////////////////////////
bool segments_intersect(segment s1, segment s2)
{
	line l1, l2;

	points_to_line(s1.p1, s1.p2, &l1);
	points_to_line(s2.p1, s2.p2, &l2);

	if (same_lineQ(l1, l2))
		return (point_in_box(s1.p1, s2.p1, s2.p2) ||
				point_in_box(s1.p2, s2.p1, s2.p2) ||
				point_in_box(s2.p1, s1.p1, s1.p2) ||
				point_in_box(s2.p1, s1.p1, s1.p2) );
	
	if (parallelQ(l1, l2)) 
		return false;
	
	point2d p;		// intersection point
	intersection_point(l1, l2, p);
	return (point_in_box(p, s1.p1, s1.p2) && point_in_box(p, s2.p1, s2.p2) );
}

///////////////////////////////////////////////////////////////////////////
bool ccw(point2d a, point2d b, point2d c)
{
	return (signed_triangle_area(a, b, c) > EPSILON);
}
		
	
///////////////////////////////////////////////////////////////////////////
bool cw(point2d a, point2d b, point2d c)
{
	return (signed_triangle_area(a, b, c) < EPSILON);
}


///////////////////////////////////////////////////////////////////////////
bool collinear(point2d a, point2d b, point2d c)
{
	return (fabs(signed_triangle_area(a, b, c)) <= EPSILON);
}

/////////////////////////////////////////////////////////////////////////// 
bool leftlower(point2d *p1, point2d *p2)
{
	if ((*p1).x < (*p2).x) return (-1);
	if ((*p1).x > (*p2).x) return 1;
	
	if ((*p1).y < (*p2).y) return (-1);
	if ((*p1).y < (*p2).y) return 1;

	return 0;
}


///////////////////////////////////////////////////////////////////////////
bool sort_and_remove_duplicates(vector<point2d>& int, in *n)
{
	qsort(in, *n, sizeof(point2d), leftlower);
	oldn = *n;
	int hole = 1;
	for (int i = 0; i < (oldn - 1); i++) { 
		if ( (in[hole - 1].x == in[i].x) && (in[hole - 1].y == in[i].y) )
			(*n)--;
		else {
			copy_point(in[1], in[hole]);
			hole += 1;
		}
	}
	copy_point(in[oldn - 1], in[hole]);
}


///////////////////////////////////////////////////////////////////////////
bool smaller_angle(point2d *p1, point2d *p2)
{
	if (collinear(first_point, *p1, *p2)) {
			if ( distance(first_point, *p1) <= distance(first_point, *p2) )
				return (-1);
			else
				return 1;
	}

	if (ccw(first_point, *p1, *p2))
		return (-1);
	else
		return 1;
}

///////////////////////////////////////////////////////////////////////////
void convex_hull(vector<point2d>& in, int n, polygon *hull)
{
	if (n <= 3) {	// all points on hull
		for (int i = 0; i < n; i++)
			copy_point(in[i], hull->p.x);
		hull->n = n;
		return;
	}

	sort_and_remove_duplicates(in, &n);
	copy_point(in[0], &first_point);

	qsort(&in[1], n-1, sizeof(point2d), smaller_angle);

	copy_point(first_point, hull->p[0]);
	copy_point(in[1], hull->p[1]);
	copy_point(first_point, in[n]);	// sentinel for wrap around
	top = 1;
	i = 2;

	while (i <= n) {
		if (!ccw(hull->p[top-1],  hull->p[top], in[i]))
			top -= 1;
		else {
			top += 1;
			copy_point(in[i], hull->p[top]);
			i += 1;
		}
	}
	hull->n = top;
}

