CC=g++
CFLAGS=-std=c++17 -Wall -O2 -g

all: main

test: all
	./main < input.txt

custom: all
	./main

clean:
	rm *.o

main: main.o
	$(CC) $^ -o $@ $(CFLAGS)
	
main.o: main.cpp
	$(CC) $^ -c $@ $(CFLAGS)
