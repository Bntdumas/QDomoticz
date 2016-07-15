#include "QDomoticzTest.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QDomoticzTest testApp;
    testApp.exec();
    return a.exec();
}
