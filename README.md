# 🏦 Royal Bank Management System

A **full-featured banking management system** built in C++ that implements 5 core data structures from scratch — no STL containers used. Built as a Data Structures project at Nile University.

![C++](https://img.shields.io/badge/C++-00599C?style=flat&logo=c%2B%2B&logoColor=white)
![Data Structures](https://img.shields.io/badge/Data%20Structures-5%20Implemented-brightgreen)
![Status](https://img.shields.io/badge/Status-Complete-brightgreen)

---

## 🧠 Data Structures Implemented From Scratch

| Module | Data Structure | Why |
|---|---|---|
| 👤 Customer Accounts | **Singly Linked List** | Dynamic customer management |
| 💳 Transaction History | **Doubly Linked List** | Forward & backward traversal |
| 🏦 Loan Applications | **Queue (FIFO)** | First-come, first-served processing |
| 💱 Currency Exchange | **Stack (LIFO)** | Most recent exchange first |
| 🏢 Bank Branches | **Binary Search Tree** | Fast branch lookup by ID |

---

## ✨ Features

### 👤 Customer Management (Singly Linked List)
- Add, remove, and display customer accounts
- Linear Search & Binary Search on customer IDs
- Sort customers by ID or Balance (Bubble Sort)
- File persistence (save/load from `customers.txt`)

### 💳 Transaction Management (Doubly Linked List)
- Record deposits, withdrawals, and transfers
- View full transaction history per customer
- Automatically updates customer balance
- File persistence (save/load from `transactions.txt`)

### 🏦 Loan Applications (Queue)
- Apply for loans (enqueue)
- Process & approve loans (dequeue — FIFO order)
- View all pending loan requests
- File persistence (save/load from `loans.txt`)

### 💱 Currency Exchange Teller (Stack)
- Exchange between 10 currencies (USD, EUR, GBP, EGP, AED, SAR, JPY, CAD, AUD, CHF)
- Real-time exchange rate calculation
- View exchange history (most recent first — LIFO)
- File persistence (save/load from `exchanges.txt`)

### 🏢 Bank Branches (Binary Search Tree)
- Add and remove branches
- Search branches by ID (BST search — O(log n))
- Display all branches in order (in-order traversal)
- File persistence (save/load from `branches.txt`)

---

## 💱 Supported Currencies

| Code | Currency | Rate (vs EGP) |
|---|---|---|
| USD | US Dollar | 49.50 |
| EUR | Euro | 53.80 |
| GBP | British Pound | 62.50 |
| AED | UAE Dirham | 13.48 |
| SAR | Saudi Riyal | 13.20 |
| JPY | Japanese Yen | 0.33 |
| CAD | Canadian Dollar | 35.40 |
| AUD | Australian Dollar | 31.80 |
| CHF | Swiss Franc | 56.20 |
| EGP | Egyptian Pound | 1.00 |

---

## 🚀 How to Run

**Requirements:** C++ compiler (GCC / Visual Studio / MinGW)

```bash
# Clone the repository
git clone https://github.com/AbdallaYoussef006/banking-management-system.git

# Navigate to project
cd banking-management-system

# Compile
g++ -o banking BankingSystem.cpp

# Run
./banking
```

Or open `BankingSystem.vcxproj` in **Visual Studio** and press F5.

---

## 📁 Data Files (Auto-generated)

| File | Contents |
|---|---|
| `customers.txt` | Customer accounts |
| `transactions.txt` | Transaction history |
| `loans.txt` | Pending loan applications |
| `exchanges.txt` | Currency exchange history |
| `branches.txt` | Bank branch directory |

---

## 🎓 About

Built as a **Data Structures Project** at Nile University, Faculty of Computer Science.
Demonstrates: Singly & Doubly Linked Lists, Queue, Stack, Binary Search Tree, file I/O, OOP in C++.

**Developer:** Abdalla Mohamed
**University:** Nile University, Cairo, Egypt
**Year:** 2025
