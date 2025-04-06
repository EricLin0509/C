all: main

main: main.c test.o
	gcc -o main main.c test.o

test.o: test.c
	gcc -c test.c -o test.o

clean:
	rm -f main test.o