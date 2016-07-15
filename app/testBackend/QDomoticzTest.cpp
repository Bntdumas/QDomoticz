#include "QDomoticzTest.h"
#include "QDomoticzController.h"
#include "ScenesModel.h"
#include "SwitchesModel.h"
#include "ui_QDomoticzTest.h"


QDomoticzTest::QDomoticzTest(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QDomoticzTest)
{
    ui->setupUi(this);
    m_controller = new QDomoticzController(this);
    m_controller->initialize();
    m_controller->setTimer(true);

    m_sceneModel = new ScenesModel(this);
    m_switchesModel = new SwitchesModel(this);

    connect(m_controller, &QDomoticzController::scenesReceived, m_sceneModel, &ScenesModel::updateScenes);
    connect(m_controller, &QDomoticzController::switchesReceived, m_switchesModel, &SwitchesModel::updateSwitches);
    connect(m_switchesModel, &SwitchesModel::setSwitch, m_controller, &QDomoticzController::toggleSwitch);
    connect(m_sceneModel, &ScenesModel::setScene, m_controller, &QDomoticzController::toggleScene);

    ui->tableScenes->setModel(m_sceneModel);
    ui->tableSwitches->setModel(m_switchesModel);
}

QDomoticzTest::~QDomoticzTest()
{
    delete ui;
}

