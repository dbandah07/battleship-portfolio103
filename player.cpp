#include "player.h"
#include "ship.h"
#include <iostream>

using namespace std; 

Player::Player(Board& pBoard) : board(pBoard) {}

Player::~Player(){
    for(size_t i = 0; i < ships.size(); i++){
        delete ships[i];
    }
    ships.clear();
}


bool Player::placeShip(Ship* shipType, int x1, char y1, int x2, char y2){
    return board.placeShip(shipType, x1, y1, x2, y2);
}

void Player::printBoard(int player, bool reveal){
    return board.printPlayerBoard(player, reveal);
}

void Player::addShip(Ship* shipType){
    ships.push_back(shipType);
}

bool Player::attack(int player, int x, char y){
    return board.attack(player, x, y);
}

bool Player::checkWin(){

    if (ships.empty()) {
        return false; // prevents false victory.
    }

    for(size_t i = 0; i < ships.size(); i++){
        if(!ships[i]->isSunk()){
            return false;
        }
    }

    return true;
}


AI::AI(Board& pBoard) : Player (pBoard) {
    srand(time(0)); // seed random num generator
    for (int i = 0; i < 100; i++) {
        alrdyAttacked[i] = false;
    }
}

AI::~AI() {} // destructor

bool AI::placeShip(Ship* shipSize, int x1, char y1, int x2, char y2){
    return Player::placeShip(shipSize, x1, y1, x2, y2);
}

void AI::placeShipRandom(Ship* shipType) {
    bool placed = false;
    int size = shipType->getSize();

    while(!(placed)) {
        int x1 = rand() % 10;
        int y1 = rand() % 10;
        bool horizontal = rand() % 2;
        
        int x2 = x1;
        int y2 = y1;


        if (horizontal) {
            y2 = y1 + size - 1;
        }
        else {
            x2 = x1 + size - 1;
        }

        // check bounds
        if (x2 < 10 && y2 < 10) {
            placed = Player::placeShip(shipType, x1, 'A' + y1, x2, 'A' + y2);
        }
    }
    
    addShip(shipType); // only added once placed;
}

bool AI::attack(int player) {
    int attempts = 0;
    while (attempts < 20) {
        int x = rand() % 10;
        int y = rand() % 10;

        int idx = y * 10 + x;

        if (!alrdyAttacked[idx]) {
            alrdyAttacked[idx] = true;

            if (Player::attack(player, x, 'A' + y)) {
                cout << "AI attacked" << endl;
                return true;
            }
            
            alrdyAttacked[idx] = false;
        }
        attempts++;
    }
    // cout << "No valid moves left for AI." << endl;

    return false;
}

