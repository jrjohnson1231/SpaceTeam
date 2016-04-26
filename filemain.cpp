//#include "Body.h"
#include "Planet.h"
#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <vector>
using namespace std;

int main()
{
	vector<Planet> planets;
	string file="planets.txt";
	/*cout<<"Enter the file name with the planet data"<<endl;
	cin>>file;*/
	string name, imagename;
	string m, x, y, z, vx, vy, vz;
	ifstream fin(file.c_str());
	if(!fin)
	{
		cout<<"Could not open file. Try again"<<endl;
		return 1;
	}
	while (!fin.eof())//assumes the file is all correct
	{
		getline(fin,name,',');
		//fin>>name;
		cout<<name<<" ";
		//fin>>imagename;
		getline(fin, imagename,',');
		cout<<imagename<<" ";
		getline(fin,m,',');
		cout<<m<<" ";
		getline(fin,x,',');
		cout<<x<<" ";
		getline(fin,y,',');
		cout<<y<<" ";
		getline(fin,z,',');
		cout<<z<<" ";
		getline(fin,vx,',');
		cout<<vx<<" ";
		getline(fin,vy,',');
		cout<<vy<<" ";
		getline(fin,vz,',');
		cout<<vz<<" ";
		Planet *newplanet=new Planet(name,imagename,atof(m.c_str()),atof(x.c_str()),atof(y.c_str()),atof(z.c_str()),atof(vx.c_str()),atof(vy.c_str()),atof(vz.c_str()));
		planets.push_back(*newplanet);
		cout<<endl;
	}
	cout<<Planet::planets.size()<<endl;
	Planet::update(1);
	delete planets;
	return 0;
}
