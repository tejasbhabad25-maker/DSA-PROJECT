#include "user_operations.h"
#include "../MAIN/globals.h"
#include "../MAIN/utils.h"
#include "../MAIN/filehandler.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>

using namespace std;

void viewProducts() {
    cout << "\n--- AVAILABLE PRODUCTS ---\n";
    gProductList.displayAll();
}

void searchUserProduct() {
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

void placeOrder(const string& customerID) {
    cout << "\n--- PLACE ORDER ---\n";
    if (gProductList.isEmpty()) {
        cout << "No products available in the store.\n";
        return;
    }

    string prodID = getValidString("Enter Product ID to purchase: ");
    Product* p = gProductList.searchByID(prodID);
    if (!p) {
        cout << "\n[!] Product with ID '" << prodID << "' does not exist.\n";
        return;
    }

    if (p->quantity <= 0) {
        cout << "\n[!] Sorry, '" << p->name << "' is currently out of stock.\n";
        return;
    }

    cout << "Product: " << p->name << " | Unit Price: $"
         << fixed << setprecision(2) << p->price
         << " | Stock Available: " << p->quantity << "\n";

    int qty = getValidInt("Enter Quantity to order: ", 1);
    if (qty > p->quantity) {
        cout << "\n[!] Insufficient stock. Only " << p->quantity << " available.\n";
        return;
    }

    // 1. Deduct stock from the product list
    Product updatedProduct = *p;
    updatedProduct.quantity -= qty;
    gProductList.updateByID(prodID, updatedProduct);

    // 2. Create the Order record
    string orderID = formatOrderID(gNextOrderID++);
    Order newOrder;
    newOrder.orderID = orderID;
    newOrder.customerID = customerID;
    newOrder.productID = prodID;
    newOrder.productNameSnapshot = p->name;
    newOrder.qty = qty;
    newOrder.unitPrice = p->price;
    newOrder.totalPrice = p->price * qty;
    newOrder.status = OrderStatus::Pending;

    // 3. Add to FIFO queue (Pending only)
    gOrderQueue.enqueue(newOrder);

    // 4. Add to complete order history
    gOrderHistory.push_back(newOrder);

    // 5. Persist changes to text files
    saveProducts();
    saveOrders();

    cout << "\n[+] Order Placed Successfully!\n";
    cout << "    Order ID:    " << orderID << "\n";
    cout << "    Item:        " << newOrder.productNameSnapshot << "\n";
    cout << "    Quantity:    " << qty << "\n";
    cout << "    Total Price: $" << fixed << setprecision(2) << newOrder.totalPrice << "\n";
    cout << "    Status:      " << orderStatusToString(newOrder.status) << "\n";
}

void viewMyOrders(const string& customerID) {
    cout << "\n--- MY ORDERS ---\n";
    vector<const Order*> myOrders;
    for (const auto& ord : gOrderHistory) {
        if (ord.customerID == customerID) {
            myOrders.push_back(&ord);
        }
    }

    if (myOrders.empty()) {
        cout << "You have not placed any orders yet.\n";
        return;
    }

    cout << string(80, '-') << "\n";
    cout << left
         << setw(10) << "Order ID"
         << setw(10) << "Product"
         << setw(24) << "Product Name"
         << setw(6)  << "Qty"
         << setw(14) << "Total Price"
         << setw(12) << "Status" << "\n";
    cout << string(80, '-') << "\n";

    for (const auto* ord : myOrders) {
        cout << left
             << setw(10) << ord->orderID
             << setw(10) << ord->productID
             << setw(24) << ord->productNameSnapshot
             << setw(6)  << ord->qty
             << "$" << setw(13) << fixed << setprecision(2) << ord->totalPrice
             << setw(12) << orderStatusToString(ord->status) << "\n";
    }
    cout << string(80, '-') << "\n";
}

void cancelOrder(const string& customerID) {
    cout << "\n--- CANCEL ORDER ---\n";
    vector<Order*> pendingOrders;

    for (auto& ord : gOrderHistory) {
        if (ord.customerID == customerID && ord.status == OrderStatus::Pending) {
            pendingOrders.push_back(&ord);
        }
    }

    if (pendingOrders.empty()) {
        cout << "You have no pending orders eligible for cancellation.\n";
        return;
    }

    cout << "Your Pending Orders:\n";
    cout << string(70, '-') << "\n";
    cout << left
         << setw(10) << "Order ID"
         << setw(24) << "Product Name"
         << setw(6)  << "Qty"
         << setw(14) << "Total Price"
         << setw(12) << "Status" << "\n";
    cout << string(70, '-') << "\n";
    for (const auto* ord : pendingOrders) {
        cout << left
             << setw(10) << ord->orderID
             << setw(24) << ord->productNameSnapshot
             << setw(6)  << ord->qty
             << "$" << setw(13) << fixed << setprecision(2) << ord->totalPrice
             << setw(12) << orderStatusToString(ord->status) << "\n";
    }
    cout << string(70, '-') << "\n";

    string ordID = getValidString("Enter Order ID to cancel (or '0' to abort): ");
    if (ordID == "0") {
        cout << "Cancellation aborted.\n";
        return;
    }

    Order* target = nullptr;
    for (auto* ord : pendingOrders) {
        if (ord->orderID == ordID) {
            target = ord;
            break;
        }
    }

    if (!target) {
        cout << "\n[!] Order ID not found among your pending orders.\n";
        return;
    }

    // 1. Update order status in orderHistory
    target->status = OrderStatus::Cancelled;

    // 2. Remove order from the FIFO pending queue
    gOrderQueue.removeByOrderID(ordID);

    // 3. Restore product stock in ProductList
    Product* p = gProductList.searchByID(target->productID);
    if (p) {
        Product restored = *p;
        restored.quantity += target->qty;
        gProductList.updateByID(target->productID, restored);
    }

    // 4. Persist updates
    saveProducts();
    saveOrders();

    cout << "\n[+] Order " << ordID << " has been cancelled successfully.\n";
    cout << "    Stock of " << target->qty << " unit(s) restored to the store catalog.\n";
}
