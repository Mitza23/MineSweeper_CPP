//
// Created by mitza on 07-Jul-21.
//

#include <QLabel>
#include <QMessageBox>
#include "PlayerPanel.h"
#include "BoardModel.h"

PlayerPanel::PlayerPanel(string name, Service &s) : playerName{name}, service{s}, defeated{false}{
    s.addSubscriber(this);
    initGUI();
    connectSignalsAndSlots();
}

void PlayerPanel::initGUI() {
    auto mainLayout = new QVBoxLayout(this);
    auto editLayout = new QHBoxLayout();
    auto buttonLayout = new QHBoxLayout();
    auto controlLayout = new QVBoxLayout();
    tableView = new QTableView();
    auto model = new BoardModel(service);
    tableView->setModel(model);
    tableView->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
    auto lineLabel = new QLabel("Line");
    lineEdit = new QLineEdit();
    lineLabel->setBuddy(lineEdit);
    auto columnLabel = new QLabel("Column");
    columnEdit = new QLineEdit();
    columnLabel->setBuddy(columnEdit);
    revealButton = new QPushButton("Reveal");
    markButton = new QPushButton("Mark mine");
    editLayout->addWidget(lineLabel);
    editLayout->addWidget(lineEdit);
    editLayout->addWidget(columnLabel);
    editLayout->addWidget(columnEdit);
    buttonLayout->addWidget(revealButton);
    buttonLayout->addWidget(markButton);
    controlLayout->addLayout(editLayout);
    controlLayout->addLayout(buttonLayout);
    mainLayout->addWidget(tableView);
    mainLayout->addLayout(controlLayout);
    this->setWindowTitle(QString::fromStdString(playerName));
    setDisabled(markButton);
    setDisabled(revealButton);
    for(int i = 0 ; i <= service.getDimension() ; i++) {
        tableView->setRowHeight(i, 90);
        tableView->setColumnWidth(i, 90);
    }
}

void PlayerPanel::connectSignalsAndSlots() {
    QObject::connect(markButton, SIGNAL(clicked()), this, SLOT(markTile()));
    QObject::connect(markButton, SIGNAL(clicked()), this, SLOT(nextTurn()));
    QObject::connect(revealButton, SIGNAL(clicked()), this, SLOT(revealTile()));
    QObject::connect(revealButton, SIGNAL(clicked()), this, SLOT(nextTurn()));
}

void PlayerPanel::markTile(){
        auto column = columnEdit->text().toStdString();
        auto line = lineEdit->text().toInt();
        if(column == ""){
            string message{"Please fill in the column"};
            QMessageBox messageBox;
            messageBox.setText(QString::fromStdString(message));
            messageBox.exec();
        }
        if(lineEdit->text().toStdString() == ""){
            string message{"Please fill in the line"};
            QMessageBox messageBox;
            messageBox.setText(QString::fromStdString(message));
            messageBox.exec();
        }
        char c = column[0];
        c = toupper(c);
        int col = c - 'A';
        service.setOverlayMarked(line, col);
        if(service.gameOver()){
            string message{"You won!"};
            QMessageBox messageBox;
            messageBox.setText(QString::fromStdString(message));
            messageBox.exec();
            service.endGame();
        }
        service.notify();
}

void PlayerPanel::revealTile(){
    auto column = columnEdit->text().toStdString();
    auto line = lineEdit->text().toInt();
    if(column == ""){
        string message{"Please fill in the column"};
        QMessageBox messageBox;
        messageBox.setText(QString::fromStdString(message));
        messageBox.exec();
    }
    if(lineEdit->text().toStdString() == ""){
        string message{"Please fill in the line"};
        QMessageBox messageBox;
        messageBox.setText(QString::fromStdString(message));
        messageBox.exec();
    }
    char c = column[0];
    c = toupper(c);
    int col = c - 'A';
    service.setOverlayRevealed(line, col);
    if(service.isMine(line, col)){
        defeated = true;
        string message{"YOU LOST! A mine has exploded"};
        QMessageBox messageBox;
        messageBox.setText(QString::fromStdString(message));
        messageBox.exec();
    }
    service.notify();
}

void PlayerPanel::updateTable() {
    delete tableView->model();
    auto model = new BoardModel(service);
    tableView->setModel(model);
}

string PlayerPanel::getPlayerName() {
    return playerName;
}

bool PlayerPanel::getTurn() {
    return turn;
}

void PlayerPanel::setTurn(bool t) {
    turn = t;
    if(t == true){
        setEnabled(markButton);
        setEnabled(revealButton);
    }
    else{
        setDisabled(markButton);
        setDisabled(revealButton);
    }
}

void PlayerPanel::nextTurn() {
    service.nextTurn();
}

bool PlayerPanel::getDefeated() {
    return defeated;
}

void PlayerPanel::terminate() {
    this->close();
}
