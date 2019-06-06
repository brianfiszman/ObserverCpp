CC=g++
CFLAGS=-I. -std=c++0x -lpthread -Wall
PROG=server
SRCS := $(patsubst %.cpp,%.o,$(wildcard *.cpp))
SRCS += $(patsubst %.cpp,%.o,$(wildcard workers/*.cpp))
SRCS += $(patsubst %.cpp,%.o,$(wildcard helpers/*.cpp))

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(PROG): $(SRCS)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f $(PROG)
	rm -f *.o
	rm -f */*.o
	rm -f */*/*.o
	rm -f */*/*/*.o
