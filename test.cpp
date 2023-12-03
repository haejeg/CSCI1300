#include <iostream>

using namespace std;

struct Asdf{
    string wow;
    int gay;
};

class Shit {
    private:
    Asdf asdf[5];

    public:
    Shit();
};

Shit::Shit() {
    
}

int main() {
    Asdf hi;
    cout << hi.gay;
    return 0;
}