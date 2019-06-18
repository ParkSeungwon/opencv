CC = g++
OBJ = $(wildcard *.o)
EXE = $(patsubst %.x, ../%.x, $(wildcard *.x))
opencvLIB = $(shell pkg-config opencv --libs)

all : $(EXE)

../%.x : %.x $(OBJ)
	$(CC) -o $@ $< $(OBJ) -lzezeon $(opencvLIB) -lpthread -lrt


