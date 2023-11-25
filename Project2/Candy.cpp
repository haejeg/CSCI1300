#include "Candy.h"

Candy::Candy() {
    name = "";
    description = "";
    price = 0.0;
    candy_type = "";
    effect = 0;
}

Candy::Candy(string zname, string zdescription, double zprice, string zcandy_type, int zeffect) {
    zname = name;
    zdescription = description;
    zprice = price;
    zcandy_type = candy_type;
    zeffect = effect;
}

string Candy::getName() const {
    return name;
}

string Candy::getDescription() const {
    return description;
}

double Candy::getPrice() const {
    return price;
}

string Candy::getCandyType() const {
    return candy_type;
}

int Candy::getEffect() const {
    return effect;
}

void Candy::setName(string zname) {
    name = zname;
}

void Candy::setDescription(string zdescription) {
    description = zdescription;
}

void Candy::setPrice(double zprice) {
    price = zprice;
}

void Candy::setCandyType(string zcandy_type) {
    candy_type = zcandy_type;
}

void Candy::setEffect(int zeffect) {
    effect = zeffect;
}