#include "filehandler.h"
#include "globals.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

// Split line using stringstream and delimiter
static vector<string> splitLine(const string& line, char delimiter = ',') {
    vector<string> tokens;
    string token;
    stringstream ss(line);
    while (getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

// Extract numeric portion from ID string (e.g. "P005" -> 5)
static int extractNumericID(const string& id, size_t prefixLen) {
    if (id.length() <= prefixLen) return 0;
    try {
        return stoi(id.substr(prefixLen));
    } catch (...) {
        return 0;
    }
}

// ==============================================================================
// PRODUCTS (products.txt)
// ==============================================================================

void loadProducts() {
    ifstream f(PRODUCTS_FILE);
    if (!f.is_open()) return;

    string line;
    int maxID = 0;
    while (getline(f, line)) {
        if (line.empty()) continue;
        vector<string> tokens = splitLine(line, ',');
        if (tokens.size() < 5) continue;
        try {
            Product p(tokens[0], tokens[1], tokens[2], stod(tokens[3]), stoi(tokens[4]));
            if (!gProductList.idExists(p.id)) {
                gProductList.insertFront(p);
                int n = extractNumericID(p.id, 1); // prefix 'P'
                maxID = max(maxID, n);
            }
        } catch (...) {}
    }
    if (maxID >= gNextProductID) {
        gNextProductID = maxID + 1;
    }
}

void saveProducts() {
    ofstream f(PRODUCTS_FILE);
    if (!f.is_open()) {
        cerr << "[Error] Cannot write to: " << PRODUCTS_FILE << endl;
        return;
    }
    for (const auto& p : gProductList.toVector()) {
        f << p.id << ","
          << p.name << ","
          << p.category << ","
          << fixed << setprecision(2) << p.price << ","
          << p.quantity << "\n";
    }
}

// ==============================================================================
// USERS (users.txt)
// ==============================================================================

void loadUsers() {
    ifstream f(USERS_FILE);
    if (!f.is_open()) return;

    string line;
    int maxID = 0;
    while (getline(f, line)) {
        if (line.empty()) continue;
        vector<string> tokens = splitLine(line, ',');
        if (tokens.size() < 4) continue;
        try {
            Customer c(tokens[0], tokens[1], tokens[2], tokens[3]);
            if (!gCustomerTable.isDuplicate(c.customerID)) {
                gCustomerTable.insert(c);
                int n = extractNumericID(c.customerID, 1); // prefix 'C'
                maxID = max(maxID, n);
            }
        } catch (...) {}
    }
    if (maxID >= gNextCustomerID) {
        gNextCustomerID = maxID + 1;
    }
}

void saveUsers() {
    ofstream f(USERS_FILE);
    if (!f.is_open()) {
        cerr << "[Error] Cannot write to: " << USERS_FILE << endl;
        return;
    }
    for (const auto& c : gCustomerTable.getAllCustomers()) {
        f << c.customerID << ","
          << c.name << ","
          << c.email << ","
          << c.password << "\n";
    }
}

// ==============================================================================
// ORDERS (orders.txt)
// ==============================================================================

void loadOrders() {
    ifstream f(ORDERS_FILE);
    if (!f.is_open()) return;

    string line;
    int maxID = 0;
    while (getline(f, line)) {
        if (line.empty()) continue;
        vector<string> tokens = splitLine(line, ',');
        if (tokens.size() < 8) continue;
        try {
            Order o;
            o.orderID             = tokens[0];
            o.customerID          = tokens[1];
            o.productID           = tokens[2];
            o.productNameSnapshot = tokens[3];
            o.qty                 = stoi(tokens[4]);
            o.unitPrice           = stod(tokens[5]);
            o.totalPrice          = stod(tokens[6]);
            o.status              = stringToOrderStatus(tokens[7]);

            gOrderHistory.push_back(o);

            // Add pending orders back into FIFO queue
            if (o.status == OrderStatus::Pending) {
                gOrderQueue.enqueue(o);
            }

            int n = extractNumericID(o.orderID, 3); // prefix 'ORD'
            maxID = max(maxID, n);
        } catch (...) {}
    }
    if (maxID >= gNextOrderID) {
        gNextOrderID = maxID + 1;
    }
}

void saveOrders() {
    ofstream f(ORDERS_FILE);
    if (!f.is_open()) {
        cerr << "[Error] Cannot write to: " << ORDERS_FILE << endl;
        return;
    }
    for (const auto& o : gOrderHistory) {
        f << o.orderID             << ","
          << o.customerID          << ","
          << o.productID           << ","
          << o.productNameSnapshot << ","
          << o.qty                 << ","
          << fixed << setprecision(2) << o.unitPrice << ","
          << fixed << setprecision(2) << o.totalPrice << ","
          << orderStatusToString(o.status) << "\n";
    }
}
