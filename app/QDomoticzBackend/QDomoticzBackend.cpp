#include "QDomoticzBackend.h"

#include <QNetworkAccessManager>
#include <QUrlQuery>
#include <QNetworkReply>
#include <QJsonDocument>

QDomoticzBackend::QDomoticzBackend(QObject *parent) :
    QObject(parent),
    m_networkManager(0),
    m_serverIP(QStringLiteral("192.168.0.148")),
    m_serverPort(8080)
{}

void QDomoticzBackend::setDomoticzServerSettings(const QString &IP, int port)
{
    m_serverIP = IP;
    m_serverPort = port;
}

void QDomoticzBackend::JSONReceived(QNetworkReply *reply)
{
    QJsonParseError errors;
    QJsonDocument document = QJsonDocument::fromJson(reply->readAll(), &errors);
    if (errors.error == QJsonParseError::NoError) {
        if (document.isObject()) {
            parseJSON(document.object());
        } else {
            qDebug() << Q_FUNC_INFO << " The received JSON is not an object";
        }
    } else {
        qDebug() << Q_FUNC_INFO << "error while parsing received JSON: "
                 <<  errors.errorString();
    }
}

void QDomoticzBackend::parseJSON(const QJsonObject &object)
{
    QVariant title;
    QVariant result;

    QVariantMap map(object.toVariantMap());
    QMapIterator<QString, QVariant> i(map);
    while (i.hasNext()) {
        i.next();
        // qDebug() << i.key() << ":" << i.value();
        // save result and type of data
        if (i.key() == QStringLiteral("title")) {
            title = i.value();
        } else if (i.key() == QStringLiteral("result"))
            result = i.value();
    }

    if (title.toString() == QStringLiteral("Scenes")) {
        parseScenes(result.value<QVariantList>());
    } else if (title.toString() == QStringLiteral("Devices")) {
        parseSwitches(result.value<QVariantList>());
    }
}

void QDomoticzBackend::parseScenes(const QVariantList &scenesToParse)
{
    //iterate over scenes
    DomoticzObjects::SceneList scenes;
    QVariantList::const_iterator iterator;
    for (iterator = scenesToParse.constBegin(); iterator != scenesToParse.constEnd(); ++iterator) {
        QVariant scene = *iterator;
        DomoticzObjects::Scene currentScene;
        // One scene
        QVariantMap map(scene.value<QVariantMap>());
        QMapIterator<QString, QVariant> i(map);
        while (i.hasNext()) {
            i.next();
            if (i.key() == QStringLiteral("Favorite")) {
                currentScene.isFavorite = i.value().toDouble() != 0;
            } else if (i.key() == QStringLiteral("Name")) {
                currentScene.name = i.value().toString();
            } else if (i.key() == QStringLiteral("idx")) {
                currentScene.ID = i.value().toString().toInt();
            } else if (i.key() == QStringLiteral("HardwareID")) {
                currentScene.hardwareID = i.value().toDouble();
            } else if (i.key() == QStringLiteral("LastUpdate")) {
                currentScene.lastUpdate = QDateTime::fromString(i.value().toString(), QStringLiteral("yyyy-MM-dd hh:mm:ss")); //2015-11-18 23:51:19
            } else if (i.key() == QStringLiteral("Timers")) {
                currentScene.timers = i.value().toString() == QStringLiteral("On");
            } else if (i.key() == QStringLiteral("Type")) {
                currentScene.type = i.value().toString();
            } else if (i.key() == QStringLiteral("Status")) {
                currentScene.status = i.value().toString() == QStringLiteral("On");
            }
        }
        scenes.append(currentScene);
    }
    Q_EMIT scenesReceived(scenes);
}

void QDomoticzBackend::parseSwitches(const QVariantList &switchesToParse)
{
    //iterate over switches
    DomoticzObjects::SwitchList switches;
    QVariantList::const_iterator iterator;
    for (iterator = switchesToParse.constBegin(); iterator != switchesToParse.constEnd(); ++iterator) {
        QVariant scene = *iterator;
        DomoticzObjects::Switch currentSwitch;
        // One scene
        QVariantMap map(scene.value<QVariantMap>());
        QMapIterator<QString, QVariant> i(map);
        while (i.hasNext()) {
            i.next();
            if (i.key() == QStringLiteral("Status")) {
                currentSwitch.status = i.value().toString() == QStringLiteral("Off") ? false:true;
            } else if (i.key() == QStringLiteral("Name")) {
                currentSwitch.name = i.value().toString();
            } else if (i.key() == QStringLiteral("SubType")) {
                currentSwitch.subType = i.value().toString();
            } else if (i.key() == QStringLiteral("Type")) {
                currentSwitch.type = i.value().toString();
            } else if (i.key() == QStringLiteral("idx")) {
                currentSwitch.ID = i.value().toString().toInt();
            }

        }
        switches.append(currentSwitch);
        //qDebug() << "New switch: " << currentSwitch.name << " ID " << currentSwitch.ID;
    }
    Q_EMIT switchesReceived(switches);
}

bool QDomoticzBackend::sendJSonRequest(const QVariantMap &array)
{
    if (!m_networkManager) {
        m_networkManager = new QNetworkAccessManager(this);
        connect(m_networkManager, &QNetworkAccessManager::finished, this, &QDomoticzBackend::JSONReceived);
    }

    // prepare query
    const QString baseUrl = QString(QStringLiteral("http://%1:%2/json.htm")).arg(m_serverIP).arg(m_serverPort);
    QUrl url(baseUrl);
    QUrlQuery urlQuery;
    Q_FOREACH (QString name, array.keys()) {
        const QString value = array[name].toString();
        urlQuery.addQueryItem(name, value);
    }
    url.setQuery(urlQuery);

    //execute
    QNetworkRequest request;
    request.setUrl(url);
    m_networkManager->get(request);
}
