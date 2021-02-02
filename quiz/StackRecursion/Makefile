CXX = g++
CXXFLAGS = -Wall -std=c++11

OBJECTS = node.o list.o stack.o

stack: $(OBJECTS)
	$(CXX) -g $(CXXFLAGS) -o $@ $^

clean: 
	rm -f *.o stack
$(OBJECTS): node.h list.h
