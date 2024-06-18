CC = gcc
CFLAGS = -Wall -g
OBJFLAGS = -c
PROGRAM = yawn
OBJECTS = main.c read.c
HEADERS = main.h read.h

all: $(PROGRAM)

$(PROGRAM): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(PROGRAM)

main.o: main.c $(HEADERS)
	$(CC) $(OBJFLAGS) main.c

read.o: read.c $(HEADERS)
	$(CC) $(OBJFLAGS) read.c