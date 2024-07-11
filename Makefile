CC = gcc
CFLAGS = -Wall -g
OBJFLAGS = -c
PROGRAM = yawn
SOURCES = main.c read.c
OBJECTS = main.o read.o
HEADERS = main.h read.h
RM = rm -f

default: all

all: $(PROGRAM)

$(PROGRAM): $(OBJECTS) $(HEADERS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(PROGRAM)

.c.o:
	$(CC) $(CFLAGS) $(OBJFLAGS) $< -o $@

clean:
	$(RM) $(PROGRAM) $(OBJECTS)
