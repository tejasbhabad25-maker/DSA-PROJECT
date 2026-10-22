#pragma once
#include "../MODELS/Product.h"
#include <vector>
#include <string>

using namespace std;

// Node of the singly linked list
struct ProductListNode {
    Product          data;
    ProductListNode* next;
    explicit ProductListNode(const Product& p);
};

// Custom Singly Linked List for product management
class ProductList {
private:
    ProductListNode* head;

public:
    ProductList();
    ~ProductList();

    // O(1): insert at head
    void insertFront(const Product& p);

    // O(n): traverse and unlink the matching node
    bool deleteByID(const string& id);

    // O(n): traverse and overwrite data of matching node
    bool updateByID(const string& id, const Product& updated);

    // Linear Search — O(n)
    Product*         searchByID(const string& id);
    vector<Product*> searchByName(const string& name);

    // Display all products in a formatted table
    void displayAll() const;

    // Returns a copy as a vector (used by Sorting)
    vector<Product> toVector() const;

    bool isEmpty() const;
    bool idExists(const string& id) const;
    int  count() const;
};
