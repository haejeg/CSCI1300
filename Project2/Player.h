#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <vector>
#include "Candy.h"

using namespace std;

class Player {
    private:
        string _name;
        string _character;
        int _position;
        int _gold;
        int _stamina;
        vector<Candy> _candies;

    public:
        Player();
        Player(string, string, int, int, int, vector<Candy>);

        string getName() const;
        string getCharacter() const;
        int getPosition() const;
        int getGold() const;
        int getStamina() const;
        vector<Candy> getCandies() const;
        int getCandyAmount() const;

        void setName(string);
        void setCharacter(string);
        void setPosition(int);
        void setGold(int);
        void setStamina(int);
        void setCandies(vector<Candy>);
        void addCandy(Candy);
        bool removeCandy(string);
        Candy findCandy(string, vector<Candy>);

        void printInventory();
};

#endif