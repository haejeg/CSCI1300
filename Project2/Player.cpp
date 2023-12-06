#include "Player.h"
#include "Board.h"
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
    if (_gold >= 100) {
        _gold = 100;
        return;
    }
    _gold = gold;
}

void Player::setStamina(int stamina)
{
    if (_stamina >= 100) {
        _stamina = 100;
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

// findCandy will find the candy in the pre-existing candies vector and will return an object when you search by name
// if not found, it will return nothing (the game should prevent something like this happening anyways..)
Candy Player::findCandy(string name, vector<Candy> candies) {
    int len = candies.size();
    for (int i = 0; i < len; i++) {
        if (toLowerCase(name) == toLowerCase(candies.at(i).getName())) {
            return candies.at(i);
        }
    }
    return Candy{};
}

bool Player::getShield() const {
    return _shield;
}

void Player::setShield(bool shield) {
    _shield = shield;
}

void Player::printInventory() {
    int _MAX_CANDY_AMOUNT = _candies.size();
    Candy printArr[_MAX_CANDY_AMOUNT] = {};
    int j = 0;
    for (int i = 0; i < _MAX_CANDY_AMOUNT; i++) {
        if (_candies[i].getName() != "") {
            printArr[j] = _candies[i];
            j++;
        }
    }

    for (int i = 0; i < _MAX_CANDY_AMOUNT; i++) {
        _candies[i] = printArr[i];
    }

    cout<<"|";
    for (int i = 0; i < _MAX_CANDY_AMOUNT / 2; i++) {
        if (_candies[i].getName() == "") {
            cout<<"[Empty]|";
        } else {
            cout<<"["<<_candies[i].getName()<<"]|";
        }
    }
    cout<<endl;
    cout<<"|";
    for (int i = (_MAX_CANDY_AMOUNT / 2); i < _MAX_CANDY_AMOUNT; i++) {
        if (_candies[i].getName() == "") {
            cout<<"[Empty]|";
        } else {
            cout<<"["<<_candies[i].getName()<<"]|";
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
        if (toLowerCase(_candies[i].getName()) == toLowerCase(name)) {
            _candies.erase(_candies.begin() + i);
            return true;
        }
    }
    return false;
}

// i should add a addCandies() and removeCandies() instead of setCandies() but this works for now