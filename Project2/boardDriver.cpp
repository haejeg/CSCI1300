#include "Board.h"
#include <iostream>
#include <stdlib.h>
#include <random>
#include <time.h>

using namespace std;

void generateCandyStores(Board board, int candy_stores[]) {
    srand((int) time(0));
    do {
        candy_stores[0] = rand() % 27;
    }
    while (candy_stores[0] % 3 != 0 || candy_stores[0] == 0);
    cout<<"Final candy store 1: "<<candy_stores[0]<<endl;
    do {
        candy_stores[1] = rand() % 27 + 28;
    }
    while ((candy_stores[1] - 1) % 3 != 0);
    cout<<"Final candy store 2: "<<candy_stores[1]<<endl;
    do {
        candy_stores[2] = rand() % 27 + 55;
    }
    while ((candy_stores[2] - 2) % 3 != 0 || candy_stores[2] >= 83);
    cout<<"Final candy store 3: "<<candy_stores[2]<<endl;

    for (int i = 0; i < 3; i++) {
        board.addCandyStore(candy_stores[i]);
    }
}

void updateBoard(Board board) {
    system("cls");
    board.displayBoard();
}

int main()
{
    Board board;
    // updateBoard(board);
    int candy_stores[3] = {0, 28, 55};
    // updateBoard(board);
    generateCandyStores(board, candy_stores);
    for (int i = 0; i < 3; i++) {
        board.displayTile(candy_stores[i]);
    }
    return 0;
}