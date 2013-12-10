CC=gcc
HARDORE=-pedantic -ansi -Wall -Werror
CFILES=./src/main.c


all: main

main:
		$(CC) ./src/main.c  -o main

main2:
		$(CC) ./src/main2.c  -o main2

main3:
		$(CC) ./src/main3.c  -o main3

HARDCORE:
		$(CC) $(CFILES) $(HARDCORE) -o main

debug:
		$(CC) -g $(CFILES)  $(CFLAGS) -o main

clean:
		rm main
