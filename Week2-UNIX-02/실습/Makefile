CC=gcc
target=fmt
objects=main.o Output.o String_Manipulation.o

$(target): $(objects)
	$(CC) -o $(target) $(objects)

$(objects): Header.h

.PHONY: clean
clean:
	rm -f $(objects) $(target)

