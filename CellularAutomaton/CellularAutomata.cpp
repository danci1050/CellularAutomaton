#include <iostream>
#include <vector>
#include <array>
#include <string>
#include "CellularAutomata.h"
#include <cmath>
#include <regex>
#include <fstream>
#include <iterator>
#include <algorithm>
using namespace std;

/*1D Cellular automata*/
vector<string> CellularAutomata::CellularAutomata1D() {
    struct Rules rules;
    vector <string> output;
    string rule;
    /*getting the rule from the user*/
    while (true) {
        cout << "Enter the number of the rule (0-256): ";
        cin >> rule;
        if (regex_match(rule, regex("^([01]?[0-9]?[0-9]|2[0-4][0-9]|25[0-6])$"))) {
            rules = setRules(std::stoi(rule));
            break;
        }
    }
    /*getting the starting row*/
    string row;
    while (true) {

        cout << "Enter the starting row" << endl;
        cin >> row;
        if (regex_match(row, regex("^[0-1]{3,}$"))) {
            break;
        }

    }
    string file;
    string fileName;
    /*checks if the user wants to export the output of the function to a file */
    while (true) {

        cout << "Export the result to file [Y/N]: " << endl;
        cin >> file;
        if (regex_match(file, regex("^[Y]$|^[y]$|^[N]$|^[n]$"))) {
            if (regex_match(file, regex("^[Y]$|^[y]$"))) {
                cout << "Enter the name of the file: ";
                cin >> fileName;
            }
            break;
        }

    }
    /*getting the number of generation which the user wants to generate*/
    string oneAtATime;
    while (true) {
        cout << "Ouput one generation at a time? [Y/N]" << endl;
        cin >> oneAtATime;
        if (regex_match(oneAtATime, regex("^[Y]$|^[y]$|^[N]$|^[n]$"))) {
            break;
        }
    }
    string genNumber="1";
    /*one generation at a time option*/
    if (regex_match(oneAtATime, regex("^[N]$|^[n]$"))) {
        
        while (true) {

            cout << "Enter the number of generations: " << endl;
            cin >> genNumber;
            if (regex_match(genNumber, regex("^[0-9]*$"))) {
                break;
            }
        }
    }
    /*adding the first line to the 1D Cellular automata*/
    output.push_back(row);
    string newLine;
    /*generating new lines from the prevous line*/
    for (int x = 0; x < std::stoi(genNumber); ++x) {


        for (int i = 0; i < row.length(); i++) {

            string s;
            if (i == 0) {
                s = row.back() + row.substr(0, 2);

            }
            else if (i == row.length() - 1) {
                s = row.substr(i - 1, 2) + row.front();
            }
            else {
                s = row.substr(i - 1, 3);
            }
            for (int j = 0; j < 8; ++j) {

                if (s == rules.rules[j].pattern) {
                    newLine += rules.rules[j].outcome;
                    break;
                }
            }
        }

        cout << newLine << endl;
        output.push_back(newLine);
        row = newLine;
        newLine = "";
        /*Asks the user if they want to generate a new line if the generation at a time was selected*/
        if (regex_match(oneAtATime, regex("^[Y]$|^[y]$"))) {
            while (true) {
                cout << "Generate new generation? [Y/N]" << endl;
                cin >> oneAtATime;
                if (regex_match(oneAtATime, regex("^[Y]$|^[y]$|^[N]$|^[n]$"))) {
                    break;
                }
            }
            if (regex_match(oneAtATime, regex("^[Y]$|^[y]$"))) {
                x--;
            }
        }
        
    }
    /*exporting the output to a file*/
    if (regex_match(file, regex("^[Y]$|^[y]$"))) {
        ExportToFile(output,fileName);
    }
    return output;
}
/*Wrapping around for 2D cellular automata*/
int CellularAutomata::getCell(int iElement, int maxi) {
    return (iElement % maxi + maxi) % maxi;
}
/*This function creates the next sate from a previus state in game of life*/
vector<string> CellularAutomata::GameOfLife(vector <string> startingState) {
    vector <string> newState(startingState.size());
    for (int i = 0; i < startingState.size(); i++)
    {
        for (int j = 0; j < startingState.at(0).size();j++) {
            int livingNeighbours = 0;
            if (startingState[getCell(i, startingState.size())].at(getCell(j + 1, startingState.at(0).size())) == '1') {
                livingNeighbours++;
            }
            if (startingState[getCell(i, startingState.size())].at(getCell(j - 1, startingState.at(0).size())) == '1') {
                livingNeighbours++;
            }
            if (startingState[getCell(i + 1, startingState.size())].at(getCell(j, startingState.at(0).size())) == '1') {
                livingNeighbours++;
            }
            if (startingState[getCell(i + 1, startingState.size())].at(getCell(j+1, startingState.at(0).size())) == '1') {
                livingNeighbours++;
            }
            if (startingState[getCell(i + 1, startingState.size())].at(getCell(j-1, startingState.at(0).size())) == '1') {
                livingNeighbours++;
            }
            if (startingState[getCell(i - 1, startingState.size())].at(getCell(j+1, startingState.at(0).size())) == '1') {
                livingNeighbours++;
            }
            if (startingState[getCell(i - 1, startingState.size())].at(getCell(j-1, startingState.at(0).size())) == '1') {
                livingNeighbours++;
            }
            if (startingState[getCell(i - 1, startingState.size())].at(getCell(j, startingState.at(0).size())) == '1') {
                livingNeighbours++;
            }
            if (startingState[i].at(j) == '1') {    
                if (livingNeighbours == 2 || livingNeighbours == 3) {
                    newState[i] += '1';
                }
                else {
                    newState[i] += '0';
                }
            }
            else {
                if (livingNeighbours == 3) {
                    newState[i] += '1';
                }
                else {
                    newState[i] += '0';
                }
            }
        }
    }
    return newState;
}

vector<string> CellularAutomata::Other2D(vector <string> startingState) {
    vector <string> newState(startingState.size());
    for (int i = 0; i < startingState.size(); i++)
    {
        for (int j = 0; j < startingState.at(0).size(); j++) {
            int livingNeighbours = 0;
            if (startingState[getCell(i, startingState.size())].at(getCell(j + 1, startingState.at(0).size())) == '1') {
                livingNeighbours++;
            }
            if (startingState[getCell(i, startingState.size())].at(getCell(j - 1, startingState.at(0).size())) == '1') {
                livingNeighbours++;
            }
            if (startingState[getCell(i + 1, startingState.size())].at(getCell(j, startingState.at(0).size())) == '1') {
                livingNeighbours++;
            }
            if (startingState[getCell(i + 1, startingState.size())].at(getCell(j + 1, startingState.at(0).size())) == '1') {
                livingNeighbours++;
            }
            if (startingState[getCell(i + 1, startingState.size())].at(getCell(j - 1, startingState.at(0).size())) == '1') {
                livingNeighbours++;
            }
            if (startingState[getCell(i - 1, startingState.size())].at(getCell(j + 1, startingState.at(0).size())) == '1') {
                livingNeighbours++;
            }
            if (startingState[getCell(i - 1, startingState.size())].at(getCell(j - 1, startingState.at(0).size())) == '1') {
                livingNeighbours++;
            }
            if (startingState[getCell(i - 1, startingState.size())].at(getCell(j, startingState.at(0).size())) == '1') {
                livingNeighbours++;
            }
            if (startingState[i].at(j) == '1') {
                if (livingNeighbours == 1 || livingNeighbours == 4) {
                    newState[i] += '1';
                }
                else {
                    newState[i] += '0';
                }
            }
            else {
                if (livingNeighbours == 2) {
                    newState[i] += '1';
                }
                else {
                    newState[i] += '0';
                }
            }
        }
    }
    return newState;
}

/*This funciton converts binary numbers to decimal numbers*/
int  CellularAutomata::BinaryToDecimal(int binary) {
    int d=0, i=0, remainder = 0;

    while (binary != 0) {
        remainder = binary % 10;
        binary = binary / 10;
        d = d + (remainder * pow(2, i));
        i++;
    }
    return d;
}
/*This function converts decimal numbers to binary numbers*/
int  CellularAutomata::DecimalToBinary(int dec) {
    if (dec < 0) {
        throw std::invalid_argument("received negative value");
    }
    string s;
    while (dec > 0) {
        s = std::to_string(dec % 2) + s;
        dec = dec / 2;
    }
    return std::stoi(s);
}
/*this functnio defines the rules for the 1D Cellular automata*/
Rules CellularAutomata::setRules(int n) {
    Rules rules;
    string s = std::to_string(CellularAutomata::DecimalToBinary(n));
    string temp(8-s.length(), '0');
    s = temp + s;
    rules.rules[0].pattern = "111";
    rules.rules[0].outcome = s.at(0);
    rules.rules[1].pattern = "110";
    rules.rules[1].outcome = s.at(1);
    rules.rules[2].pattern = "101";
    rules.rules[2].outcome = s.at(2);
    rules.rules[3].pattern = "100";
    rules.rules[3].outcome = s.at(3);
    rules.rules[4].pattern = "011";
    rules.rules[4].outcome = s.at(4);
    rules.rules[5].pattern = "010";
    rules.rules[5].outcome = s.at(5);
    rules.rules[6].pattern = "001";
    rules.rules[6].outcome = s.at(6);
    rules.rules[7].pattern = "000";
    rules.rules[7].outcome = s.at(7);
    return rules;
}
/*This function writes a string vector to a file*/
void CellularAutomata::ExportToFile(vector <string> v,string fileName) {

    ofstream File(fileName);
    if (!File) {
        cout << "Failed to write to file" << endl;
    }
    else {
        for (const auto& e : v) File << e << "\n";
    }
}
/*This function reads a file to a string vector*/
vector <string> CellularAutomata::ImportFile(string fileName) {
    vector<string> data;
    ifstream File(fileName);
    if (!File) {
        cout << "Cannot open the file";
    }
    else {
        for (string line; getline(File, line);) {
            data.push_back(line);
        }
    }
    return data;
}