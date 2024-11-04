#include "Exchange.h"
#include "Types.h"
#include "TradeReporter.h"

using namespace LOB;

class CoutTradeReporter : public TradeReporter {
public:
    virtual void on_trade(OrderId order_id, Price price, Quantity quantity) override {
        std::cout << "Trade report: BuyOrderID = " << order_id
                  << ", Price = " << price
                  << ", Quantity = " << quantity << std::endl;
    }
};

int main() {


    //test1
//    {
//        CoutTradeReporter reporter;
//        LOB::Exchange exchange(reporter);
//        exchange.on_add(1, LOB::Side::Bid, 150, 10);
//        exchange.on_add(2, LOB::Side::Bid, 150, 50);
//        exchange.on_add(3, LOB::Side::Bid, 155, 20);
//        exchange.on_add(4, LOB::Side::Ask, 140, 1000);
//    }
    cout << "------------------------------------------------" << endl;

//    {
//        CoutTradeReporter reporter;
//        LOB::Exchange exchange(reporter);
//        exchange.on_add(1, LOB::Side::Ask, 71, 10);
//        exchange.on_add(3, LOB::Side::Ask, 70, 50);
//        exchange.on_add(2, LOB::Side::Ask, 70, 20);
//        exchange.on_add(4, LOB::Side::Bid, 75, 100);
//        exchange.on_add(4, LOB::Side::Ask, 69, 2000);
//    }
 //       cout << "------------------------------------------------" << endl;

//    {
//        CoutTradeReporter reporter;
//        LOB::Exchange exchange(reporter);
//        exchange.on_add(1, LOB::Side::Ask, 71, 10);
//        exchange.on_add(3, LOB::Side::Ask, 70, 50);
//        exchange.on_add(2, LOB::Side::Ask, 70, 20);
//        exchange.on_add(4, LOB::Side::Bid, 75, 1000);
//       // exchange.on_add(4, LOB::Side::Ask, 69, 2000);
//    }
//
//    cout << "------------------------------------------------" << endl;
//    {
//        CoutTradeReporter reporter;
//        LOB::Exchange exchange(reporter);
//        exchange.on_add(1, LOB::Side::Ask, 71, 10);
//        exchange.on_add(3, LOB::Side::Ask, 70, 50);
//        exchange.on_add(2, LOB::Side::Ask, 70, 20);
//        exchange.on_add(4, LOB::Side::Bid, 70, 85);
//        exchange.on_add(666, LOB::Side::Ask, 69, 20);
//        exchange.on_add(666, LOB::Side::Bid, 69, 15);
//        // exchange.on_add(4, LOB::Side::Ask, 69, 2000);
//    }
//    cout << "------------------------------------------------" << endl;
//    //exchange.on_delete(1);
//    {
//        CoutTradeReporter reporter;
//        LOB::Exchange exchange(reporter);
//        exchange.on_add(1, LOB::Side::Bid, 140, 10);
//        exchange.on_add(2, LOB::Side::Bid, 150, 50);
//        exchange.on_add(3, LOB::Side::Bid, 140, 20);
//        exchange.on_add(4, LOB::Side::Ask, 140, 1000);
//        exchange.on_add(5, LOB::Side::Bid, 140, 1000);
//    }
//
//    cout << "------------------------------------------------" << endl;
//    //exchange.on_delete(1);
//    {
//        CoutTradeReporter reporter;
//        LOB::Exchange exchange(reporter);
//        exchange.on_add(1, LOB::Side::Bid, 140, 10);
//        exchange.on_add(2, LOB::Side::Bid, 150, 50);
//        exchange.on_add(3, LOB::Side::Bid, 140, 20);
//        exchange.on_add(4, LOB::Side::Ask, 140, 1000);
//        exchange.on_delete(3);
//        exchange.on_add(5, LOB::Side::Bid, 140, 1000);
//    }






    cout << "------------------------------------------------" << endl;
    //exchange.on_delete(1);
//    {
//        CoutTradeReporter reporter;
//        LOB::Exchange exchange(reporter);
//        exchange.on_add(1, LOB::Side::Ask, 140, 10);
//        exchange.on_add(2, LOB::Side::Ask, 150, 50);
//        exchange.on_add(3, LOB::Side::Ask, 145, 20);
//        exchange.on_add(8, LOB::Side::Ask, 145, 6);
//        exchange.on_add(9, LOB::Side::Ask, 150, 5);
//        exchange.on_add(10, LOB::Side::Ask, 140, 7);
//        exchange.on_add(4, LOB::Side::Bid, 150, 1000);
//        exchange.on_delete(4);
//        exchange.on_add(5, LOB::Side::Ask, 140, 1000);
//    }
    cout << "------------------------------------------------" << endl;
    {
        CoutTradeReporter reporter;
        LOB::Exchange exchange(reporter);
        exchange.on_add(1, LOB::Side::Bid, 160, 10);
        exchange.on_add(2, LOB::Side::Bid, 150, 50);
        exchange.on_add(3, LOB::Side::Bid, 155, 20);
        exchange.on_add(6, LOB::Side::Bid, 150, 5);
        exchange.on_add(7, LOB::Side::Bid, 160, 6);
        exchange.on_add(8, LOB::Side::Bid, 155, 7);
        exchange.on_add(4, LOB::Side::Ask, 150, 1000);
        exchange.on_delete(3);
        exchange.on_delete(4);
        exchange.on_add(5, LOB::Side::Bid, 150, 1000);
    }
    return 0;
}
