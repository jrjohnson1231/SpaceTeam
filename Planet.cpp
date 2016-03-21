#include "Planet.hpp"

Planet::Planet(double m, double x, double y, double z)
{
	mass=m;
	pos.set(x,y,z);
}

Tensor Planet::calcForce(Planet p)
{
	double G=6.67e-11; 
	//totalForce=(G*mass*p.getMass())/(pos.distance(p.getPos())*pos.distance(p.getPos()));
	totalForce.setx((G*mass*p.getMass())/((p.getx()-pos.getx())*(p.getx()-pos.getx())));
	if(pos.getx()>p.getx())
	{
		totalForce.setx(totalForce.getx()*-1);
	}
	return totalForce;
}

Tensor Planet::calcAccel()
{
	accel.setx(totalForce.getx()/mass);
	accel.sety(totalForce.gety()/mass);
	accel.setz(totalForce.getz()/mass);
	return accel;
}

double Planet::getMass()
{
	return mass;
}

double Planet::distance(Planet p)
{
	return sqrt((pos.getx()-p.getx())*(pos.getx()-p.getx())+(pos.gety()-p.gety())*(pos.gety()-p.gety())+(pos.getz()-p.getz())*(pos.getz()-p.getz()));
}

/*Tensor Planet::getPos()
{
	return pos;
}*/

double Planet::getx()
{
	return pos.getx();
}

double Planet::gety()
{
	return pos.gety();
}

double Planet::getz()
{
	return pos.getz();
}

void Planet::update(double dt)
{
	pos.setx(pos.getx()+vel.getx()*dt);
	cout<<"pos "<<pos.getx()<<endl;
	pos.sety(pos.gety()+vel.gety()*dt);
	pos.setz(pos.getz()+vel.getz()*dt);
	vel.setx(vel.getx()+accel.getx()*dt);
	cout<<"vel "<<vel.getx()<<endl;
	vel.sety(vel.gety()+accel.gety()*dt);
	vel.setz(vel.getz()+accel.getz()*dt);
}




