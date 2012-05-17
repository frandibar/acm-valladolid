#include <iostream>
#include <vector>

using std::cout;

template <int T>
class point_impl
{
public:
	point_impl() :
		m_Points(T, 0)
	{
	}

	inline double& coord(int coord)
	{return m_Points[coord];}

	inline const double& coord(int coord) const
	{return m_Points[coord];}

protected:
	std::vector<double> m_Points;
};

template <int T>
class point :
	public point_impl<T>
{
public:
};


template <>
class point<1> :
	public point_impl<1>
{
public:
	point(double a_1)
	{
		m_Points[0] = a_1;
	}
};

template<>
class point<2> :
	public point_impl<2>
{
public:
	point(double a_1, double a_2)
	{
		m_Points[0] = a_1;
		m_Points[1] = a_2;
	}
};


int main()
{
	point<2> a(5.4, 3);
	cout << a.coord(0) << std::endl;

	point<15> v;
	cout << v.coord(0) << std::endl;
	return 0;
}

