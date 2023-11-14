#include ".\board.h"
#include ".\ComputerPlayer.h"
#include <stdlib.h>
#include <iostream>
#include <climits>


ComputerPlayer::ComputerPlayer(int _c, Board* b){
    compColor = _c;
    if(compColor == -1){
        plrColor = -2;
    }else{
        plrColor = -1;
    }

    board = b;
    int size = (*board).getWidth();


    defaultValues = new int[size];//(int*)calloc(size, sizeof(int));

    int distance = 0;

    for(int i = 0; i < ((size/2) + 1); i++){ //Initialize the default values
        distance = -1 * (size/2) + i; //(size/2) + i is the distance from the center it becomes negative to assign a negative weight to these columns
        *(defaultValues + i) = distance;
        *(defaultValues + size - 1 - i) = distance;
    }
}

int ComputerPlayer::SimulateMove(){
    int currentRanks[(*board).getWidth()]; // Creates an array to hold the current weight to each column
    copy(defaultValues, defaultValues+((*board).getWidth() ), currentRanks);

    for(int i = 0; i < (*board).getWidth(); i++){
        int row = (*board).getRow(i);
        if(row != -1){
            int* compRankings = (*board).findMatches(compColor, {i, row}, true); //Find the number of matches in each direction for the current position
            for(int j = 0; j < 4; j++){
                switch(compRankings[j]){
                    case 4:
                        return i;
                    case 3:
                        currentRanks[i]+=2;
                    case 2:
                        currentRanks[i]++;
                    case 1:
                        currentRanks[i]++;
                    default:
                        break;
                }
            }
            delete[] compRankings;//free(compRankings);
            int* playerRankings = (*board).findMatches(plrColor, {i, row}, true); //Find the number of matches that the opposing player could potentially get if it were their turn
            for(int j = 0; j < 4; j++){
                switch(playerRankings[j]){
                    case 4:
                        currentRanks[i] += 50;
                    case 3:
                        currentRanks[i] ++;
                    default:
                        break;
                }
            }
            delete[] playerRankings;//free(playerRankings);
            playerRankings = (*board).findMatches(plrColor, {i, row - 1}, true);

            for(int j = 0; j < 4; j++){
                switch(playerRankings[j]){
                    case 4:
                        currentRanks[i] -= 50;
                    case 3:
                        currentRanks[i] --;
                    case 2:
                        currentRanks[i]--;
                    default:
                        break;
                }
            }

            delete[] playerRankings;//free(playerRankings);
        }else{
            currentRanks[i] = INT_MIN;
        }
    }

    int maxIdx = 0;
    for(int i = 1; i < (*board).getWidth(); i++){
        if(currentRanks[i] > currentRanks[maxIdx]){
            maxIdx = i;
        }
    }
    return maxIdx;
}

int ComputerPlayer::getPlrColor(){
    return plrColor;
}
ComputerPlayer::~ComputerPlayer(){
    delete[] defaultValues; //free(defaultValues);
}