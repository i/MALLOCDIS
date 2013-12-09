CC=gcc
HARDORE=-pedantic -ansi -Wall -Werror
CFILES=./src/main.c


all:
		$(CC) $(CFILES)  -o ???

HARDCORE:
		$(CC) $(CFILES) $(HARDCORE) -o ???

debug:
		$(CC) -g $(CFILES)  $(CFLAGS) -o ???

clean:
		rm ???
