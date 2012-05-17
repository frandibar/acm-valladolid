#include <iostream>

using namespace std;

inline bool closeEnough(double a, double b, double eps)
// compare the tolerance
{
	return ((a > b) ? (a-b < eps) : (b-a < eps));
}

double squareRoot(double x, double epsilon)
// find square root of x with the given precision
{
	double y = x;

  	while (!closeEnough(x, y*y, epsilon))
     	y = (y + x / y) / 2.0;
  	return y;
}

int main()
{
  	double x, sqrt, epsilon;

	cin >> x;
	epsilon = 0.005;
	cout << "square root of " << x << " is " << squareRoot(x,epsilon) << endl;
	cin >> x;
	return 0;
}

