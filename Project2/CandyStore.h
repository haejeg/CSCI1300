#ifndef CANDYSTORE_H
#define CANDYSTORE_H

#include "Board.h"
#include "Candy.h"
#include <iostream>
#include <vector>

using namespace std;

class CandyStore
{
    private:
        vector<Candy> _inventory;
        int _candy_amount;
        int _candy_store_position;
        string _candy_store_name;
        const static int _MAX_CANDY_AMOUNT = 3;

    public:
        CandyStore();
        CandyStore(int, string);
        
        int getCandyAmount() const;
        void displayCandies();
        bool removeCandy(string);
        bool fillCandy(vector<Candy>);
        int getCandyStorePosition() const;
        void setCandyStorePosition(int);
        Candy findCandy(string);
};

#endif