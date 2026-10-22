#pragma once
#include <string>

using namespace std;

// Text File Paths for Database Storage
inline const string PRODUCTS_FILE = "FILES/products.txt";
inline const string USERS_FILE    = "FILES/users.txt";
inline const string ORDERS_FILE   = "FILES/orders.txt";

// Data loading functions (load from text files into memory on startup)
void loadProducts();
void loadUsers();
void loadOrders();

// Data persistence functions (save in-memory structures to text files)
void saveProducts();
void saveUsers();
void saveOrders();

// Backward compatibility aliases
inline void loadCustomers() { loadUsers(); }
inline void saveCustomers() { saveUsers(); }
