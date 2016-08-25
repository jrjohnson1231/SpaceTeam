User Manual
===========

Special Libraries/Frameworks Needed: 
-----------------------------------
This project utilized SDL 1.2 for the graphics capabilities.
The flags in the Makefile are set so that the compiler looks in the /Library/Frameworks folder, explained more below.
SDL_image and SDL_ttf libraries are also used for image and text capabilities.

Building/Compilation Instructions:
----------------------------------
*This program has been tested to run on Macs. It has not been tested to run on the student machines. 
In the terminal/command line, enter the command ‘make’. This will compile all parts of the project and create an executable called ‘main’.
You must have the SDL, SDL_image, and SDL_ttf frameworks installed in the /Library/Frameworks directory of your Mac. If they are located elsewhere adjust the -F flags in the Makefile to point to the correct Frameworks directory.
To compile on other machines, open the Makefile and change the -F flags to point to the correct location of the required frameworks It is also possible to use the -L and -I flags to include the libraries and not the entire framework.
Enter the command ‘./main’ to run the executable. 

User Controls:
--------------
The file ‘planets.txt’ contains the data used to run the force-calculating simulation
To change the planets’ initial conditions, or to add more planets, the user must edit the text file, keeping in mind the following format: 
planetname,planet/image/file,mass,radius,xpos,ypos,zpos,xvelocity,yvelocity,zvelocity,
Example:
Earth,images/Earth_small.png,5.97e24,6.37e6,149.6e9,0,0,0,30000,0,
Moon,images/Moon_small.png,7.33e22,1.74e6,149.6e9,3.84e8,0,1022,30000,0,
Sun,images/Sun.png,1.989e30,6.96e8,0,0,0,0,0,0

Do NOT include a trailing comma for the last planet or it will attempt to read the next line!!!

The easiest place to store an image is in the provided images folder. The user can also specify their own textfile using the command line arguments displayed below. We have provided a few images and example systems in the repository.

2.  To run the program, compile and run with instructions from the previous section.
The program can take in up to two command line arguments.. These must be made in the form:
../main [filename] [dt]
	Where filename is the name of the file with planet data with the format in 1.
	Where dt is a positive integer representing the number of seconds between each force calculation.
3.  To exit the program, click the red circle/X at the top left of the window. 

Known Bugs:
----------
This force simulation is calculated using the Verlet Approximation Method. If you run the program for long enough, the entire system moves with respect to the screen. This is due to the nature of an approximation. Since the calculations are not exact, momentum and energy aren’t completely conserved, which causes the center of mass of the system to move about the frame. If the Verlet Method were able to create perfectly circular or perfectly elliptical motion, this problem would be gone. 
The text at the top of the screen is flashy and transparent because the graphics run so fast, and the text is updated every frame. We also used an unsigned long long, but it eventually overflows and gives incorrect, negative numbers. This is only an issue for simulations with a large dt.
If an image does not properly load, or does not exist, the program may produce a segmentation fault. The SDL_DisplayFormat() function in particular has been troublesome. We have tried to limit the use of these dangerous SDL functions, and have also attempted to catch these exceptions and are often successful. Occasionally however, the exception occurs inside the SDL internals, where we have no exception handling control. This is rare, but still possible.
The images are also not to scaled. They maintain their raw size for simulations.


Other Information:
-----------------
This project has not been tested over ssh, so we do not know if the Makefile will correctly build the project. In the Building/Compilation Instructions section we have suggested how the Makefile can be changed to compile on other machines.
