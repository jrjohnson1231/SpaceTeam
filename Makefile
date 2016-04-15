all: main

main: main.o Planet.o Tensor.o ChargedParticle.o Body.o
	g++ -g -Wall main.o ChargedParticle.o Body.o Planet.o  Tensor.o -o main

main.o: main.cpp
	g++ -c main.cpp

Tensor.o: Tensor/Tensor.cpp
	g++ -c Tensor/Tensor.cpp
  
Planet.o: Planet.cpp
	g++ -c Planet.cpp

ChargedParticle.o: ChargedParticle.cpp
	g++ -c ChargedParticle.cpp

Body.o: Body.cpp
	g++ -c Body.cpp

clean:
	rm  *.o main
