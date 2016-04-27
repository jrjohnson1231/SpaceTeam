#include "Window.h"
#include "Timer.h"
#include "Tensor.h"
#include "Planet.h"
#include <iostream>
#include <string>
#include <vector>

#define DT 1800

//vector<Body *> readFile(string);
//void cleanup(vector<Body *>);

int main ( int argc, char** argv )
{
	//vector<Body *> objects = readFile("planets.txt");
	Tensor t(0,0);
	Tensor t2(0,0);
	cout<<argc<<endl;
	int count =0;
	if (argc==3)
    {
      for (count = 1; count < argc; count++)
		{
	 		printf("argv[%d] = %s\n", count, argv[count]);
	 		Window w("Test",argv[1],800,600,stoull(argv[2]));
	 		// Run application, handle events, etc.
			w.run();
		}
    }
    else if (argc==1)
    {
    	Window w("Test","planets.txt",800,600);
    	// Run application, handle events, etc.
		w.run();
    }
    else 
    {
    	cout<<"That is not a valid command line argument."<<endl<<"Enter in the form ./main filename dt"<<endl;
    }
	
	//cleanup(objects);
	return 0;
}

/*vector<Body *> readFile(string file)
{
	vector<Body *> objects;
	string name, imagename;
	string m, x, y, z, vx, vy, vz;
	ifstream fin(file.c_str());
	if(!fin)
	{
		cout<<"Could not open file. Try again"<<endl;
		return objects;
	}
	while (!fin.eof())//assumes the file is all correct
	{
		getline(fin,name,',');
		//fin>>name;
		//fin>>imagename;
		getline(fin, imagename,',');
		getline(fin,m,',');
	getline(fin,x,',');
		getline(fin,y,',');
		getline(fin,z,',');
		getline(fin,vx,',');
		getline(fin,vy,',');
		getline(fin,vz,',');
		Body *newP = new Planet(name,imagename,atof(m.c_str()),atof(x.c_str()),atof(y.c_str()),atof(z.c_str()),atof(vx.c_str()),atof(vy.c_str()),atof(vz.c_str()));
		if (newP != NULL)
		{
			objects.push_back(newP);
		}
		else
		{
			cout << "Could not initialize " << name << endl;
		}
		// Flush trailing \n
		string dummy;
		getline(fin, dummy);
	}
	return objects;
}*/

/*void cleanup(vector<Body *> objects)
{
	for (int i = 0; i < objects.size(); i++)
	{
		objects.erase(objects.begin());
	}
}*/
