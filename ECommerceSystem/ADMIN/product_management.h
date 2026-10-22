#pragma once

// Admin panel functions — called from options_admin.cpp
void addProduct();
void deleteProduct();
void updateProduct();
void displayProducts();
void searchProduct();   // search by ID or name
void sortProducts();    // merge sort by price or name
void viewAllOrders();   // view full order history (admin view)
