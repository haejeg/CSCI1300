#include "Board.h"
#include "CandyStore.h"
#include "Candy.h"
#include "Utilities.h"
#include <iostream>
#include <stdlib.h>
#include <random>
#include <fstream>
#include <sstream>

//My candylist.txt and characters.txt are chatgpt generated (so it's more diverse)

using namespace std;

void generateCards() {
    int cards[9] = {1, 2, 3, 1, 2, 3, 1, 2, 3};

    int cardCounts[6] = {0, 0, 0, 0, 0, 0};

    for (int i = 0; i < 100; i++) {
        int random = rand() % 9;
        if (random == 0 || random == 3) {
            cardCounts[0]++;
            cout<<cards[0]<<" selected."<<endl;
        } else if (random == 1 || random == 4) {
            cardCounts[1]++;
            cout<<cards[1]<<" selected."<<endl;
        } else if (random == 2 || random == 5) {
            cardCounts[2]++;
            cout<<cards[2]<<" selected."<<endl;
        } else if (random == 6) {
            cardCounts[3]++;
            cout<<cards[3]<<" selected."<<endl;
        } else if (random == 7) {
            cardCounts[4]++;
            cout<<cards[4]<<" selected."<<endl;
        } else {
            cardCounts[5]++;
            cout<<cards[5]<<" selected."<<endl;
        } 
    }
}

//Read candy data from file (Hw7)
vector<Candy> readCandy(string file_name, vector<Candy> candies) {
    ifstream fin(file_name);
    // If file is inaccessible return empty vector
    if (fin.fail()) {
        cout<<"Failed to open file"<<endl;
        return candies;
    }
    string line;
    //Syntax is name|description|price|candy_type|effect
    while (getline(fin, line)) {
        if (!line.empty()) {
            stringstream ss;
            ss << line;
            Candy candy;
            string sep;
            // make this neater if i have the time <-
            getline(ss, sep, '|');
            candy.setName(sep);
            getline(ss, sep, '|');
            candy.setDescription(sep);
            getline(ss, sep, '|');
            candy.setPrice(stod(sep));
            getline(ss, sep, '|');
            candy.setCandyType(sep);
            getline(ss, sep);
            candy.setEffect(stoi(sep));
            // make sure it's always in this order or its index oop
            candies.push_back(candy);
        }
    }
    // Check
    return candies;
}

// findCandy will find the candy in the pre-existing candies vector and will return an object when you search by name
// if not found, it will return nothing (the game should prevent something like this happening anyways..)
Candy findCandy(string name, vector<Candy> candies) {
    int len = candies.size();
    for (int i = 0; i < len; i++) {
        if (toLowerCase(name) == toLowerCase(candies.at(i).getName())) {
            return candies.at(i);
        }
    }
    return Candy{};
}

// same thing as findCandy but for characters
int findCharacter(string name, vector<Character> chars) {
    int len = chars.size();
    for (int i = 0; i < len; i++) {
        if (toLowerCase(name) == toLowerCase(chars.at(i).name)) {
            return i;
        }
    }
    return -1;
}

//This function is much like the read candy function
vector<Character> readCharacters(string file_name, vector<Character> characters, vector<Candy> candies) {
    ifstream fin(file_name);
    // If file is inaccessible return empty vector
    if (fin.fail()) {
        cout<<"Failed to open file"<<endl;
        return characters;
    }
    string line;
    //Syntax is name|stamina|gold|candies
    while (getline(fin, line)) {
        if (!line.empty()) {
            stringstream ss;
            ss << line;
            Character character;
            string sep;
            // make this neater if i have the time <-
            getline(ss, sep, '|');
            character.name = sep;
            getline(ss, sep, '|');
            character.stamina = stoi(sep);
            getline(ss, sep, '|');
            character.gold = stoi(sep);
            // now switch the commas to indicate that they are candy
            getline(ss, sep, ',');
            character.candies.push_back(findCandy(sep, candies));
            getline(ss, sep, ',');
            character.candies.push_back(findCandy(sep, candies));
            getline(ss, sep, ',');
            character.candies.push_back(findCandy(sep, candies));
            getline(ss, sep);
            character.candies.push_back(findCandy(sep, candies));
            // lets make sure that the candy initial candy limit is 4 so it's not oob
            characters.push_back(character);
        }
    }
    // Check
    return characters;
}

//Generate candy stores and add them to the board
void generateCandyStores(Board board, CandyStore candy_stores[]) {
    // seed random according to time
    srand((int) time(0));
    // set candy store positions & have checks so values correspond with the colors
    do {
        candy_stores[0].setCandyStorePosition(rand() % 27);
    }
    // i made sure it can't be on the starting tile
    while (candy_stores[0].getCandyStorePosition() % 3 != 0 || candy_stores[0].getCandyStorePosition() == 0);
    do {
        candy_stores[1].setCandyStorePosition(rand() % 27 + 28);
    }
    // pretty easy math here, -1 for green, -2 for blue
    while ((candy_stores[1].getCandyStorePosition() -  1) % 3 != 0);
    do {
        candy_stores[2].setCandyStorePosition(rand() % 27 + 55);
    }
    // making sure it can't be on the last finishing tile
    while ((candy_stores[2].getCandyStorePosition() - 2) % 3 != 0 || candy_stores[2].getCandyStorePosition() >= 83);

    for (int i = 0; i < 3; i++) {
        board.addCandyStore(candy_stores[i].getCandyStorePosition());
    }
}

//print all the available characters from vector
void printCharacters(vector<Character> characters) {
    int len = characters.size();
    for (int i = 0; i < len; i++) {
        cout << "Character name: " << characters.at(i).name << endl;
        cout << "Character stamina: " << characters.at(i).stamina << endl;
        cout << "Character gold: " << characters.at(i).gold << endl;
        cout << "Character candies: ";
        int len2 = characters.at(i).candies.size();
        //iterate through candies and print them
        for (int j = 0; j < len2; j++) {
            // if it's the last candy, don't print a comma
            if (j == len2 - 1) {
                cout << characters.at(i).candies.at(j).getName() << endl;
                break;
            }
            else {
                cout << characters.at(i).candies.at(j).getName() << ", ";
            }
        }
        cout << endl;
    }
}

int main() {
    // vector for selected characters for each player, and a vector for the list of characters
    vector<Character> characters;
    vector<Player> players;
    int numberOfPlayers = 0;
    cout << "How many players are going to play this game?" << endl;
    cin >> numberOfPlayers;
    
    // initialize candy stores and give them default values (not really necessary, i just chose 0 28 and 54 because of the limit squares)
    CandyStore candy_stores[3] = {CandyStore(0, "Magenta"), CandyStore(28, "Green"), CandyStore(54, "Blue")};

    //list of candies
    vector<Candy> candies;

    // read candies and store them in candies array
    candies = readCandy("candylist.txt", candies);

    // read characters. this needs to be after candies because the candies will be used to determine the character traits
    characters = readCharacters("characters.txt", characters, candies);
    if (numberOfPlayers > characters.size()) { // if number of players are greater than the number of characters stop game
        cout << "Invalid input! Restart the game with a valid amount of players" << endl;
        return -1;
    }

    clearInput();

    // get players to choose their characters
    for (int i = 0; i < numberOfPlayers; i++) {
        string name;
        cout << "Enter player " << i + 1 << " name :" << endl; // because players start from (1) not (0) unlike the index    
        getline(cin, name);
        cout << "Nice! Now here are the available characters you can select from:" << endl;
        printCharacters(characters); //print the list of characters (from vector)
        string character;
        cout << "Enter the name of the character you want to select: " << endl;
        getline(cin, character);
        while (findCharacter(character, characters) == -1) {
            cout << "Invalid character! Please enter a valid character name: " << endl;
            getline(cin, character);
        }

        // add player to players vector and remove character from characters vector
        Character characterObj = characters.at(findCharacter(character, characters));
        players.push_back(Player{name, character, 0, characterObj.gold, characterObj.candies, characterObj.stamina}); // add player to players vector
        characters.erase(characters.begin() + findCharacter(character, characters)); //using the erase method instead of iterating
        // since we're not really limited by anything (beginning index + index of character to delete)
        cout << "Character selected successfully!" << endl;
    }

    // declare board object with player count
    Board board(numberOfPlayers, players);

    // generate candy stores
    generateCandyStores(board, candy_stores);

    // add candies to the candy stores using fillcandy function
    for (int i = 0; i < 3; i++) {
        candy_stores[i].fillCandy(candies);
    }
    
    board.displayBoard();
    return 0;
}