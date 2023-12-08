#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include "Candy.h"
#include <vector>

using namespace std;

class Player {
    private:
        string _name;
        int _id;
        string _character;
        int _position;
        int _gold;
        int _stamina;
        bool _shield;
        vector<Candy> _candies;

    public:
        Player();
        Player(string, string, int, int, int, vector<Candy>);

        void setName(string);
        string getName() const;

        void setCharacter(string);
        string getCharacter() const;

        void setPosition(int);
        int getPosition() const;

        void setGold(int);
        int getGold() const;
        void setShield(bool); // protects the player from being robbed
        bool getShield() const;

        void setStamina(int);
        int getStamina() const;

        vector<Candy> getCandies() const;
        void setCandies(vector<Candy>);
        void addCandy(Candy);
        bool removeCandy(string);
        Candy findCandy(string, vector<Candy>);
        int getCandyAmount() const;

        void printInventory();
};

#endif