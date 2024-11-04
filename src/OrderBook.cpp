#include "OrderBook.h"
#include "Types.h"



namespace LOB {

    void OrderBook::addOrder(const OrderPtr &order, bool isBuy) {
        auto oppositeHead = isBuy ? _sellHead : _buyHead;
        PriceLevelPtr prev = nullptr;
        Price price = order->_price;
        for (auto level = oppositeHead; level && order->_qty > 0;)
        {
            if ((isBuy && order->_price >= level->_price) || (!isBuy && order->_price <= level->_price))
            {
                auto &orderList = level->_orders;
                while (!orderList.empty() && order->_qty > 0)
                {
                    auto matchOrder = orderList.front();
                    if (!matchOrder || matchOrder->_isDeleted)
                    {
                        orderList.erase(orderList.begin());
                        continue;
                    }

                    Quantity quantity = std::min(order->_qty, matchOrder->_qty);
                    _tradeReporter.on_trade(matchOrder->_id, matchOrder->_price, quantity);  //price is resting order price
                    _tradeReporter.on_trade(order->_id, matchOrder->_price, quantity);

                    order->_qty -= quantity;
                    matchOrder->_qty -= quantity;

                    if (matchOrder->_qty == 0)
                    {
                        //matchOrder->_isDeleted = true; //doesn't matter
                        orderList.erase(orderList.begin()); //NOTE: sometime we wanted to keep inactive order record
                        _orderMap.erase(matchOrder->_id);
                    }
                }

                //TODO: can have a timer to cleanup
                if (orderList.empty())
                {
                    //remove current PriceLevel
                    auto next = level->_next;
                    if (level == oppositeHead) //shall always opposite head as remove from top
                    {
                        oppositeHead = level->_next;
                    }
                    else
                    {
                        cout << "WARNING: removing non-top of book" << endl;
                    }

                    level = next;
                }
                else
                {
                    prev = level; //not nullptr now
                    level = level->_next;
                }
            }
            else //never hit this, just in case
                break;
        }

        // remaining add to the same side book
        if (order->_qty > 0)
        {
            addOrderToPriceLevel(order, isBuy);
            _orderMap[order->_id] = order;
        }
    }

    void OrderBook::addOrderToPriceLevel(const OrderPtr &order, bool isBuy)
    {
        Price price = order->_price;
        bool isFound = false;

        if (isBuy)
        {
            // Insert in the buy linked list
            if (!_buyHead || order->_price > _buyHead->_price)
            {
                //isFound = true;
                auto newPriceLevel = _levelsPool.alloc();
                newPriceLevel->insertFirstToPriceLevel(order);
                newPriceLevel->_next = _buyHead;
                _buyHead = newPriceLevel;
                return;
            }
            else //_buyHead not nullptr
            {        // try to find insertionPoint in the linked list which is prev level of current order's level
                auto insertionPoint = _buyHead;
                auto nextPoint = _buyHead->_next;
                while (insertionPoint) //need test this line
                {
                    if (order->_price == insertionPoint->_price)
                    {
                        isFound = true;
                        break;
                    }
                    else if (!nextPoint || order->_price > nextPoint->_price)
                    {
                        break;
                    }

                    if (insertionPoint->_next)
                    {//insertionPoint cannot be nullptr
                        insertionPoint = insertionPoint->_next;
                        nextPoint = insertionPoint->_next;
                    }
                    else  //shall never hit
                        break;
                }

                if (isFound)
                {
                    insertionPoint->_orders.emplace_back(order);;
                }
                else // not found
                {
                    auto newPriceLevel = _levelsPool.alloc();
                    newPriceLevel->insertFirstToPriceLevel(order);
                    insertionPoint->_next = newPriceLevel;
                    newPriceLevel->_next = nextPoint;
                }
            }
        }
        else
        {
            // Insert in the sell linked list
            if (!_sellHead || order->_price < _sellHead->_price)
            {
                //isFound = true;
                auto newPriceLevel = _levelsPool.alloc();
                newPriceLevel->insertFirstToPriceLevel(order);
                newPriceLevel->_next = _sellHead;
                _sellHead = newPriceLevel;
                return;
            }
            else
            {        // try to find insertionPoint in the linked list which is prev level of current order's level
                auto insertionPoint = _sellHead;
                auto nextPoint = _sellHead->_next;
                while (insertionPoint) //need test this line
                {
                    if (order->_price == insertionPoint->_price)
                    {
                        isFound = true;
                        break;
                    }
                    else if (!nextPoint || order->_price < nextPoint->_price)
                    {
                        break;
                    }

                    if (insertionPoint->_next)
                    {//insertionPoint cannot be nullptr
                        insertionPoint = insertionPoint->_next;
                        nextPoint = insertionPoint->_next;
                    }
                    else
                        break;
                }

                if (isFound)
                {
                    insertionPoint->_orders.emplace_back(order);;
                }
                else // not found
                {
                    auto newPriceLevel = _levelsPool.alloc();
                    newPriceLevel->insertFirstToPriceLevel(order);
                    insertionPoint->_next = newPriceLevel;
                    newPriceLevel->_next = nextPoint;
                }
            }
        }
    }

    void OrderBook::removeOrder(const OrderId &id)
    {
        auto order = findOrder(id);
        if (order)
        {
            order->_isDeleted = true;
            _orderMap.erase(id);
        }
        else
        {
            cout << "WARNING: cannot find order:" << id << endl;
        }
    }

    void OrderBook::modifyOrder(OrderId id, OrderId origId, Price price, Quantity quantity, bool isBuy)
    {
        auto order = findOrder(origId);
        if (order) //change orderId, price, quantity and move level if needed
        {
            _orderMap.erase(id); //remove the old id anyway
            order->_id = id;
            order->_qty = quantity;
            if ( order->_price != price ) //NOTE: if price change, need move level, now price is int, need change if double
            {
                order->_price = price;
                //move book level
            }
        }
        else
        {
            cout << "modifyOrder WARNING: cannot find order:" << id << endl;
        }
    }

    OrderPtr OrderBook::findOrder(const OrderId &id)
    {
        auto it = _orderMap.find(id);
        if (it != _orderMap.end())
            return it->second;

        return nullptr;
    }


}