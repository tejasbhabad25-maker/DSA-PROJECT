#pragma once
#include "../DATA_STRUCTURES/ProductList.h"
#include "../DATA_STRUCTURES/OrderQueue.h"
#include "../DATA_STRUCTURES/CustomerHashTable.h"
#include "../MODELS/Order.h"
#include <vector>
#include <string>
#include <cstdio>

using namespace std;

// Global application state declarations
extern ProductList        gProductList;
extern CustomerHashTable  gCustomerTable;
extern OrderQueue         gOrderQueue;
extern vector<Order>      gOrderHistory;
extern int                gNextOrderID;
extern int                gNextProductID;
extern int                gNextCustomerID;

// ID Formatting Helpers
inline string formatProductID(int n) {
    char buf[8];
    snprintf(buf, sizeof(buf), "P%03d", n);
    return string(buf);
}

inline string formatCustomerID(int n) {
    char buf[8];
    snprintf(buf, sizeof(buf), "C%03d", n);
    return string(buf);
}

inline string formatOrderID(int n) {
    char buf[10];
    snprintf(buf, sizeof(buf), "ORD%03d", n);
    return string(buf);
}
