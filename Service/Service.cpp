//
// Created by mitza on 07-Jul-21.
//

#include "Service.h"
#include "../UI/PlayerPanel.h"
#include <iostream>
#include <QMessageBox>


Service::Service(const string &fileName): checkedMines{0}, index{-1} {
    ifstream fi(fileName);
    int n;
    fi >> n;
//    cout << n << endl;
    board = Board(n);
    int m;
    fi >> m;
//    cout << m << endl;
    board.placeMines(m);
    string s;
    while (fi >> s){
        players.push_back(s);
    }
    fi.close();
    for(int i = 0 ; i < n ; i++){
        for(int j = 0 ; j < n ; j++) {
            overlay[i][j] = 0; /// 0 - covered     1 - marked as mine      2 - revealed
        }
    }
}

int Service::getAdjacentMines(int i, int j) const{
    return  board.getAdjacentMines(i, j);
}

bool Service::isMine(int i, int j) {
    if(board.isMine(i, j)){
        return true;
    }
    return false;
}

bool Service::gameOver() {
    if(checkedMines == board.getMines())
        return true;
    return false;
}

int Service::getOverlay(int i, int j) const {
    return overlay[i][j];
}

void Service::setOverlayMarked(int i, int j) {
    overlay[i][j] = 1;
    if(board.isMine(i, j)){
        checkedMines++;
    }
}

void Service::setOverlayRevealed(int i, int j) {
    overlay[i][j] = 2;
}

Board &Service::getBoard() {
    return board;
}

int Service::getDimension() const {
    return board.getDimension();
}

const vector<string> &Service::getPlayers() const {
    return players;
}

void Service::notify() {
    for(PlayerPanel* p : subscribers){
        p->updateTable();
    }
}

void Service::addSubscriber(PlayerPanel *p) {
    subscribers.push_back(p);
    p->setTurn(false);
}

void Service::nextTurn() {
    checkFails();
    if(index > 0)
        subscribers[index]->setTurn(false);
    int c = 0;
    do {
//        cout << index << endl;
        index++;
        c++;
        index %= subscribers.size();
    } while (subscribers[index]->getDefeated() && c <= subscribers.size());
    if(c > subscribers.size()) {
        string message{"GAME OVER"};
        QMessageBox messageBox;
        messageBox.setText(QString::fromStdString(message));
        messageBox.exec();
        endGame();
    }
    index %= subscribers.size();
    subscribers[index]->setTurn(true);
}

void Service::endGame() {
    for(auto s : subscribers){
        s->terminate();
    }
}

void Service::checkFails() {
    int c = 0;
    for(auto s : subscribers){
        if(s->getDefeated() == true)
            c++;
    }
    if(c == subscribers.size()) {
        endGame();
        string message{"GAME OVER, YOU LOST"};
        QMessageBox messageBox;
        messageBox.setText(QString::fromStdString(message));
        messageBox.exec();
    }
    if(checkedMines == getDimension()) {
        endGame();
        string message{"GAME OVER, YOU WON"};
        QMessageBox messageBox;
        messageBox.setText(QString::fromStdString(message));
        messageBox.exec();
    }
}
