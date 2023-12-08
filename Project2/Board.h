#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include "Player.h"
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

struct specialTile {
    string tile_type;
    int index;  
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
        vector<Player> _previous_position;
        vector<Player> _player_position;
        vector<specialTile> _special_tiles;
        vector<specialTile> _treasure_tiles;

    public:
        Board();
        Board(int, vector<Player>);

        void resetBoard();
        void displayTile(int);
        void displayBoard();

        int getBoardSize() const;

        int getCandyStoreCount() const;
        bool addCandyStore(int);
        bool isPositionCandyStore(int); 
        int getCandyStorePosition(int) const;

        vector<specialTile> getSpecialTiles() const;
        vector<specialTile> getTreasureTiles() const;

        // all player stuff since vector<Player> _player_position is private in Board which means we need to use getters and setters to access Player stuff
        string getPlayerName(int) const;
        string getPlayerCharacter(int) const;

        int getPlayerPosition(int) const;
        bool movePlayer(int tile_to_move_forward, int);
        bool setPlayerPosition(int, int);      
        vector<Player> getPlayers() const;  
        int getPreviousPlayerPosition(int playerid) const;
        void setPlayerStamina(int, int);
        void setPlayerGold(int, int);
        void setPlayerShield(int, bool);
        void setPlayerCandies(int, vector<Candy>);
        void addCandyToPlayer(int, Candy);
        bool removeCandyFromPlayer(int, string);
        Candy findCandyFromPlayer(int, string);
        int getPlayerCandyAmount(int) const;

        int getPlayerStamina(int) const;
        int getPlayerGold(int) const;
        bool getPlayerShield(int) const;
        vector<Candy> getPlayerCandies(int) const;
        void printPlayerInventory(int);

        // tile stuff
        void addSpecialTile(specialTile);
        bool isSpecialTile(int);
        specialTile getSpecialTile(int);

        void addTreasureTile(specialTile);
        bool isTreasureTile(int);
};

#endif