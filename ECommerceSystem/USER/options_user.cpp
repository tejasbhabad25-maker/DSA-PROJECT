#include "options_user.h"
#include "user_operations.h"
#include "../MAIN/utils.h"
#include <iostream>

using namespace std;

void showUserPanel(const string& customerID) {
    while (true) {
        cout << "\n========== USER PANEL (" << customerID << ") ==========\n";
        cout << "1. View Products\n";
        cout << "2. Search Product\n";
        cout << "3. Place Order\n";
        cout << "4. View My Orders\n";
        cout << "5. Cancel Order\n";
        cout << "6. Logout\n";

        int choice = getMenuChoice(1, 6);
        switch (choice) {
            case 1:
                viewProducts();
                pressEnter();
                break;
            case 2:
                searchUserProduct();
                pressEnter();
                break;
            case 3:
                placeOrder(customerID);
                pressEnter();
                break;
            case 4:
                viewMyOrders(customerID);
                pressEnter();
                break;
            case 5:
                cancelOrder(customerID);
                pressEnter();
                break;
            case 6:
                cout << "\nLogging out from User Panel...\n";
                return;
        }
    }
}
