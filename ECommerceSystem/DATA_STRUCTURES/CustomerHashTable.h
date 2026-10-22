#pragma once
#include "../MODELS/Customer.h"
#include <vector>
#include <string>

using namespace std;

const int TABLE_SIZE = 101;

// Hash Table with Separate Chaining for Customer/User lookup
class CustomerHashTable {
private:
    vector<Customer> table[TABLE_SIZE];

    int hashFunction(const string& customerID) const;

public:
    CustomerHashTable();

    bool insert(const Customer& c);
    Customer* search(const string& customerID);
    bool isDuplicate(const string& customerID) const;
    vector<Customer> getAllCustomers() const;
};
