#include "Board.h"
#include "CandyStore.h"
#include "Player.h"
#include "Candy.h"
#include "Utilities.h"
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
            candy.name = sep;
            getline(ss, sep, '|');
            candy.description = sep;
            getline(ss, sep, '|');
            candy.price = abs(stod(sep)); // i had to use abs because chatgpt does not give me consistent numerical results for candies generation (sometimes stuff will be negative for no reason)
            getline(ss, sep, '|');
            candy.candy_type = sep;
            getline(ss, sep);
            candy.effect = abs(stoi(sep)); // i had to use abs because chatgpt does not give me consistent numerical results for candies generation (sometimes stuff will be negative for no reason)
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
        if (toLowerCase(name) == toLowerCase(candies.at(i).name)) {
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

struct Card { // i really dont need this but this is in minimum requirements
    string color;
    int feature;
};

bool drawCard(Board& board, int playerid, vector<Card>& cards) {
    srand((int) time(0));
    string str = "";
    int randDraw = rand() % 3;
    if (randDraw == 0) {
        str = "Cotton Candy Magenta";
    }
    else if (randDraw == 1) {
        str = "Minty Green";
    }
    else {
        str = "Bubblegum Blue";
    }
    int willDouble = rand() % 100;
    int playerPosition = board.getPlayerPosition(playerid);
    for (int i = playerPosition + 1; i < 82; i++) {
        if (randDraw == getTileType(i)) {
            if (willDouble <= 33) {
                for (int j = i + 1; j < 81; j++) {
                    if (randDraw == getTileType(j)) {
                        board.setPlayerPosition(j, playerid);
                        str.insert(0, "Double ");
                        cout<<board.getPlayerName(playerid)<<" drew a "<<str<<" card."<<endl;
                        cards.push_back(Card{str, j});
                        return false;
                    }
                }
            }
            else {
                board.setPlayerPosition(i, playerid);
                cout<<board.getPlayerName(playerid)<<" drew a "<<str<<" card."<<endl;
                cards.push_back(Card{str, i});
                return false;
            }
        }
    }
    cards.push_back(Card{str, 83});
    board.setPlayerPosition(83, playerid);
    
    return true;
}

//Generate candy stores and add them to the board
void generateCandyStores(Board& board, CandyStore candy_stores[]) {
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
    // return empty candystore object if not found
    return CandyStore{};
}

// Create a special tiles (no class needed because there's nothing to specifically store besides the tile numbers)
void generateSpecialTiles(Board& board, int percentage) {
    srand((int) time(0));
    int count = 0;
    // for all 83 tiles
    for (int i = 1; i < 82; i++) {
        // if random is within percentage
        if (rand() % 100 <= percentage) {
            specialTile tempTile;
            tempTile.index = i;
            // generate random tile type
            int randTile = rand() % 4 + 1;
            switch(randTile) { // because 4 random tiles
                case 1:
                    tempTile.tile_type = "shortcut";
                    break;
                case 2:
                    tempTile.tile_type = "icecream";
                    break;
                case 3:
                    tempTile.tile_type = "gumdrop";
                    break;
                case 4:
                    tempTile.tile_type = "gingerbread";
                    break;
                //no default needed because it's impossible
            }
            // add to special tiles in board object
            cout<<"Special tile generated at position "<<i<<endl;
            board.addSpecialTile(tempTile);
            cout<<"Special  tile type: "<<tempTile.tile_type<<endl;
            count++;
        }
        if (count > 5) {
            return;
        }
    }
}

int doSpecialTile(Board& board, int position, int playerid, vector<Card>& cards) {
    if (board.getSpecialTile(position).tile_type == "shortcut") {
        cout<<"You've landed on a shortcut tile! Move 4 steps forward."<<endl;
        if (!board.setPlayerPosition(board.getPlayerPosition(playerid) + 4, playerid)) {
            return 1;
        };
        return 0;
    } else if (board.getSpecialTile(position).tile_type == "icecream") {
        cout<<"You've landed on an icecream tile! Draw another card."<<endl;
        drawCard(board, playerid, cards);
    } else if (board.getSpecialTile(position).tile_type == "gumdrop") {
        srand((int) time(0));
        int randNum = rand() % 6 + 5;
        cout<<"You've landed on a gumdrop tile.. You will be taken 4 steps backwards and also lost "<< randNum <<" coins in that process"<<endl;
        if (!board.setPlayerPosition(board.getPlayerPosition(playerid) - 4, playerid)) {
            return -2;
        }
    } else if (board.getSpecialTile(position).tile_type == "gingerbread") {
        cout<<"You've landed on a gingerbread tile! You will be taken to your previous position"<<endl;
        if (!board.setPlayerPosition(board.getPreviousPlayerPosition(playerid), playerid)) {
            return -1;
        }
    }
    return 0;
}

// Generate hidden treasures (no class needed because there's nothing to specifically store besides the tile numbers)
void generateTreasureTiles(Board& board) { // pass this by reference so that i dont have to return anything (hassle)
    srand((int) time(0));
    // iterate it 3 times since there should be 3 hidden treasures across the map
    for (int i = 0; i < 3; i++) {
        if (i == 0 || board.isPositionCandyStore(i) || board.isSpecialTile(i)) {
            // make sure it's not on the starting tile, special tile, or candy store
            int randNum = rand() % 82 + 1;
            specialTile tempTile;
            tempTile.index = randNum;
            tempTile.tile_type = "Treasure";
            board.addTreasureTile(tempTile);
        }
        int randNum = rand() % 83 + 1;
        specialTile tempTile;
        tempTile.index = randNum;
        tempTile.tile_type = "Treasure";
        board.addTreasureTile(tempTile);
    }
}

// Homework 7
bool playRockPaperScissors() {
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
int doCalamity(Board& board, int playerid, int tile) {
    // should calmity happen?
    if (isCalamity(board, tile)) {
        cout<<"Oh no! You encountered a calamity!"<<endl;
        int calamityType = rand() % 100;
        if (calamityType <= 30) {
            cout<<"Candy Bandits have swiped your gold coins!"<<endl;
            int coinLoss = rand() % 10 + 1;
            board.setPlayerGold(playerid, board.getPlayerGold(playerid) - coinLoss);
            cout<<"You've lost "<<coinLoss<<" gold coins from this encounter :("<<endl;
            cout << "Your new gold count is: " << board.getPlayerGold(playerid)<<endl;
            return 0;
        }
        else if (calamityType <= 65) {
            cout<<"You got lost in the lollipop labyrinth!"<<endl;
            cout<<"You can recover this damage by winning in rock paper scissors."<<endl;
            if (!playRockPaperScissors()) {
                cout<<"You've lost a turn from this encounter :("<<endl;
                return 1;
            }
            else {
                cout<<"You've won the game! You've recovered from the calamity!"<<endl;
                return 0;
            }
        }
        else if (calamityType <= 90) {
            cout<<"A candy avalanche has struck!"<<endl;
            cout<<"You can recover this damage by winning in rock paper scissors."<<endl;
            if (!playRockPaperScissors()) {
                int staminaLost = rand() % 6 + 5;
                board.setPlayerStamina(playerid, board.getPlayerStamina(playerid) - staminaLost);
                cout<<"You've lost a turn and "<<staminaLost<<" units of stamina from this encounter :("<<endl;
                cout << "Your new stamina is: " << board.getPlayerStamina(playerid)<<endl;
                return 1;
            }
            else {
                cout<<"You've won the game! You've recovered from the calamity!"<<endl;
                return 0;
            }
        }
        else {
            cout<<"You are stuck in a sticky taffy trap!"<<endl;
            cout<<"You can escape the taffy trap by using a magical candy in your inventory!"<<endl;
            if (board.getPlayerCandyAmount(playerid) == 0) {
                cout<<"You don't have any candies in your inventory! You've lost a turn from this encounter :("<<endl;
                return 1;
            }
            else {
                cout<<"Here are the candies in your inventory:"<<endl;
                board.printPlayerInventory(playerid);
                string candy;
                cout<<"Enter the name of the candy you want to use to escape the taffy trap, or if you don't want to use any type exit to leave"<<endl;
                clearInput();
                getline(cin, candy);
                while (!board.removeCandyFromPlayer(playerid, candy) && toLowerCase(candy) != "exit") {
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

// give random treasure function
void giveRandomTreasure(Board board, int playerid) {
    srand((int) time(0));
    int randNum = rand() % 100;
    if (randNum <= 30) { // set stamina randomly between 10 and 30
        int randStam = rand() % 21 + 10;
        cout<<"You get "<<randStam<<" units of stamina!"<<endl;
        board.setPlayerStamina(playerid, board.getPlayerStamina(playerid) + randStam);
    }
    else if (randNum <= 40) { // set gold randomly between 20 and 40
        int randGold = rand() % 21 + 20;
        cout<<"You've found a treasure chest full of gold.. You've gained "<<randGold<<" gold."<<endl;
        board.setPlayerGold(playerid, board.getPlayerGold(playerid) + randGold);
    }
    else if (randNum <= 70) { // shield treasure
        cout<<"You've stumbled upon the Robber's repel, this is a shield that will protect you against a robber once."<<endl;
        board.setPlayerShield(playerid, true);
    }
    else { // get candy
        cout<<"You've found a magical candy! You've gained a magical candy!"<<endl;
        int randChance = rand() % 100;
        if (randChance <= 70) {
            Candy tempCandy;
            tempCandy.candy_type = "stamina";
            tempCandy.effect = 50;
            tempCandy.name = "Magical Jellybean";
            tempCandy.description = "A magical jellybean that will give you a stamina boost";
            board.addCandyToPlayer(playerid, tempCandy);
        }
        else {
            Candy tempCandy;
            tempCandy.candy_type = "treasure";
            tempCandy.effect = 0;
            tempCandy.name = "Magical Truffle";
            tempCandy.description = "A magical truffle that will give you a chance at obtaining a different treasure";
            board.addCandyToPlayer(playerid, tempCandy);
        }
    }
}

// // read all riddles from the text file given
void readRiddles(vector<Riddle>& riddles) {
    // open file
    fstream fin;
    fin.open("riddles.txt");
    if (fin.fail()) {
        cout<<"Failed to open file"<<endl;
        return;
    }
    string line;
    //Syntax is question|answer
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
    fin.close(); // close file
}

// // check whether or not the player got a riddle correct
bool checkRiddles(vector<Riddle>& riddles) {
    // seed random according to time
    int randomRiddle = rand() % riddles.size();
    cout<<"Riddle: "<<riddles.at(randomRiddle).question<<endl; // print random riddle
    string answer;
    cin.ignore();
    getline(cin, answer);
    if (toLowerCase(answer) == toLowerCase(riddles.at(randomRiddle).answer)) { // if answer is correct
        cout<<"Correct!"<<endl; 
        return true; // return true
    }
    cout<<"Incorrect!"<<endl;
    return false; // if answer is not right return false
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
                cout << characters.at(i).candies.at(j).name << endl;
                break;
            }
            else {
                cout << characters.at(i).candies.at(j).name << ", ";
            }
        }
        cout << endl;
    }
}

// useCandy function for using a candy
void useCandy(Board& board, int playerid, vector<Candy> candies) {
    clearInput();
    // print inventory and ask player what they want to use
    cout<<"Here's the inventory:"<<endl;
    board.printPlayerInventory(playerid);
    string candyName;
    cout<<"Enter the name of the candy you want to use (or type exit to leave)"<<endl;
    getline(cin, candyName);
    while (!board.removeCandyFromPlayer(playerid, candyName) && candyName != "exit") { // if the candy is not in the inventory, ask again, since this uses removeCandy function it will automatically remove it from the inventory if it's valid
        cout<<"Invalid candy! Enter a valid candy"<<endl;
        getline(cin, candyName);
    }
    if (candyName == "exit") {
        return;
    }
    Candy candy = findCandy(candyName, candies); // find the candy in the candies vector

    // what player do you want to use this on
    cout<<"Enter the player name you want to use this candy on, it can be yourself (or type exit to leave)"<<endl;
    string name;
    getline(cin, name);
    while (toLowerCase(name) != "exit") {
        int len = board.getPlayers().size();
        // loop through all players and make sure that the name is valid
        for (int i = 0; i < len; i++) {
            if (toLowerCase(name) == toLowerCase(board.getPlayerName(i))) {
                // if it is, use the candy on that player
                // if stamina candy, add stamina
                cout<<"Candy type: "<<candy.candy_type<<endl;
                if (candy.candy_type == "stamina") {
                    cout<<"Stamina of player "<<board.getPlayerName(i)<<" before: "<<board.getPlayerStamina(i)<<endl;
                    board.setPlayerStamina(i, board.getPlayerStamina(i) + candy.effect);
                    cout<<"You've used the candy on "<<board.getPlayerName(i)<<"!"<<endl;
                    cout<<"Their stamina went to "<<board.getPlayerStamina(i)<<"!"<<endl;
                    cout<<"Here's the inventory after the change:"<<endl;
                    board.printPlayerInventory(playerid);
                    return;
                }
                else if (candy.candy_type == "shield") {
                    cout<<"Shield of player "<<board.getPlayerName(i)<<" before: "<<board.getPlayerShield(i)<<endl;
                    board.setPlayerShield(i, true);
                    cout<<"You've used the candy on "<<board.getPlayerName(i)<<"!"<<endl;
                    cout<<"Their shield is now "<<board.getPlayerShield(i)<<"!"<<endl;
                    cout<<"Here's the inventory after the change:"<<endl;
                    board.printPlayerInventory(playerid);
                    return;
                }
                else if (candy.candy_type == "attack") {
                    cout<<"Stamina of player "<<board.getPlayerName(i)<<" before: "<<board.getPlayerStamina(i)<<endl;
                    board.setPlayerStamina(i, board.getPlayerStamina(i) - candy.effect);
                    cout<<"You've used the candy on "<<board.getPlayerName(i)<<"!"<<endl;
                    cout<<"Their stamina went to "<<board.getPlayerStamina(i)<<"!"<<endl;
                    cout<<"Here's the inventory after the change:"<<endl;
                    board.printPlayerInventory(playerid);
                    return;
                }
                else if (candy.candy_type == "treasure") {
                    cout<<"You've used the candy on "<<board.getPlayerName(i)<<"!"<<endl;
                    giveRandomTreasure(board, i);
                    cout<<"Here's the inventory after the change:"<<endl;
                    board.printPlayerInventory(playerid);
                    return;
                }
            }
        }
        cout<<"Invalid player! Enter a valid player name"<<endl;
        getline(cin, name);
    }
}


int main() {
    // vector for selected characters for each player, and a vector for the list of characters
    ofstream debug;
    debug.open("debug.txt");
    if (debug.fail()) {
        cout<<"Debug error. Make sure debug.txt is modifiable."<<endl;
        debug.close();
    }

    vector<Card> cards;
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
    int charLen = characters.size();
    if (numberOfPlayers > charLen) { // if number of players are greater than the number of characters stop game
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

    debug<<"Candy stores generated"<<endl;
    for (int i = 0; i < 3; i++) {
        debug<<"Candy store "<<i<<" position: "<<candy_stores[i].getCandyStorePosition()<<endl;
    }

    // add candies to the candy stores using fillcandy function
    for (int i = 0; i < 3; i++) {
        candy_stores[i].fillCandy(candies);
    }

    generateSpecialTiles(board, 12); // I decided not to make it a 25% chance because it seems to fill up too quickly (and it's not really fun to play with)

    debug<<"Special tiles generated"<<endl;
    int specialLen = board.getSpecialTiles().size();
    for (int i = 0; i < specialLen; i++) {
        debug<<"Special tile "<<i<<" position: "<<board.getSpecialTiles().at(i).index<<endl;
    }

    generateTreasureTiles(board); // generate treasure tiles

    debug<<"Treasure tiles generated"<<endl;
    int treasureLen = board.getTreasureTiles().size();
    for (int i = 0; i < treasureLen; i++) {
        debug<<"Treasure tile "<<i<<" position: "<<board.getTreasureTiles().at(i).index<<endl;
    }

    vector<int> turnsLost(numberOfPlayers); // vector for turns lost for each player


    bool win = false; // win condition
    int winner = 0; // winner index for later

    // start by displaying the board
    cout<<"Let's begin the game. Here's the board:"<<endl;
    board.displayBoard();

    do { // iterate until someone wins
        int len = players.size(); // get length of players vector
        int i = 0;
        while (i < len) { // iterate through players
            if (turnsLost[i] > 0) { // if player has lost a turn, skip their turn
                cout<<"Player "<<board.getPlayerName(i)<<" doesn't have a turn this round. They will be skipped."<<endl;
                turnsLost[i]--;
                i++;
                continue;
            }
            if (board.getPlayerStamina(i) <= 0) { // if player has no stamina, skip their turn
                cout<<"Player "<<board.getPlayerName(i)<<" has no stamina left. They will be skipped."<<endl;
                turnsLost[i]+=2;
                i++;
                continue;
            }
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
                case 1: {
                    // draw card, move player, check if player is on candy store, check if player is on special tile, or if on a treasure tile
                    // srand((int) time(0));
                    int marshHail = rand() % 100;
                    if (marshHail <= 5) { 
                        int randTiles = rand() % 4 + 1;
                        cout<<"A marshmellow hailstorm has hit the board! Every player on the board goes back "<<randTiles<<" tiles!"<<endl;
                        for (int j = 0; j < len; j++) {
                            board.setPlayerPosition(board.getPlayerPosition(j) - randTiles, j);
                        }
                        i++;
                        break;
                    }
                    }

                    if (drawCard(board, i, cards)) {
                        winner = i;
                        win = true;
                    }

                    // move player to candy store for debugging purposes
                    // board.setPlayerPosition(candy_stores[0].getCandyStorePosition(), i);

                    // board.setPlayerPosition(board.getSpecialTiles().at(2).index, i);

                    // board.setPlayerPosition(board.getTreasureTiles().at(0).index, i);

                    // same tile constraints (if two players are on the same tile, the first player will be moved back to the previous tile)
                    for (int j = 0; j < len; j++) {
                        if (board.getPlayerPosition(i) == board.getPlayerPosition(j) && i != j) { // make sure that the player is not checking against itself
                            board.setPlayerPosition(board.getPlayerPosition(j) - 1, j); // set player position to previous position
                            int randRobber = rand() % 26 + 5;
                            board.setPlayerGold(i, board.getPlayerGold(i) - randRobber); // subtract random gold from player
                            cout<<"Player "<<board.getPlayerName(i)<<" has been robbed by Player "<<board.getPlayerName(j)<<"! They've lost "<<randRobber<<" gold."<<endl;
                            board.setPlayerGold(j, board.getPlayerGold(j) + randRobber); // add random gold to player  
                            cout<<"Player "<<board.getPlayerName(j)<<" has stolen "<<randRobber<<" gold from Player "<<board.getPlayerName(i)<<"!"<<endl;
                        }
                    }
                    
                    if (board.isPositionCandyStore(board.getPlayerPosition(i))) { // check if player is on candy store
                        //print candystore
                        getCandyStore(board, board.getPlayerPosition(i), candy_stores).displayCandies();
                        string candy;
                        cout<<"Enter the name of the candy you want to buy or type exit to leave"<<endl;
                        clearInput();
                        getline(cin, candy);
                        // if candy is not in the candy store, ask again or if they want to leave type exit
                        cout<<"Candy store position: "<<getCandyStore(board, board.getPlayerPosition(i), candy_stores).getCandyStorePosition()<<endl;
                        while (getCandyStore(board, board.getPlayerPosition(i), candy_stores).findCandy(candy).name == "" && toLowerCase(candy) != "exit") { 
                            cout<<"Invalid candy! Enter a valid candy"<<endl;
                            getline(cin, candy);
                        }
                        // if they type exit then leave the candy store (there's probably a more efficient way to go about this)
                        if (toLowerCase(candy) == "exit") {
                            cout<<"You've left the candy store"<<endl;
                        }
                        else { // if they don't type exit then add the candy to the player's inventory and subtract the candy cost gold
                            board.addCandyToPlayer(i, findCandy(candy, candies));
                            board.setPlayerGold(i, board.getPlayerGold(i) - findCandy(candy, candies).price);
                            cout<<"You've bought a "<<findCandy(candy, candies).name<<"!"<<endl;
                        }
                    }
                    else if (board.isSpecialTile(board.getPlayerPosition(i))) { // check if player is on special tile
                        // do special tile stuff
                        specialTile tile = board.getSpecialTile(board.getPlayerPosition(i));
                        int getSpecialValue = doSpecialTile(board, board.getPlayerPosition(i), i, cards);
                        if (getSpecialValue == 1) { // if it's a shortcut tile go forward 4 steps
                            winner = i;
                            win = true;
                        }
                        else if (getSpecialValue == -1) { // if it's a gumdrop tile go back 4 steps
                            board.setPlayerPosition(board.getPreviousPlayerPosition(i), i);
                        }
                        else if (getSpecialValue == -2) {
                            board.setPlayerPosition(board.getPlayerPosition(i) - 4, i);
                            turnsLost[i]++;
                        }
                        // other stuff doesn't matter since it's just icecream
                    }
                    else if (board.isTreasureTile(board.getPlayerPosition(i))) { // check if player is on treasure tile
                        // do treasure tile stuff
                        if (checkRiddles(riddles)) {
                            // if riddle is correct, give random treasure
                            cout<<"Congratulations! You got the riddle correct!"<<endl;
                            giveRandomTreasure(board, i);
                        }
                        else {
                            // if riddle is incorrect just print a message and don't do anyting else
                            cout<<"Unfortunately you got your riddle incorrect.."<<endl;
                        }
                    }
                    else {
                        // do calamity stuff
                        int getCalamityValue = doCalamity(board, i, board.getPlayerPosition(i));
                        if (getCalamityValue == 1) {
                            // if it's a gumdrop, lose a turn and stamina
                            turnsLost[i]++;
                        }
                    }
                    i++; // move turns
                    break;
                case 2:
                    // use candy
                    useCandy(board, i, board.getPlayerCandies(i));
                    i++; // move turns
                    break;
                case 3:
                    cout<<"Player "<<board.getPlayerName(i)<<"'s stats:"<<i<<endl;
                    cout<<"Character: "<<board.getPlayerCharacter(i)<<endl;
                    cout<<"Stamina: "<<board.getPlayerStamina(i)<<endl;
                    cout<<"Gold: "<<board.getPlayerGold(i)<<endl;
                    cout<<"Inventory: "<<endl;
                    board.printPlayerInventory(i);
                    // checking stats does not take up a turn
                    break;
            }
            cout<<"Board after turn:"<<endl;
            board.displayBoard();
        }
    }
    while(!win);
    
    board.setPlayerPosition(83, winner);
    board.displayBoard();
    cout<<"You've reached the end of the board! Congratulations Player "<<players.at(winner).getName()<<endl;
    
    cout<<"Here are your stats:"<<endl; 
    for (int i = 0; i < numberOfPlayers; i++) {
        cout<<"Player "<<board.getPlayerName(i)<<"'s stats:"<<i<<endl;
        cout<<"Character: "<<board.getPlayerCharacter(i)<<endl;
        cout<<"Stamina: "<<board.getPlayerStamina(i)<<endl;
        cout<<"Gold: "<<board.getPlayerGold(i)<<endl;
        cout<<"Inventory: "<<endl;
        board.printPlayerInventory(i);
    }
    cout<<"ALL CARDS DRAWN"<<endl;
    int cardlen = cards.size();
    for (int i = 0; i < cardlen; i++) {
        cout<<"Card number "<<i+1<<": ";
        cout<<cards.at(i).color<<" | Position: "<<cards.at(i).feature<<endl;
    }

    ofstream fout;
    fout.open("stats.txt");
    if (fout.fail()) {
        cout<<"Failed to open file"<<endl;
        return -1;
    }
    fout<<"STATS ---------------------------------------"<<endl;
    for (int i = 0; i < numberOfPlayers; i++) {
        fout<<"Player "<<board.getPlayerName(i)<<"'s stats:"<<i<<endl;
        fout<<"Character: "<<board.getPlayerCharacter(i)<<endl;
        fout<<"Stamina: "<<board.getPlayerStamina(i)<<endl;
        fout<<"Gold: "<<board.getPlayerGold(i)<<endl;
        fout<<"Candies: | ";
        int len = board.getPlayerCandies(i).size();
        for (int j = 0; j < len; j++) {
            fout<<board.getPlayerCandies(i).at(j).name<<" | ";
        }
        fout<<endl;
    }
    fout<<"ALL CARDS DRAWN"<<endl;
    for (int i = 0; i < cardlen; i++) {
        fout<<"Card number "<<i+1<<": ";
        fout<<cards.at(i).color<<" | Position: "<<cards.at(i).feature<<endl;
    }
    fout.close();

    return 0;
}