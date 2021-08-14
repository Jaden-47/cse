#include "ll.hpp"
#include <fstream>
#include <iostream>
#define textfile "twain-cleaned.txt"

using namespace std;

int main(int argc, char **argv)
{
    // codes from line 9 to line 20 copied from codio "Hello" folder

    if (argc < 3) // must provide two arguments as input
    {
        throw std::invalid_argument("Usage: ./twain <INPUT FILE> <OUTPUT FILE>"); // throw error
    }

    ifstream input;  // stream for input file
    ofstream output; // stream for output file
    ifstream text;   // stream for the twain text

    input.open(argv[1]);  // open input file
    output.open(argv[2]); // open output file
    text.open(textfile);  // open the twain text file

    string word;

    LinkedList word_list[26];

    // read in the words in the twain
    while (getline(text, word)) // get next line of input, store as a word
    {
        int first = word[0]-97;
        if (first < 0 || first > 25)
        {
            continue;
        }
        Node *findWord = word_list[first].find(word);
        if (findWord)
        {
            findWord->cnt++;
        }
        else
        {
            word_list[first].insert(word);
        }
    }
    cout<<word_list[23].print()<<endl<<endl;

    
    for (int i = 0; i < 26; i++)
    {
        word_list[i].sortList();
    }
    //word_list[23].sortList();

    cout<<word_list[23].print()<<endl;


    string number;
    Node *findone;
    while (input >> word, input >> number)
    {
        findone = word_list[word[0] - 97].findNodeRank(atoi(number.c_str()));
        if (findone == NULL)
        {
            output << "-" << endl;
        }
        else
        {
            output << findone->data <<" "<< findone->cnt << endl;
        }
    }

    for (int i = 0; i < 26; i++)
    {
        word_list[i].deleteList();
    }
    input.close();
    output.close();
}