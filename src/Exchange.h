#pragma once


#include "TradeReporter.h"
#include "Types.h"
#include "OrderBook.h"

using namespace std;

namespace LOB
{

class Exchange
{
public:
    explicit Exchange(TradeReporter & reporter);
    void on_add(OrderId id, Side side, Price price, Quantity quantity);
    void on_delete(OrderId id);
    void on_modify(OrderId id, OrderId origId, Side side, Price price, Quantity quantity);

private:
    std::shared_ptr<OrderBook> _orderBookPtr;
};


}
