#ifndef PLAYER_H
#define PLAYER_H
#include "board.h"
#include <string>
#include <vector>

class Player 
{
protected:
    Board& board; // easier to manage if we have a player that HAS a board instead of inherets
    vector<Ship*> ships;

public:
    Player(Board& pBoard);
    virtual ~Player();
    virtual bool placeShip(Ship* shipType, int x1, char y1, int x2, char y2); // initializer, calls board
    void addShip(Ship* shipType); //add ship to vector
    void printBoard(int player, bool reveal); //print player's board, calls board
    virtual bool attack(int player, int x, char y); //attack, calls board
    bool checkWin(); //true if win, false if not, calls ships
};


class AI : public Player // inheritance 
{
private:
    bool alrdyAttacked[100]; // tracks the cells which have alrdy been attacked
    
public:
    AI(Board& pBoard);
    ~AI();
    bool placeShip(Ship* shipType, int x1, char y1, int x2, char y2); // initializer, calls board
    void placeShipRandom(Ship* shipType); // random placement
    bool attack(int player);   // random attack
};


#endif
