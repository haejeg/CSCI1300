#include "Board.h"
#include "CandyStore.h"
#include "Player.h"
#include "Utilities.h"
#include "Candy.h"
#include <iostream>
#include <stdlib.h>
#include <random>
#include <fstream>
#include <sstream>

//My candylist.txt and characters.txt are chatgpt generated (so it's more diverse)

using namespace std;

struct Character {
    string name;
    int position;
    int gold;
    vector<Candy> candies;
    int stamina;
};

struct Riddle {
    string question;
    string answer;
};

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

//This function is much like the read candy function (in my case, I want each character to start with a candy count of 3) 
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

// returns the color of the tile. (0 for magenta, 1 for green, 2 for blue)
int getTileType(int tile) {
    if (tile % 3 == 0) {
        return 0;
    }
    else if ((tile - 1) % 3 == 0) {
        return 1;
    }
    else {
        return 2;
    }
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

// Get candy store by position
CandyStore getCandyStore(Board board, int position, CandyStore candy_stores[]) {
    for (int i = 0; i < 3; i++) {
        if (candy_stores[i].getCandyStorePosition() == position) {
            return candy_stores[i];
        }
    }
    return CandyStore{};
}

// Create a special tiles (no class needed because there's nothing to specifically store besides the tile numbers)
void generateSpecialTiles(Board board, int percentage) {
    srand((int) time(0));
    // for all 83 tiles
    for (int i = 0; i < 83; i++) {
        // if random is within percentage
        if (rand() % 100 <= percentage) {
            specialTile tempTile;
            tempTile.index = i;
            switch(rand() % 3 + 1) { // because 4 random tiles
                case 1:
                    tempTile.tile_type = "shortcut";
                case 2:
                    tempTile.tile_type = "icecream";
                case 3:
                    tempTile.tile_type = "gumdrop";
                case 4:
                    tempTile.tile_type = "gingerbread";
                //no default needed because it's impossible
            }
            // add to special tiles in board object
            board.addSpecialTile(tempTile);
        }
    }
}

// Generate hidden treasures (no class needed because there's nothing to specifically store besides the tile numbers)
void generateTreasureTiles(Board board) { // pass this by reference so that i dont have to return anything (hassle)
    srand((int) time(0));
    // iterate it 3 times since there should be 3 hidden treasures across the map
    for (int i = 0; i < 3; i++) {
        int randNum = rand() % 83 + 1;
        specialTile tempTile;
        tempTile.index = randNum;
        tempTile.tile_type = "Treasure";
        board.addTreasureTile(tempTile);
    }
}

// Homework 7
bool playRockPaperScissors(Player player) {
    srand((int) time(0));
    int p1;
    bool tie = true;

    do {
        cout<<"Player 1: Select rock, paper, or scissors"<<endl;
        cout<<"1. Rock"<<endl;
        cout<<"2. Paper"<<endl;
        cout<<"3. Scissors"<<endl;
        cin>>p1;
        int p2 = rand() % 3 + 1;
        if (!((p1 == 1) || (p1 == 2) || (p1 == 3))) {
            cout<<"Enter a valid input!"<<endl;
            cout<<"1. Rock"<<endl;
            cout<<"2. Paper"<<endl;
            cout<<"3. Scissors"<<endl;
        }
        if (p2 == 1) {
            cout<<"You've won the rock paper scissors game congratulations!"<<endl;
            tie = false;
        }
        else if (p2 == 2) {
            cout<<"Tied the game.. Reroll!"<<endl;
            tie = true;
        }
        else if (p2 == 3) {
            cout<<"You've lost the game unfortunately :("<<endl;
            return false;
        }
    } while(tie);
    return true;
}

// Check percentage-wise whether or not a calamity will happen or not in a tile
bool isCalamity(Board board, int tile) {
    // if tile isn't candy store, special tile, or treasure tile that means that it is a regular tile
    if (!board.isPositionCandyStore(tile) && !board.isSpecialTile(tile) && !board.isTreasureTile(tile)) {
        srand((int) time(0));
        int randNum = rand() % 100;
        // if percentage <= 40 then calamity happens
        if (randNum <= 40) {
            return true;
        }
    }
    return false;
}

// Calamities should return the amount of turns lost
int doCalamity(Board board, Player player, int tile) {
    // should calmity happen?
    if (isCalamity(board, tile)) {
        cout<<"Oh no! You encountered a calamity!"<<endl;
        int calamityType = rand() % 100;
        if (calamityType <= 30) {
            cout<<"Oh no! Candy Bandits have swiped your gold coins!"<<endl;
            int coinLoss = rand() % 10 + 1;
            player.setGold(player.getGold() - coinLoss);
            cout<<"You've lost "<<coinLoss<<" gold coins from this encounter :("<<endl;
            return 0;
        }
        else if (calamityType <= 65) {
            cout<<"Oh dear! You got lost in the lollipop labyrinth!"<<endl;
            cout<<"You can recover this damage by winning in rock paper scissors."<<endl;
            if (!playRockPaperScissors(player)) {
                cout<<"You've lost a turn from this encounter :("<<endl;
                return 1;
            }
            else {
                cout<<"You've won the game! You've recovered from the calamity!"<<endl;
                return 0;
            }
        }
        else if (calamityType <= 90) {
            cout<<"Watch out! A candy avalanche has struck!"<<endl;
            cout<<"You can recover this damage by winning in rock paper scissors."<<endl;
            if (!playRockPaperScissors(player)) {
                int staminaLost = rand() % 6 + 5;
                player.setStamina(player.getStamina() - staminaLost);
                cout<<"You've lost a turn and "<<staminaLost<<" units of stamina from this encounter :("<<endl;
                return 1;
            }
            else {
                cout<<"You've won the game! You've recovered from the calamity!"<<endl;
                return 0;
            }
        }
        else {
            cout<<"Oops! You are stuck in a sticky taffy trap!"<<endl;
            cout<<"You can escape the taffy trap by using a magical candy in your inventory!"<<endl;
            if (player.getCandies().size() == 0) {
                cout<<"You don't have any candies in your inventory! You've lost a turn from this encounter :("<<endl;
                return 1;
            }
            else {
                cout<<"Here are the candies in your inventory:"<<endl;
                player.printInventory();
                string candy;
                cout<<"Enter the name of the candy you want to use to escape the taffy trap, or if you don't want to use any type exit to leave"<<endl;
                getline(cin, candy);
                while (player.removeCandy(candy) && toLowerCase(candy) != "exit") {
                    cout<<"Invalid candy! Enter a valid candy"<<endl;
                    getline(cin, candy);
                }
                if (toLowerCase(candy) == "exit") {
                    cout<<"You've lost a turn from this encounter :("<<endl;
                    return 1;
                }
                else {
                    cout<<"You've escaped the taffy trap! You've recovered from the calamity!"<<endl;
                    return 0;
                }
            }
        }
    }
    return 0;
}

/*
In Candyland, our game relies on a unique deck of Cards to add an element of chance and excitement to your journey. 
These cards come in three colors: magenta, green, and blue, each representing a regular move, and their rarer counterparts: double magenta, double green, and double blue,
offer an opportunity to advance two tiles(same color) further. When a player draws a card from the deck, a message prompt informs them of the card type, 
indicating whether it's a single-color or double-color card. The double-color cards allow a player to advance two tiles further of the same color when drawn.
So, if a player draws a double minty green card, for instance, they'll progress two green-color tiles ahead instead of one. Every turn, players randomly select a card from this deck,
shaping the course of their adventure.
*/

bool movePlayer(Board& board, Player& player, int playerid) {
    srand((int) time(0));
    int randDraw = rand() % 3;
    int willDouble = rand() % 100;
    int playerPosition = board.getPlayerPosition(playerid);
    for (int i = playerPosition + 1; i < 82; i++) {
        if (randDraw == getTileType(i)) {
            if (willDouble <= 33) {
                for (int j = i + 1; j < 81; j++) {
                    if (randDraw == getTileType(j)) {
                        board.setPlayerPosition(j, playerid);
                        return false;
                    }
                }
            }
            else {
                board.setPlayerPosition(i, playerid);
                return false;
            }
        }
    }
    board.setPlayerPosition(83, playerid);
    return true;
}

// // read all riddles from the text file given
void readRiddles(vector<Riddle>& riddles) {
    fstream fin;
    fin.open("riddles.txt");
    if (fin.fail()) {
        cout<<"Failed to open file"<<endl;
        return;
    }
    string line;
    while (getline(fin, line)) {
        if (!line.empty()) {
            stringstream ss;
            ss << line;
            Riddle riddle;
            string sep;
            // make this neater if i have the time <-
            getline(ss, sep, '|');
            riddle.question = sep;
            getline(ss, sep);
            riddle.answer = sep;
            riddles.push_back(riddle);
        }
    }
    fin.close();
}

// // check whether or not the player got a riddle correct
bool checkRiddles(vector<Riddle>& riddles) {
    int randomRiddle = rand() % riddles.size();
    cout<<"Riddle: "<<riddles.at(randomRiddle).question<<endl;
    string answer;
    getline(cin, answer);
    if (toLowerCase(answer) == toLowerCase(riddles.at(randomRiddle).answer)) {
        cout<<"Correct!"<<endl;
        return true;
    }
    cout<<"Incorrect!"<<endl;
    return false;
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

// useCandy function for using a candy
void useCandy(Board& board, Player player, vector<Candy> candies) {
    clearInput();
    // print inventory and ask player what they want to use
    cout<<"Here's the inventory:"<<endl;
    player.printInventory();
    string candyName;
    cout<<"Enter the name of the candy you want to use"<<endl;
    getline(cin, candyName);
    while (!player.removeCandy(candyName)) { // if the candy is not in the inventory, ask again, since this uses removeCandy function it will automatically remove it from the inventory if it's valid
        cout<<"Invalid candy! Enter a valid candy"<<endl;
        getline(cin, candyName);
    }
    Candy candy = findCandy(candyName, candies); // find the candy in the candies vector

    // what player do you want to use this on
    cout<<"Enter the player name you want to use this candy on, it can be yourself (or type exit to leave)"<<endl;
    clearInput();
    string name;
    getline(cin, name);
    while (toLowerCase(name) != "exit") {
        if (toLowerCase(name) == toLowerCase(player.getName())) {
            //if used on self
            cout<<"You've used the candy on yourself!"<<endl;
            // if stamina candy, add stamina
            if (candy.getCandyType() == "stamina") {
                player.setStamina(player.getStamina() + candy.getEffect());
                cout<<"Your stamina went from "<<player.getStamina()<<" to "<<player.getStamina() + candy.getEffect()<<"!"<<endl;
                return;
            }
            return;
        }
        else { // if not used on self
            int len = board.getPlayers().size();
            // loop through all players and make sure that the name is valid
            for (int i = 0; i < len; i++) {
                if (toLowerCase(name) == toLowerCase(board.getPlayers().at(i).getName())) {
                    // if it is, use the candy on that player
                    // if stamina candy, add stamina
                    if (candy.getCandyType() == "stamina") {
                        board.getPlayers().at(i).setStamina(board.getPlayers().at(i).getStamina() + candy.getEffect());
                        cout<<"You've used the candy on "<<board.getPlayers().at(i).getName()<<"!"<<endl;
                        cout<<"Their stamina went from "<<board.getPlayers().at(i).getStamina()<<" to "<<board.getPlayers().at(i).getStamina() + candy.getEffect()<<"!"<<endl;
                        return;
                    }
                }
                return;
            }
            cout<<"Invalid player! Enter a valid player name"<<endl;
            getline(cin, name);
        }
    }
    // print inventory after change
    cout<<"Here's the inventory after the change:"<<endl;
    player.printInventory();
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

    // read riddles (vector of riddles, readriddles function)
    vector<Riddle> riddles;
    readRiddles(riddles);

    // read characters. this needs to be after candies because the candies will be used to determine the character traits
    characters = readCharacters("characters.txt", characters, candies);
    if (numberOfPlayers > characters.size()) { // if number of players are greater than the number of characters stop game
        cout << "Invalid input! Restart the game with a valid amount of players" << endl;
        return -1;
    }

    clearInput();

    // get players to choose their characters, remove them if they are selected and add them to the players vector
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
        Player player;
        player.setName(name);
        player.setCharacter(characterObj.name);
        player.setPosition(0);
        player.setGold(characterObj.gold);
        player.setStamina(characterObj.stamina);
        player.setCandies(characterObj.candies);
        players.push_back(player); // add player to players vector
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

    bool win = false; // win condition
    int winner = 0; // winner index for later

    // start by displaying the board
    cout<<"Let's begin the game. Here's the board:"<<endl;
    board.displayBoard();

    do { // iterate until someone wins
        int len = players.size(); // get length of players vector
        for (int i = 0; i < len; i++) { // iterate through players
            int optionNum; // option number for the menu
            cout<<"It's "<<players.at(i).getName()<<"'s turn"<<endl; // print player name
            cout<<"Choose an option:"<<endl; // print menu
            cout<<"1. Draw a card"<<endl;
            cout<<"2. Use candy"<<endl;
            cout<<"3. Show player stats"<<endl;
            cin>>optionNum;
            while (!((optionNum == 1) || (optionNum == 2) || (optionNum == 3))) { // make sure it's a valid input
                clearInput(); 
                cout<<"Invalid input. Enter a valid one."<<endl; 
                cin>>optionNum; // get input again
            }
            switch (optionNum) {
                default:
                    // this is impossible since we already checked for valid input (it's just for jokes)
                    cout<<"Something happened here..."<<endl;
                    break;
                case 1:
                    // draw card, move player, check if player is on candy store, check if player is on special tile, or if on a treasure tile
                    if (movePlayer(board, players.at(i), i)) {
                        winner = i;
                        win = true;
                    }
                    if (board.isPositionCandyStore(board.getPlayerPosition(i))) {
                        //print candystore
                        getCandyStore(board, board.getPlayerPosition(i), candy_stores).displayCandies();
                        string candy;
                        cout<<"Enter the name of the candy you want to buy or type exit to leave"<<endl;
                        getline(cin, candy);
                        while (!getCandyStore(board, board.getPlayerPosition(i), candy_stores).removeCandy(candy) && toLowerCase(candy) != "exit") {
                            cout<<"Invalid candy! Enter a valid candy"<<endl;
                            getline(cin, candy);
                        }
                        if (toLowerCase(candy) == "exit") {
                            cout<<"You've left the candy store"<<endl;
                        }
                        else {
                            players.at(i).addCandy(findCandy(candy, candies));
                            players.at(i).setGold(players.at(i).getGold() - findCandy(candy, candies).getPrice());
                        }
                    }
                    if (board.isSpecialTile(board.getPlayerPosition(i))) {
                        // do special tile stuff
                    }
                    break;
                case 2:
                    // use candy
                    useCandy(board, players.at(i), players.at(i).getCandies());
                    break;
                case 3:
                    cout<<"Player "<<players.at(i).getName()<<"'s stats:"<<endl;
                    cout<<"Character: "<<players.at(i).getCharacter()<<endl;
                    cout<<"Stamina: "<<players.at(i).getStamina()<<endl;
                    cout<<"Gold: "<<players.at(i).getGold()<<endl;
                    cout<<"Inventory: "<<endl;
                    players.at(i).printInventory();
                    break;
            }
            cout<<"Board after turn:"<<endl;
            board.displayBoard();
            clearInput();
        }
    }
    while(!win);
    
    cout<<"You've reached the end of the board! Congratulations Player "<<players.at(winner).getName()<<endl;
    board.displayBoard();

    return 0;
}