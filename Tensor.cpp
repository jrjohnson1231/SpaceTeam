#include "Tensor.h"

/* ----- CONSTRUCTORS ----- */

/* Initializes all values */
Tensor::Tensor(double x_value, double y_value, double z_value)
{
	x = x_value;
	y = y_value;
	z = z_value;
}


/* ----- SET FUNCTIONS */

void Tensor::setx(double x_value) 
{
	x = x_value;
}

void Tensor::sety(double y_value)
{
	y = y_value;
}

void Tensor::setz(double z_value)
{
	z = z_value;
}

/* Set the whole tensor at once */
void Tensor::set(double x_value, double y_value, double z_value)
{
	x = x_value;
	y = y_value;
	z = z_value;
}


/* ----- GET FUNCTIONS */

double Tensor::getx()
{
	return x;
}
double Tensor::gety()
{
	return y;
}
double Tensor::getz()
{
	return z;
}

/* Magnitude of tensor */
double Tensor::getr()
{
	return std::sqrt(pow(x, 2)+pow(y, 2)+pow(z,2));
}


/* ----- MEMBER FUNCTIONS ----- */

void Tensor::clear() 
{
	set(0,0,0);
}


/* ----- OVERLOADED OPERATORS ----- */

ostream& operator<<(ostream& stream, const Tensor& t) 
{
	stream << "x=" << t.x << "  y=" << t.y << "  z=" << t.z << endl;
	return stream;
}

Tensor Tensor::operator+(Tensor t2) 
{
	double x = this->x + t2.x;
	double y = this->y + t2.y;
	double z = this->z + t2.z;
	Tensor newT(x, y, z);

	return newT;
}

Tensor Tensor::operator-(Tensor t2) 
{
	Tensor inverse = t2 * (-1);

	return (*this) + inverse;
}

Tensor Tensor::operator*(double k) 
{
	double x = k*(this->x);
	double y = k*(this->y);
	double z = k*(this->z);

	Tensor newT(x, y, z);

	return newT;
}

Tensor Tensor::operator/(double k) 
{
	k = 1/k;

	return (*this)*k;
}