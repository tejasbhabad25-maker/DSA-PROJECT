#pragma once
#include <string>

using namespace std;

// Customer / User model
struct Customer {
    string customerID;
    string name;
    string email;
    string password;

    Customer() {}

    Customer(const string& id_, const string& name_,
             const string& email_, const string& pwd_)
        : customerID(id_), name(name_), email(email_), password(pwd_) {}
};

// Type alias
using User = Customer;
