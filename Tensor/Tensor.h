#ifndef TENSOR_H
#define TENSOR_H

#include <cmath>

class Tensor
{
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
		template<typename T>
		Tensor operator*(T);
		template<typename T>
		Tensor operator/(T);

	private:
		double x;
		double y;
		double z;
};

#endif // TENSOR_H
