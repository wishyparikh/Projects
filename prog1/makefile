

CC = g++
FLAGS = -std=c++11

SOURCES := $(wildcard t*.cpp)

EXECUTABLES = $(SOURCES:.cpp=)

all: $(EXECUTABLES)

# t1: t1.cpp List.h _test.h _util.h
#	g++ -std=c++11 t1.cpp -o t1

% : %.cpp List.h _util.h _test.h 
	$(CC) $(FLAGS) $< -o $@

clean:
	rm -f $(EXECUTABLES)

