#ifndef CANDY_H
#define CANDY_H

#include <iostream>

using namespace std;

// struct candy should be candy.h because it's used in multiple files
struct Candy {
    string name;
    string description;
    double price;
    string candy_type;
    int effect;
};

#endif