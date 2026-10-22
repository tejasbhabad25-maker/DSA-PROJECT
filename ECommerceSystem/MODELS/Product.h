#pragma once
#include <string>

using namespace std;

// Product model
struct Product {
    string id;
    string name;
    string category;
    double price;
    int    quantity;

    Product() : price(0.0), quantity(0) {}

    Product(const string& id_, const string& name_,
            const string& cat_, double price_, int qty_)
        : id(id_), name(name_), category(cat_), price(price_), quantity(qty_) {}

    static bool validate(double price_, int qty_) {
        return price_ > 0.0 && qty_ >= 0;
    }
};
