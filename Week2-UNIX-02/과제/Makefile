cc=gcc
target=a.out
objects=20170175.o NCounter.o ResultPrinter.o

$(target): $(objects)
	$(cc) -o $(target) $(objects)

$(objects): 20170175.h

.PHONY: clean
clean:
	rm -f $(objects) $(target)

