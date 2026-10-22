#include "OrderQueue.h"
#include <iostream>
#include <iomanip>

using namespace std;

// Node
OrderQueueNode::OrderQueueNode(const Order& o) : data(o), next(nullptr) {}

// Constructor / Destructor
OrderQueue::OrderQueue() : front(nullptr), rear(nullptr), queueSize(0) {}

OrderQueue::~OrderQueue() {
    OrderQueueNode* curr = front;
    while (curr) {
        OrderQueueNode* tmp = curr->next;
        delete curr;
        curr = tmp;
    }
    front = rear = nullptr;
}

// Enqueue O(1)
void OrderQueue::enqueue(const Order& o) {
    OrderQueueNode* node = new OrderQueueNode(o);
    if (!rear) {
        front = rear = node;
    } else {
        rear->next = node;
        rear = node;
    }
    ++queueSize;
}

// Dequeue O(1)
bool OrderQueue::dequeue() {
    if (!front) return false;
    OrderQueueNode* tmp = front;
    front = front->next;
    if (!front) rear = nullptr;
    delete tmp;
    --queueSize;
    return true;
}

// Remove by Order ID O(n)
bool OrderQueue::removeByOrderID(const string& orderID) {
    if (!front) return false;

    // Head matches
    if (front->data.orderID == orderID) {
        return dequeue();
    }

    // Traverse
    OrderQueueNode* curr = front;
    while (curr->next) {
        if (curr->next->data.orderID == orderID) {
            OrderQueueNode* tmp = curr->next;
            curr->next = tmp->next;
            if (tmp == rear) rear = curr;
            delete tmp;
            --queueSize;
            return true;
        }
        curr = curr->next;
    }
    return false;
}

// Display Pending
void OrderQueue::displayPending() const {
    if (!front) {
        cout << "\n  [!] No pending orders in queue.\n";
        return;
    }
    cout << "\n  Pending Orders Queue (FIFO — first placed = first listed):\n";
    cout << "  " << string(74, '-') << "\n";
    cout << "  " << left
         << setw(10) << "OrderID"
         << setw(12) << "CustomerID"
         << setw(10) << "ProductID"
         << setw(20) << "Product"
         << setw(6)  << "Qty"
         << setw(12) << "Total ($)"
         << "\n";
    cout << "  " << string(74, '-') << "\n";

    OrderQueueNode* curr = front;
    while (curr) {
        const Order& o = curr->data;
        cout << "  " << left
             << setw(10) << o.orderID
             << setw(12) << o.customerID
             << setw(10) << o.productID
             << setw(20) << o.productNameSnapshot
             << setw(6)  << o.qty
             << setw(12) << fixed << setprecision(2) << o.totalPrice
             << "\n";
        curr = curr->next;
    }
    cout << "  " << string(74, '-') << "\n";
}

bool OrderQueue::isEmpty() const { return front == nullptr; }
int  OrderQueue::size()    const { return queueSize; }
