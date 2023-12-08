#include "Utilities.h"

// change string inputted all into lowercase using the tolower() function
string toLowerCase(string str) {
    string res = "";
    int len = str.length();
    // iterate through every single character
    for (int i = 0; i < len; i++) {
        res += tolower(str[i]);
    }
    return res;
}

//  just a function to clear all input to avoid cin/getline errors
void clearInput() {
    cin.clear();
    cin.ignore(1000, '\n');
}