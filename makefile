CC=g++
CFLAGS=-I. -std=c++0x -lpthread -Wall
OBJ = main.cpp server.cpp client.cpp clientCluster.cpp 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

server: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
