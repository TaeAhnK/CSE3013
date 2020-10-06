CC=g++
TARGET=a.out
OBJECTS=main.o
CPPFLAGS=-g
$(TARGET): $(OBJECTS)
	$(CC) -o $(TARGET) $(OBJECTS)

$(OBJECTS): LinkedList.h Stack.h

.PHONY: clean
clean:
	rm -f $(OBJECTS) $(TARGET)
