#include "auction.h"
#include "tools.h"
#include <QDebug>
#include <cmath>


Auction::Auction(int aucId,int itemId,QString owner,QString ownerRealm,double bid, double buyout,int quantity,Timeleft timeleft)
:m_AucId(aucId),m_ItemId(itemId),m_Owner(owner),m_OwnerRealm(ownerRealm),m_Bid(bid),m_Buyout(buyout),m_Quantity(quantity),m_Timeleft(timeleft)
{

}


int Auction::getId()
{
    return m_ItemId;
}

QString Auction::getOwner()
{
    return m_Owner;
}

double Auction::getBid()
{
    return m_Bid;
}

double Auction::getBuyout()
{
    return m_Buyout   ;
}

int Auction::getQuantity()
{
    return m_Quantity;
}

bool Auction::operator< (Auction i)
{
    return (this->getBuyout()<i.getBuyout());
}

QString Auction::goldFormat(double gold)
{
    QString str;

    if((gold / 10000) < 10)
    {
        str.append("0");
    }

    str.append(QString::number(floor(gold / 10000)));


    gold -= floor(gold / 10000) * 10000;

    str.append("'");

    if((gold / 100) < 10)
    {
        str.append("0");
    }

    str.append(QString::number(floor(gold / 100)));

    gold -= floor(gold / 100) * 100;

    str.append("'");

    if(gold < 10)
    {
        str.append("0");
    }

    str.append(QString::number(gold));


    str.append("");

    return str;
}





