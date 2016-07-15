#ifndef QDOMOTICZCONTROLLER_H_
#define QDOMOTICZCONTROLLER_H_

#include "QDomoticzBackend_global.h"

#include "DomoticzObjects.h"
#include <QObject>
#include <QMutex>

/**
 * @brief This class is a higher level interface to the Domoticz server,
 *        it contains a bunch of methods that allow you to easily retreive and send information
 *        to the Domoticz server.
 */

class QDomoticzBackend;
class QTimer;

class QDOMOTICZBACKENDSHARED_EXPORT QDomoticzController: public QObject
{
    Q_OBJECT
public:
    QDomoticzController(QObject *parent = 0);
    void initialize(QDomoticzBackend* backend = 0);

    void setTimer(bool status);

    void getScenes();
    void getAll();
    void getSwitches();

    void allLightsOff();


    // coffee machine methods
    enum CoffeeSize {
        Big,
        Small
    };

    enum CoffeeState {
        OK,
        Warning,
        Error
    };

    void makeACoffee(CoffeeSize size);
    void setCoffeeMachinePower(bool state);
    CoffeeState coffeeMachineState();



public Q_SLOTS:
    /**
     * @brief Poll the server for the devices status
     */
    void pollServer();

    void toggleSwitch(int ID, bool flag);
    void toggleScene(int ID, bool flag);


Q_SIGNALS:
    void switchesReceived(const QList<DomoticzObjects::Switch> &list);
    void scenesReceived(const QList<DomoticzObjects::Scene> &list);

private:
    bool isInitialized();

    QDomoticzBackend* m_backend;
    QTimer *m_pollTimer;
};

#endif // QDOMOTICZCONTROLLER_H_
