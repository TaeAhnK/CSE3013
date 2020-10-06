CC=g++
TARGET=a.out
OBJECTS=main.o
CPPFLAGS=-g
$(TARGET): $(OBJECTS)
	$(CC) -o  $(TARGET) $(OBJECTS)

$(OBJECTS): Array.h GrowableArray.h

.PHONY: clean
clean:
	rm -f $(OBJECTS) $(TARGET)

