CC = g++
CCFLAGS = 
LD = g++
LDFLAGS = -g -Wall -framework SDL -framework SDL_image -framework SDL_ttf
OBJECTS = main.o Object.o ../Planet.o ../Body.o Tensor.o Timer.o Window.o
EXECUTABLE = main

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(LD) -o $(EXECUTABLE) $(OBJECTS) $(LDFLAGS)

%.o: %.cpp
	$(CC) -o $@ -c $<

clean:
	rm $(EXECUTABLE) *.o
