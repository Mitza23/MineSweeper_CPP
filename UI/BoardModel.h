//
// Created by mitza on 07-Jul-21.
//

#ifndef E3_MITZA23_BOARDMODEL_H
#define E3_MITZA23_BOARDMODEL_H


#include <QAbstractTableModel>
#include <Board.h>
#include <QBrush>
#include "../Service/Service.h"

class BoardModel : public QAbstractTableModel{
    Q_OBJECT
private:
    Service service;
public:
    BoardModel(Service& s);

    int columnCount(const QModelIndex &parent) const override;

    int rowCount(const QModelIndex &parent) const override;

    QVariant data(const QModelIndex &index, int role) const override;

//    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
};


#endif //E3_MITZA23_BOARDMODEL_H
