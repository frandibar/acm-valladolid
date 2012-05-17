#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>

struct Point
{
	Point(int a_X, int a_Y) :
		x(a_X), y(a_Y)
	{}

	int x;
	int y;
};

struct MyFun :
	public std::binary_function<Point, Point, bool>
{
	MyFun(const Point& a_Point) :
		m_P(a_Point)
	{}

	bool operator()(const Point& a_L, const Point& a_R)
	{
		double da = (a_L.x - m_P.x)*(a_L.x - m_P.x) + (a_L.y - m_P.y)*(a_L.y - m_P.y);
		double db = (a_R.x - m_P.x)*(a_R.x - m_P.x) + (a_R.y - m_P.y)*(a_R.y - m_P.y);
		return da < db;
	}

	Point m_P;
};

std::ostream& operator<<(std::ostream& a_Os, const Point& a_P)
{
	a_Os << "(" << a_P.x << ", " << a_P.y << ")";
	return a_Os;
}

int main()
{
	std::vector<Point> points;

	points.push_back(Point(1, 1));
	points.push_back(Point(2, 1));
	points.push_back(Point(1, 3));

	/*
	MyFun f(Point(0, 0));

	f( Point(0, 0), Point(0, 0) );
	*/

	std::sort(points.begin(), points.end(), MyFun(Point(1, 4)) );
	std::copy(points.begin(), points.end(), std::ostream_iterator<Point>(std::cout, "\n") );

	return 0;
}
