//
// Created by danci on 07/11/2021.
//

#ifndef CELLULARAUTOMATA_CELLULARAUTOMATA_H
#define CELLULARAUTOMATA_CELLULARAUTOMATA_H

#endif //CELLULARAUTOMATA_CELLULARAUTOMATA_H
#include <string>
#include <vector>
using namespace std;
/*rule struct for the 1D cellular automata*/
struct Rule
{
    string pattern;
    string outcome;
};
/*struct containing all the rules for the 1D cellular automata*/
struct Rules
{
    Rule rules[8];
};

class CellularAutomata{
public:
    /*generates a new state from a previus sate of the game of lie*/
    static  vector<string> GameOfLife(vector <string> startingState);
    /*creates a 1d cellular automata based on user input*/
    static vector<string> CellularAutomata1D();
    /*does the wrapping around for the game of life funciton*/
    static int getCell(int i, int maxi);
    /*convers decimal to binary*/
    static int DecimalToBinary(int dec);
    /*converts binary to decimal*/
    static int  BinaryToDecimal(int binary);
    /*sets the rules for the 1D cellular automata*/
    static Rules setRules(int n);
    /*exports a string vector to a file*/
    static void ExportToFile(vector <string> v, string fileName);
    /*imports a files contets to a string vector*/
    static vector <string> ImportFile(string fileName);

    static vector<string> Other2D(vector <string> startingState);
};



