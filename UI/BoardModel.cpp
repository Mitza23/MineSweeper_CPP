//
// Created by mitza on 07-Jul-21.
//

#include "BoardModel.h"

BoardModel::BoardModel(Service &s) : service{s} {}

int BoardModel::columnCount(const QModelIndex &parent) const {
    return service.getDimension() + 1;
}

int BoardModel::rowCount(const QModelIndex &parent) const {
    return service.getDimension() + 1;
}

QVariant BoardModel::data(const QModelIndex &index, int role) const {
    auto row = index.row() - 1;
    auto column = index.column() - 1;
    int element;
    if(row >= 0 && column >= 0)
        element = service.getOverlay(row, column);
    else
        element = -1;

    QBrush redBrush(Qt::red);
    QBrush blueBrush(Qt::cyan);
    QBrush whiteBrush(Qt::white);
    QBrush greenBrush(Qt::green);

    switch (role) {
        case Qt::BackgroundRole: {
            if (element == 0) {
                return greenBrush;
            } else if (element == 1) {
                return redBrush;
            } else if (element == 2) {
                return blueBrush;
            } else
                return whiteBrush;
        }
        case Qt::DisplayRole: {
            if(element == 0){
                return QString("");
            }else if (element == 1) {
                return QString("*");
            } else if (element == 2) {
                return QString::number(service.getAdjacentMines(row, column));
            } else if(row == -1 && column != -1){
                char l = 'A' + column;
                string s;
                s += l;
                return QString::fromStdString(s);
            } else if(column == -1 && row != -1){
                char l = '0' + row;
                string s;
                s += l;
                return QString::fromStdString(s);
            } else{
                return QString("");
            }
        }
        default:
            return QVariant();
    }
}
