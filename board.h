#ifndef BOARD_H
#define BOARD_H
#include <vector>
#include "ship.h"

using namespace std; 

struct Cell {
    Ship* ship; // pointer to ship occupying cell
    bool hit; // has cell been fired upon?

    Cell() : ship(nullptr), hit(false) {} // default constructor
};

class Board {
private:
    vector<Cell> playerBoard;    

public:
    Board();
    bool placeShip(Ship* shipType, int x1, char y1, int x2, char y2);
    bool attack(int player, int x, char y); // executes attack, returns true if a ship was attacked
    void printPlayerBoard(int player, bool revealShips) const; // displays ship for player, hides ships if reveal ships is false
};

#endif
