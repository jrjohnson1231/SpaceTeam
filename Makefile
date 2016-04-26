CC = g++
CCFLAGS = -F/Library/Frameworks -std=c++11
LD = g++
LDFLAGS = -g -Wall -framework SDL -framework SDL_image -framework SDL_ttf -F/Library/Frameworks
OBJECTS = filemain.o Planet.o Body.o  Charged.o Tensor/Tensor.o
EXECUTABLE = filemain

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(LD) -o $(EXECUTABLE) $(OBJECTS) $(LDFLAGS)

%.o: %.cpp
	$(CC) -o $@ -c $< $(CCFLAGS)

clean:
	rm $(EXECUTABLE) *.o
