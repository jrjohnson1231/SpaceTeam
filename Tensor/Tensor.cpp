#include "Tensor.h"

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
