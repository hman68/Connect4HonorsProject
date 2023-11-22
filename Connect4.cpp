#include ".\board.h"
#include ".\ComputerPlayer.h"
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

Board board;

void play();
void ComputerPlay(int compColor);

int main(){

    char menu;
    
    srand(time(0));

    cout << "Welcome to Connect 4!!" << endl;
    do{
        cout << "Please select an option: (N)ew Game, (C)ustom Game, (E)xit" << endl;
        cin >> menu;
        menu = toupper(menu);

        switch(menu){
            case 'N':
                cout <<"Would you like to play against a computer (Y or N)" << endl;
                cin >> menu;
                if(toupper(menu) == 'Y'){
                    int computer = (rand() % 2) - 2;
                    cout << "You are playing as the " << ((computer != -1) ? "yellow" : "red") <<" chips" << endl;
                    ComputerPlay(computer);
                }else{
                    play();
                }
                break;
            case 'C':
                int h, w;
                cout << "Please enter a height"<< endl;
                cin >> h;
                cout << "Please enter a width"<< endl;
                cin >> w;
                board = Board(h, w);
                
                cout <<"Would you like to play against a computer (Y or N)" << endl;
                cin >> menu;
                if(toupper(menu) == 'Y'){
                    int player = (rand() % 2) - 2;
                    cout << "You are playing as the " << ((player != -1) ? "yellow" : "red") <<" chips" << endl;
                    ComputerPlay(player);
                }else{
                    play();
                }
                break;
            case 'E':
                break;
            default:
                cout << "Invalid Option, please try again"<<endl;
                break;
        }
        board.clear();
    }while(menu != 'E');
    return 0;
}

void play(){
    bool player = true;

    int emptySpaces = board.getHeight() * board.getWidth();
    int move;

    while(emptySpaces > 0){
        board.display();
        for(int i = 1; i <= board.getWidth(); i++){
            cout << " " << i;
        }
        cout << endl << endl;
        cout << ((player) ? "Yellow" : "Red");
        cout  << ": please input your move (1 - " << board.getWidth() << ")" << endl;

        cin >> move;
        if(board.getRow(move - 1) >= 0){
            if(board.place((player) ? -1 : -2, move)){
             board.display();
             cout <<((player) ? "Yellow" : "Red") << " Player Wins!!" << endl;
             return;
            }
            emptySpaces--;
            player = !player;
        }else{
            cout << "That move is not possible, please pick another"<< endl;
        }
    }

    if(emptySpaces == 0){
        board.display();
        cout << "Game Tie" << endl;
        return;
    }
}

void ComputerPlay(int compColor){
    ComputerPlayer comp(compColor, &board);

    bool isPlayerTurn = (compColor == -1) ? false : true; //If it is the player's turn

    int emptySpaces = board.getHeight() * board.getWidth();
    int move;

    while(emptySpaces > 0){
        board.display();
        for(int i = 1; i <= board.getWidth(); i++){
            cout << " " << i;
        }
        cout << endl << endl;

        if(isPlayerTurn){
            cout << "Player, please input your move (1 - " << board.getWidth() << ")" << endl;

            cin >> move;
            if(board.getRow(move - 1) >= 0){
                if(board.place(comp.getPlrColor(), move)){
                  board.display();
                  cout << "The Player Wins!!" << endl;
                  return;
                }
                isPlayerTurn = false;
            }else{
            cout << "That move is not possible, please pick another"<< endl;
            }

        }else{
            if(board.place(compColor, comp.SimulateMove() + 1)){
                board.display();
                cout << "The Computer Wins" << endl;
                return;
            }
            isPlayerTurn = true;
        }
        emptySpaces--;
    }
}