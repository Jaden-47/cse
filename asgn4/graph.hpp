#ifndef __graph_hpp__
#define __graph_hpp__

#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
#include <unordered_map>
#include <queue>
#include <unordered_set>

using namespace std;

class Edge
{
public:
    string movie;
    string actor;
    Edge();                             // default constructor, never used
    Edge(string actor1, string movie1); // construct the first node to the Movie list
};

class Graph
{
public:
    unordered_map<string, vector<Edge>> actors;
    Graph();                                                    // default constructor with 1,000,000 actors
    void make_edge(string actor1, string actor2, string movie); // make connection between actor1 and actor2
    string print();                                             // print the whole graph
    string print(string actor);                                 // print the list that start with the string
    string path(string actor1, string actor2);                  // compute the path
};

#endif
