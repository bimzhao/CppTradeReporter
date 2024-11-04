#pragma once
#include "TradeReporter.h"
#include "Types.h"

using namespace std;

namespace LOB {

    template <typename T, size_t RESERVED_SIZE>
    struct pool
    {
        pool()
        {
            _allocatedPool.reserve(RESERVED_SIZE);
            for (size_t i = 0; i < RESERVED_SIZE; ++i)
            {
                _allocatedPool.emplace_back(std::make_unique<T>());
                _availablePool.emplace_back(_allocatedPool.back().get());
            }
        }

        ~pool()
        {
            _allocatedPool.clear();
            _availablePool.clear();
        }

        std::shared_ptr<T> alloc()
        {
            if (!_availablePool.empty())
            {
                T* obj = _availablePool.back();
                _availablePool.pop_back();
                //cout << "allocate from pool:" << _availablePool.size() << endl;
                return std::shared_ptr<T>(obj, [this](T* ptr) { _availablePool.emplace_back(ptr); });
            }
            else
            {
                return std::make_shared<T>();
            }
        }

    private:
        std::vector<std::unique_ptr<T>> _allocatedPool; //TODO: maintain a free vector to reuse deleted level
        std::vector<T*> _availablePool;
    };

    class OrderBook {
    public:
        static constexpr size_t NUM_LEVELS = 1 << 1;  //NOTE: just for this purpose
        using levelVector = pool<PriceLevel, NUM_LEVELS>;
        levelVector _levelsPool;

        OrderBook(TradeReporter &reporter) : _tradeReporter(reporter) {}
        void addOrder(const OrderPtr &order, bool isBuy);
        void removeOrder(const OrderId &id);
        void modifyOrder(OrderId id, OrderId origId, Price price, Quantity quantity, bool isBuy);

    private:
        void addOrderToPriceLevel(const OrderPtr &order, bool isBuy);
        //void removeOrderFromPriceLevel(PriceLevelPtr priceLevel, OrderPtr order);
        OrderPtr findOrder(const OrderId &id);

        PriceLevelPtr _buyHead = nullptr;  // Head of the buy price levels
        PriceLevelPtr _sellHead = nullptr;  // Head of the sell price levels
        std::unordered_map<OrderId, OrderPtr> _orderMap; // To quickly find orders by ID
        //std::map<Price, PriceLevelPtr> _priceLevelMap; // To quickly find price levels by price
        TradeReporter &_tradeReporter; //Test.cpp will have any subclassd eg. TradeRecorder to inject here
    };
}
