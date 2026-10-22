#pragma once
#include <string>

using namespace std;

// User operations functions called from options_user.cpp
void viewProducts();
void searchUserProduct();
void placeOrder(const string& customerID);
void viewMyOrders(const string& customerID);
void cancelOrder(const string& customerID);
