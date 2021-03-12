CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -Wpedantic -std=c++11 
OBJECTS = main.o nqueens.o

all: nqueens

nqueens: $(OBJECTS)
	$(CXX) $(CXXFLAGS) -g -o nqueens main.o nqueens.o -lm

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -g -c main.cpp

nqueens.o: nqueens.cpp nqueens.hpp
	$(CXX) $(CXXFLAGS) -g -c nqueens.cpp

valgrind:
	make clean; make; valgrind ./nqueens

clean: 
	rm -rf nqueens *.o