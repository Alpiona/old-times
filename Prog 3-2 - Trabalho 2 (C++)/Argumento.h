//
// Created by Sandor ferreira da silva on 31/07/17.
//

#ifndef P3_T2_ARGUMENTO_H
#define P3_T2_ARGUMENTO_H
#include <iostream>
#include <vector>
#include <map>

using namespace std;


class Argumento {
    map<string, string> args;
    vector<string> indicators;

public:
    Argumento(int argc, char* args[]);
    string get(string value);

};


#endif //P3_T2_ARGUMENTO_H
