#include <algorithm>
#include <QDate>
#include <QMutex>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "auction.h"
#include "secret.h"




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QStringList lab = { "Owner", "Bid", "Buyout", "G/P" ,"Quantity" };



    ui->twAuc->setHeaderLabels(lab);



    apiCaller = new ApiCaller(manager);

    QString vl = "VERY_LONG";
    QString l = "LONG";
    QString m = "MEDIUM";
    QString s = "SHORT";

    m_TMap[vl] = Timeleft::VERY_LONG;
    m_TMap[l] = Timeleft::LONG;
    m_TMap[m] = Timeleft::MEDIUM;
    m_TMap[s] = Timeleft::SHORT;



    getAH();





}

void MainWindow::getAH()
{
    QUrl url = QUrl("https://eu.api.battle.net/wow/auction/data/archimonde?locale=en_GB" + key);

    apiCaller->call(url,this,SLOT(handleAHUrl(QNetworkReply*)));
}


void MainWindow::handleAHUrl(QNetworkReply* reply)
{
    if(reply->error() == QNetworkReply::NoError)
    {
        QString m_str(reply->readAll());
        const QJsonObject  m_json = QJsonDocument::fromJson(m_str.toUtf8()).object();

        QUrl url = QUrl(m_json["files"][0]["url"].toString());

        qDebug() << url;

        apiCaller->call(url,this,SLOT(handleAH(QNetworkReply*)));


    }
    else
    {
        qDebug() << "api error ahu";
    }
}

void MainWindow::handleAH(QNetworkReply* reply)
{
    if(reply->error() == QNetworkReply::NoError)
    {
        QString m_str(reply->readAll());
        const QJsonObject  m_json = QJsonDocument::fromJson(m_str.toUtf8()).object();

        QJsonValue ja = m_json["auctions"];

        qDebug() << ja.toArray().size();

        //WARNING ja.toArray().size()
        for (int i=0; i<ja.toArray().size(); i++)
        {

            std::unordered_map<int,Items>::iterator got = listModel->find(ja[i]["item"].toInt());

            QJsonValue jo = ja[i];

            Auction a = Auction(jo["auc"].toInt(),
                    jo["item"].toInt(),
                    jo["owner"].toString(),
                    jo["ownerRealm"].toString(),
                    jo["bid"].toDouble(),
                    jo["buyout"].toDouble(),
                    jo["quantity"].toInt(),
                    timeMap(jo["timeLeft"].toString()));






            if ( got == listModel->getList().end() )
            {
                Items it;
                it.auctions.push_back(a);

                listModel->add(ja[i]["item"].toInt(),it);

            }
            else
            {
                got->second.auctions.push_back(a);


            }

            if(a.getOwner() == QString("Yloona"))
            {

                listModel->find(ja[i]["item"].toInt())->second.active = true;
            }


        }



        int i = 0;
        for(auto elem : listModel->getList())
        {
            if (!elem.second.active)
            {
                continue;
            }

            QTreeWidgetItem *tree= new QTreeWidgetItem();
            tree->setText(0,QString::number(elem.second.auctions[0].getId()));

            std::sort (elem.second.auctions.begin(), elem.second.auctions.end());

            for(auto auc : elem.second.auctions)
            {
                QTreeWidgetItem *subtree = new QTreeWidgetItem();

                subtree->setText(0,auc.getOwner());
                subtree->setText(1,Auction::goldFormat(auc.getBid()));
                subtree->setText(2,Auction::goldFormat(auc.getBuyout()));
                subtree->setText(3,Auction::goldFormat(auc.getBuyout()/auc.getQuantity()));
                subtree->setText(4,QString::number(auc.getQuantity()));

                subtree->setTextAlignment(1,Qt::AlignRight);
                subtree->setTextAlignment(2,Qt::AlignRight);
                subtree->setTextAlignment(3,Qt::AlignRight);
                subtree->setTextAlignment(4,Qt::AlignHCenter);

                tree->addChild(subtree);
            }

            ui->twAuc->insertTopLevelItem(i,tree);

            i++;
        }


    }
    else
    {
        qDebug() << "api error ah";
    }
}

Timeleft MainWindow::timeMap(QString time)
{
    return m_TMap.value(time);
}


MainWindow::~MainWindow()
{
    delete ui;
}


