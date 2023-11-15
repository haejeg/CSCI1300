#include "Board.h"
#include "CandyStore.h"
#include <iostream>
#include <stdlib.h>
#include <random>
#include <fstream>
#include <sstream>

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
            getline(ss, sep, '|');
            candy.name = sep;
            getline(ss, sep, '|');
            candy.description = sep;
            getline(ss, sep, '|');
            candy.price = stod(sep);
            getline(ss, sep, '|');
            candy.candy_type = sep;
            getline(ss, sep);
            candy.effect = stoi(sep);
            candies.push_back(candy);
        }
    }
    // Check
    cout<<"Candy list read successfully"<<endl;
    return candies;
}

//Generate candy stores and add them to the board
void generateCandyStores(Board board, CandyStore candy_stores[]) {
    srand((int) time(0));
    do {
        candy_stores[0].setCandyStorePosition(rand() % 27);
    }
    while (candy_stores[0].getCandyStorePosition() % 3 != 0 || candy_stores[0].getCandyStorePosition() == 0);
    cout<<"Final candy store 1: "<<candy_stores[0].getCandyStorePosition()<<endl;
    do {
        candy_stores[1].setCandyStorePosition(rand() % 27 + 28);
    }
    while ((candy_stores[1].getCandyStorePosition() -  1) % 3 != 0);
    cout<<"Final candy store 2: "<<candy_stores[1].getCandyStorePosition()<<endl;
    do {
        candy_stores[2].setCandyStorePosition(rand() % 27 + 55);
    }
    while ((candy_stores[2].getCandyStorePosition() - 2) % 3 != 0 || candy_stores[2].getCandyStorePosition() >= 83);
    cout<<"Final candy store 3: "<<candy_stores[2].getCandyStorePosition()<<endl;

    for (int i = 0; i < 3; i++) {
        board.addCandyStore(candy_stores[i].getCandyStorePosition());
    }
    cout<<"Candy stores generated successfully"<<endl;
}

void updateBoard(Board board) {
    board.displayBoard();
}

int main()
{
    Board board, board2;
    CandyStore candy_stores[3] = {CandyStore(0, "Magenta"), CandyStore(28, "Green"), CandyStore(54, "Blue")};
    cout<<"Initializing candy from data.."<<endl;
    vector<Candy> candies;
    candies = readCandy("candylist.txt", candies);
    cout<<"Generating candy stores.."<<endl;
    generateCandyStores(board, candy_stores);
    cout<<"Adding candies to candy stores.."<<endl;
    for (int i = 0; i < 3; i++) {
        candy_stores[i].fillCandy(candies);
    }
    


    cout<<"WOW"<<candy_stores[0].getCandyAmount()<<endl;

    for (int i = 0; i < 3; i++) {
        board.displayTile(candy_stores[i].getCandyStorePosition());
        board.setPlayerPosition(candy_stores[i].getCandyStorePosition());
        candy_stores[i].displayCandies();
    }

    // for (int i = 0; i < 83; i++) {
    //     int storeCount = 0;
    //     board.movePlayer(1);
    //     if (board.isPositionCandyStore(i)) {
            
    //         cout<<storeCount<<endl;
    //         storeCount++;
    //     }
    // }

    updateBoard(board);
    
    return 0;
}