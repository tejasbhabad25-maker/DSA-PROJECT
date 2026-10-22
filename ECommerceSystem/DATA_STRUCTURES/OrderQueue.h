#pragma once
#include "../MODELS/Order.h"
#include <string>

using namespace std;

// Node of the FIFO queue
struct OrderQueueNode {
    Order           data;
    OrderQueueNode* next;
    explicit OrderQueueNode(const Order& o);
};

// Custom FIFO Queue for pending order processing
class OrderQueue {
private:
    OrderQueueNode* front;
    OrderQueueNode* rear;
    int             queueSize;

public:
    OrderQueue();
    ~OrderQueue();

    void enqueue(const Order& o);   // O(1)
    bool dequeue();                 // O(1)
    bool removeByOrderID(const string& orderID); // O(n)

    void displayPending() const;
    bool isEmpty() const;
    int  size() const;
};
