#pragma once
#include <string>
#include <iostream>
#include <limits>
#include <stdexcept>

using namespace std;

// Read a non-empty string with no commas
inline string getValidString(const string& prompt) {
    string s;
    while (true) {
        cout << prompt;
        getline(cin, s);
        if (s.empty()) {
            cout << "  [!] Input cannot be empty. Try again.\n";
            continue;
        }
        if (s.find(',') != string::npos) {
            cout << "  [!] Commas are not allowed in fields. Try again.\n";
            continue;
        }
        return s;
    }
}

// Read an integer >= minVal
inline int getValidInt(const string& prompt, int minVal = 0) {
    while (true) {
        cout << prompt;
        string line;
        getline(cin, line);
        try {
            int v = stoi(line);
            if (v >= minVal) return v;
            cout << "  [!] Value must be >= " << minVal << ". Try again.\n";
        } catch (...) {
            cout << "  [!] Invalid number. Try again.\n";
        }
    }
}

// Read a double >= minVal
inline double getValidDouble(const string& prompt, double minVal = 0.01) {
    while (true) {
        cout << prompt;
        string line;
        getline(cin, line);
        try {
            double v = stod(line);
            if (v >= minVal) return v;
            cout << "  [!] Value must be >= " << minVal << ". Try again.\n";
        } catch (...) {
            cout << "  [!] Invalid number. Try again.\n";
        }
    }
}

// Read a menu choice in [min, max]
inline int getMenuChoice(int min, int max) {
    while (true) {
        cout << "\n  Enter choice: ";
        string line;
        getline(cin, line);
        try {
            int v = stoi(line);
            if (v >= min && v <= max) return v;
        } catch (...) {}
        cout << "  [!] Invalid choice. Enter a number between "
             << min << " and " << max << ".\n";
    }
}

// Pause until user presses Enter
inline void pressEnter() {
    cout << "\n  Press Enter to continue...";
    string dummy;
    getline(cin, dummy);
}
