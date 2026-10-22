#include "ProductList.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cctype>

using namespace std;

// Helper: case-insensitive substring check
static bool containsIgnoreCase(const string& haystack, const string& needle) {
    string h = haystack, n = needle;
    transform(h.begin(), h.end(), h.begin(), ::tolower);
    transform(n.begin(), n.end(), n.begin(), ::tolower);
    return h.find(n) != string::npos;
}

// Node
ProductListNode::ProductListNode(const Product& p) : data(p), next(nullptr) {}

// Constructor / Destructor
ProductList::ProductList() : head(nullptr) {}

ProductList::~ProductList() {
    ProductListNode* curr = head;
    while (curr) {
        ProductListNode* tmp = curr->next;
        delete curr;
        curr = tmp;
    }
    head = nullptr;
}

// Insert
void ProductList::insertFront(const Product& p) {
    ProductListNode* node = new ProductListNode(p);
    node->next = head;
    head = node;
}

// Delete
bool ProductList::deleteByID(const string& id) {
    if (!head) return false;

    // Special case: head matches
    if (head->data.id == id) {
        ProductListNode* tmp = head;
        head = head->next;
        delete tmp;
        return true;
    }

    ProductListNode* curr = head;
    while (curr->next) {
        if (curr->next->data.id == id) {
            ProductListNode* tmp = curr->next;
            curr->next = tmp->next;
            delete tmp;
            return true;
        }
        curr = curr->next;
    }
    return false;
}

// Update
bool ProductList::updateByID(const string& id, const Product& updated) {
    ProductListNode* curr = head;
    while (curr) {
        if (curr->data.id == id) {
            curr->data = updated;
            return true;
        }
        curr = curr->next;
    }
    return false;
}

// Search by ID (Linear Search O(n))
Product* ProductList::searchByID(const string& id) {
    ProductListNode* curr = head;
    while (curr) {
        if (curr->data.id == id) return &curr->data;
        curr = curr->next;
    }
    return nullptr;
}

// Search by Name
vector<Product*> ProductList::searchByName(const string& name) {
    vector<Product*> results;
    ProductListNode* curr = head;
    while (curr) {
        if (containsIgnoreCase(curr->data.name, name)) {
            results.push_back(&curr->data);
        }
        curr = curr->next;
    }
    return results;
}

// Display All
void ProductList::displayAll() const {
    if (!head) {
        cout << "\n  [!] No products available.\n";
        return;
    }
    cout << "\n  " << string(67, '-') << "\n";
    cout << "  " << left
         << setw(8)  << "ID"
         << setw(20) << "Name"
         << setw(15) << "Category"
         << setw(12) << "Price ($)"
         << setw(8)  << "Stock"
         << "\n";
    cout << "  " << string(67, '-') << "\n";

    ProductListNode* curr = head;
    while (curr) {
        const Product& p = curr->data;
        cout << "  " << left
             << setw(8)  << p.id
             << setw(20) << p.name
             << setw(15) << p.category
             << setw(12) << fixed << setprecision(2) << p.price
             << setw(8)  << p.quantity
             << "\n";
        curr = curr->next;
    }
    cout << "  " << string(67, '-') << "\n";
}

// To Vector
vector<Product> ProductList::toVector() const {
    vector<Product> v;
    ProductListNode* curr = head;
    while (curr) {
        v.push_back(curr->data);
        curr = curr->next;
    }
    return v;
}

// Helpers
bool ProductList::isEmpty() const { return head == nullptr; }

bool ProductList::idExists(const string& id) const {
    ProductListNode* curr = head;
    while (curr) {
        if (curr->data.id == id) return true;
        curr = curr->next;
    }
    return false;
}

int ProductList::count() const {
    int n = 0;
    ProductListNode* curr = head;
    while (curr) { ++n; curr = curr->next; }
    return n;
}
