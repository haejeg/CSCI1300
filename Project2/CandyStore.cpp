#include "CandyStore.h"

string toLowerCase(string str) {
    int len = str.length();
    for (int i = 0; i < len; i++) {
        str[i] = tolower(str[i]);
    }
    return str;
}

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

void CandyStore::displayCandies() {
    cout<<_candy_amount<<endl;
    cout<<_inventory.size()<<endl;
    if (_candy_amount == 0) {
        cout<<"No candies in store."<<endl;
        return;
    }

    cout<<"Candies present in store "<<_candy_store_name<<" are "<<endl;
    for (int i = 0; i < _candy_amount; i++) {
        cout<<_inventory.at(i).name<<endl;
    }
}

// Mutators
void CandyStore::setCandyStorePosition(int position)
{
    _candy_store_position = position;
}

bool CandyStore::removeCandy(string name) {
    int lastIdx = 0;
    bool res = false;

    for (int i = 0; i < _MAX_CANDY_AMOUNT; i++) {
        if (toLowerCase(_inventory[i].name) == toLowerCase(name)) {
            lastIdx = i;
            res = true;
        }
    }

    if (res) {
        _candy_amount--;
        _inventory[lastIdx].name = "";
        _inventory[lastIdx].description = "";
        _inventory[lastIdx].price = 0;
        _inventory[lastIdx].candy_type = "";
    }

    return res;
}

bool CandyStore::fillCandy(vector<Candy> candies) {
    srand((int) time(0));
    int candy_count = 9;
    for (int i = 0; i < candy_count; i++) {
        //Pick random number of candies going into the store
        int randIdx = rand() % candies.size();
        _inventory.push_back(candies.at(randIdx));
        _candy_amount++;
    }
    cout<<"Candies added successfully"<<endl;
    return true;
}