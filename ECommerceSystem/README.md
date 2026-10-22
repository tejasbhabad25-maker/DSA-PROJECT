# E-Commerce System (DSA Mini Project in C++)

A complete, modular, console-based E-Commerce System implemented from scratch in C++17 for a college Data Structures and Algorithms (DSA) mini project.

---

## 📌 Features & Architecture

- **Clean Syntax**: Uses `using namespace std;` throughout for clean, beginner-friendly C++ code.
- **Dedicated Admin and User Modules**: Separate modular folders for `ADMIN/` and `USER/`.
- **Text File Database (`.txt`)**: Text file persistence for catalog items, registered users, and orders (`products.txt`, `users.txt`, `orders.txt`).
- **Custom Singly Linked List (`ProductList`)**: Dynamic product catalog with $O(1)$ head insertion, $O(n)$ search, update, and deletion.
- **Custom FIFO Queue (`OrderQueue`)**: Linked-node queue managing pending orders with $O(1)$ enqueue and dequeue operations.
- **Custom Hash Table with Separate Chaining (`CustomerHashTable`)**: Fixed-size prime modulus array (101 buckets) storing user accounts with $O(1)$ average-time lookup.
- **Merge Sort Algorithm (`Sorting`)**: Stable divide-and-conquer $O(n \log n)$ sorting on product copies by price or product name.
- **Input Validation (`utils`)**: Safe stream reading via `getline` with comma guarding and type conversions.

---

## 📂 Project Structure

```
ECommerceSystem/
├── MAIN/
│   ├── main.cpp                  # Application entry point & main menu loop
│   ├── globals.h                 # Shared application state externs & ID formatters
│   ├── utils.h                   # Safe input utilities & type parsers
│   ├── filehandler.h / .cpp      # Text file persistence (load/save)
│   └── login.h / .cpp            # Admin authentication & user login/registration
├── ADMIN/
│   ├── options_admin.h / .cpp    # Admin panel menu loop & dispatch
│   └── product_management.h / .cpp # Admin catalog CRUD, search, sort, & order view
├── USER/
│   ├── options_user.h / .cpp     # User panel menu loop & dispatch
│   └── user_operations.h / .cpp  # Order placement, view orders, order cancel
├── MODELS/
│   ├── Product.h                 # Product data struct
│   ├── Customer.h                # Customer / User account data struct
│   └── Order.h                   # Order model & OrderStatus enum
├── DATA_STRUCTURES/
│   ├── ProductList.h / .cpp      # Custom Singly Linked List
│   ├── OrderQueue.h / .cpp       # Custom FIFO Queue
│   ├── CustomerHashTable.h / .cpp # Custom Hash Table (Separate Chaining)
│   └── Sorting.h / .cpp          # Merge Sort (by price & by name)
└── FILES/
    ├── products.txt              # Persistent product records
    ├── users.txt                 # Persistent user accounts
    └── orders.txt                # Persistent order records
```

---

## 🔑 Default Credentials

### Administrator
- **Username**: `admin`
- **Password**: `admin123`

### Demo Users (Pre-seeded in `users.txt`)
- **User ID**: `C001` | **Password**: `pass123` (John Doe)
- **User ID**: `C002` | **Password**: `secret456` (Alice Smith)
*(You can also register a new user account directly from Option 2 on the Main Menu!)*

---

## 🛠️ How to Compile and Run

Navigate into the `ECommerceSystem/` directory and run:

```bash
cd ECommerceSystem
g++ -std=c++17 -Wall -Wextra -o ecommerce ^
  MAIN/main.cpp ^
  MAIN/login.cpp ^
  MAIN/filehandler.cpp ^
  ADMIN/options_admin.cpp ^
  ADMIN/product_management.cpp ^
  USER/options_user.cpp ^
  USER/user_operations.cpp ^
  DATA_STRUCTURES/ProductList.cpp ^
  DATA_STRUCTURES/OrderQueue.cpp ^
  DATA_STRUCTURES/CustomerHashTable.cpp ^
  DATA_STRUCTURES/Sorting.cpp
```

### Execution
Run the compiled executable from within the `ECommerceSystem/` folder so relative paths to `FILES/*.txt` resolve properly:

```bash
.\ecommerce.exe
```

---

## 🎓 DSA Complexity Summary

| Component | Underlying Data Structure | Operation | Time Complexity | Space Complexity |
|---|---|---|---|---|
| **Product Catalog** | Singly Linked List | Insert Front | $O(1)$ | $O(1)$ |
| | Singly Linked List | Search / Update / Delete | $O(n)$ | $O(1)$ |
| **Order Processing** | FIFO Queue (Linked Node) | Enqueue / Dequeue | $O(1)$ | $O(1)$ |
| | FIFO Queue | Display Pending | $O(n)$ | $O(1)$ |
| **User Lookup** | Hash Table (Separate Chaining) | Insert / Search | $O(1)$ average, $O(n)$ worst | $O(N)$ |
| **Product Sorting** | Merge Sort (Vector buffer) | Sort by Price / Name | $O(n \log n)$ guaranteed | $O(n)$ auxiliary |
