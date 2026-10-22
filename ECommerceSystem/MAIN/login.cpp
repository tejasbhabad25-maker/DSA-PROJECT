#include "login.h"
#include "globals.h"
#include "utils.h"
#include "filehandler.h"
#include "../MODELS/Customer.h"
#include <iostream>
#include <string>

using namespace std;

// Admin credentials
static const string ADMIN_USERNAME = "admin";
static const string ADMIN_PASSWORD = "admin123";

// Admin Login
bool adminLogin() {
    cout << "\n  --- Admin Login ---\n";
    cout << "  Username: ";
    string uid;
    getline(cin, uid);

    cout << "  Password: ";
    string pwd;
    getline(cin, pwd);

    if (uid == ADMIN_USERNAME && pwd == ADMIN_PASSWORD) {
        cout << "\n  [OK] Login successful. Welcome, Admin!\n";
        return true;
    }
    cout << "\n  [!] Invalid credentials.\n";
    return false;
}

// User / Customer Login
string customerLogin() {
    while (true) {
        cout << "\n  --- User Menu ---\n";
        cout << "  1. Login with existing account\n";
        cout << "  2. Register new account\n";
        cout << "  3. Back to main menu\n";

        cout << "\n  Enter choice: ";
        string line;
        getline(cin, line);
        int choice = -1;
        try { choice = stoi(line); } catch (...) {}

        if (choice == 1) {
            cout << "\n  User ID (e.g. C001): ";
            string id;
            getline(cin, id);

            cout << "  Password: ";
            string pwd;
            getline(cin, pwd);

            Customer* c = gCustomerTable.search(id);
            if (c && c->password == pwd) {
                cout << "\n  [OK] Welcome back, " << c->name << "!\n";
                return id;
            }
            cout << "\n  [!] Invalid User ID or password.\n";

        } else if (choice == 2) {
            string newID = registerCustomer();
            if (!newID.empty()) return newID;

        } else if (choice == 3) {
            return "";

        } else {
            cout << "  [!] Invalid choice. Enter 1, 2, or 3.\n";
        }
    }
}

// User Registration
string registerCustomer() {
    cout << "\n  --- New User Registration ---\n";

    string name  = getValidString("  Full Name    : ");
    string email = getValidString("  Email Address: ");
    string pwd   = getValidString("  Password     : ");

    string cid = formatCustomerID(gNextCustomerID++);

    Customer c(cid, name, email, pwd);

    if (!gCustomerTable.insert(c)) {
        cout << "  [!] Registration failed. Please try again.\n";
        --gNextCustomerID;
        return "";
    }

    saveUsers();

    cout << "\n  [OK] Registration successful!\n";
    cout << "       Your User ID : " << cid << "\n";
    cout << "       Please remember this ID for future logins.\n";
    return cid;
}
