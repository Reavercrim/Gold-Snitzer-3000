#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "apimanager.h"
#include "tools.h"
#include "auction.h"
#include "items.h"

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QMap>


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

    std::unordered_map<int,Items> model;


};



#endif // MAINWINDOW_H
