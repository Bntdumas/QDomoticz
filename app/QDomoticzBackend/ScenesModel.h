#ifndef SCENESMODEL_H
#define SCENESMODEL_H

#include <QAbstractTableModel>
#include <QMutex>
#include "DomoticzObjects.h"

/**
 * @brief this model handles presenting data for scenes.
 */

class ScenesModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit ScenesModel(QObject *parent = 0);
    int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    int columnCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    Qt::ItemFlags flags(const QModelIndex & index) const Q_DECL_OVERRIDE;
    bool setData(const QModelIndex & index, const QVariant & value, int role = Qt::EditRole) Q_DECL_OVERRIDE;

    int IDForName(const QString &name);
    QList<int> allIDs();

public Q_SLOTS:
    /**
     * @brief Update the local cache
     */
    void updateScenes(const QList<DomoticzObjects::Scene> &list);

Q_SIGNALS:
    void setScene(int ID, bool state);

private:
    DomoticzObjects::SceneList m_scenes;
    QMutex m_locker;


};

#endif // SCENESMODEL_H
