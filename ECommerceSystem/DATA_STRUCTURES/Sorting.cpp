#include "Sorting.h"
#include <string>
#include <algorithm>
#include <cctype>

using namespace std;

// Generic Merge
static void merge(vector<Product>& arr, int left, int mid, int right,
                  bool(*cmp)(const Product&, const Product&)) {
    vector<Product> tmp;

    int i = left, j = mid + 1;

    while (i <= mid && j <= right) {
        if (cmp(arr[i], arr[j])) tmp.push_back(arr[i++]);
        else                      tmp.push_back(arr[j++]);
    }

    while (i <= mid)   tmp.push_back(arr[i++]);
    while (j <= right) tmp.push_back(arr[j++]);

    for (int k = left; k <= right; ++k) {
        arr[k] = tmp[k - left];
    }
}

// Recursive Merge Sort O(n log n)
static void mergeSort(vector<Product>& arr, int left, int right,
                      bool(*cmp)(const Product&, const Product&)) {
    if (left >= right) return;
    int mid = left + (right - left) / 2;
    mergeSort(arr, left,    mid,   cmp);
    mergeSort(arr, mid + 1, right, cmp);
    merge(arr, left, mid, right, cmp);
}

// Comparators
static bool compareByPrice(const Product& a, const Product& b) {
    return a.price < b.price;
}

static bool compareByName(const Product& a, const Product& b) {
    string na = a.name, nb = b.name;
    transform(na.begin(), na.end(), na.begin(), ::tolower);
    transform(nb.begin(), nb.end(), nb.begin(), ::tolower);
    return na < nb;
}

// Public API
void mergeSortByPrice(vector<Product>& products) {
    if (products.size() <= 1) return;
    mergeSort(products, 0, (int)products.size() - 1, compareByPrice);
}

void mergeSortByName(vector<Product>& products) {
    if (products.size() <= 1) return;
    mergeSort(products, 0, (int)products.size() - 1, compareByName);
}
