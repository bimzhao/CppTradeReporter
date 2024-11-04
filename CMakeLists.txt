cmake_minimum_required(VERSION 3.25)
project(TradeReporter)

set(CMAKE_CXX_STANDARD 20)

add_executable(TradeReporter src/main.cpp
        src/TradeReporter.h
        src/Types.h
        src/Exchange.cpp
        src/Exchange.h
        src/OrderBook.cpp
        src/OrderBook.h
)
