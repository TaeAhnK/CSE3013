CC=g++
TARGET=a.out
OBJECTS=main.o Array.o RangeArray.o
CPPFLAGS=-g
$(TARGET): $(OBJECTS)
	$(CC) -o  $(TARGET) $(OBJECTS)

$(OBJECTS): Array.h RangeArray.h

.PHONY: clean
clean:
	rm -f $(OBJECTS) $(TARGET)

