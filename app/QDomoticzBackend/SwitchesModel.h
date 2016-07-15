#ifndef SwitchesModel_H
#define SwitchesModel_H

#include <QAbstractTableModel>
#include <QMutex>
#include "DomoticzObjects.h"

/**
 * @brief this model handles presenting data for switches.
 */

class SwitchesModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit SwitchesModel(QObject *parent = 0);
    int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    int columnCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    Qt::ItemFlags flags(const QModelIndex & index) const Q_DECL_OVERRIDE;
    bool setData(const QModelIndex & index, const QVariant & value, int role = Qt::EditRole) Q_DECL_OVERRIDE;


public Q_SLOTS:
    /**
     * @brief Update the local cache
     */
    void updateSwitches(const QList<DomoticzObjects::Switch> &list);

Q_SIGNALS:
    void setSwitch(int ID, bool state);

private:
    DomoticzObjects::SwitchList m_switches;
    QMutex m_locker;
};

#endif // SwitchesModel_H
