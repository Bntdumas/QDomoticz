#include "ScenesModel.h"
#include <QMutexLocker>
#include <QDebug>

ScenesModel::ScenesModel(QObject *parent):
    QAbstractTableModel(parent)
{
}

int ScenesModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_scenes.count();
}

int ScenesModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 8;
}

QVariant ScenesModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    DomoticzObjects::Scene currentScene = m_scenes.at(index.row());

    if (role == Qt::DisplayRole) {
        switch (index.column()) {
        case 0:
            return currentScene.ID;
        case 1:
            return currentScene.name;
        case 2:
            return currentScene.hardwareID;
        case 3:
            return currentScene.isFavorite;
        case 4:
            return currentScene.lastUpdate;
        case 5:
            return QVariant();
        case 6:
            return currentScene.timers;
        case 7:
            return currentScene.type;
        default:
            break;
        }
    } else if (role == Qt::CheckStateRole && index.column() == 5) {
        return currentScene.status? Qt::Checked : Qt::Unchecked;
    } else
        return QVariant();
}

QVariant ScenesModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        switch(section){
        case 0:
            return tr("ID");
        case 1:
            return tr("Name");
        case 2:
            return tr("Hardware ID");
        case 3:
            return tr("Favorite");
        case 4:
            return tr("Last update");
        case 5:
            return tr("Status");
        case 6:
            return tr("Timers");
        case 7:
            return tr("Type");
        }
    }
    return QAbstractTableModel::headerData(section, orientation, role);
}

Qt::ItemFlags ScenesModel::flags(const QModelIndex &index) const
{
    if (index.column() == 5)
        return Qt::ItemIsEnabled | Qt::ItemIsUserCheckable | Qt::ItemIsEditable;
    else
        return QAbstractTableModel::flags(index);
}

bool ScenesModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    const int deviceID = data(createIndex(index.row(), 0)).toInt();
    bool newState = value.toInt() == 2;
    Q_EMIT setScene(deviceID, newState);
    Q_EMIT dataChanged(index, index);
}

void ScenesModel::updateScenes(const QList<DomoticzObjects::Scene> &list)
{
    Q_EMIT layoutAboutToBeChanged();
    QMutexLocker locker(&m_locker);
    m_scenes = list;
    Q_EMIT layoutChanged();
}
