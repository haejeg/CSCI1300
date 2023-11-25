#include "Utilities.h"

string toLowerCase(string str) {
    string res = "";
    for (int i = 0; i < str.length(); i++) {
        res += tolower(str[i]);
    }
    return res;
}

void clearInput() {
    cin.clear();
    cin.ignore(1000, '\n');
}