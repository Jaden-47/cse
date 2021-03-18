// Filename: movies.cpp
//

#include <iostream>
#include <stack>
#include <stdexcept>
#include <fstream>
#include <array>
#include <vector>
#include <algorithm>
#include <sstream>
#include <cstring>
#include "graph.hpp"
#define textfile "cleaned_movielist.txt"
using namespace std;

int main(int argc, char **argv)
{
    if (argc < 3) // must provide two arguments as input
    {
        throw std::invalid_argument("Usage: ./treewrapper <INPUT FILE> <OUTPUT FILE>"); // throw error
    }

    ifstream input;      // stream for input file
    ofstream output;     // stream for output file
    ifstream movie_list; // stream for movie list

    input.open(argv[1]);       // open input file
    output.open(argv[2]);      // open output file
    movie_list.open(textfile); // open the movie list

    string movie_line, actors_line;                    // to store the next command and operation
    char *com, *valstr, *movie_name, *actor1, *actor2; // for using with strtok, strtol
    Graph graph = Graph();
    while (getline(movie_list, movie_line)) // get next line of input, store as repeat
    {
        if (movie_line.length() == 0) // command is empty
        {
            continue;
        }
        com = strdup(movie_line.c_str()); // annoying, first copy string into a "C-style" string
        movie_name = strtok(com, " \t");  //tokenize command on whitespace, first token is movie name
        valstr = movie_name;
        vector<string> v;
        while (valstr)
        {
            string s = valstr;
            v.push_back(s);
            valstr = strtok(NULL, " \t");
        }
        for (int i = 1; i < (int)v.size() - 1; i++)
        {
            for (int j = i + 1; j < (int)v.size(); j++)
            {
                //cout<<"1"<<v[0]<<" a:"<<v[i]<<" b:"<<v[j]<<endl;
                graph.make_edge(v[i], v[j], v[0]);
            }
        }
    }
    while (getline(input, actors_line))
    {
        //cout<<actors_line<<endl;
        if (actors_line.length() == 0)
            continue;
        com = strdup(actors_line.c_str());
        actor1 = strtok(com, " \t");
        actor2 = strtok(NULL, " \t");
        //cout<<"a1: "<<actor1<<" a2: "<<actor2<<endl;
        //cout<<(graph.actors.find("Blanche_Bayliss") == graph.actors.end())<<endl;
        output<<graph.path((string)actor1, (string)actor2)<<endl;
    }
    input.close();
    output.close();
    movie_list.close();
}
