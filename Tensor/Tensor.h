#ifndef TENSOR_H
#define TENSOR_H

// Written by Scary.

#include <cmath>
#include <iostream>
using namespace std;

class Tensor
{
	friend class Body;
	friend ostream& operator<<(ostream&, const Tensor&);

	public:
		// Constructor - Create/set Tensor values
		Tensor(double x_value = 0, double y_value = 0, double z_value = 0);
		// Destructor
		~Tensor();

		//Set functions
		void setx(double);
		void sety(double);
		void setz(double);
		// This one sets both/all of the data simputaneously
		void set(double,double,double = 0);

		// This resets all the data to 0
		void clear();

		//Get functions
		double getx();
		double gety();
		double getz();
		// Get the length of the Tensor
		double getr();
		// Get the angle of the Tensor
		double gettheta();

		// Overloaded operators
		Tensor operator+(Tensor);
		Tensor operator-(Tensor);
		Tensor operator*(double);
		Tensor operator/(double);

	private:
		double x;
		double y;
		double z;
};

#endif // TENSOR_H
