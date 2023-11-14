#ifndef BOARD_H_

#define BOARD_H_

#include <vector>

const int DEFAULT_HEIGHT = 6;
const int DEFAULT_LENGTH = 7;

const int YELLOW = -1;
const int RED = -2;

using namespace std;

class Board{

    private:
        vector<vector<int>> board;
    public:
        Board();
        Board(int _h, int _l);

        int getWidth();
        int getHeight();
        int getRow(int col);

        void display();
        void clear();
        bool place(int color, int collumn);
        int* findMatches(int color, pair<int,int> coords, bool multiple = false);
        int matchCount(int color, pair<int,int> coords, int direction);
        pair<int,int> applyDirection(pair<int,int> coords, int direction);
};

#endif