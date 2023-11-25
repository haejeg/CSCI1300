#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include "Candy.h"
#include <vector>
#define RED "\033[;41m"     /* Red */
#define GREEN "\033[;42m"   /* Green */
#define BLUE "\033[;44m"    /* Blue */
#define MAGENTA "\033[;45m" /* Magenta */
#define CYAN "\033[;46m"    /* Cyan */
#define ORANGE "\033[48;2;230;115;0m"  /* Orange (230,115,0)*/
#define RESET "\033[0m"

using namespace std;

struct Tile
{
    string color;
    string tile_type;
};

// this will included all needed values that a player needs to have
struct Player {
    string name;
    string character;
    int position;
    int gold;
    vector<Candy> candies;
    int stamina;
};

struct Character {
    string name;
    int position;
    int gold;
    vector<Candy> candies;
    int stamina;
};

class Board
{
    private:
        const static int _BOARD_SIZE = 83;
        Tile _tiles[_BOARD_SIZE];
        const static int _MAX_CANDY_STORE = 3;
        int _candy_store_position[_MAX_CANDY_STORE];
        int _candy_store_count;
        // process of mind. initially, just an int, make that into an array of int, then vector of int, then vector of Player structs
        vector<Player> _player_position;

    public:
        Board();
        Board(int, vector<Player>);

        void resetBoard();
        void displayTile(int);
        void displayBoard();

        bool setPlayerPosition(int, int);

        int getBoardSize() const;
        int getCandyStoreCount() const;
        int getPlayerPosition(int) const;

        bool addCandyStore(int);
        bool isPositionCandyStore(int); 

        bool movePlayer(int tile_to_move_forward, int);
};

#endif