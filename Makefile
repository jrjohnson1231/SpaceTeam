CC = g++
CCFLAGS = -F/Library/Frameworks -std=c++11
LD = g++
LDFLAGS = -Wall -framework SDL -framework SDL_image -framework SDL_ttf -F/Library/Frameworks
OBJECTS = main.o Planet.o Charged.o Body.o Tensor.o Timer.o Window.o
EXECUTABLE = main

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(LD) -o $(EXECUTABLE) $(OBJECTS) $(LDFLAGS)

$(EXECUTABLE).o: $(EXECUTABLE).cpp
	$(CC) $(CCFLAGS) -o $@ -c $<

%.o: %.cpp %.h
	$(CC) $(CCFLAGS) -o $@ -c $<

clean:
	rm $(EXECUTABLE) *.o
