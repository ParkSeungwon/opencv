CC = g++
OBJ = $(wildcard *.o)
EXE = $(patsubst %.x, ../%.x, $(wildcard *.x))
opencvLIB = $(shell pkg-config opencv4 --libs)

all : $(EXE)

../%.x : %.x $(OBJ)
	$(CC) -o $@ $< $(OBJ) $(opencvLIB) -lpthread -lrt -lstdc++fs 


