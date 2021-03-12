CXX = g++
CXXFLAGS = -Wall

OBJECTS = graph.o movie.o

movie: $(OBJECTS)
	$(CXX) -g $(CXXFLAGS) -o sixdegrees graph.o movie.o

graph.o: graph.cpp graph.hpp
	$(CXX) -g $(CXXFLAGS) -c graph.cpp
	
movie.o: graph.cpp graph.hpp movie.cpp
	$(CXX) -g $(CXXFLAGS) -c movie.cpp

clean: 
	rm -rf *.o sixdegrees

