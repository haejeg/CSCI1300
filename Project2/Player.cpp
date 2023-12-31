#include "Player.h"
#include "Board.h"
#include "Candy.h"
#include "Utilities.h"

Player::Player()
{
    _name = "";
    _character = "";
    _position = 0;
    _gold = 0;
    _stamina = 0;
    _candies = {};
}

// even though the constructor doesn't have all parameters, it doesn't really matter because shield should be disabled by default anyways
Player::Player(string name, string character, int position, int gold, int stamina, vector<Candy> candies)
{
    _name = name;
    _character = character;
    _position = position;
    _gold = gold;
    _stamina = stamina;
    _candies = candies;
    _shield = false;
}

// getters and setters
string Player::getName() const
{
    return _name;
}

string Player::getCharacter() const
{
    return _character;
}

int Player::getPosition() const
{
    return _position;
}

int Player::getGold() const
{
    return _gold;
}

int Player::getStamina() const
{
    return _stamina;
}

vector<Candy> Player::getCandies() const
{
    return _candies;
}

void Player::setName(string name)
{
    _name = name;
}

void Player::setCharacter(string character)
{
    _character = character;
}

void Player::setPosition(int position)
{
    _position = position;
}

void Player::setGold(int gold)
{
    if (gold >= 100) {
        _gold = 100;
        return;
    }
    else if (gold <= 0) {
        _gold = 0;
        return;
    }
    _gold = gold;
}

void Player::setStamina(int stamina)
{
    if (stamina >= 100) {
        _stamina = 100;
        return;
    }
    else if (stamina <= 0) {
        _stamina = 0;
        return;
    }
    _stamina = stamina;
}

void Player::setCandies(vector<Candy> candies)
{
    _candies = candies;
}

int Player::getCandyAmount() const {
    return _candies.size();
}

bool Player::getShield() const {
    return _shield;
}

void Player::setShield(bool shield) {
    _shield = shield;
}

// findCandy will find the candy in the pre-existing candies vector and will return an object when you search by name
// if not found, it will return nothing (the game should prevent something like this happening anyways..)
Candy Player::findCandy(string name, vector<Candy> candies) {
    int len = candies.size();
    for (int i = 0; i < len; i++) {
        if (toLowerCase(name) == toLowerCase(candies.at(i).name)) {
            return candies.at(i);
        }
    }
    return Candy{};
}

void Player::printInventory() {
    // print inventory in whatever grid the user wants
    int _MAX_CANDY_AMOUNT = _candies.size();
    if (getCandyAmount() == 0) { // check for candies
        cout<<"No candies in inventory."<<endl;
        return;
    }
    if (getCandyAmount() == 1) { // if it's only one just print one element and return (this is because of how the | | are printed in the board)
        cout<<"|["<<_candies[0].name<<"]|"<<endl;
        return;
    }

    vector<Candy> printArr(_MAX_CANDY_AMOUNT); // create a new array to print
    int j = 0;
    for (int i = 0; i < _MAX_CANDY_AMOUNT; i++) { // remove empty candies
        if (_candies[i].name != "") {
            printArr[j] = _candies[i];
            j++;
        }
    }

    for (int i = 0; i < _MAX_CANDY_AMOUNT; i++) {
        _candies[i] = printArr[i];
    }
    
    cout<<"|";
    // divide by 2 because we want to print half the max candies on one line and the other half on the next line
    for (int i = 0; i < _MAX_CANDY_AMOUNT / 2; i++) {
        if (_candies[i].name == "") {
            cout<<"[Empty]|";
        } else {
            cout<<"["<<_candies[i].name<<"]|";
        }
    }
    cout<<endl;
    cout<<"|";
    for (int i = (_MAX_CANDY_AMOUNT / 2); i < _MAX_CANDY_AMOUNT; i++) {
        if (_candies[i].name == "") {
            cout<<"[Empty]|";
        } else {
            cout<<"["<<_candies[i].name<<"]|";
        }
    }
    cout<<endl;
}

void Player::addCandy(Candy candy) {
    _candies.push_back(candy);
}

bool Player::removeCandy(string name) {
    int len = _candies.size();
    for (int i = 0; i < len; i++) {
        if (toLowerCase(_candies[i].name) == toLowerCase(name)) {
            _candies.erase(_candies.begin() + i);
            return true;
        }
    }
    return false;
}

// i should add a addCandies() and removeCandies() instead of setCandies() but this works for now