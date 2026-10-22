#include "CustomerHashTable.h"

using namespace std;

CustomerHashTable::CustomerHashTable() {}

// Hash Function: sum of digits % TABLE_SIZE
int CustomerHashTable::hashFunction(const string& customerID) const {
    int sum = 0;
    for (char c : customerID) {
        if (c >= '0' && c <= '9') sum += (c - '0');
    }
    return sum % TABLE_SIZE;
}

// Insert O(1) average
bool CustomerHashTable::insert(const Customer& c) {
    if (isDuplicate(c.customerID)) return false;
    int idx = hashFunction(c.customerID);
    table[idx].push_back(c);
    return true;
}

// Search O(1) average
Customer* CustomerHashTable::search(const string& customerID) {
    int idx = hashFunction(customerID);
    for (Customer& c : table[idx]) {
        if (c.customerID == customerID) return &c;
    }
    return nullptr;
}

// Duplicate Check
bool CustomerHashTable::isDuplicate(const string& customerID) const {
    int idx = hashFunction(customerID);
    for (const Customer& c : table[idx]) {
        if (c.customerID == customerID) return true;
    }
    return false;
}

// Get All Customers
vector<Customer> CustomerHashTable::getAllCustomers() const {
    vector<Customer> all;
    for (int i = 0; i < TABLE_SIZE; ++i) {
        for (const Customer& c : table[i]) {
            all.push_back(c);
        }
    }
    return all;
}
