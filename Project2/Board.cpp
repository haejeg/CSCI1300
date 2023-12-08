#include "Board.h"

Board::Board()
{
    resetBoard();
}

Board::Board(int playercount, vector<Player> selections) {
    resetBoard();
    _player_position = selections;
    _previous_position = selections;
}

void Board::addTreasureTile(specialTile specialTile) {
    _treasure_tiles.push_back(specialTile);
}

bool Board::isTreasureTile(int index) {
    int len = _treasure_tiles.size();
    for (int i = 0; i < len; i++) {
        if (index == _treasure_tiles.at(i).index) {
            return true;
        }
    }
    return false;
}

bool Board::isSpecialTile(int index) {
    int len = _special_tiles.size();
    for (int i = 0; i < len; i++) {
        if (index == _special_tiles.at(i).index) {
            return true;
        }
    }
    return false;
}

void Board::resetBoard()
{
    const int COLOR_COUNT = 3;
    const string COLORS[COLOR_COUNT] = {MAGENTA, GREEN, BLUE};
    Tile new_tile;
    string current_color;
    for (int i = 0; i < _BOARD_SIZE - 1; i++)
    {
        current_color = COLORS[i % COLOR_COUNT];
        new_tile = {current_color, "regular tile"};
        _tiles[i] = new_tile;
    }
    new_tile = {ORANGE, "regular tile"};
    _tiles[0] = new_tile;
    _tiles[_BOARD_SIZE - 1] = new_tile;

    _candy_store_count = 0;
    for (int i = 0; i < _MAX_CANDY_STORE; i++)
    {
        _candy_store_position[i] = -1;
    }

    int len = _player_position.size();
    for (int i = 0; i < len; i++)
    {
        _player_position.at(i).setPosition(0);
    }
}

void Board::displayTile(int position)
{
    // is there a player on this position? - initial false
    bool playerActive = false;
    if (position < 0 || position >= _BOARD_SIZE)
    {
        return;
    }
    Tile target = _tiles[position];
    cout << target.color;
    int len = _player_position.size();
    for (int i = 0; i < len; i++)
    {
        if (position == _player_position.at(i).getPosition())
        {
            // if there is a player then print player by their player id
            cout << " " << i + 1 ; // i + 1 because it's weird having player 0 and doesn't make much sense
            playerActive = true;
        }
    }
    // if player is not active print two more spaces (this is for spacing reasons)
    if (!playerActive) {
        cout << "  ";
    }
    cout << " " << RESET;
}

void Board::displayBoard()
{
    //if players are stacked on top of each other, then we need to readjust the board
    //Initial readjustment - the case where every piece is in the first square
    int readjustment = (_player_position.size() - 1) * 2;
    //Calculate readjustment
    int len = _player_position.size(); 
    vector<int> overlappingIdxs; //Indexes that will overlap so ignore when iterating
    bool overlap = false; //Set initial overlap to false
    int count = 1; // Initial count needs to be 1 in case there are no overlaps
    for (int i = 0; i < len - 1; i++) { //len - 1 to be cautious of idx out of bounds
        if (overlappingIdxs.size() != 0) { //if overlapping size is 0 no need to worry about it
            int laplen = overlappingIdxs.size();
            for (int j = 0; j < laplen; j++) {
                if (j == i) {
                    overlap = true;
                }
            }
        }
        if (!overlap) {
            for (int j = i + 1; j < len; j++) {
                if (_player_position.at(i).getPosition() == _player_position.at(j).getPosition()) {
                    count++;
                    overlappingIdxs.push_back(i);
                }
            }
            overlap = false;
        }
    }
    if (count > 1) {
        readjustment = (count - 1) * 2 + (_player_position.size() - count) * 2 + 5;
    } else {
        readjustment = 5;
    }

    cout << ORANGE << "Start" << RESET;

    // First horizontal segment
    for (int i = 0; i <= 23; i++)
    {
        displayTile(i);
    }
    cout << endl;
    
    // First vertical segment
    for (int i = 24; i <= 28; i++)
    {
        //readjust for player overlap in square for first vertical segment
        for (int j = 0; j < 69 + readjustment; j++)
        {
            cout << " ";
        }
        displayTile(i);
        cout << endl;
    }
    // Second horizontal segment
    //readjust for player overlap in square for second horizontal segment (only once instead of iterated)
    for (int i = 0 ; i < readjustment; i++) {
        cout << " ";
    }
    for (int i = 52; i > 28; i--)
    {
        displayTile(i);
    }
    cout << endl;
    // Second vertical segment
    for (int i = 53; i <= 57; i++)
    {   
        //readjust for player overlap in square for second vertical segment (iterated)
        for (int j = 0; j < readjustment; j++) {
            cout << " ";
        }
        displayTile(i);
        for (int j = 0; j < 23; j++)
        {
            cout << "   ";
        }
        cout << endl;
    }
    // Third horizontal segment
    //readjust for player overlap in square for third horizontal segment
    for (int j = 0; j < readjustment; j++) {
            cout << " ";
    }
    for (int i = 58; i < _BOARD_SIZE; i++)
    {    
        displayTile(i);
    }
    cout << ORANGE << "Castle" << RESET << endl;
}

int Board::getPreviousPlayerPosition(int playerid) const
{
    return _previous_position.at(playerid).getPosition();
}

// setplayerposition should log where the player was beforehand
bool Board::setPlayerPosition(int new_position, int playerid)
{
    if (new_position >= 0 && new_position < _BOARD_SIZE)
    {
        _previous_position.at(playerid).setPosition(_player_position.at(playerid).getPosition());
        _player_position.at(playerid).setPosition(new_position);
        return true;
    }
    return false;
}

vector<specialTile> Board::getSpecialTiles() const {
    return _special_tiles;
}

vector<specialTile> Board::getTreasureTiles() const {
    return _treasure_tiles;
}

string Board::getPlayerName(int playerid) const
{
    return _player_position.at(playerid).getName();
}

int Board::getBoardSize() const
{
    return _BOARD_SIZE;
}

int Board::getCandyStoreCount() const
{
    return _candy_store_count;
}
 
int Board::getPlayerPosition(int playerid) const
{
    return _player_position.at(playerid).getPosition();
}

vector<Player> Board::getPlayers() const
{
    return _player_position;
}

specialTile Board::getSpecialTile(int index) {
    int len = _special_tiles.size();
    for (int i = 0; i < len; i++) {
        if (index == _special_tiles.at(i).index) {
            return _special_tiles.at(i);
        }
    }
    specialTile empty;
    empty.index = -1;
    return empty;
}

int Board::getCandyStorePosition(int index) const
{
    return _candy_store_position[index];
}

// addcandystore to board
bool Board::addCandyStore(int position)
{
    if (_candy_store_count >= _MAX_CANDY_STORE)
    {
        return false;
    }
    _candy_store_position[_candy_store_count] = position;
    _candy_store_count++;
    return true;
}

// returns whether or not tile is a candystore
bool Board::isPositionCandyStore(int board_position)
{
    for (int i = 0; i < _candy_store_count; i++)
    {
        if(_candy_store_position[i] == board_position)
        {
            return true;
        }
    }
    return false;
}

// movePlayer should have a feature in which it logs the player's last move so it is able to undo it when landing on gingerbread tile
bool Board::movePlayer(int tile_to_move_forward, int playerid)
{
    int new_player_position = tile_to_move_forward + _player_position.at(playerid).getPosition();
    if(new_player_position < 0 || new_player_position >= _BOARD_SIZE)
    {
        return false;
    }
    _player_position.at(playerid).setPosition(new_player_position);
    return true;
}

void Board::setPlayerStamina(int playerid, int stamina) {
    _player_position.at(playerid).setStamina(stamina);
}

void Board::setPlayerGold(int playerid, int gold) {
    _player_position.at(playerid).setGold(gold);
}

void Board::setPlayerShield(int playerid, bool shield) {
    _player_position.at(playerid).setShield(shield);
}

void Board::setPlayerCandies(int playerid, vector<Candy> candies) {
    _player_position.at(playerid).setCandies(candies);
}

// Generate hidden treasures (no class needed because there's nothing to specifically store besides the tile numbers)
void Board::generateTreasureTiles() { // pass this by reference so that i dont have to return anything (hassle)
    srand((int) time(0));
    // iterate it 3 times since there should be 3 hidden treasures across the map
    for (int i = 0; i < 3; i++) {
        if (i == 0 || isPositionCandyStore(i) || isSpecialTile(i)) {
            // make sure it's not on the starting tile, special tile, or candy store
            int randNum = rand() % 82 + 1;
            specialTile tempTile;
            tempTile.index = randNum;
            tempTile.tile_type = "Treasure";
            addTreasureTile(tempTile);
        }
        int randNum = rand() % 83 + 1;
        specialTile tempTile;
        tempTile.index = randNum;
        tempTile.tile_type = "Treasure";
        addTreasureTile(tempTile);
    }
}

void Board::addSpecialTile(specialTile specialTile) {
    _special_tiles.push_back(specialTile);
}

// Create a special tiles (no class needed because there's nothing to specifically store besides the tile numbers)
void Board::generateSpecialTiles(int percentage) {
    srand((int) time(0));
    int count = 0;
    // for all 83 tiles
    for (int i = 1; i < 82; i++) {
        // if random is within percentage
        if (rand() % 100 <= percentage) {
            specialTile tempTile;
            tempTile.index = i;
            // generate random tile type
            int randTile = rand() % 4 + 1;
            switch(randTile) { // because 4 random tiles
                case 1:
                    tempTile.tile_type = "shortcut";
                    break;
                case 2:
                    tempTile.tile_type = "icecream";
                    break;
                case 3:
                    tempTile.tile_type = "gumdrop";
                    break;
                case 4:
                    tempTile.tile_type = "gingerbread";
                    break;
                //no default needed because it's impossible
            }
            // add to special tiles in board object
            addSpecialTile(tempTile);
            count++;
        }
        if (count > 5) {
            return;
        }
    }
}

void Board::addCandyToPlayer(int playerid, Candy candy) {
    _player_position.at(playerid).addCandy(candy);
}

bool Board::removeCandyFromPlayer(int playerid, string name) {
    return _player_position.at(playerid).removeCandy(name);
}

Candy Board::findCandyFromPlayer(int playerid, string name) {
    return _player_position.at(playerid).findCandy(name, _player_position.at(playerid).getCandies());
}

int Board::getPlayerCandyAmount(int playerid) const {
    return _player_position.at(playerid).getCandyAmount();
}

int Board::getPlayerStamina(int playerid) const {
    return _player_position.at(playerid).getStamina();
}

int Board::getPlayerGold(int playerid) const {
    return _player_position.at(playerid).getGold();
}

bool Board::getPlayerShield(int playerid) const {
    return _player_position.at(playerid).getShield();
}

vector<Candy> Board::getPlayerCandies(int playerid) const {
    return _player_position.at(playerid).getCandies();
}

void Board::printPlayerInventory(int playerid) {
    _player_position.at(playerid).printInventory();
}

string Board::getPlayerCharacter(int playerid) const {
    return _player_position.at(playerid).getCharacter();
}