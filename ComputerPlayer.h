#ifndef COMPPLR_H_

#define COMPPLR_H_

#include <vector>

class ComputerPlayer{
    private:
        int compColor;
        int plrColor;
        int* defaultValues;
        Board* board;

    public:
        ComputerPlayer(int _c, Board* b);
        ~ComputerPlayer();
        int SimulateMove();
        int getPlrColor();
};

#endif