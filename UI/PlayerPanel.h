//
// Created by mitza on 07-Jul-21.
//

#ifndef E3_MITZA23_PLAYERPANEL_H
#define E3_MITZA23_PLAYERPANEL_H


#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QTableView>
#include "../Service/Service.h"
#include "BoardModel.h"
#include <string>
#include <QVBoxLayout>

using std::string;

class PlayerPanel : public QWidget{
    Q_OBJECT
private:
    string playerName;
    Service& service;
    bool turn;
    bool defeated;

    QTableView* tableView;
    QLineEdit* lineEdit;
    QLineEdit* columnEdit;
    QPushButton* revealButton;
    QPushButton* markButton;

    void initGUI();

    void connectSignalsAndSlots();

public:
    PlayerPanel(string name, Service& s);

    string getPlayerName();

    bool getTurn();

    void setTurn(bool t);

    bool getDefeated();

    void terminate();

public slots:
    void markTile();

    void revealTile();

    void updateTable();

    void nextTurn();

};


#endif //E3_MITZA23_PLAYERPANEL_H
