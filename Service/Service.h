//
// Created by mitza on 07-Jul-21.
//

#ifndef E3_MITZA23_SERVICE_H
#define E3_MITZA23_SERVICE_H


#include <Board.h>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

class PlayerPanel;

class Service {
private:
    Board board;
    vector<string> players;
    int checkedMines;
    int overlay[100][100];
    vector<PlayerPanel*> subscribers;
    int index;
public:
    Service(const string& fileName);

    int getAdjacentMines(int i, int j) const;

    bool isMine(int i, int j);

    bool gameOver();

    int getOverlay(int i, int j) const;

    void setOverlayMarked(int i, int j);

    void setOverlayRevealed(int i, int j);

    Board &getBoard();

    int getDimension() const;

    const vector<string> &getPlayers() const;

    void notify();

    void addSubscriber(PlayerPanel* p);

    void nextTurn();

    void endGame();

    void checkFails();
};


#endif //E3_MITZA23_SERVICE_H
