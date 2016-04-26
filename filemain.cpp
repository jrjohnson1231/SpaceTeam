//#include "Body.h"
#include "Planet.h"
#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <vector>
using namespace std;

//this is a driver that reads in planet information from a file
//it uses it to create new planets

/*template<typename T>
class FileReader() 
{
	public:
		FileReader();
		~FileReader();
	private:
		vector<T> objects;i*/

vector<Planet *> getObjects();
int main()
{
	vector<Planet *> objects = getObjects();
	return 0;
}
	
vector<Planet *> getObjects() {
	vector<Planet *> objects;
	string file="planets.txt";
	/*cout<<"Enter the file name with the planet data"<<endl;
	cin>>file;*/
	string name, imagename;
	string m, r, x, y, z, vx, vy, vz;
	ifstream fin(file.c_str());
	if(!fin)
	{
		cout<<"Could not open file. Try again"<<endl;
		return objects;
	}
	//read in all information from the file
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
		getline(fin,r,',');
		cout<<r<<" ";
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
		//add a new planet
		Planet *newP = new Planet(name,imagename,atof(m.c_str()),atof(r.c_str()),atof(x.c_str()),atof(y.c_str()),atof(z.c_str()),atof(vx.c_str()),atof(vy.c_str()),atof(vz.c_str()));
		objects.push_back(newP);
		cout<<endl;
		// Flush trailing \n
		string dummy;
		getline(fin, dummy);
	}
	Planet::update(1);
	Planet::update(1);
	return objects;
	for (int i = 0; i < objects.size(); i++)
	{
		objects.erase(objects.begin());
	}
	//return 0;
}

Planet newPlanet(string name, string imagename, double m, double x, double y, double z, double vx, double vy, double vz)
{
	Planet newP(name, imagename, m, x, y, z, vx, vy, vz);
	return newP;
}
