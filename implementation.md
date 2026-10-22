# E-Commerce System — DSA Mini Project (C++)
## Implementation Plan & Architecture Document

> **College DSA Mini Project** | C++17 | Console-Based | All DSA from scratch

---

## Table of Contents

1. [Directory Structure](#1-directory-structure)
2. [File Responsibilities](#2-file-responsibilities)
3. [Menu → Function → File Mapping](#3-menu--function--file-mapping)
4. [Data Structure Interaction Map](#4-data-structure-interaction-map)
5. [Class Relationships](#5-class-relationships)
6. [Key Design Decisions](#6-key-design-decisions)
7. [DSA Concepts Summary](#7-dsa-concepts-summary)
8. [Phase 2 — Implementation Order](#8-phase-2--implementation-order)
9. [Phase 3 — Compilation Commands](#9-phase-3--compilation-commands)
10. [Phase 4 — Test Cases](#10-phase-4--test-cases)
11. [Phase 5 — Viva Preparation](#11-phase-5--viva-preparation)

---

## 1. Directory Structure

```
ECommerceSystem/
│
├── MAIN/
│   ├── main.cpp                  ← Entry point, main menu, startup/shutdown
│   ├── login.h                   ← Login function declarations
│   └── login.cpp                 ← Admin/customer auth logic
│
├── ADMIN/
│   ├── options_admin.h           ← Admin panel menu declaration
│   ├── options_admin.cpp         ← Admin menu loop & dispatch
│   ├── product_management.h      ← Product CRUD + sort/search declarations
│   └── product_management.cpp    ← Product CRUD + sort/search definitions
│
├── USER/
│   ├── options_user.h            ← User panel menu declaration
│   ├── options_user.cpp          ← User menu loop & dispatch
│   ├── user_operations.h         ← Order placement, view, cancel declarations
│   └── user_operations.cpp       ← Order operations definitions
│
├── MODELS/
│   ├── Product.h                 ← Product struct definition
│   ├── Order.h                   ← Order struct + status enum definition
│   └── Customer.h                ← Customer/User struct definition
│
├── DATA_STRUCTURES/
│   ├── ProductList.h             ← Custom singly linked list (declaration)
│   ├── ProductList.cpp           ← Custom singly linked list (implementation)
│   ├── OrderQueue.h              ← Custom FIFO queue (declaration)
│   ├── OrderQueue.cpp            ← Custom FIFO queue (implementation)
│   ├── CustomerHashTable.h       ← Hash table w/ chaining (declaration)
│   ├── CustomerHashTable.cpp     ← Hash table w/ chaining (implementation)
│   ├── Sorting.h                 ← Merge sort declaration
│   └── Sorting.cpp               ← Merge sort implementation
│
├── FILES/
│   ├── products.txt              ← Persistent product storage
│   ├── users.txt                 ← Persistent user storage
│   └── orders.txt                ← Persistent order storage
│
├── README.md                     ← Credentials, build guide, usage notes
└── implementation.md             ← This document
```

---

## 2. File Responsibilities

### MAIN/

| File | Responsibility |
|------|----------------|
| main.cpp | Bootstraps the application. On startup, calls loadProducts(), loadCustomers(), loadOrders(). Displays the 3-option main menu in a loop. Routes to admin or customer login. On exit, saves all data and frees memory. |
| login.h | Declares bool adminLogin() and std::string customerLogin() (returns customerID on success, empty string on failure). Also declares registerCustomer(). |
| login.cpp | Implements login logic. Admin credentials are stored ONLY HERE as const strings, clearly commented as demo-only. Customer login queries CustomerHashTable by ID and validates password. |

### ADMIN/

| File | Responsibility |
|------|----------------|
| options_admin.h | Declares void showAdminPanel() — runs the 8-option admin session loop. |
| options_admin.cpp | Implements the admin menu loop. Reads user input and dispatches to product_management. |
| product_management.h | Declares: addProduct(), deleteProduct(), updateProduct(), displayProducts(), searchProduct(), sortProducts(), viewAllOrders(). |
| product_management.cpp | Full implementations of all product CRUD, search wrappers, sort launcher, and order viewer. |

### CUSTOMER/

| File | Responsibility |
|------|----------------|
| options_customer.h | Declares void showCustomerPanel(const std::string& customerID). |
| options_customer.cpp | Implements the customer menu loop. Receives the logged-in customerID and dispatches to customer_operations. |
| customer_operations.h | Declares: viewProducts(), searchProduct(), placeOrder(), viewMyOrders(), cancelOrder(). |
| customer_operations.cpp | Full implementations: stock validation, queue enqueue, history append, cancellation with stock restore. |

### MODELS/

| File | Content |
|------|---------|
| Product.h | struct Product with id, name, category, price, quantity — plus constructor and validation helper. |
| Order.h | enum class OrderStatus (Pending, Completed, Cancelled) and struct Order with all order fields. |
| Customer.h | struct Customer with customerID, name, email, password — plus constructor. |

### DATA_STRUCTURES/

| File | Content |
|------|---------|
| ProductList.h/.cpp | Custom singly linked list. insertFront(), deleteByID(), updateByID(), displayAll(), searchByID(), searchByName(), toVector(). Destructor frees all nodes. |
| OrderQueue.h/.cpp | Custom FIFO queue using linked nodes. enqueue(), dequeue(), displayPending(), isEmpty(), size(). Destructor frees all nodes. |
| CustomerHashTable.h/.cpp | Fixed array of vector<Customer> buckets (separate chaining). Hash: customerID % 101. insert(), search(), isDuplicate(). Average O(1) lookup. |
| Sorting.h/.cpp | Merge sort on vector<Product> (a copy — never mutates the linked list). Comparators for price and name. |

### FILES/

| File | CSV Format |
|------|-----------|
| products.csv | id,name,category,price,quantity |
| customers.csv | customerID,name,email,password |
| orders.csv | orderID,customerID,productID,productName,qty,unitPrice,totalPrice,status |

Note: Fields must not contain commas. Input validation will reject commas in names/categories.

---

## 3. Menu to Function to File Mapping

### Main Menu

```
Main Menu
├── 1. Admin Login
│       → adminLogin()                         MAIN/login.cpp
│       → [on success] showAdminPanel()        ADMIN/options_admin.cpp
│
├── 2. Customer Login
│       → customerLogin()                      MAIN/login.cpp
│           option to Register New Customer
│               → registerCustomer()           MAIN/login.cpp
│       → [on success] showCustomerPanel(id)   CUSTOMER/options_customer.cpp
│
└── 3. Exit
        → saveAllData() + free memory          MAIN/main.cpp
```

### Admin Panel (8 options)

| # | Menu Option | Function | Source File |
|---|-------------|----------|-------------|
| 1 | Add Product | addProduct() | ADMIN/product_management.cpp |
| 2 | Delete Product | deleteProduct() | ADMIN/product_management.cpp |
| 3 | Update Product | updateProduct() | ADMIN/product_management.cpp |
| 4 | Display Products | displayProducts() | ADMIN/product_management.cpp |
| 5 | Search Product | searchProduct() | ADMIN/product_management.cpp → DATA_STRUCTURES/ProductList.cpp |
| 6 | Sort Products | sortProducts() | ADMIN/product_management.cpp → DATA_STRUCTURES/Sorting.cpp |
| 7 | View Orders | viewAllOrders() | ADMIN/product_management.cpp (reads global orderHistory) |
| 8 | Logout | return to main loop | ADMIN/options_admin.cpp |

### Customer Panel (6 options)

| # | Menu Option | Function | Source File |
|---|-------------|----------|-------------|
| 1 | View Products | viewProducts() | CUSTOMER/customer_operations.cpp |
| 2 | Search Product | searchProduct() | CUSTOMER/customer_operations.cpp → DATA_STRUCTURES/ProductList.cpp |
| 3 | Place Order | placeOrder(customerID) | CUSTOMER/customer_operations.cpp |
| 4 | View My Orders | viewMyOrders(customerID) | CUSTOMER/customer_operations.cpp |
| 5 | Cancel Order | cancelOrder(customerID) | CUSTOMER/customer_operations.cpp |
| 6 | Logout | return to main loop | CUSTOMER/options_customer.cpp |

---

## 4. Data Structure Interaction Map

```
APPLICATION STARTUP (main.cpp)
├── loadProducts()   ──►  ProductList      (Linked List)
├── loadCustomers()  ──►  CustomerHashTable
└── loadOrders()     ──►  orderHistory     (vector<Order>)
                      └►  OrderQueue       (re-enqueue Pending orders)

ProductList                  CustomerHashTable         orderHistory
Singly Linked List           Hash Table                vector<Order>
──────────────               ─────────────             ────────────
O(1) insert at head          TABLE_SIZE = 101          Full history
O(n) delete by ID            Hash: id % 101            Filtered per customer
O(n) search by ID/name       Chaining: vector<C>       on viewMyOrders()
O(n) display                 O(1) avg lookup
toVector() → sort buffer                               OrderQueue
                                                       FIFO Queue
                                                       ──────────
                                                       Pending only
                                                       O(1) enqueue
                                                       O(1) dequeue
                                                       Rebuilt on startup

Sorting
──────
Input:   vector<Product> (copy from ProductList.toVector())
Sorts:   by price OR name
Output:  sorted vector for display only — list unchanged
Complexity: O(n log n) time, O(n) auxiliary space

placeOrder(customerID):
  1. Validate product exists   → ProductList.searchByID()
  2. Check stock available     → product.quantity >= requestedQty
  3. Deduct stock              → ProductList.updateByID()
  4. Create Order object
  5. Enqueue                   → OrderQueue.enqueue()
  6. Append to history         → orderHistory.push_back()
  7. Save                      → saveOrders(), saveProducts()

cancelOrder(customerID):
  1. Show customer's orders    → filter orderHistory by customerID
  2. Validate ownership+status → order.customerID == loggedIn && Pending
  3. Update status             → order.status = Cancelled
  4. Restore stock             → ProductList.updateByID() (qty += cancelled qty)
  5. Save                      → saveOrders(), saveProducts()

deleteProduct(id):
  1. Remove from ProductList   → ProductList.deleteByID()
  2. orderHistory UNTOUCHED    → snapshots preserved (productNameSnapshot)
  3. Save                      → saveProducts()
```

---

## 5. Class Relationships

```
Product ◄── ProductListNode (data: Product, next: Node*)
             └── owned by ProductList
                 Methods: insertFront, deleteByID, updateByID,
                          searchByID, searchByName, displayAll,
                          toVector, ~ProductList

Customer ◄── CustomerHashTable
             table[101]: vector<Customer>  (separate chaining)
             Methods: hash(id), insert, search, isDuplicate

Order ◄── OrderQueueNode (data: Order, next: Node*)
           └── owned by OrderQueue
               Methods: enqueue, dequeue, displayPending, isEmpty, ~OrderQueue
Order ◄── vector<Order> orderHistory  (global, all orders, filtered by customerID)

Sorting (free functions):
  mergeSortByPrice(vector<Product>&)
  mergeSortByName(vector<Product>&)
  merge(left, right, comparator)

GLOBAL STATE (declared in main.cpp, extern in headers):
  ProductList        gProductList
  CustomerHashTable  gCustomerTable
  OrderQueue         gOrderQueue
  vector<Order>      gOrderHistory
  int                gNextOrderID
  int                gNextProductID
```

---

## 6. Key Design Decisions

| Decision | Rationale |
|----------|-----------|
| ProductList is a custom linked list | Demonstrates pointer manipulation and core DSA concept |
| OrderQueue is separate from orderHistory | Queue tracks processing state; history is the permanent log |
| CustomerHashTable uses int-keyed hash | Simple modulo hash on auto-incremented numeric ID |
| Sorting done on a copy (vector<Product>) | Merge sort needs random access; sorted view is display-only |
| Global state with extern declarations | Simplest approach suitable for a college project |
| Admin credentials only in login.cpp | Single location, clearly marked as demo-only |
| No Stack implemented | No undo feature planned; including stack without purpose is academically dishonest |
| Commas restricted in text fields | Simplest CSV safety strategy, validated on input |
| orderHistory is never purged | Cancellations update status only; the record remains |

---

## 7. DSA Concepts Summary

| Concept | Where Used | Complexity |
|---------|-----------|------------|
| Singly Linked List | ProductList — product storage | Insert O(1), Search/Delete O(n) |
| Hash Table + Chaining | CustomerHashTable — auth lookup | O(1) avg, O(n) worst |
| FIFO Queue | OrderQueue — pending orders | Enqueue/Dequeue O(1) |
| Merge Sort | Sorting — sort products | O(n log n) time, O(n) space |
| Linear Search | ProductList.searchByID/Name() | O(n) — correct for unsorted linked list |
| Vector (STL) | orderHistory, sort buffer, chaining buckets | Used where dynamic resizing is appropriate |

### OOP Concepts

| Concept | Where |
|---------|-------|
| Classes & Objects | ProductList, OrderQueue, CustomerHashTable |
| Encapsulation | Private members + public methods in all DS classes |
| Constructors | Product, Order, Customer structs |
| Destructors | ~ProductList(), ~OrderQueue() — prevent memory leaks |
| Const correctness | const string& parameters, const member functions |
| Separation of Concerns | MODELS / DATA_STRUCTURES / ADMIN / CUSTOMER isolation |

---

## 8. Phase 2 — Implementation Order

Files generated strictly in this order to avoid forward-reference issues:

```
Step  1:  MODELS/Product.h
Step  2:  MODELS/Order.h
Step  3:  MODELS/Customer.h
Step  4:  DATA_STRUCTURES/ProductList.h
Step  5:  DATA_STRUCTURES/ProductList.cpp
Step  6:  DATA_STRUCTURES/OrderQueue.h
Step  7:  DATA_STRUCTURES/OrderQueue.cpp
Step  8:  DATA_STRUCTURES/CustomerHashTable.h
Step  9:  DATA_STRUCTURES/CustomerHashTable.cpp
Step 10:  DATA_STRUCTURES/Sorting.h
Step 11:  DATA_STRUCTURES/Sorting.cpp
Step 12:  MAIN/login.h
Step 13:  MAIN/login.cpp
Step 14:  ADMIN/product_management.h
Step 15:  ADMIN/product_management.cpp
Step 16:  ADMIN/options_admin.h
Step 17:  ADMIN/options_admin.cpp
Step 18:  CUSTOMER/customer_operations.h
Step 19:  CUSTOMER/customer_operations.cpp
Step 20:  CUSTOMER/options_customer.h
Step 21:  CUSTOMER/options_customer.cpp
Step 22:  MAIN/main.cpp
Step 23:  FILES/products.csv        (empty seed file)
Step 24:  FILES/customers.csv       (empty seed file)
Step 25:  FILES/orders.csv          (empty seed file)
Step 26:  README.md
```

---

## 9. Phase 3 — Compilation Commands

Working directory: ECommerceSystem/
Compiler: g++ (MinGW on Windows)
Standard: C++17

### Single compile command (run from inside ECommerceSystem/):

```bash
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

### Run:

```bash
.\ecommerce.exe
```

Important: Run the executable from the ECommerceSystem/ directory so relative paths to FILES/*.txt resolve correctly.

---

## 10. Phase 4 — Test Cases

### Authentication Tests

| Test | Input | Expected Output |
|------|-------|-----------------|
| Admin login correct | ID: admin, PW: admin123 | Login successful. Welcome, Admin! |
| Admin login wrong PW | ID: admin, PW: wrong | Invalid credentials. Try again. |
| Customer register | New ID, name, email, PW | Registration successful! |
| Customer login correct | Valid ID + PW | Welcome, [Name]! |
| Customer login wrong | Valid ID + wrong PW | Invalid credentials. |
| Duplicate customer ID | Same ID twice | Customer ID already exists. |

### Product Management Tests

| Test | Action | Expected |
|------|--------|----------|
| Add product | Name: Laptop, Cat: Electronics, Price: 45000, Qty: 10 | Product added with auto ID P001 |
| Add product negative price | Price: -100 | Invalid price. Must be > 0. |
| Add product zero qty | Qty: 0 | Invalid quantity. Must be >= 1. |
| Display products (empty) | No products | No products available. |
| Display products | After adding 3 | Formatted table with all 3 |
| Search by ID | Search P001 | Shows Laptop details |
| Search by name | Search lap (case-insensitive) | Shows Laptop |
| Search not found | Search XYZNOTFOUND | Product not found. |
| Delete product | Delete P001 | Product deleted. |
| Update product | Update P001 price to 42000 | Product shows new price |

### Sorting Tests

| Test | Action | Expected |
|------|--------|----------|
| Sort by price asc | Products at 500, 200, 1000 | Displays: 200, 500, 1000 |
| Sort by name asc | Zebra, Apple, Mango | Displays: Apple, Mango, Zebra |
| Sort does not mutate list | After sort, display products | Original insertion order preserved |

### Order Tests

| Test | Action | Expected |
|------|--------|----------|
| Place order valid | Product P001, qty 2 | Order placed. Stock reduced from 10 to 8 |
| Place order insufficient stock | Product P001, qty 100 (stock: 8) | Insufficient stock. Available: 8 |
| Place order zero qty | Qty: 0 | Invalid quantity. |
| Place order nonexistent product | ID: P999 | Product not found. |
| View my orders | Customer C001 | Shows only C001 orders |
| View my orders (empty) | New customer | You have no orders yet. |
| Cancel pending order | Order in Pending status | Order cancelled. Stock restored. |
| Cancel already cancelled | Already Cancelled | Cannot cancel. Order is already Cancelled. |
| Cancel other customer order | Wrong customerID | Order not found or not yours. |
| Stock after cancel | Cancelled qty 2 from stock 8 | Stock returns to 10 |

### Persistence Tests

| Test | Steps | Expected |
|------|-------|---------|
| Product persists | Add product → Exit → Restart | Product still in list |
| Customer persists | Register → Exit → Restart → Login | Login succeeds |
| Order persists | Place order → Exit → Restart → View Orders | Order still in history |
| Pending queue rebuilt | Place order → Exit → Restart → Admin view orders | Order shows as Pending |
| Stock persists | Place order (10→8) → Exit → Restart | Stock shows 8 |

### Invalid Input Tests

| Test | Input | Expected |
|------|-------|---------|
| Menu choice out of range | Enter 9 on main menu | Invalid choice. Try again. |
| Non-numeric menu input | Enter abc | Invalid input. Please enter a number. |
| Empty product name | Name: (empty) | Name cannot be empty. |
| Comma in product name | Name: Lap,top | Commas are not allowed in fields. |

---

## 11. Phase 5 — Viva Preparation

### Time Complexities

| Operation | Data Structure | Complexity | Reason |
|-----------|---------------|------------|--------|
| Insert product | Linked List | O(1) | Insert at head |
| Delete product | Linked List | O(n) | Must traverse to find node |
| Search product | Linked List | O(n) | Linear traversal (unsorted) |
| Sort products | Merge Sort | O(n log n) | Divide and conquer |
| Customer lookup | Hash Table | O(1) avg | Direct bucket access |
| Customer lookup | Hash Table | O(n) worst | All keys in one bucket |
| Enqueue order | Queue | O(1) | Append to rear |
| Dequeue order | Queue | O(1) | Remove from front |
| View my orders | Vector filter | O(n) | Scan all orders |

### Common Viva Questions & Answers

Q: What is the time complexity of searching a product?
A: O(n) — linear search through the linked list. Since the list is unsorted, we must traverse each node.

Q: Why use a hash table for customers instead of a linked list?
A: Customer lookup on login must be fast. Hash table gives O(1) average lookup versus O(n) for a linked list.

Q: What is separate chaining?
A: When two customers hash to the same bucket index, both are stored in a vector<Customer> at that index. We search linearly within the bucket.

Q: Why does sorting not change the linked list?
A: Merge sort requires contiguous memory. We copy the list into a vector, sort the copy, and display it. Original list order is unchanged.

Q: How do you prevent duplicate order IDs?
A: A global counter gNextOrderID is incremented on each order placed, saved to orders.csv, and restored on startup.

Q: What happens to orders when a product is deleted?
A: The order history stores a productNameSnapshot — the product name at the time of purchase. Historical orders still show the correct product name and price.

Q: How do you handle stock consistency on cancellation?
A: Cancel checks that order status is Pending before proceeding. Stock is restored exactly once. Order status is then set to Cancelled, preventing double-cancellation.

Q: What is the space complexity of merge sort?
A: O(n) auxiliary space — merge sort creates temporary arrays during the merge step.

Q: How is data persisted?
A: CSV files. On startup, loadProducts(), loadCustomers(), loadOrders() parse CSVs and populate in-memory structures. On every successful operation, the relevant CSV is fully rewritten.

Q: What is the hash function used?
A: hash(customerID) = numericID % 101 where 101 is a prime number to reduce clustering.

---

## Admin Credentials (Demo)

| Field | Value |
|-------|-------|
| Username | admin |
| Password | admin123 |

> This is a college demonstration project. Authentication is not production-grade.

---

*E-Commerce System — DSA Mini Project in C++*
