# E-Commerce System — Data Structures and Algorithms Mini Project (C++)

A complete, modular, console-based E-Commerce System implemented from scratch in C++17 for a college DSA mini project.

Refer to:
- Detailed Architecture & Viva Guide: [implementation.md](file:///c:/DSA-PROJECT/implementation.md)
- Project Source & Documentation: [ECommerceSystem/README.md](file:///c:/DSA-PROJECT/ECommerceSystem/README.md)

---

## Quick Compilation & Execution

Open terminal inside `c:\DSA-PROJECT\ECommerceSystem` and run:

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

Run:
```bash
.\ecommerce.exe
```

### Credentials
- **Admin**: `admin` / `admin123`
- **User**: `C001` / `pass123` (or register a new account)
