#include "model.h"

namespace unicorn {

Model::Model(QObject *parent) : QAbstractListModel (parent)
{

}

int Model::rowCount(const QModelIndex&) const {
    return _items.size();
}

QVariant Model::data(const QModelIndex& index, int /*role*/) const {
    QObject* item = _items.at(index.row());
    return QVariant::fromValue(item);
}

void Model::insert(QObject* item) {
    beginInsertRows(QModelIndex(), 0, 0);
    _items.push_front(item);
    endInsertRows();
}

void Model::remove(QObject* item) {
    for (int i = 0; i < _items.size(); ++i) {
        if (_items.at(i) == item) {
            beginRemoveRows(QModelIndex(), i, i);
            _items.remove(i);
            endRemoveRows();
            break;
        }
    }
}

void Model::clear()
{
    beginResetModel();
    _items.clear();
    endResetModel();
}

QHash<int, QByteArray> Model::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[Qt::UserRole + 1] = "item";
    return roles;
}

}
