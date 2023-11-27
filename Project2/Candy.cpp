#include "Candy.h"

Candy::Candy() {
    _name = "";
    _description = "";
    _price = 0.0;
    _candy_type = "";
    _effect = 0;
}

Candy::Candy(string name, string description, double price, string candy_type, int effect) {
    name = name;
    _description = description;
    _price = price;
    _candy_type = candy_type;
    _effect = effect;
}

string Candy::getName() const {
    return _name;
}

string Candy::getDescription() const {
    return _description;
}

double Candy::getPrice() const {
    return _price;
}

string Candy::getCandyType() const {
    return _candy_type;
}

int Candy::getEffect() const {
    return _effect;
}

void Candy::setName(string name) {
    _name = name;
}

void Candy::setDescription(string description) {
    _description = description;
}

void Candy::setPrice(double price) {
    _price = price;
}

void Candy::setCandyType(string candy_type) {
    _candy_type = candy_type;
}

void Candy::setEffect(int effect) {
    _effect = effect;
}