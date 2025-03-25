CC = gcc
CFLAGS = -Wall
LDFLAGS =
EXEC = main

SRCFILES = $(wildcard *.c)
OBJFILES = $(patsubst %.c, %.o, $(SRCFILES))

all: main

main: $(OBJFILES)
	$(CC) $(CFLAGS) -o reseau $^

%.o: %.c
	$(CC) $(LDFLAGS) -o $@ -c $<

.PHONY: clean mrproper

clean:
	rm -rf *.o

mrproper: clean
	rm -rf reseau
