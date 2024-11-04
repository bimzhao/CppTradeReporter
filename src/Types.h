#pragma once

#include <memory>
#include <ctime>
#include <vector>
#include <cstddef>
#include <map>
#include <stack>
#include <unordered_map>
#include <iostream>

namespace LOB {

    using OrderId = unsigned long;
    using Price = int;
    using Quantity = unsigned int;

    enum class Side {Bid, Ask};

    struct Order {
        Order(OrderId id, Price price, Quantity quantity)
        : _id(id), _price(price), _qty(quantity), _isDeleted(false) {}

        OrderId _id;
        Price _price;
        Quantity _qty;
        bool _isDeleted; // Flag to mark orders as deleted
    };

    using OrderPtr = std::shared_ptr<Order>;

    struct PriceLevel {
        PriceLevel(Price price = 0, size_t capacity = 100)
                : _price(price), _orders(), _next(nullptr)
        {
            _orders.reserve(capacity); // Pre-allocate memory
        }

        void insertFirstToPriceLevel(OrderPtr order, size_t capacity = 100)
        {
            _price = order->_price;
            _orders.clear();
            _orders.reserve(capacity);
            _orders.emplace_back(order);
        }

        Price _price;
        std::vector<OrderPtr> _orders; // Vector of orders at this price level
        std::shared_ptr<PriceLevel> _next; // Next price level
    };

    using PriceLevelPtr = std::shared_ptr<PriceLevel>;

}

