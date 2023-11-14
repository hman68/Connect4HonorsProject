#include ".\board.h"
#include <iostream>
#include <vector>
#include <cstring>


using namespace std;

Board::Board(){
    board = vector<vector<int>>(DEFAULT_HEIGHT, vector<int>(DEFAULT_LENGTH,0));              //Defines the board to be a vector with the size of 6x7
    for(int i = DEFAULT_HEIGHT - 1; i >= 0; i--){
        for(int j = 0; j < DEFAULT_LENGTH; j++){
            board[i][j] = (DEFAULT_HEIGHT - 1 - i);                                          //This initializes the board so that each row is the number of turns needed before a token can be placed in that row
        }
    }
}

Board::Board(int _h, int _l){
    board = vector<vector<int>>(_h, vector<int>(_l,0));                                      //Defines the board to be a vector with the size of hxl
    for(int i = _h - 1; i >= 0; i--){
        for(int j = 0; j < _l; j++){
            board[i][j] = (_h - 1 - i);                                                      //This initializes the board so that each row is the number of turns needed before a token can be placed in that row
        }
    }    
}

int Board::getWidth(){
    return board[0].size();
}

int Board::getHeight(){
    return board.size();
}

/*
    int getRow(int)

    Returns the bottommost empty row in the given column

    int col     The column to check
*/
int Board::getRow(int col){
    for(int i = getHeight() - 1; i > 0; i--){
        if(board[i][col] == 0){
            return i;
        }
    }
    return -1;
}
/*
    void display()
    
    prints the board to the console, using Y for yellow pieces and R for red pieces
*/
void Board::display(){
    for(int i = 0; i < board.size(); i++){                                                  //Go through each row of the board
        for(int j = 0; j < (board[0].size()) * 2 + 1; j++){                                 //This is the number of dashes that need to be created for a board of variable size (2 per number to allow for vertical separation, 1 extra for the final side marker)
            cout << "-";
        }
        cout << endl;
        for(int j = 0; j < board[0].size(); j++){                                           //Goes through the row and outputs Y or R if a yellow (-1) or red (-2) chip is in that place or a space, and puts a vertical separation between the values
            cout << "|";
            if(board[i][j] == YELLOW){
                cout << "Y";
            }else if(board[i][j] == RED){
                cout << "R";
            }else{
                cout << " ";
            }
        }
        cout << "|" << endl;
    }
     for(int j = 0; j < (board[0].size()) * 2 + 1; j++){                                    //Bottom row of - horizontal separation
        cout << "-";
    }
    cout << endl;
}

/*
    void clear()

    Clears the board
*/
void Board::clear(){
    for(int i = board.size() - 1; i >= 0; i--){
        for(int j = 0; j < board[0].size(); j++){
            board[i][j] = (board.size() - 1 - i);                                                      //This initializes the board so that each row is the number of turns needed before a token can be placed in that row
        }
    }
}

/*
    void place(int, int)

    int color           The color of piece to place: -1 Yellow and -2 Red
    int column          The column to place the piece in (1 - (board[i].size()-1)
*/
bool Board::place(int color, int column){
    for(int i = board.size() - 1; i >= 0; i--){                                             //Loops through the board from bottom up since chips are more likely to be at the bottom
        if(board[i][column - 1] == 0){                                                     //If this is the lowest unocupied space then set the color
            board[i][column - 1] = color;
            for(int j = i - 1; j >= 0; j--){                                                //Updates the other values in the collumn and exits
                board[j][column -1]--;
            }
            int* matches = findMatches(color, {column -1, i});
            int numMatches = *matches;
            return ( numMatches >=4);
        }
    }

    return false;
}
/*
    int* findMatches(int, pair<int,int>, bool)

    int color                   The color to check: -1 Yellow, -2 Red
    pair<int,int> coords        The coordinates to check in order x,y. {0,0} is the top left corner
    bool multiple               Determines if the function returns an array of the matches in each direction or just the longest match

    Prerequisite: The square located at coords is of the color input
*/

int* Board::findMatches(int color, pair<int,int> coords, bool multiple){
    int *values = new int[4]; //(int*)malloc(sizeof(int) * 4); //Creates the int array to be returned

    for(int i = 0; i <= 3; i++){
        *(values + i) = 1 + matchCount(color, applyDirection(coords, i + 1), i + 1) + matchCount(color, applyDirection(coords, -i - 1), -i - 1); //Finds the number of matches in direction i+1 by adding the matches in the positive and negative i+1 direction, plus one for the square that is being checked
    }

    if(!multiple){
        int max = 0;
        int init = 0;
        int* rValue = &init; //New int pointer for the max value

        for(int i = 0; i < 4; i++){
            if(*(values + i) > *(values+max)){
                max = i;
            }
        }
        *rValue = *(values+max); //set the reference value of the return value to be equal to the max value
        delete[] values; //free(values);  //Free the values array to prevent memory leaks
        return rValue;
    }else{
        return values;
    }
    cout <<"Error";
    return nullptr;
}

/*
    Direction Mapping

    -4  1  2        1/-1 = Up/Down
    -3  0  3        2/-2 = Up Right/Down Left
    -2 -1  4        3/-3 = Right/Left
                    4/-4 = Down Right/Up Left
*/
int Board::matchCount(int color, pair<int,int> coords, int direction){
    
    if(coords.first < 0 || coords.first >= board[0].size() || coords.second < 0 || coords.second >= board.size()){ //If the coords are out of bounds, end the recursion and return 0
        return 0;
    }else if(board[coords.second][coords.first] == color){ //If the value at coords is equal to the color

       return 1 + matchCount(color, applyDirection(coords, direction), direction); //Recursive function, continuously adds one
    }else{ //If there is no longer a match, return 0 and end recursion
        return 0;
    }
}


/*
    pair<int,int> applyDirection(pair<int,int>, int)

    pair<int,int> coords        Coordinates before the direction is applied
    int direction               Direction to be applied
*/
pair<int,int> Board::applyDirection(pair<int,int> coords, int direction){ 
    pair<int,int> newCoords = coords;
    switch(direction){
        case 1:
            newCoords.second--;
            break;
        case 2:
            newCoords.first++;
            newCoords.second--;
            break;
        case 3:
            newCoords.first++;
            break;
        case 4:
            newCoords.first++;
            newCoords.second++;
            break;
        case -1:
            newCoords.second++;
            break;
        case -2:
            newCoords.first--;
            newCoords.second++;
            break;
        case -3:
            newCoords.first--;
            break;
        case -4:
            newCoords.first--;
            newCoords.second--;
            break;
        default:
            cout << "Invalid Direction"<<endl;
    }
    return newCoords;


    }