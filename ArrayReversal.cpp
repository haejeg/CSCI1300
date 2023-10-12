#include <iostream>
 
using namespace std;

void swap(char letters[], int first_element, int second_element) {
    char tempValue = letters[first_element];
    letters[first_element] = letters[second_element];
    letters[second_element] = tempValue;
}

void reverseArray(char letters[], int letters_length) {
    for (int i = 0; i < letters_length / 2; i++) {
        swap(letters, i, letters_length - i - 1);
    }
}

int main() {
    char letters[7] = {'a', 'b', 'c', 'd', 'e', 'f', 'g'};
    reverseArray(letters, sizeof(letters));
    for(int i = 0; i < sizeof(letters); i++) {
        cout<<letters[i]<<" "<<endl;
    }

    return 0;
}

