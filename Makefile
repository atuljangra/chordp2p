
CC=g++
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=main.cpp 
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
	rm $(EXECUTABLE) $(OBJECTS)
