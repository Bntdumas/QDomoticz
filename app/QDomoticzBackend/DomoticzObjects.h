#ifndef DOMOTICZOBJECTS_H_
#define DOMOTICZOBJECTS_H_

#include <QDateTime>

namespace DomoticzObjects {

struct SunriseSunset {
    QDateTime serverTime;
    QDateTime sunset;
    QDateTime sunrise;

    SunriseSunset (QDateTime serverTime, QDateTime sunset, QDateTime sunrise):
        serverTime(serverTime), sunset(sunset), sunrise(sunrise) {}
};
typedef QList<SunriseSunset> SunriseSunsetList;

struct Switch {
    QString name;
    QString subType;
    QString type;
    int ID;
    bool status;

    Switch() {}
};
typedef QList<Switch> SwitchList;

struct Scene {
    bool isFavorite;
    int hardwareID;
    QDateTime lastUpdate;
    QString name;
    bool status;
    bool timers;
    QString type;
    int ID;

    Scene() {}
};
typedef QList<Scene> SceneList;
}

#endif // DOMOTICZOBJECTS_H_
