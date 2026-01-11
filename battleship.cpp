//MAIN GAME FILE
#include "board.h"
#include "player.h"
#include <iostream>

using namespace std;

// testing board:
int main() {
/*  Play Loop */

    cout << "Start Battleship" << endl << endl;

// gets mode
    cout << "Enter the mode you would like to play in: " << endl;
    cout << "1 - Solo (vs AI)" << endl;
    cout << "2 - Two-Players" << endl;
    
    int mode;
    cin >> mode;

// initiate players

    Board p1Board;
    Board p2Board;

    Player p1(p1Board);
    Player* p2 = nullptr; // possibly AI

    if (mode == 1) {
        p2 = new AI(p2Board); // AI mode
    }
    else {
        p2 = new Player(p2Board); // 2-player
    }
//set up boards
    for(int i = 0; i < 2; i++) { //each player gets a turn
        Player* currPlayer = NULL; //assign current player
        if(i == 0){
            currPlayer = &p1;
        }
        else{
            currPlayer = p2;
        }
        
        cout << "Player " << i + 1 << " place your ships." << endl;

//print player board
        currPlayer->printBoard(i, true);
    
//begin placing two of each ship
        for(int cnt = 0; cnt < 2; cnt++) { //player one then player two
            for(int s = 0; s < 3; s++) { //go through the three ship types

                cout << "S = ship" << endl;
                cout << "* = open water" << endl << endl;

                cout << "Small ship = 2 spaces" << endl;
                cout << "Medium ship = 3 spaces" << endl;
                cout << "Large ship = 4 spaces" << endl << endl;

                int x1, x2;
                char y1, y2;

                Ship* shipType = NULL; //declare current ship type
                if(s == 0){
                    shipType = new Small(i);
                }
                else if(s == 1){
                    shipType = new Med(i);
                }
                else{
                    shipType = new Large(i);
                }

                string shipName = shipType->getShipType();

                if (mode == 1 && i == 1) {
                        ((AI*)p2)->placeShipRandom(shipType); // track only if placed
                }
                else {
                    bool placed = false; //check if ship successfully placed
                    while (!placed){
                        cout << "Input Start and End coordinates for " << shipName <<" Ship (ex. A0 A1): " << endl;
                            
                        cin >> y1 >> x1 >> y2 >> x2;
                        if (!currPlayer->placeShip(shipType, x1, y1, x2, y2)) { //if placement invalid
                            cout << "Invalid coords, try again." << endl;
                        }
                        else {
                            placed = true;
                        } 
                    }
                    currPlayer->printBoard(i, true); //reprint board for reference
                    currPlayer->addShip(shipType);
                    }
                }            
            }

            for(int hide = 0; hide < 20; hide++){ //hides previous turn from next player
                cout << endl;
            }
        }

// attack phase

    int turn = 0; //track whos turn
    bool winner = false;

//loop until winner
    while(!winner) {
        int p = turn%2;
        Player* currPlayer = NULL; //assign current player
        if(p == 0){
            currPlayer = &p1;
        }
        else if(p == 1){
            currPlayer = p2;
        } 
        else{
            cout << "Player turn error." << endl;
            return 0;
        }

        cout << "Player " << p+1 << "'s turn to begin attacking." << endl << endl; 

        int e; //assign current enemy
        if(p == 0){
            e = 1;
        }
        else{
            e = 0;
        }

        bool attacking = true; 

    // loop until missed ship

        //  AI
        if (mode == 1 && currPlayer == p2) {
            // while(attacking){
                cout << "AI Turn" << endl;
                currPlayer->printBoard(e, false); // shows opponent board
                bool hit = ((AI*)p2)->attack(((p + 1) % 2));

                if(!hit){
                    attacking = false;
                    break;
                }

                if (hit && currPlayer->checkWin()) {
                    cout << endl << "Player: " << p+1 << " Wins!" << endl;
                    cout << "Winner's Board: " << endl;
                    currPlayer->printBoard(p, true);
                    winner = true;
                }
            }
        }   

    // PvP
        else {
            
            while(attacking){
                currPlayer->printBoard(e, false); //print board for reference

                bool hit = false;
                cout << "Choose coordinate to attack (ex. A0):" << endl;
                int x;
                char y;
                cin >> y >> x;
                hit = currPlayer->attack(p, x, y);

                if(!hit){
                    attacking = false;
                    break;
                }

                if (hit && currPlayer->checkWin()) {
                    cout << endl << "Player: " << p+1 << " Wins!" << endl;
                    cout << "Winner's Board: " << endl;
                    currPlayer->printBoard(p, true);
                    winner = true;
                }
            }
        }
//next turn
        turn++;
    }
    
    delete p2;
    return 0;
}
