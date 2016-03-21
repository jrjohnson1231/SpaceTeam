all: main

main: mainplanet.o Planet.o Tensor.o
	g++ -g -Wall mainplanet.o Planet.o  Tensor.o -o main

mainplanet.o: mainplanet.cpp
	g++ -c mainplanet.cpp

Tensor.o: Tensor/Tensor.cpp
	g++ -c Tensor/Tensor.cpp
  
Planet.o: Planet.cpp
	g++ -c Planet.cpp

clean:
	rm  *.o main
