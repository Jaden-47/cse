#ifndef __graph_hpp__
#define __graph_hpp__

#include <algorithm>
#include <iostream>
#include <map>

using namespace std;

class Edge
{
public:
    string movie;
    Edge *next;
    int vertex_index;
    Edge();                        // default constructor, never used
    Edge(string name1, int index, Edge *next1); // construct the first node to the Movie list

    string print(); // construct a string that holds all edges
};

class Vertex
{
public:
    bool visited;
    Edge *first;
    string actor;
    Vertex(); // default constructor, never used
    Vertex(string actor_name, Edge *first_edge);

    string print(); // construct a string that holds the vertex and all related edges
};

class Graph
{
public:
    int num_actors; // track of the current size of actors;
    Vertex *actors;
    Graph();                                                    // default constructor with 1,000,000 actors
    void make_edge(string actor1, string actor2, string movie); // make connection between actor1 and actor2
    int get_vertex(string actor); // return the index of given actor, if not exist, return -1;
    int get_vertex(Vertex actor); // return the index of given actor, if not exist, return -1;
    string print();
};

#endif
