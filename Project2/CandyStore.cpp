#include "CandyStore.h"
#include "Utilities.h"
#include "Board.h"

// Constructors
CandyStore::CandyStore()
{
    _candy_amount = 0;
    _candy_store_position = -1;
    _candy_store_name = "";
}

CandyStore::CandyStore(int position, string name)
{
    _candy_amount = 0;
    _candy_store_position = position;
    _candy_store_name = name;
}

// Accessors
int CandyStore::getCandyStorePosition() const
{
    return _candy_store_position;
}

int CandyStore::getCandyAmount() const
{
    return _candy_amount;
}

// display all candies in store
void CandyStore::displayCandies() {
    // if no candies are in store return
    if (_candy_amount == 0) {
        cout<<"No candies in store."<<endl;
        return;
    }

    // if there are candies iterate through all candies and print
    cout<<"Candies present in store "<<_candy_store_name<<" are "<<endl;
    for (int i = 0; i < _candy_amount; i++) {
        cout<<_inventory.at(i).getName()<<endl;
    }
}

// Mutators
void CandyStore::setCandyStorePosition(int position)
{
    _candy_store_position = position;
}

// remove candy from store when bought by user
bool CandyStore::removeCandy(string name) {
    int lastIdx = 0;
    bool res = false;
    for (int i = 0; i < _MAX_CANDY_AMOUNT; i++) {
        if (toLowerCase(_inventory[i].getName()) == toLowerCase(name)) {
            lastIdx = i;
            res = true;
        }
    }

    if (res) {
        _candy_amount--;
        _inventory[lastIdx].setName("");
        _inventory[lastIdx].setDescription("");
        _inventory[lastIdx].setPrice(0);
        _inventory[lastIdx].setCandyType("");
    }

    return res;
}

// fill candystore with random candies (limited to 9 per store by default)
bool CandyStore::fillCandy(vector<Candy> candies) {
    srand((int) time(0));
    int candy_count = 3;
    for (int i = 0; i < candy_count; i++) {
        //Pick random number of candies going into the store
        int randIdx = rand() % candies.size();
        _inventory.push_back(candies.at(randIdx));
        _candy_amount++;
    }
    return true;
}
