CC=gcc
HARDORE=-pedantic -ansi -Wall -Werror
CFILES=./src/main.c


all:
		$(CC) $(CFILES)  -o main

HARDCORE:
		$(CC) $(CFILES) $(HARDCORE) -o main

debug:
		$(CC) -g $(CFILES)  $(CFLAGS) -o main

clean:
		rm main
