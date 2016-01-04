CC=g++
CFLAGS=-Wall -Werror -fmax-errors=1 -std=c++11
LDFLAGS=-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

SOURCES=element.cpp component.cpp layout.cpp
OBJECTS=$(SOURCES:.cpp=.o)

TEST_SOURCES=test_app.cpp $(SOURCES)
TEST_OBJECTS=$(TEST_SOURCES:.cpp=.o)
TEST_EXECUTABLE=test_app

all: test
test: $(TEST_EXECUTABLE)
	./$(TEST_EXECUTABLE)
$(TEST_EXECUTABLE): $(TEST_OBJECTS)
	$(CC) $(CFLAGS) $(TEST_OBJECTS) $(LDFLAGS) -o $(TEST_EXECUTABLE)
$(TEST_OBJECTS): $(TEST_SOURCES)
	$(CC) -c $(CFLAGS) $(TEST_SOURCES)
clean:
	rm -f *.o $(TEST_EXECUTABLE)
