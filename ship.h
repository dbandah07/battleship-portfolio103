// add #'s
#ifndef SHIP_H
#define SHIP_H

#include <string>


class Ship {
protected: // so the children can use them
    int size_; // num of tiles ship occupies
    int hitCount_; // num of hit the ship has taken
    int player_; // player1 = 0; player2 = 1;
    bool sunk;

public: 
    Ship(int size, int player); // constructor
    virtual ~Ship() {}; // virtual destructor for polymorphic cleanup
    virtual void takeHit(); // inc. hit count when ship is hit
    virtual bool isSunk(); // returns true if ship is sunk
    int getSize() const; // returns size of ship
    virtual std::string getShipType();
};

class Small : public Ship {
    public: 
    Small(int player); // size 2
    virtual std::string getShipType();
};

class Med : public Ship {
    public:
    Med(int player); // size 3
    virtual std::string getShipType();

};

class Large : public Ship {
    public:
    Large(int player); // size 4
    virtual std::string getShipType();

};

#endif
