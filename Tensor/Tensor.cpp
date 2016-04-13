#include "Tensor.h"

// Written by Scary (overloaded operator by John

ostream& operator<<(ostream& stream, const Tensor& t) {
	stream << "x=" << t.x << "  y=" << t.y << "  z=" << t.z << endl;

	return stream;
}

Tensor::Tensor(double x_value, double y_value, double z_value)
{

	x = x_value;
	y = y_value;
	z = z_value;
}

Tensor::~Tensor()
{
}

void Tensor::setx(double x_value){ x = x_value;}
void Tensor::sety(double y_value){ y = y_value;}
void Tensor::setz(double z_value){ z = z_value;}

void Tensor::set(double x_value, double y_value, double z_value)
{
	x = x_value;
	y = y_value;
	z = z_value;
}

void Tensor::clear() {
	set(0,0,0);
}

double Tensor::getx(){ return x; }
double Tensor::gety(){ return y; }
double Tensor::getz(){ return z; }

double Tensor::getr(){ return std::sqrt(pow(x, 2)+pow(y, 2)+pow(z,2)); }

double Tensor::gettheta()
{
		if(x > 0 && y >= 0){return atan((y/ x));}
		else if(x < 0 && y >= 0){return atan(( y/ x))+ 4*atan(1);}
		else if(x < 0 && y <= 0){return atan((y/ x))+ 4*atan(1);}
		else if(x > 0 && y <= 0){return atan((y/ x))+ 8*atan(1);}
		else if(x == 0 && y >= 0){return 2*atan(1);}
		else if(x == 0 && y <= 0){return 6*atan(1);}
		return 0;
}


Tensor Tensor::operator+(Tensor t2) {
	double x = this->x + t2.x;
	double y = this->y + t2.y;
	double z = this->z + t2.z;
	Tensor newT(x, y, z);

	return newT;
}

Tensor Tensor::operator-(Tensor t2) {
	Tensor inverse = t2 * (-1);

	return (*this) + inverse;
}

Tensor Tensor::operator*(double k) {
	double x = k*(this->x);
	double y = k*(this->y);
	double z = k*(this->z);

	Tensor newT(x, y, z);

	return newT;
}

Tensor Tensor::operator/(double k) {
	k = 1/k;

	return (*this)*k;
}
