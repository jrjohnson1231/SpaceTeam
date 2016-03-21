all: main

main: mainplanet.o Planet.o 
	g++ mainplanet.o Planet.o  -o main

mainplanet.o: mainplanet.cpp
	g++ -c mainplanet.cpp
  
Planet.o: Planet.cpp
	g++ -c Planet.cpp

clean:
	rm  *.o

