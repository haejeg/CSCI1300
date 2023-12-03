#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;

struct Candy {
    string name;
    string description;
    double price;
    string candy_type;
};

class Player {
    private:
        static const int _MAX_CANDY_AMOUNT = 4;
        int _stamina;
        double _gold;
        string _effect;
        Candy _inventory[_MAX_CANDY_AMOUNT];
        int _candy_amount;

    public:
        Player();
        Player(int stam, double gold, string effect, Candy[], const int ARR_SIZE);
        int getCandyAmount();
        void setStamina(int stam);
        int getStamina();
        void setGold(double gold);
        double getGold();
        void setEffect(string effect);
        string getEffect();
        void printInventory();
        Candy findCandy(string name);
        bool addCandy(Candy candy);
        bool removeCandy(string name);
};

string toLowerCase(string str) {
    int len = str.length();
    for (int i = 0; i < len; i++) {
        str[i] = tolower(str[i]);
    }
    return str;
}

void clearInput() {
    cin.clear();
    cin.ignore(10000, '\n');
}

Player::Player() {
    _stamina = 0;
    _gold = 0;
    _candy_amount = 0;
    _effect = "";
}

Player::Player(int stam, double gold, string effect, Candy candy[], const int ARR_SIZE) {
    _stamina = stam;
    _gold = gold;
    _candy_amount = 0;
    _effect = effect;
    for (int i = 0; i < ARR_SIZE; i++) {
        if (candy[i].name != "") {
            _inventory[_candy_amount] = candy[i];
            _candy_amount++;
        }
    }
}

void Player::setStamina(int stam) {
    _stamina = stam;
}

int Player::getStamina() {
    return _stamina;
}

void Player::setGold(double gold) {
    _gold = gold;
}

double Player::getGold() {
    return _gold;
}

void Player::setEffect(string effect) {
    _effect = effect;
}

string Player::getEffect() {
    return _effect;
}

int Player::getCandyAmount() {
    return _candy_amount;
}

void Player::printInventory() {
    Candy printArr[_MAX_CANDY_AMOUNT] = {""};
    int j = 0;
    for (int i = 0; i < _MAX_CANDY_AMOUNT; i++) {
        if (_inventory[i].name != "") {
            printArr[j] = _inventory[i];
            j++;
        }
    }

    for (int i = 0; i < _MAX_CANDY_AMOUNT; i++) {
        _inventory[i] = printArr[i];
    }

    cout<<"|";
    for (int i = 0; i < _MAX_CANDY_AMOUNT / 2; i++) {
        if (_inventory[i].name == "") {
            cout<<"[Empty]|";
        } else {
            cout<<"["<<_inventory[i].name<<"]|";
        }
    }
    cout<<endl;
    cout<<"|";
    for (int i = (_MAX_CANDY_AMOUNT / 2); i < _MAX_CANDY_AMOUNT; i++) {
        if (_inventory[i].name == "") {
            cout<<"[Empty]|";
        } else {
            cout<<"["<<_inventory[i].name<<"]|";
        }
    }
    cout<<endl;
}

Candy Player::findCandy(string name) {
    for (int i = 0; i < _MAX_CANDY_AMOUNT; i++) {
        if (toLowerCase(_inventory[i].name) == toLowerCase(name)) {
            return _inventory[i];
        }
    }
    return Candy {"", "", 0, ""};
}

bool Player::addCandy(Candy candy) {
    for (int i = 0; i < _MAX_CANDY_AMOUNT; i++) {
        if (_inventory[i].name == "") {
            _inventory[i].name = candy.name;
            _inventory[i].description = candy.description;
            _inventory[i].price = candy.price;
            _inventory[i].candy_type = candy.candy_type;
            _candy_amount++;
            return true;
        }
    }
    return false;
}

bool Player::removeCandy(string name) {
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

void playRockPaperScissors(Player players[2]) {
    string candy1, candy2;
    int winner;
    char p1, p2;
    bool tie = false;
    
    if (players[0].getCandyAmount() == 0 || players[1].getCandyAmount() == 0) {
        cout<<"Not enough candy!"<<endl;
        return;
    }

    cout<<"Player 1 Inventory"<<endl;
    players[0].printInventory();
    cout<<"Player 1: Select candy to bet"<<endl;
    cin.ignore();
    getline(cin, candy1);
    while ((players[0].findCandy(candy1)).name == "") {
        cout<<"Invalid selection!"<<endl;
        getline(cin, candy1);
    }

    cout<<"Player 2 Inventory"<<endl;
    players[1].printInventory();
    cout<<"Player 2: Select candy to bet"<<endl;
    getline(cin, candy2);
    while ((players[1].findCandy(candy2)).name == "") {
        cout<<"Invalid selection!"<<endl;
        getline(cin, candy2);
    }

    do {
        cout<<"Player 1: Enter r, p, or s"<<endl;
        cin>>p1;
        while (p1 != 'r' && p1 != 'p' && p1 != 's') {
            cout<<"Invalid selection!"<<endl;
            cin>>p1;
        }
        cout<<"Player 2: Enter r, p, or s"<<endl;
        cin>>p2;
        while (p2 != 'r' && p2 != 'p' && p2 != 's') {
            cout<<"Invalid selection!"<<endl;
            cin>>p2;
        }
        if (p1 == p2) {
            cout<<"Tie! Play again"<<endl;
            tie = true;
        } else {
            tie = false;
        }
    } 
    while(tie);

    if (p1 == 'r') {
        if (p2 == 'p') {
            winner = 2;
        } else {
            winner = 1;
        }
    } else if (p1 == 'p') {
        if (p2 == 'r') {
            winner = 1;
        } else {
            winner = 2;
        }
    } else if (p1 == 's') {
        if (p2 == 'r') {
            winner = 2;
        } else {
            winner = 1;
        }
    }

    if (winner == 1) {
        cout<<"Player "<<winner<<" has won "<<candy2<<" from player 2!"<<endl;
        players[0].addCandy(players[1].findCandy(candy2));
        players[1].removeCandy(candy2);
    } else {
        cout<<"Player "<<winner<<" has won "<<candy1<<" from player 1!"<<endl;
        players[1].addCandy(players[0].findCandy(candy1));
        players[0].removeCandy(candy1);
    }
}

vector<Candy> readCandy(string file_name, vector<Candy> candies) {
    ifstream fin(file_name);

    if (fin.fail()) {
        cout<<"Failed to open file"<<endl;
        return candies;
    }

    string line;
    while (getline(fin, line)) {
        if (!line.empty()) {
            stringstream ss;
            ss << line;
            Candy candy;
            string sep;
            getline(ss, sep, '|');
            candy.name = sep;
            getline(ss, sep, '|');
            candy.description = sep;
            getline(ss, sep, '|');
            candy.price = stod(sep);
            getline(ss, sep);
            candy.candy_type = sep;
            candies.push_back(candy);
        }
    }
    return candies;
}

// cout<<"Welcome to rock-paper-scissors, candy edition!"<<endl;
// cout<<"Choose an option:"<<endl;
// cout<<"1. Load Candy"<<endl;
// cout<<"2. Display player stats"<<endl;
// cout<<"3. Edit player stats"<<endl;
// cout<<"4. Play rock-paper-scissors"<<endl;
// cout<<"5. Exit"<<endl;
// cout<<"Player "<<player<<" stats:"<<endl;
// cout<<"Stamina: "<<players[player].getStamina()<<" ";
// cout<<"Gold: "<<players[player].getGold()<<" ";
// cout<<"Effect: "<<players[player].getEffect()<<" ";
// cout<<"Inventory: "<<endl;
// cout<<"Which player's stats do you want to edit? Choose 1 or 2:"<<endl;
// cout<<"Editing player [1 or 2] stats:\n1. Edit stamina\n2. Edit gold\n3. Edit effect\n4. Add candy\n5. Remove candy"<<endl;

int main() {
    Player players[2];
    int option;
    vector<Candy> candies;
    bool wrongInput = false;
    cout<<setprecision(2)<<fixed;
    cout<<"Welcome to rock-paper-scissors, candy edition!"<<endl;
    do {
        if (!wrongInput) {
            cout<<"Choose an option:"<<endl;
            cout<<"1. Load Candy"<<endl;
            cout<<"2. Display player stats"<<endl;
            cout<<"3. Edit player stats"<<endl;
            cout<<"4. Play rock-paper-scissors"<<endl;
            cout<<"5. Exit"<<endl;
            cin>>option;
        }
        
        switch(option) {
            case 1: {
                cout<<"Enter file to read:"<<endl; 
                string file_name;
                cin>>file_name;
                candies = readCandy(file_name, candies);
                break;
            }
            case 2: {
                int player;
                cout<<"Which player's stats do you want to display? Choose 1 or 2:"<<endl;
                cin>>player;
                cin.ignore();
                while (player != 1 && player != 2) {
                    clearInput();
                    cout<<"Invalid selection!"<<endl;
                    cin.ignore();
                    cin>>player;
                }
                cout<<"Player "<<player<<" stats:"<<endl;
                cout<<"Stamina: "<<players[player - 1].getStamina()<<endl;
                cout<<"Gold: "<<players[player - 1].getGold()<<endl;
                cout<<"Effect: "<<players[player - 1].getEffect()<<endl;
                cout<<"Inventory: "<<endl;
                players[player - 1].printInventory();
                break;
            }
            case 3: {
                int player;
                cout<<"Which player's stats do you want to edit? Choose 1 or 2:"<<endl;
                cin.ignore();
                cin>>player;
                while (player != 1 && player != 2) {
                    cout<<"Invalid selection!"<<endl;
                    clearInput();
                    cin>>player;
                }
                int edit;
                cout<<"Editing player "<<player<<" stats:\n1. Edit stamina\n2. Edit gold\n3. Edit effect\n4. Add candy\n5. Remove candy"<<endl;
                cin.ignore();
                cin>>edit;
                while (edit != 1 && edit != 2 && edit != 3 && edit != 4 && edit != 5) {
                    cout<<"Invalid selection!"<<endl;
                    clearInput();
                    cin>>edit;
                }
                int playerIdx = player - 1;
                switch (edit) {
                    case 1: {
                        int stamina;
                        cout<<"Editing stamina. Enter a value between 1 and 10:"<<endl;
                        cin.ignore();
                        cin>>stamina;
                        while (!(stamina >= 1 && stamina <= 10) || cin.fail()) {
                            cout<<"Invalid input!"<<endl;
                            clearInput();
                            cin>>stamina;
                        }
                        players[playerIdx].setStamina(stamina);
                        break;
                    }
                    case 2: {
                        double gold;
                        cout<<"Editing gold. Enter a value between 0 and 1000:"<<endl;
                        cin.ignore();
                        cin>>gold;
                        while (!(gold >= 0 && gold <= 1000) || cin.fail()) {
                            clearInput();
                            cout<<"Invalid input!"<<endl;
                            cin>>gold;
                        }
                        players[playerIdx].setGold(gold);
                        break;
                    }
                    case 3: {
                        string effect;
                        cout<<"Editing effect. Enter the name of an effect as a string:"<<endl;
                        cin.ignore();
                        getline(cin, effect);
                        players[playerIdx].setEffect(effect);
                        break;
                    }
                    case 4: {
                        string candy;
                        int len = candies.size();
                        if (len == 0) {
                            cout<<"Cannot add candy! Read a candy file first"<<endl;
                            break;
                        }
                        cout<<"Adding candy. Enter one of the following options:"<<endl;
                        for (int i = 0; i < len; i++) {
                            cout<<"Name: "<<candies.at(i).name<<". Description: "<<candies.at(i).description<<". Price: "<<candies.at(i).price<<". Type: "<<candies.at(i).candy_type<<endl;
                        }
                        cin.ignore();
                        getline(cin, candy);
                        while (toLowerCase(candy) != toLowerCase(candies.at(0).name) && toLowerCase(candy) != toLowerCase(candies.at(1).name) && toLowerCase(candy) != toLowerCase(candies.at(2).name) && toLowerCase(candy) != toLowerCase(candies.at(3).name)) {
                            cout<<"Invalid input!"<<endl;
                            getline(cin, candy);
                        }
                        
                        for (int i = 0; i < len; i++) {
                            if (toLowerCase(candy) == toLowerCase(candies.at(i).name)) {
                                players[playerIdx].addCandy(candies.at(i));
                            }
                        }
                        break;
                    }
                    case 5: {
                        string candy;
                        cout<<"Removing candy. Enter the name of a candy in player "<<player<<"'s inventory:"<<endl;
                        players[playerIdx].printInventory();
                        cin.ignore();
                        getline(cin, candy);
                        while (!players[playerIdx].removeCandy(candy)) {
                            cout<<"Invalid selection!"<<endl;
                            cin.ignore();
                            getline(cin, candy);
                        }
                        
                        break;
                    }
                }
                break;
            }
            case 4: {
                playRockPaperScissors(players);
                break;
            }
            case 5: {
                break;
            }
            default: {
                clearInput();
                cout<<"Invalid selection!"<<endl;
                cin>>option;
                wrongInput = true;
                break;
            }
        }
    }
    while(option != 5);
    return 0;
}