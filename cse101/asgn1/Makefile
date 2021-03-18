CXX = g++
CXXFLAGS = -std=c++11 
OBJECTS = twain.o ll.o
#-Wall -Wextra -Werror -Wpedantic
all: twain

twain: $(OBJECTS)
	$(CXX) $(CXXFLAGS) -g -o twain ll.o twain.o

ll.o: ll.cpp ll.hpp
	$(CXX) $(CXXFLAGS) -g -c ll.cpp
	
twain.o: twain.cpp
	$(CXX) $(CXXFLAGS) -g -c twain.cpp

valgrind:
	make clean; make; valgrind ./twain more-input.txt output.txt

clean: 
	rm -rf twain *.o