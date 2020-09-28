CC=g++
TARGET=a.out
OBJECTS=main.o str.o
CPPFLAGS=-g
$(TARGET): $(OBJECTS)
	$(CC) -o $(TARGET) $(OBJECTS)

$(OBJECTS): str.h

.PHONY: clean
clean:
	rm -f $(OBJECTS) $(TARGET)
