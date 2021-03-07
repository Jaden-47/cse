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

    string movie_line;               // to store the next command and operation
    char *com, *valstr, *movie_name; // for using with strtok, strtol
    int a=0;
    Graph graph=Graph();
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
        for (int i = 1; i < (int)v.size()-1; i++)
        {
            for(int j=i+1;j<(int)v.size();j++){
                //cout<<"1"<<v[0]<<" a:"<<v[i]<<" b:"<<v[j]<<endl;
                graph.make_edge(v[i],v[j],v[0]);
            }
        }
        a++;
        if(a==5) break;
    }
    graph.path("Blanche_Bayliss","William_Courtenay");
    input.close();
    output.close();
    movie_list.close();
}
