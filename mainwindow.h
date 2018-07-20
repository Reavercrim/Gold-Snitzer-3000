#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QMap>

#include "apimanager.h"
#include "tools.h"
#include "auction.h"
#include "items.h"
#include "listmodel.h"




namespace Ui {


class MainWindow;
}



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void getAH();
    Timeleft timeMap(QString time);

public slots:
    void handleAHUrl(QNetworkReply *reply);
    void handleAH(QNetworkReply *reply);

private:
    Ui::MainWindow *ui;
    QNetworkAccessManager *manager = new QNetworkAccessManager();
    ApiCaller* apiCaller;
    QMap<QString,Timeleft> m_TMap;

    ListModel* listModel = new ListModel(this);
};



#endif // MAINWINDOW_H
