#include <iostream>
#include "Tensor.h"
using namespace std;

int main()
{
	Tensor t(1,1);
	Tensor r(3,-4);
	cout << "t = [ " << t.getx() << ", " << t.gety() << ", " << t.getz() << " ]" << endl;
	cout << "r = [ " << r.getx() << ", " << r.gety() << ", " << r.getz() << " ]" << endl;
	cout << "raduis of t = " << t.getr() << endl;
	cout << "theta of t = " << t.gettheta() << endl;
	Tensor s = t+r;
	cout << "t + r = " << s.getx() << ", " << s.gety() << ", " << s.getz() << endl;
	s = t-r;
	cout << "t - r = " << s.getx() << ", " << s.gety() << ", " << s.getz() << endl;
	s = t*5;
	cout << "t * 5 = " << s.getx() << ", " << s.gety() << ", " << s.getz() << endl;
	s = t/5;
	cout << "t / 5 = " << s.getx() << ", " << s.gety() << ", " << s.getz() << endl;
}
