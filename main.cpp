//
// Created by mitza on 07-Jul-21.
//

#include <QApplication>
#include "Service/Service.h"
#include "UI/PlayerPanel.h"
#include <iostream>

using namespace std;

int main(int argc, char** argv){
    QApplication a(argc, argv);
    Service service{"input.txt"};
    auto players = service.getPlayers();
    for(auto p : players){
//        cout << p << endl;
        auto newPanel = new PlayerPanel(p, service);
        newPanel->show();
    }
    service.nextTurn();
    return a.exec();
}
