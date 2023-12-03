#ifndef CANDY_H
#define CANDY_H
#include <iostream>

using namespace std;

class Candy {
    private:
        string _name;
        string _description;
        double _price;
        string _candy_type;
        int _effect;
        
    public:
        Candy();
        Candy(string, string, double, string, int);

        string getName() const;
        string getDescription() const;
        double getPrice() const;
        string getCandyType() const;
        int getEffect() const;

        void setName(string);
        void setDescription(string);
        void setPrice(double);
        void setCandyType(string);
        void setEffect(int);    
};

#endif