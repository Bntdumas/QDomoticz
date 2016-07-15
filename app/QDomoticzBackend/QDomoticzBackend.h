#ifndef QDOMOTICZBACKEND_H
#define QDOMOTICZBACKEND_H

#include "QDomoticzBackend_global.h"
#include "DomoticzObjects.h"
#include <QObject>
#include <QJsonObject>

class QNetworkAccessManager;
class QNetworkReply;

/**
 * @brief This class handles the low level communication with the domoticz server.
 */

class QDOMOTICZBACKENDSHARED_EXPORT QDomoticzBackend: public QObject
{
Q_OBJECT
public:
    QDomoticzBackend(QObject *parent = 0);
    void setDomoticzServerSettings(const QString &IP, int port);
    bool sendJSonRequest(const QVariantMap &array);

private Q_SLOTS:
    void JSONReceived(QNetworkReply *reply);

Q_SIGNALS:
    void switchesReceived(const QList<DomoticzObjects::Switch> &list);
    void scenesReceived(const QList<DomoticzObjects::Scene> &list);
   // void sunriseSunsetReceived(const SunriseSunsetList &list);

private:
    void parseJSON(const QJsonObject &object);
    void parseScenes(const QVariantList &scenesToParse);
    void parseSwitches(const QVariantList &switchesToParse);

    /**
     * @brief test if the returned data is of type "switch"
     */
    bool isSwitch(const QVariantList &result);

    QString m_serverIP;
    int m_serverPort;


    QNetworkAccessManager *m_networkManager;
};



#endif // QDOMOTICZBACKEND_H
