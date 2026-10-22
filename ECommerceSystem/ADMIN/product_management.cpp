#include "product_management.h"
#include "../MAIN/globals.h"
#include "../MAIN/utils.h"
#include "../MAIN/filehandler.h"
#include "../DATA_STRUCTURES/Sorting.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>

using namespace std;

void addProduct() {
    cout << "\n--- ADD PRODUCT ---\n";
    string productID = formatProductID(gNextProductID++);
    cout << "Auto-assigned Product ID: " << productID << "\n";

    string name = getValidString("Enter Product Name: ");
    string category = getValidString("Enter Category: ");
    double price = getValidDouble("Enter Price: $", 0.01);
    int quantity = getValidInt("Enter Quantity: ", 0);

    Product p(productID, name, category, price, quantity);
    gProductList.insertFront(p);
    saveProducts();

    cout << "\n[+] Product added successfully with ID: " << productID << "\n";
}

void deleteProduct() {
    cout << "\n--- DELETE PRODUCT ---\n";
    if (gProductList.isEmpty()) {
        cout << "Product catalog is empty.\n";
        return;
    }

    string id = getValidString("Enter Product ID to delete: ");
    if (gProductList.deleteByID(id)) {
        saveProducts();
        cout << "\n[+] Product " << id << " deleted successfully.\n";
        cout << "    (Note: Historical orders containing this product remain preserved.)\n";
    } else {
        cout << "\n[!] Product with ID '" << id << "' not found.\n";
    }
}

void updateProduct() {
    cout << "\n--- UPDATE PRODUCT ---\n";
    if (gProductList.isEmpty()) {
        cout << "Product catalog is empty.\n";
        return;
    }

    string id = getValidString("Enter Product ID to update: ");
    Product* p = gProductList.searchByID(id);
    if (!p) {
        cout << "\n[!] Product with ID '" << id << "' not found.\n";
        return;
    }

    cout << "\nCurrent Details:\n";
    cout << "  Name:     " << p->name << "\n";
    cout << "  Category: " << p->category << "\n";
    cout << "  Price:    $" << fixed << setprecision(2) << p->price << "\n";
    cout << "  Quantity: " << p->quantity << "\n";
    cout << "\nEnter New Values:\n";

    string newName = getValidString("New Name: ");
    string newCategory = getValidString("New Category: ");
    double newPrice = getValidDouble("New Price: $", 0.01);
    int newQuantity = getValidInt("New Quantity: ", 0);

    Product updated(id, newName, newCategory, newPrice, newQuantity);
    gProductList.updateByID(id, updated);
    saveProducts();

    cout << "\n[+] Product updated successfully.\n";
}

void displayProducts() {
    cout << "\n--- PRODUCT CATALOG ---\n";
    gProductList.displayAll();
}

void searchProduct() {
    cout << "\n--- SEARCH PRODUCT ---\n";
    if (gProductList.isEmpty()) {
        cout << "Product catalog is empty.\n";
        return;
    }

    cout << "1. Search by Product ID\n";
    cout << "2. Search by Product Name\n";
    cout << "3. Back\n";
    int choice = getMenuChoice(1, 3);

    if (choice == 1) {
        string id = getValidString("Enter Product ID: ");
        Product* p = gProductList.searchByID(id);
        if (p) {
            cout << "\n" << string(75, '-') << "\n";
            cout << left
                 << setw(8)  << "ID"
                 << setw(24) << "Name"
                 << setw(16) << "Category"
                 << setw(12) << "Price"
                 << setw(8)  << "Stock" << "\n";
            cout << string(75, '-') << "\n";
            cout << left
                 << setw(8)  << p->id
                 << setw(24) << p->name
                 << setw(16) << p->category
                 << "$" << setw(11) << fixed << setprecision(2) << p->price
                 << setw(8)  << p->quantity << "\n";
            cout << string(75, '-') << "\n";
        } else {
            cout << "\n[!] No product found with ID: " << id << "\n";
        }
    } else if (choice == 2) {
        string name = getValidString("Enter Product Name (or partial name): ");
        vector<Product*> results = gProductList.searchByName(name);
        if (results.empty()) {
            cout << "\n[!] No products matching '" << name << "' found.\n";
        } else {
            cout << "\nFound " << results.size() << " match(es):\n";
            cout << string(75, '-') << "\n";
            cout << left
                 << setw(8)  << "ID"
                 << setw(24) << "Name"
                 << setw(16) << "Category"
                 << setw(12) << "Price"
                 << setw(8)  << "Stock" << "\n";
            cout << string(75, '-') << "\n";
            for (const auto* p : results) {
                cout << left
                     << setw(8)  << p->id
                     << setw(24) << p->name
                     << setw(16) << p->category
                     << "$" << setw(11) << fixed << setprecision(2) << p->price
                     << setw(8)  << p->quantity << "\n";
            }
            cout << string(75, '-') << "\n";
        }
    }
}

void sortProducts() {
    cout << "\n--- SORT PRODUCTS (Merge Sort) ---\n";
    if (gProductList.isEmpty()) {
        cout << "Product catalog is empty.\n";
        return;
    }

    cout << "1. Sort by Price (Ascending)\n";
    cout << "2. Sort by Name (Ascending)\n";
    cout << "3. Back\n";
    int choice = getMenuChoice(1, 3);

    if (choice == 3) return;

    vector<Product> prodCopy = gProductList.toVector();

    if (choice == 1) {
        mergeSortByPrice(prodCopy);
        cout << "\n[+] Products sorted by Price (Ascending):\n";
    } else if (choice == 2) {
        mergeSortByName(prodCopy);
        cout << "\n[+] Products sorted by Name (Ascending):\n";
    }

    cout << string(75, '-') << "\n";
    cout << left
         << setw(8)  << "ID"
         << setw(24) << "Name"
         << setw(16) << "Category"
         << setw(12) << "Price"
         << setw(8)  << "Stock" << "\n";
    cout << string(75, '-') << "\n";
    for (const auto& p : prodCopy) {
        cout << left
             << setw(8)  << p.id
             << setw(24) << p.name
             << setw(16) << p.category
             << "$" << setw(11) << fixed << setprecision(2) << p.price
             << setw(8)  << p.quantity << "\n";
    }
    cout << string(75, '-') << "\n";
}

void viewAllOrders() {
    cout << "\n--- ALL ORDERS (Order History & Queue) ---\n";
    if (gOrderHistory.empty()) {
        cout << "No orders have been placed yet.\n";
        return;
    }

    cout << string(85, '-') << "\n";
    cout << left
         << setw(10) << "Order ID"
         << setw(12) << "Customer"
         << setw(10) << "Product"
         << setw(22) << "Product Name"
         << setw(6)  << "Qty"
         << setw(12) << "Total"
         << setw(12) << "Status" << "\n";
    cout << string(85, '-') << "\n";

    for (const auto& ord : gOrderHistory) {
        cout << left
             << setw(10) << ord.orderID
             << setw(12) << ord.customerID
             << setw(10) << ord.productID
             << setw(22) << ord.productNameSnapshot
             << setw(6)  << ord.qty
             << "$" << setw(11) << fixed << setprecision(2) << ord.totalPrice
             << setw(12) << orderStatusToString(ord.status) << "\n";
    }
    cout << string(85, '-') << "\n";

    cout << "\n--- PENDING ORDER QUEUE (FIFO) ---\n";
    gOrderQueue.displayPending();
}
