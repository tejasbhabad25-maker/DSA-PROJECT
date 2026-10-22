#pragma once
#include <string>

using namespace std;

void viewProducts();
void searchCustomerProduct();
void placeOrder(const string& customerID);
void viewMyOrders(const string& customerID);
void cancelOrder(const string& customerID);
