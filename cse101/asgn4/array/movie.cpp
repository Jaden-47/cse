// Filename: movies.cpp
//
// This is the main wrapper for the BST class.
//
// After running make, the usage is:
//     ./treewrapper <INPUT_FILE> <OUTPUT_FILE>
//
// The input file contains a list of operations performed on a BST. The operations are insert, delete, find, printing in/pre/post order
// Each line is of the form:
//
//         i <INT>: insert <INT> into BST
//         f <INT>: find if <INT> is in BST
//         d <INT>: delete <INT> from BST
//         pin: print tree in order
//         ppre: print tree pre-order
//         ppost: print tree post-order
//
// The find and print operations generate output, which is either "found/didn't find <INT>" or the tree printed in the desired order.
//
// The output file contains the output of all commands that lead to output.
//
// In addition, the console output shows the operations performed, and also prints the tree (for every print command).
//
// C. Seshadhri, Jan 2020

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
    //string val = 0; // the value from the command
    int a=0;
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

        Graph graph=Graph();
        
        a++;
        if(a==10) break;
        
        for (int i = 1; i < (int)v.size()-1; i++)
        {
            for(int j=i+1;j<(int)v.size();j++){
                cout<<"1"<<v[0]<<" a:"<<v[i]<<" b:"<<v[j]<<endl;
                graph.make_edge(v[i],v[j],v[0]);
            }
        }
        output<<endl;
        
    }

    input.close();
    output.close();
    movie_list.close();
}
