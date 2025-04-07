CC = gcc

all: main

main: main.c test.o
	$(CC) -o main main.c test.o

test.o: test.c
	$(CC) -c test.c -o test.o

clean:
	rm -f main test.o