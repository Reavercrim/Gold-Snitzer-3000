#ifndef AUCTION_H
#define AUCTION_H

#include <QString>

#include "tools.h"

class Auction
{
public:
    Auction(int aucId,int itemId,QString owner,QString ownerRealm,double bid,double buyout,int quantity,Timeleft timeleft);

    int getId();
    QString getOwner();
    double getBid();
    double getBuyout();
    int getQuantity();

    bool operator< (const Auction i);

    static QString goldFormat(double gold);

private:
    int m_AucId;
    int m_ItemId;
    QString m_Owner;
    QString m_OwnerRealm;
    double m_Bid;
    double m_Buyout;
    int m_Quantity;
    Timeleft m_Timeleft;




};




#endif // AUCTION_H
