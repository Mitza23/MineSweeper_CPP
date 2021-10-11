//
// Created by mitza on 07-Jul-21.
//

#include "Board.h"

Board::Board(int n) : n(n), mines{0} {
    for(int i = 0 ; i <= n ; i++){
        for(int j = 0 ; j <= n ; j++){
            matrix[i][j] = 0;
        }
    }
}

int Board::getTile(int i, int j) const {
    return matrix[i][j];
}

void Board::setTile(int i, int j, int val) {
    matrix[i][j] = val;
}

int Board::getDimension() const {
    return n;
}

void Board::placeMines(int nr) {
    mines += nr;
    srand(getpid());
    int i, j;
    for(int m = 0 ; m < nr ; m++){
        do {
            i = rand() % n;
            j = rand() % n;
        } while (matrix[i][j] == 1);
        matrix[i][j] = 1;
    }
}

int Board::max(int a, int b) {
    if(a > b)
        return a;
    return b;
}

int Board::min(int a, int b) {
    if(a < b)
        return a;
    return b;
}

int Board::getAdjacentMines(int i, int j) const {
    int c = 0;
    for(int lin = max(0, i - 1) ; lin <= min(n-1, i + 1) ; lin++){
        for(int col = max(0, j - 1) ; col <= min(n-1, j + 1) ; col++){
            c += matrix[lin][col];
        }
    }
    return c;
}

bool Board::isMine(int i, int j) {
    if(matrix[i][j] == 1)
        return true;
    return false;
}

Board::Board() {}

int Board::getMines() {
    return mines;
}
