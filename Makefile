CC=gcc

all:
	$(CC) -o test test.c -lm

clean:
	-rm test
