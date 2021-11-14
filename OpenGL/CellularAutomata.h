//
// Created by danci on 07/11/2021.
//

#ifndef CELLULARAUTOMATA_CELLULARAUTOMATA_H
#define CELLULARAUTOMATA_CELLULARAUTOMATA_H

#endif //CELLULARAUTOMATA_CELLULARAUTOMATA_H
#include <string>
#include <vector>
using namespace std;
struct Rule
{
    string pattern;
    string outcome;
};

struct Rules
{
    Rule rules[8];
};

class CellularAutomata{
public:

    static  vector<string> GameOfLife(vector <string> startingState);
    static vector<string> CellularAutomata1D();
    static int getCell(int i, int maxi);
    static int DecimalToBinary(int dec);
    static int  BinaryToDecimal(int binary);
    static Rules setRules(int n);
    static void ExportToFile(vector <string> v, string fileName);
    static vector <string> ImportFile(string fileName);
};



