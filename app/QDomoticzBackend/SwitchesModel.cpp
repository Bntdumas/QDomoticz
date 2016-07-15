#include "SwitchesModel.h"
#include <QMutexLocker>
#include <QDebug>


SwitchesModel::SwitchesModel(QObject *parent):
    QAbstractTableModel(parent)
{
}

int SwitchesModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_switches.count();
}

int SwitchesModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 5;
}

QVariant SwitchesModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    DomoticzObjects::Switch currentSwitch = m_switches.at(index.row());

    if (role == Qt::DisplayRole) {
        switch (index.column()) {
        case 0:
            return currentSwitch.ID;
        case 1:
            return currentSwitch.name;
        case 2:
            return currentSwitch.type;
        case 3:
            return currentSwitch.subType;
        case 4:
            return QVariant();
        default:
            break;
        }
   // } else if (role == Qt::BackgroundColorRole) {
   //         DomoticzObjects::Switch currentSwitch = m_switches.at(index.row());
   //         return currentSwitch.status ? QColor("Green"):QColor("red");
    } else if (role == Qt::CheckStateRole && index.column() == 4) {
       return currentSwitch.status? Qt::Checked : Qt::Unchecked;
    }


    else
        return QVariant();
}

QVariant SwitchesModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        switch(section){
        case 0:
            return tr("ID");
        case 1:
            return tr("Name");
        case 2:
            return tr("Type");
        case 3:
            return tr("Sub-type");
        case 4:
            return tr("status");
        }
    }
    return QAbstractTableModel::headerData(section, orientation, role);
}

Qt::ItemFlags SwitchesModel::flags(const QModelIndex &index) const
{
    if (index.column() == 4)
       return Qt::ItemIsEnabled | Qt::ItemIsUserCheckable | Qt::ItemIsEditable;
    else
        return QAbstractTableModel::flags(index);
}

bool SwitchesModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    const int deviceID = data(createIndex(index.row(), 0)).toInt();
    bool newState = value.toInt() == 2;
    Q_EMIT setSwitch(deviceID, newState);
    Q_EMIT dataChanged(index, index);
}

void SwitchesModel::updateSwitches(const QList<DomoticzObjects::Switch> &list)
{
    Q_EMIT layoutAboutToBeChanged();
    QMutexLocker locker(&m_locker);
    m_switches = list;
    Q_EMIT layoutChanged();
}

