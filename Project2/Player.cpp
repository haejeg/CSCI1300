#include "Player.h"

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
    _gold = gold;
}

void Player::setStamina(int stamina)
{
    _stamina = stamina;
}

void Player::setCandies(vector<Candy> candies)
{
    _candies = candies;
}