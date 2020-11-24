cc=gcc
target=maze.out
objects=maze.o

$(target): $(objects)
	$(cc) -o $(target) $(objects)

$(objects): maze.h

.PHONY: clean
clean:
	rm -f $(objects) $(target)