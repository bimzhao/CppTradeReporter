#include "Exchange.h"


namespace LOB {

//TODO: if we have symbol list to maintain
//orderBook *orderBook::s_books = new orderBook[order_book::MAX_BOOKS];

Exchange::Exchange(TradeReporter & reporter)
: _orderBookPtr(std::make_shared<OrderBook>(reporter))
{}

void Exchange::on_add(OrderId id, Side side, Price price, Quantity quantity)
{
    bool isBuy = (side == Side::Bid);
    auto order = std::make_shared<Order>(id, price, quantity);
    _orderBookPtr->addOrder(order, isBuy);
}

void Exchange::on_delete(OrderId id)
{
    _orderBookPtr->removeOrder(id);
}

void Exchange::on_modify(OrderId id, OrderId origId, Side side, Price price, Quantity quantity)
{
    bool isBuy = (side == Side::Bid);
    _orderBookPtr->modifyOrder(id, origId, price, quantity, isBuy);
}

}
