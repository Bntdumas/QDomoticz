#include "QDomoticzController.h"
#include "QDomoticzBackend.h"
#include "DomoticzObjects.h"

#include <QVariantMap>
#include <QDebug>
#include <QTimer>
#include <QMutexLocker>

QDomoticzController::QDomoticzController(QObject *parent) :
    QObject(parent),
    m_backend(0),
    m_pollTimer(new QTimer(this))
{
    m_pollTimer->setInterval(500);
    connect(m_pollTimer, &QTimer::timeout, this, &QDomoticzController::pollServer);
}

void QDomoticzController::initialize(QDomoticzBackend *backend)
{
    if (backend) {
        m_backend = backend;
        return;
    }

    m_backend = new QDomoticzBackend(this);

    //signals  forwarding
    connect(m_backend, &QDomoticzBackend::scenesReceived, this, &QDomoticzController::scenesReceived);
    connect(m_backend, &QDomoticzBackend::switchesReceived, this, &QDomoticzController::switchesReceived);
    return;
}

void QDomoticzController::setTimer(bool status)
{
    if (status)
        m_pollTimer->start();
    else
        m_pollTimer->stop();

}

void QDomoticzController::getScenes()
{
    if(!isInitialized())
        return;
    QVariantMap params;
    params[QStringLiteral("type")] = QStringLiteral("scenes");
    m_backend->sendJSonRequest(params);
}

void QDomoticzController::getAll()
{
    if(!isInitialized())
        return;
    QVariantMap params;
    params[QStringLiteral("type")] = QStringLiteral("devices");
    params[QStringLiteral("filter")] = QStringLiteral("all");
    params[QStringLiteral("used")] = QStringLiteral("true");
    params[QStringLiteral("order")] = QStringLiteral("Name");
    params[QStringLiteral("favorite")] = QStringLiteral("true");
    m_backend->sendJSonRequest(params);
}

void QDomoticzController::getSwitches()
{
    if(!isInitialized())
        return;
    QVariantMap params;
    params[QStringLiteral("type")] = QStringLiteral("devices");
    params[QStringLiteral("filter")] = QStringLiteral("light");
    params[QStringLiteral("used")] = QStringLiteral("true");
    m_backend->sendJSonRequest(params);
}

void QDomoticzController::toggleSwitch(int ID, bool flag)
{
    // /json.htm?type=command&param=switchlight&idx=99&switchcmd=On
    const QString flagStr = flag ? QStringLiteral("On"):QStringLiteral("Off");
    if(!isInitialized())
        return;
    QVariantMap params;
    params[QStringLiteral("type")] = QStringLiteral("command");
    params[QStringLiteral("param")] = QStringLiteral("switchlight");
    params[QStringLiteral("idx")] = QString::number(ID);
    params[QStringLiteral("switchcmd")] = flagStr;
    m_backend->sendJSonRequest(params);
}

void QDomoticzController::toggleScene(int ID, bool flag)
{
    // /json.htm?type=command&param=switchscene&idx=&switchcmd=
    const QString flagStr = flag ? QStringLiteral("On"):QStringLiteral("Off");

    if(!isInitialized())
        return;

    QVariantMap params;
    params[QStringLiteral("type")] = QStringLiteral("command");
    params[QStringLiteral("param")] = QStringLiteral("switchscene");
    params[QStringLiteral("idx")] = QString::number(ID);
    params[QStringLiteral("switchcmd")] = flagStr;
    m_backend->sendJSonRequest(params);
}

void QDomoticzController::allLightsOff()
{
//    Q_FOREACH (const DomoticzObjects::Switch currentSwitch, m_switches) {
//        toggleSwitch(currentSwitch.ID, false);
    //    }
}

void QDomoticzController::makeACoffee(QDomoticzController::CoffeeSize size)
{

}

void QDomoticzController::setCoffeeMachinePower(bool state)
{

}

QDomoticzController::CoffeeState QDomoticzController::coffeeMachineState()
{
    //CoffeeMachineStatus
}

void QDomoticzController::pollServer()
{
    getScenes();
    getSwitches();
}

bool QDomoticzController::isInitialized()
{
    if (!m_backend) {
        qWarning() << "The backend is not initialized, use QDomoticzController::initialize().";
        return false;
    }
    return true;
}
