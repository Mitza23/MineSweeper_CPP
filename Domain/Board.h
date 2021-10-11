//
// Created by mitza on 07-Jul-21.
//

#ifndef E3_MITZA23_BOARD_H
#define E3_MITZA23_BOARD_H


#include <memory>

class Board {
private:
    int matrix[100][100]; /// 0 - clear   1 - mine
    int n;
    int mines;
public:
    Board();

    Board(int n);

    int getTile(int i, int j) const;

    void setTile(int i, int j, int val);

    int getDimension() const;

    int getMines();

    void placeMines(int nr);

    static int max(int a, int b);

    static int min(int a, int b);

    int getAdjacentMines(int i, int j) const;

    bool isMine(int i, int j);


};


#endif //E3_MITZA23_BOARD_H
