#include "ll.hpp"
#include <fstream>
#include <iostream>

using namespace std;

int main(int argc, char **argv){
    // codes from line 9 to line 20 copied from codio "Hello" folder

    if (argc < 3) // must provide two arguments as input
    {
        throw std::invalid_argument("Usage: ./freq <INPUT FILE> <OUTPUT FILE>"); // throw error
    }

    ifstream input; // stream for input file
    ofstream output; // stream for output file

    input.open(argv[1]); // open input file
    output.open(argv[2]); // open output file

    string word;

    while(getline(input,word)) // get next line of input, store as repeat
    {
        
    }

}