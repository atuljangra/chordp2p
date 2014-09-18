
CC=g++
CFLAGS=-c -Wall -std=c++11
LDFLAGS=
SOURCES= $(wildcard *.cpp)
OBJECTS=$(SOURCES:.cpp=.o)
	EXECUTABLE=chord

all: $(SOURCES) $(EXECUTABLE)
		
$(EXECUTABLE): $(OBJECTS) 
		$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
		$(CC) $(CFLAGS) $< -o $@

run:
	./$(EXECUTABLE)

clean:
	rm -f $(EXECUTABLE) $(OBJECTS)
