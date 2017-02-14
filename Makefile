CC = g++
CFLAGS = -c -std=c++11 -march=native -O2

LIBS := ./lib/libGLEW.a
LIBS += ./lib/libglfw3.a

INCLUDE := -I./include

LINKS := -lGL
LINKS += -lXi
LINKS += -lX11
LINKS += -lXrandr
LINKS += -lXcursor
LINKS += -lXxf86vm
LINKS += -lXinerama
LINKS += -ldl
LINKS += -lpthread

all: engine

engine: main.o shaderProgram.o resources.o
	$(CC) -g $? $(LIBS) $(LINKS) -o $@

main.o:
	$(CC) $(CFLAGS) main.cpp $(INCLUDE) -o $@

shaderProgram.o: shaderProgram.cpp
	$(CC) $(CFLAGS) $? $(INCLUDE) -o $@

resources.o: resources.cpp
	$(CC) $(CFLAGS) $? $(INCLUDE) -o $@

clean:
	-rm -f *.o engine
