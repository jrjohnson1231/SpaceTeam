#include "Body.h"
#include "Planet.h"
#include <iostream>
#include <string>

using namespace std;

int main()
{

	string file;
	cout<<"Enter the file name with the planet data"<<endl;
	cin>>file;
	string name, imagename;
	double m, x, y, z, vx, vy, vz;
	fstream fin(file.c_str());
	if(!fin)
	{
		cout<<"Could not open file. Try again"<<endl;
		return 1;
	}
	while (!fin.eof())//assumes the file is all correct
	{
		getline (fin, name, ",");
		cout<<name<<" ";
		getline (fin, imagename, ",");
		cout<<imagename<<" ";
		fin>>m;
		cout<<m<<" ";
		fin>>x;
		cout<<x<<" ";
		fin>>y;
		cout<<y<<" ";
		fin>>z;
		cout<<z<<" ";
		fin>>vx;
		cout<<vx<<" ";
		fin>>vy;
		cout<<vy<<" ";
		fin>>vz;
		cout<<vz<<" ";
		Planet newplanet(name,imagename,m,x,y,z,vx,vy,vz);
		cout<<endl<<endl<<"MADE A PLANET"<<endl<<endl;
		cout<<endl;
	}
return 0;
}