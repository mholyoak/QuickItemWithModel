#include "QuickItemWithModel.h"

#include <iostream>

ItemModel::ItemModel(QObject *parent):
    QAbstractListModel (parent)
{
}

QHash<int, QByteArray> ItemModel::roleNames() const
{
    auto roles = QAbstractItemModel::roleNames();
    roles.insert(int(Role::ItemModelRole), QByteArray("name"));
    return roles;
}

QVariant ItemModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        return QVariant(); // Return Null variant if index is invalid
    }

    switch (role) {
    case Qt::DisplayRole: // The default display role now displays the first name as well
    case int(Role::ItemModelRole):
    {
        QString itemModelName = QString("Name-%1").arg(index.row());
        return QVariant::fromValue(itemModelName);
    }
    default:
        return QVariant();
    }
}

int ItemModel::rowCount(const QModelIndex & /*parent*/) const
{
    return 100;
}


QuickItemWithModel::QuickItemWithModel(QQuickItem *parent):
    QQuickItem(parent),
    title_("Custom Menu")
{
}

QString QuickItemWithModel::title() const
{
    return title_;
}

void QuickItemWithModel::setTitle(const QString& newTitle)
{
    title_ = newTitle;
}

ItemModel* QuickItemWithModel::itemModel()
{
    return &itemModel_;
}

void QuickItemWithModel::itemModelSelected(QString itemName)
{
    std::cout << "C++ itemModelSelected " << itemName.toStdString() << std::endl;
    auto notifyText = QString("Notify Text: %1").arg(itemName);
    emit notificationText(notifyText);

}
