#include "ship.h"

using namespace std;

Ship::Ship(int size, int player) {
    size_ = size; // sets size of ship
    player_ = player; // who owns what ship
    hitCount_ = 0; // intialize to 0
    sunk = false;
}

// Counts number of hits ship takes if it has not already taken all possible hits
void Ship::takeHit() {
    if(hitCount_ < size_) {
        hitCount_++;
    }
}

// Returns true if the ship has been hit as many times as its size
bool Ship::isSunk() {
    if (hitCount_ >= size_) {
        sunk = true;
    }
    return sunk;
}

// Returns total size of ship
int Ship::getSize() const {
    return size_;
}

std::string Ship::getShipType(){
    return "Ship";
}

//Ship Types

Small::Small(int player) : Ship(2, player) {}

// returns type of ship as a string for player
string Small::getShipType() {
    return "Small";
}

Med::Med(int player) : Ship(3, player) {}

// returns type of ship as a string for player
string Med::getShipType() {
    return "Medium";
}

Large::Large(int player) : Ship(4, player) {}

// returns type of ship as a string for player
string Large::getShipType()  {
    return "Large";
}
