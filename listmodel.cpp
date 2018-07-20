#include <iterator>
#include "listmodel.h"


ListModel::ListModel(QObject *parent)
    : QAbstractListModel(parent)
{

}

std::unordered_map<int,Items> ListModel::getList()
{
    return this->aucMap;
}

void ListModel::mapIndex()
{
    indexMap.clear();

    int i = 0;

    for (auto const& x : aucMap)
    {
        indexMap.emplace(i,x.first);
        i++;
    }

}

bool ListModel::add(int id, Items item)
{
    return this->aucMap.emplace(id,item).second;
}

std::unordered_map<int,Items>::iterator ListModel::find(int id)
{
    return this->aucMap.find(id);
}


int ListModel::rowCount(const QModelIndex &parent) const
{
    return aucMap.size();
}


QVariant ListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
             return QVariant();

     if (index.row() >= aucMap.size())
         return QVariant();

     if (role == Qt::DisplayRole)
     {
         //return aucMap.at(indexMap.at(index.row()).second).second;
         //return indexMap.at(index.row());
         return QVariant();
     }
     else
         return QVariant();

}

/*QVariant ListModel::headerData(int section, Qt::Orientation orientation,
                                     int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal)
        return QString("Column %1").arg(section);
    else
        return QString("Row %1").arg(section);
}*/

