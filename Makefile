CC = g++
CCFLAGS = -F/Library/Frameworks
LD = g++
LDFLAGS = -g -Wall -framework SDL -framework SDL_image -framework SDL_ttf -F/Library/Frameworks
OBJECTS = main.o Planet.o Body.o  Charged.o Tensor/Tensor.o
EXECUTABLE = main

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(LD) -o $(EXECUTABLE) $(OBJECTS) $(LDFLAGS)

%.o: %.cpp
	$(CC) -o $@ -c $< $(CCFLAGS)

clean:
	rm $(EXECUTABLE) *.o
