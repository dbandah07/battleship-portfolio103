#include "board.h"
#include <iostream>

using namespace std;
// KEY:
    // X = ship was hit at this loc (ie. there is a ship here)
    // O = no ship was hit at this loc (ie. there is no ship at this loc)
    // S = ship (ie. ship revealed to b here)
    // . = cell that has not been hit
    // if rotated, VERTICAL

Board::Board() {
// initialize player boards to 100 cells (fixed 10x10 board);
    playerBoard.resize(100);
}

// // initializer
bool Board::placeShip(Ship* shipType, int x1, char y1Char, int x2, char y2Char){

    //get ship size
    int size = shipType->getSize();

    //conv y to int
    int y1 = y1Char - 'A';
    int y2 = y2Char - 'A';

    //debug, check variables
    cout << "x1 " << x1 << endl;
    cout << "y1 " << y1 << endl;
    cout << "x2 " << x2 << endl;
    cout << "y2 " << y2 << endl;

    //determine if coords are valid
    if (x1 < 0 || x1 > 9 || y1 < 0 || y1 > 9) { // out of bounds;
        cout << "Out of Bounds." << endl;
        return false;
    }
    if (x2 < 0 || x2 > 9 || y2 < 0 || y2 > 9) { // out of bounds;
        cout << "Out of Bounds." << endl;
        return false;
    }

    
    // determine if ship is rotated 
    bool horizontal = false;
    bool vertical = false; 
    if (x1 == x2) { // ship is horizontal. original rotation. not true.
        vertical = true;
    }
    else if (y1 == y2){
        horizontal = true;
    }
    else{
        cout << "Invalid rotation." << endl;
        return false; // out of bounds
    }

    //check length
    int len;
    if(vertical){
        len = y1 - y2;
    }
    else{
        len = x1 - x2;
    }

    if(abs(len) != size - 1){
        cout << "Invalid length." << endl;
        return false;
    }

    //check bottom or leftmost coordinates
    if(horizontal){
        if(x1 > x2){
            int temp = x2;
            x2 = x1;
            x1 = temp;
        }
    }
    else{
        if(y1 < y2){
            int temp = y2;
            y1 = y2;
            y2 = temp;
        }
    }

    for (int i = 0; i < size; i++) {
        int row = 0;
        int col = 0;

        if (vertical) {
            row = y1 - i;
            col = x1;
        }
        else {
            row = y1;
            col = x1 + i;
        }

        int idx = (row*10) + (col);


        if (playerBoard[idx].ship != nullptr) {
            cout << "Ship already placed in cell." << endl;
            return false; // collides with another ship
        }


        playerBoard[idx].ship = shipType; // place the ship
    }
    return true;
}

// displays ship for player, hides ships if revealShips is false
void Board::printPlayerBoard(int player, bool revealShips) const {
// KEY:
    // X = ship was hit at this loc (ie. there is a ship here)
    // O = no ship was hit at this loc (ie. there is no ship at this loc)
    // S = ship (ie. ship revealed to b here)
    // * = open cell (ie. ship can be placed here)
    // . = cell that has not been hit
    
    cout << endl << "   ";
    for (int r = 0; r < 10; r++) { // print entire row first;
        cout << r << "  ";
    }
    cout << endl;
    
    for (int c = 0; c < 10; c++) { // colums
        char name = 'A' + c;
        cout << name << "  ";

        for (int r = 0; r < 10; r++) {
            int idx = (c * 10) + r;
            const Cell cell = playerBoard[idx];

            if (cell.hit) { // if hit, 
                if (cell.ship) { // AND if that hit is a ship, then mark x
                    cout << "X  ";
                }
                else {
                    cout << "O  "; // no ship is present at this loc;
                }
            }
            else {
                if (revealShips && cell.ship) { //reveal ship loc
                    cout << "S  ";
                }
                else if ( revealShips && !cell.ship){ //reveal open space loc
                    cout << "*  ";
                }
                else { //don't reveal unsearched space
                    cout << ".  "; 
                }
            }
        }
        cout << endl;
    }

    cout << endl;
    
}

// excutes attack, returns true if a ship was attacked
bool Board::attack(int player, int x, char yChar) {
    
    int y = yChar - 'A'; //char to int
    
    bool invalid = true;
    while(invalid) { //check coordinates
        if (x < 0 || x > 9 || y < 0 || y > 9) { // out of bounds;
            cout << "Invalid coordinates." << endl;
            cout << "Choose another coordinate to attack (ex. A0):" << endl;

            cin >> yChar >> x;
            y = yChar - 'A';
        }
        else {
            invalid  = false;
        }
    }

    int idx = (y * 10) + x; // get index;



if(!playerBoard[idx].hit){ //unsearch cell
    playerBoard[idx].hit = true; //hit cell
        
    if(playerBoard[idx].ship) { //ship in cell
        playerBoard[idx].ship->takeHit(); //hit ship
        string shipName = playerBoard[idx].ship->getShipType();
        cout << shipName << " ship was hit!" << endl;
        
        if(playerBoard[idx].ship->isSunk()) { //check if sunk ship
            cout << "Ship sunk!" << endl;
            return true; //successful hit
        }
        return true;
    }
        
    else { //not successful
        cout << "No ship was hit." << endl;
        return false;
    }
}
else { //not successful
    cout << "Cell already hit." << endl;
    return false;

    }

}

