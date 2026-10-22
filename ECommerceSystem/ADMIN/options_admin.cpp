#include "options_admin.h"
#include "product_management.h"
#include "../MAIN/utils.h"
#include <iostream>

using namespace std;

void showAdminPanel() {
    while (true) {
        cout << "\n========== ADMIN PANEL ==========\n";
        cout << "1. Add Product\n";
        cout << "2. Delete Product\n";
        cout << "3. Update Product\n";
        cout << "4. Display Products\n";
        cout << "5. Search Product\n";
        cout << "6. Sort Products\n";
        cout << "7. View Orders\n";
        cout << "8. Logout\n";

        int choice = getMenuChoice(1, 8);
        switch (choice) {
            case 1:
                addProduct();
                pressEnter();
                break;
            case 2:
                deleteProduct();
                pressEnter();
                break;
            case 3:
                updateProduct();
                pressEnter();
                break;
            case 4:
                displayProducts();
                pressEnter();
                break;
            case 5:
                searchProduct();
                pressEnter();
                break;
            case 6:
                sortProducts();
                pressEnter();
                break;
            case 7:
                viewAllOrders();
                pressEnter();
                break;
            case 8:
                cout << "\nLogging out from Admin Panel...\n";
                return;
        }
    }
}
