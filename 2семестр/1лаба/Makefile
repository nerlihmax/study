CC=gcc
CFLAGS=-Wall

all: run

main: clean
	$(CC) $(CFLAGS) main.c -o main.o

clean:
	rm main.o

run: main
	./main