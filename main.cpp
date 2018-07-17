#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QCoreApplication::setOrganizationName("ReaverSoft");
    QCoreApplication::setOrganizationDomain("Reav.er");
    QCoreApplication::setApplicationName("GS");

    MainWindow w;
    w.setWindowIcon(QIcon(":/icon/coins.png"));

    w.show();



    return a.exec();
}
