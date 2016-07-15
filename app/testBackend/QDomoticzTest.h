#ifndef QDOMOTICZTEST_H
#define QDOMOTICZTEST_H

#include <QDialog>

namespace Ui {
class QDomoticzTest;
}

class ScenesModel;
class SwitchesModel;
class QDomoticzController;

class QDomoticzTest : public QDialog
{
    Q_OBJECT

public:
    explicit QDomoticzTest(QWidget *parent = 0);
    ~QDomoticzTest();

private:
    Ui::QDomoticzTest *ui;
    ScenesModel *m_sceneModel;
    SwitchesModel *m_switchesModel;
    QDomoticzController *m_controller;

};

#endif // QDOMOTICZTEST_H
