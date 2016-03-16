#include <iostream>
#include "Tensor.h"
using namespace std;

int main()
{
	Tensor t(1,1);
	cout << t.getr() << endl;
	cout << t.gettheta() << endl;
}
