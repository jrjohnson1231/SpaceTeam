all: main

main: main.o Planet.o Tensor.o ChargedParticle.o Body.o
	g++ -g -Wall main.o ChargedParticle.o Body.o Planet.o  Tensor.o -o main -framework SDL -framework SDL_image -F/Library/Frameworks

main.o: main.cpp
	g++ -c main.cpp -F/Library/Frameworks

Tensor.o: Tensor/Tensor.cpp
	g++ -c Tensor/Tensor.cpp -F/Library/Frameworks
  
Planet.o: Planet.cpp
	g++ -c Planet.cpp -F/Library/Frameworks

ChargedParticle.o: ChargedParticle.cpp
	g++ -c ChargedParticle.cpp -F/Library/Frameworks

Body.o: Body.cpp
	g++ -c Body.cpp -F/Library/Frameworks

clean:
	rm  *.o main
