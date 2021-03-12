#include <iostream>
#include <stack>
#include <fstream>
#include <sstream>
#include <string>
#include <string.h>
#include <algorithm>
#include <vector>
#include "nqueens.hpp"
using namespace std;

int main(int argc, char **argv)
{
    if (argc < 3) // must provide two arguments as input
    {
        throw std::invalid_argument(
            "Usage: ./hello <INPUT FILE> <OUTPUT FILE>"); // throw error
    }

    ifstream input;  // stream for input file
    ofstream output; // stream for output file

    input.open(argv[1]);  // open input file
    output.open(argv[2]); // open output file

    string in_line; // to store the input string from the file

    while (getline(input, in_line))
    {
        stringstream ss;
        ss << in_line;
        string word;
        getline(ss, word, ' ');
        nqueens board = nqueens(atoi(word.c_str()));
        while (getline(ss, word, ' '))
        {
            int x = atoi(word.c_str());
            getline(ss, word, ' ');
            int y = atoi(word.c_str());
            board.insert(x - 1, y - 1);
        }
        string result;
        if (board.find())
        {
            result = board.print();
        }
        else
        {
            result = "No solution";
        }
        output << result << endl;
    }
    input.close();
    output.close();
}