#pragma once
#include <string>

using namespace std;

// Order status enum
enum class OrderStatus { Pending, Completed, Cancelled };

// Convert enum to string
inline string orderStatusToString(OrderStatus s) {
    switch (s) {
        case OrderStatus::Pending:   return "Pending";
        case OrderStatus::Completed: return "Completed";
        case OrderStatus::Cancelled: return "Cancelled";
    }
    return "Unknown";
}

// Convert string back to enum
inline OrderStatus stringToOrderStatus(const string& s) {
    if (s == "Completed") return OrderStatus::Completed;
    if (s == "Cancelled") return OrderStatus::Cancelled;
    return OrderStatus::Pending;
}

// Order model
struct Order {
    string      orderID;
    string      customerID;
    string      productID;
    string      productNameSnapshot;
    int         qty;
    double      unitPrice;
    double      totalPrice;
    OrderStatus status;

    Order() : qty(0), unitPrice(0.0), totalPrice(0.0), status(OrderStatus::Pending) {}

    Order(const string& oid, const string& cid,
          const string& pid, const string& snap,
          int qty_, double unitPrice_,
          OrderStatus status_ = OrderStatus::Pending)
        : orderID(oid), customerID(cid), productID(pid),
          productNameSnapshot(snap), qty(qty_), unitPrice(unitPrice_),
          totalPrice(unitPrice_ * qty_), status(status_) {}
};
