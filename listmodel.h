#ifndef LISTMODEL_H
#define LISTMODEL_H

#include <QAbstractListModel>
#include <unordered_map>

#include "items.h"


class ListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    ListModel(QObject *parent = 0);

    std::unordered_map<int,Items> getList();

    void mapIndex();

    bool add(int id, Items item);
    std::unordered_map<int,Items>::iterator find(int id);

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
    /*QVariant headerData(int section, Qt::Orientation orientation,
                             int role = Qt::DisplayRole) const;*/

private:
    std::unordered_map<int,Items> aucMap;
    std::unordered_map<int,int> indexMap;

};

#endif // LISTMODEL_H
