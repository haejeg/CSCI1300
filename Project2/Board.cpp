#include "Board.h"

Board::Board()
{
    resetBoard();
}

Board::Board(int playercount, vector<Player> selections) {
    resetBoard();
    _player_position = selections;
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
    //Initial readjustment - the case where every piece is in the first square
    int readjustment = (_player_position.size() - 1) * 2;
    //Calculate readjustment
    int len = _player_position.size(); 
    vector<int> overlappingIdxs; //Indexes that will overlap so ignore when iterating
    bool overlap = false; //Set initial overlap to false
    int count = 1; // Initial count needs to be 1 in case there are no overlaps
    for (int i = 0; i < len - 2; i++) { //len - 1 to be cautious of idx out of bounds
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
                cout<< i << j << endl;
                if (_player_position.at(i).getPosition() == _player_position.at(j).getPosition()) {
                    count++;
                    overlappingIdxs.push_back(i);
                }
            }
            overlap = false;
        }
    }
    cout << count << " " << _player_position.size() << endl;
    readjustment = (count - 1) * 2 + (_player_position.size() - count) * 2 + 5;

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

bool Board::setPlayerPosition(int new_position, int playerid)
{
    if (new_position >= 0 && new_position < _BOARD_SIZE)
    {
        _player_position.at(playerid).setPosition(new_position);
        return true;
    }
    return false;
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