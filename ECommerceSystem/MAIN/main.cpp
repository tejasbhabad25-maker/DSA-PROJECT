#include "globals.h"
#include "utils.h"
#include "filehandler.h"
#include "login.h"
#include "../ADMIN/options_admin.h"
#include "../USER/options_user.h"
#include <iostream>

using namespace std;

// Definition of Global Application State
ProductList        gProductList;
CustomerHashTable  gCustomerTable;
OrderQueue         gOrderQueue;
vector<Order>      gOrderHistory;
int                gNextOrderID = 1;
int                gNextProductID = 1;
int                gNextCustomerID = 1;

int main() {
    cout << "===================================================\n";
    cout << "   WELCOME TO THE E-COMMERCE SYSTEM (DSA PROJECT)  \n";
    cout << "===================================================\n";

    // 1. Load persistent records from text files
    loadProducts();
    loadUsers();
    loadOrders();

    // 2. Main menu loop
    while (true) {
        cout << "\n========== E-COMMERCE SYSTEM ==========\n\n";
        cout << "1. Admin Login\n";
        cout << "2. User Login\n";
        cout << "3. Exit\n";

        int choice = getMenuChoice(1, 3);
        if (choice == 1) {
            if (adminLogin()) {
                showAdminPanel();
            } else {
                pressEnter();
            }
        } else if (choice == 2) {
            string customerID = customerLogin();
            if (!customerID.empty()) {
                showUserPanel(customerID);
            }
        } else if (choice == 3) {
            cout << "\nSaving all system records...\n";
            saveProducts();
            saveUsers();
            saveOrders();
            cout << "Thank you for using the E-Commerce System. Goodbye!\n";
            break;
        }
    }

    return 0;
}
