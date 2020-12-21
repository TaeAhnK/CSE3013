.SUFFIXES : .c .o
CC=gcc
CFLAGS = -g

OBJ1 = 20170175_P1.o
OBJ2 = 20170175_P2.o
SRCS = $(OBJ1:.o=.c) $(OBJ2:.o=.c)

all : P1 P2

P1 : $(OBJ1)
	$(CC) -o P1 $(OBJ1)

P2 : $(OBJ2)
	$(CC) -o P2 $(OBJ2)

clean:
	rm -f $(OBJ1) $(OBJ2) P1 P2