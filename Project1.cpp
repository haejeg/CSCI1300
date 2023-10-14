#include <iostream>
using namespace std;
//made by Danny! education purposes only, don't copy and paste, instead look at why the code works and create your own solution (although it'll be similar anyways lmao)
//do not read this unless absolutely necessary. View Project1Psuedocode.py for the psuedocode version

char shiftChar(char letter, int shift) {
    if (letter >= 'a' && letter <= 'z') { //check to see if the letter is inbetween lowercase a & lowercase z
        char result = (letter + shift) % 26; //resets value to 0 so that we get essentially the 'real' shift value, all this function has to do now is add 26 until ascii range
        //iterations to readjust to a-z ascii char range
        while (result < 'a') {
            result += 26;
        } 
        // return resulting value
        return result;
    }
    // return letter normally if nothing's there
    return letter;
}

int getMethod2ShiftAmount(string key) {
    int vowels = 0; //set a variable called vowels equal to 0, this variable that will increment by 1 everytime there's a vowel
    for (int i = 0; i < key.length(); i++) { //loop through the string 'key'
        if (key[i] == 'a' || key[i] == 'e' || key[i] == 'i' || key[i] == 'o' || key[i] == 'u' || key[i] == 'y') { //check for vowels
            vowels++; //increment vowels
        }
    }
    return (vowels + key.length()) % 26; //equation from method 2
}

int getMethod3ShiftAmount(string key1, string key2) {
    int count = 0; //set a variable named count and set it equal to 0, this variable will increment by 1 everytime there's an overlapping character
    for (int i = 0; i < key1.length(); i++) { //create a row x column array iteration, this iteration will be the row
        for (int j = 0; j < key2.length(); j++) { //this iteration will be the column
            if (key1[i] == key2[j]) { //for every row, it will go through all of key2.length()'s value as a column to check if there are any characters matching
                count++; //increment if there is
            }
        }
    }
    return count % 26; //equation from method 3
}

char encryptChar(char c, int method, string key1, string key2) {
    //create a switch statement to use user input (method) & organize accordingly
    switch(method) {
        case 1: 
            c = shiftChar(c, 1); //shifts by 1, as said in method 1
            break;
        case 2:
            c = shiftChar(c, getMethod2ShiftAmount(key1)); //shifts by return value of the calculation of method 2's shift value
            break;
        case 3:
            c = shiftChar(c, getMethod3ShiftAmount(key1, key2)); //shifts by return value of the calculation of method 3's shift value
            break;
        default:
            cout<<"Invalid encryption method"<<endl; //default case
            break;
    }
    return c;
}

char decryptChar(char c, int method_choice, string key1, string key2) {
    //all decryptChar() is - a function that just does the opposite of encryptChar(), so everything will be the same but negative
    //create a switch statement to use user input (method) & organize accordingly
    switch(method_choice) {
        case 1:
            c = shiftChar(c, -1); //shifts by -1, to undo method 1
            break;
        case 2:
            c = shiftChar(c, -getMethod2ShiftAmount(key1)); //shifts by negative return value of the calculation of method 2's shift value
            break;
        case 3:
            c = shiftChar(c, -getMethod3ShiftAmount(key1, key2)); //shifts by negative return value of the calculation of method 3's shift value
            break;
        default:
            cout<<"Invalid decryption method"<<endl; //default case
            break;
    }
    return c;
}

string encryptMessage(string message, int method_choice, string key1, string key2) {
    //same idea as encryptChar(), only change is that you're iterating through the string variable 'message' and setting each individual char of the message to its encrypted value
    switch(method_choice) {
        case 1: //all formats below follow this format
            for (int i = 0; i < message.length(); i++) { //iteration through string
                message[i] = encryptChar(message[i], 1, key1, key2); //just use encryptChar() since it's already a function lmao
            }
            break; 
        case 2: //same idea as case 1 but method 2
            for (int i = 0; i < message.length(); i++) {
                message[i] = encryptChar(message[i], 2, key1, key2);
            }
            break;
        case 3: //same idea as case 1 but method 3
            for (int i = 0; i < message.length(); i++) {
                message[i] = encryptChar(message[i], 3, key1, key2);
            }
            break;
        case 4:
        {
            for (int i = 0; i < message.length(); i+=3) { //the iteration i+=3 makes it that the i value goes in the pattern of 0, 3, 6, 9
                //that is because this is the simplest way to do it. message[i] (the first index), message[i + 1] (the index after the first index), message[i + 2] (the third)
                //since the iteration is skipping by 3 everytime, [i], [i + 1], [i + 2] works perfectly
                message[i] = encryptChar(message[i], 1, key1, key2);
                message[i + 1] = encryptChar(message[i + 1], 2, key1, key2);
                message[i + 2] = encryptChar(message[i + 2], 3, key1, key2);
            }
            break;
        }
        default:
            cout<<"Invalid encryption method"<<endl; //default case
            break;
    }
    return message;
}

string decryptMessage(string message, int method_choice, string key1, string key2) {
    //same idea as encryptMessage(), but backwards. Very simple stuff!
    //all of the below follow the exact same syntax as encryptMessage(), remember, the function used is decryptChar() instead of encryptChar().
    switch(method_choice) {
        case 1:
            for (int i = 0; i < message.length(); i++) {
                message[i] = decryptChar(message[i], 1, key1, key2);
            }
            break;
        case 2:
            for (int i = 0; i < message.length(); i++) {
                message[i] = decryptChar(message[i], 2, key1, key2);
            }
            break;
        case 3:
            for (int i = 0; i < message.length(); i++) {
                message[i] = decryptChar(message[i], 3, key1, key2);
            }
            break;
        case 4:
        {
            for (int i = 0; i < message.length(); i+=3) {
                message[i] = decryptChar(message[i], 1, key1, key2);
                message[i + 1] = decryptChar(message[i + 1], 2, key1, key2);
                message[i + 2] = decryptChar(message[i + 2], 3, key1, key2);
            }
            break;
        }
        default:
            cout<<"Invalid decryption method"<<endl; //default case
            break;
    }
    return message;
}

int main() {
    //holy shit this is where things kinda get messy
    int option, method; //two ints. option is the option they're given for menu navigation. method is the encryption method that they choose. Both are 0 by default
    string key1, key2, message; //i mean this is self explanatory. message = message for encryption/decryption, key1 is key1, key2 is key2 lol
    bool setkey1, setkey2, setmethod, wrongoption; //booleans for checking whether or not user has either set key1, key2, method.
    /*I'm sure there are numerous ways to approach this problem. However, I chose to create a boolean named wrongoption for options that aren't 1-6. For whatever reason
    the coderunner does not want us to prompt the user with another menu cout prompt whenever the options are wrong. You'll see as you go down the code, I'll be
    commenting on it.*/
    do {
        if (!wrongoption) { //if wrongoption is !true (false), and it was a correct input, it will prompt the user with cout menu navigation
            //the '\n' character is a character for newline. this will essentially act as a endl; but u don't separate the strings. pretty useful!
            cout<<"Please input 1-6 followed by enter to navigate the menu:\n1. Set Encryption Key 1\n2. Set Encryption Key 2\n3. Select Encryption Method\n4. Encrypt Message\n5. Decrypt Message\n6. Exit Program"<<endl;
            cin>>option; //prompt user for option
        } else {
            wrongoption = false; //set wrongoption to false again. since wrongoption would be true when this else statement runs, so they can be wrong again.
            //i swear this will make more sense once you look at default case lol
        }
        //i decided to use switch case for this because I needed more practice with it, but this might've been a mistake.. would it have been neater had i used if/elseifs fuck knows
        switch(option) {
            case 1: //user wants to set key1
                cout<<"Enter key:"<<endl;
                cin.ignore(); //cin.ignore() makes it so that getline() doesn't instantly get applied, due to getline() ending when enter is pressed, this might be a good practice
                //do not take my word on that though, i have almost no idea if it actually is. seems like it's a necessary solution for me though.
                getline(cin, key1); //getline(). search this method up if you don't know it already. it's very important!
                while (key1.length() < 1) { //while key's length is less than 1, keep prompting user until it's going to be a valid input. I have no idea why-
                //key.length() == 0 does not work here. Maybe something about length()'s function? If someone figures it out tell me please :)
                    cout<<"Invalid key"<<endl; 
                    cout<<"Enter key:"<<endl;
                    getline(cin, key1); //reprompt user
                }
                //fun fact: the while loop could probably be a do while loop instead
                cout<<"Successfully set encryption key1 to "<<key1<<endl; //when it passes through its done!
                setkey1 = true; //set boolean to true!
                break;
            case 2: //user wants to set key2
                //key2 is literally copypaste of key1. Enjoy
                cout<<"Enter key:"<<endl;
                cin.ignore();
                getline(cin, key2);
                while (key2.length() < 1) {
                    cout<<"Invalid key"<<endl;
                    cout<<"Enter key:"<<endl;
                    getline(cin, key2);
                }
                cout<<"Successfully set encryption key2 to "<<key2<<endl;
                setkey2 = true;
                break;
            case 3: //user wants to set encryption method
                cout<<"Please input 1-4 to decide encryption technique.\n1. Method1 only (shift by 1)\n2. Method2 only (shift by first key)\n3. Method3 only (shift by both keys)\n4. Mix of Method1, Method2, Method3"<<endl;
                cin>>method;
                while (true) { //do a while loop- hold on a minute. I actually don't think this if inside the while loop even needs to be here! It can just contain the conditions-
                //in the if statement right? this can be a good check to make sure that you're actually reading this yay
                    if (!(method >= 1 && method <= 4)) { 
                        cout<<"Invalid encryption choice"<<endl;
                        cin.clear(); //clears the user input box
                        cin.ignore(10000, '\n'); /*This reads and discards characters from the input buffer. If this isn't there, "Invalid encryption choice" will-
                        print however many characters there are in the string for the error check (kinda wack that this happens actually), there's probably a better solution to
                        this..*/
                        cin>>method;
                    } else {
                        setmethod = true;
                        cout<<"Successfully set encryption type to "<<method<<endl;
                        break;
                    }
                }
                break;
            case 4: //user wants to encrypt a message
                if ((setkey1 && setkey2 && setmethod) == false) { //makes sure that all things are set, if not, print msg, and stop.
                    cout<<"You cannot do this until you set both keys and choose an encryption method"<<endl;
                    break; //you either do this break, or you do an else. it's really up to you!
                } 
                cout<<"Enter your message to encrypt:"<<endl;
                cin.ignore(); //refer to line 172 if ur confused
                getline(cin, message);
                cout<<encryptMessage(message, method, key1, key2)<<endl;
                break;
            case 5: //user wants to decrypt a message
                //same thing for encryption but uses decryptMessage() instead
                if ((setkey1 && setkey2 && setmethod) == false) {
                    cout<<"You cannot do this until you set both keys and choose an encryption method"<<endl;
                    break;
                } 
                cout<<"Enter your message to decrypt:"<<endl;
                cin.ignore();
                getline(cin, message);
                cout<<decryptMessage(message, method, key1, key2)<<endl;
                break;
            case 6:
                //just break the loop since option == 6 will mean the while loop will stop running and it prints goodbye outside of the while loop
                break;
            default:
                wrongoption = true; //set boolean wrongoption = true. Now it won't print the menu navigation thing in the front before reprompting the user!
                cin.clear(); //refer to line 204 if ur confused
                cin.ignore(10000, '\n'); //refer to line 205 if ur confused
                cout<<"Invalid input"<<endl;
                cin>>option; //reprompt user
                break;
        }
    }
    while (option != 6); //did you even know that it was actually a do while loop this whole entire time?!

    cout<<"Goodbye."<<endl;
    //Created by Danny. 10/8/2023 cheers!
    //Whoever's reading this, you did a great job coming this far! This coderunner was absolutely brutal!! (for me at least. maybe yall too smart idfk)
    return 0;
}

/*Note to self: (u guys literally don't have to read this shit)
- more practice for do while loops, i keep forgetting to use them
- get more familiar and understand why and how cin works that way. why did i have to use all those methods? - i still don't know
- avoid using unnecessary code
- literally use functions that are there for you >:(
*/
