#ifndef ITEM_H
#define ITEM_H

#include "auction.h"
#include <vector>


struct Items
{
    bool active = false;
    std::vector<Auction> auctions;
};


#endif // ITEM_H
