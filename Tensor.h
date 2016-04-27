#ifndef TENSOR_H
#define TENSOR_H

#include <cmath> // sqrt, pow
#include <iostream> // cout
using namespace std;

class Tensor
{
	friend class Body;
	friend ostream& operator<<(ostream&, const Tensor&); // Prints vector in nice format

	public:
		// ConstructorS
		Tensor(double x_value=0, double y_value=0, double z_value=0);

		// Set functions
		void setx(double);
		void sety(double);
		void setz(double);
		void set(double,double,double=0); // Sets everything at once

		// Get functions
		double getx();
		double gety();
		double getz();
		double getr(); // Gets magnitude of tensor

		// Member functions
		void clear(); // Resets all values to 0

		// Overloaded operators
		Tensor operator+(Tensor);
		Tensor operator-(Tensor);
		Tensor operator*(double);
		Tensor operator/(double);

	private:
		// Object variables
		double x;
		double y;
		double z;
};

#endif
