#pragma once
#include <string>

using namespace std;

// Returns true if admin login succeeds
bool adminLogin();

// Prompts the user to login or register
// Returns the customerID string on success, empty string if user goes back
string customerLogin();

// Registers a new user, inserts into hash table, saves to text file
// Returns the new customerID on success, empty string on failure
string registerCustomer();
