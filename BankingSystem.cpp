#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <sstream>
using namespace std;

// ==================== CUSTOMER ACCOUNTS (Single Linked List) ====================
class Customer_Accounts {
    class Node {
    public:
        int id;
        string name;
        string email;
        int phone;
        int balance;
        Node* next;

        Node() {
            next = nullptr;
            id = 0;
            balance = 0;
            phone = 0;
            name = "";
            email = "";
        }
    };

    Node* head;
    int length;

public:
    Customer_Accounts() {
        head = nullptr;
        length = 0;
    }

    bool is_empty() {
        return head == nullptr;
    }

    void addfirst(int ID, string Name, string Email, int Phone, int Balance) {
        Node* newnode = new Node();
        newnode->id = ID;
        newnode->name = Name;
        newnode->email = Email;
        newnode->phone = Phone;
        newnode->balance = Balance;

        if (is_empty()) {
            head = newnode;
            newnode->next = nullptr;
        }
        else {
            newnode->next = head;
            head = newnode;
        }
        length++;
    }

    void addlast(int ID, string Name, string Email, int Phone, int Balance) {
        Node* newnode = new Node();
        newnode->id = ID;
        newnode->name = Name;
        newnode->email = Email;
        newnode->phone = Phone;
        newnode->balance = Balance;

        if (is_empty()) {
            head = newnode;
            newnode->next = nullptr;
        }
        else {
            Node* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newnode;
            newnode->next = nullptr;
        }
        length++;
    }

    void addposition(int position, int ID, string Name, string Email, int Phone, int Balance) {
        if (position == 1 || is_empty()) {
            addfirst(ID, Name, Email, Phone, Balance);
        }
        else if (position > length) {
            addlast(ID, Name, Email, Phone, Balance);
        }
        else {
            Node* newnode = new Node();
            newnode->id = ID;
            newnode->name = Name;
            newnode->email = Email;
            newnode->phone = Phone;
            newnode->balance = Balance;

            Node* temp = head;
            for (int i = 0; i < position - 2; i++) {
                temp = temp->next;
            }
            newnode->next = temp->next;
            temp->next = newnode;
            length++;
        }
    }

    // Main function to add customer (wrapper)
    void addCustomer(int ID, string Name, string Email, int Phone, int Balance) {
        addlast(ID, Name, Email, Phone, Balance);
        cout << "Customer added successfully!\n";
    }

    void removefirst() {
        if (is_empty()) {
            cout << "There is not any customer account, nothing to remove!\n";
        }
        else if (length == 1) {
            delete head;
            head = nullptr;
            length--;
        }
        else {
            Node* temp = head;
            head = head->next;
            delete temp;
            length--;
        }
    }

    void removelast() {
        if (is_empty()) {
            cout << "There is not any customer account, nothing to remove!\n";
        }
        else if (length == 1) {
            delete head;
            head = nullptr;
            length--;
        }
        else {
            Node* cur = head->next;
            Node* prev = head;
            while (cur->next != nullptr) {
                prev = cur;
                cur = cur->next;
            }
            delete cur;
            prev->next = nullptr;
            length--;
        }
    }

    void removeposition(int position) {
        if (is_empty()) {
            cout << "There is not any customer account, nothing to remove!\n";
        }
        else if (position == 1) {
            removefirst();
        }
        else if (position == length) {
            removelast();
        }
        else {
            Node* temp = head;
            for (int i = 0; i < position - 2; i++) {
                temp = temp->next;
            }
            Node* temp2 = temp->next;
            Node* temp3 = temp2->next;
            delete temp2;
            temp->next = temp3;
            length--;
        }
    }

    void removeCustomer(int ID) {
        Node* temp = head;
        Node* target_id = nullptr;
        int pos = 1;

        while (temp != nullptr) {
            if (temp->id == ID) {
                target_id = temp;
                break;
            }
            temp = temp->next;
            pos++;
        }
        if (target_id != nullptr) {
            removeposition(pos);
            cout << "Customer with ID " << ID << " has been removed.\n";
        }
        else {
            cout << "Customer ID not found!\n";
        }
    }

    void display(int ID) {
        Node* temp = head;
        Node* targetID = nullptr;

        while (temp != nullptr) {
            if (temp->id == ID) {
                targetID = temp;
                break;
            }
            temp = temp->next;
        }

        if (targetID == nullptr) {
            cout << "ID Not Found!\n";
            return;
        }

        cout << "\n========== Customer Details ==========\n";
        cout << "ID: " << targetID->id << "\n";
        cout << "Name: " << targetID->name << "\n";
        cout << "Email: " << targetID->email << "\n";
        cout << "Phone: " << targetID->phone << "\n";
        cout << "Balance: $" << targetID->balance << "\n";
        cout << "======================================\n\n";
    }

    // Display ALL customers
    void displayCustomers() {
        if (is_empty()) {
            cout << "No customers in the system!\n";
            return;
        }

        Node* temp = head;
        cout << "\n========== All Customers ==========\n";
        while (temp != nullptr) {
            cout << "ID: " << temp->id << " | Name: " << temp->name << " | Balance: $" << temp->balance << "\n";
            temp = temp->next;
        }
        cout << "===================================\n\n";
    }

    // Linear Search
    bool linearSearch(int ID) {
        Node* temp = head;
        int comparisons = 0;
        while (temp != nullptr) {
            comparisons++;
            if (temp->id == ID) {
                cout << "Linear Search: Found after " << comparisons << " comparisons.\n";
                return true;
            }
            temp = temp->next;
        }
        cout << "Linear Search: Not found after " << comparisons << " comparisons.\n";
        return false;
    }

    // Convert linked list to array for sorting
    int* toArray(int& size) {
        size = length;
        if (size == 0) return nullptr;

        int* arr = new int[size];
        Node* temp = head;
        int i = 0;
        while (temp != nullptr) {
            arr[i++] = temp->id;
            temp = temp->next;
        }
        return arr;
    }

    // Binary Search (requires sorted IDs)
    bool binarySearch(int ID) {
        int size;
        int* arr = toArray(size);
        if (arr == nullptr) {
            cout << "No customers to search!\n";
            return false;
        }

        // First sort the array
        sort(arr, arr + size);

        int left = 0, right = size - 1;
        int comparisons = 0;
        bool found = false;

        while (left <= right) {
            comparisons++;
            int mid = left + (right - left) / 2;

            if (arr[mid] == ID) {
                found = true;
                break;
            }
            else if (arr[mid] < ID) {
                left = mid + 1;
            }
            else {
                right = mid - 1;
            }
        }

        delete[] arr;

        if (found) {
            cout << "Binary Search: Found after " << comparisons << " comparisons.\n";
        }
        else {
            cout << "Binary Search: Not found after " << comparisons << " comparisons.\n";
        }
        return found;
    }

    // Bubble Sort by ID
    void sortByID() {
        if (is_empty() || length == 1) {
            cout << "Nothing to sort!\n";
            return;
        }

        bool swapped;
        Node* ptr1;
        Node* lptr = nullptr;

        do {
            swapped = false;
            ptr1 = head;

            while (ptr1->next != lptr) {
                if (ptr1->id > ptr1->next->id) {
                    // Swap data
                    swap(ptr1->id, ptr1->next->id);
                    swap(ptr1->name, ptr1->next->name);
                    swap(ptr1->email, ptr1->next->email);
                    swap(ptr1->phone, ptr1->next->phone);
                    swap(ptr1->balance, ptr1->next->balance);
                    swapped = true;
                }
                ptr1 = ptr1->next;
            }
            lptr = ptr1;
        } while (swapped);

        cout << "Customers sorted by ID successfully!\n";
    }

    // Sort by Balance (Descending)
    void sortByBalance() {
        if (is_empty() || length == 1) {
            cout << "Nothing to sort!\n";
            return;
        }

        bool swapped;
        Node* ptr1;
        Node* lptr = nullptr;

        do {
            swapped = false;
            ptr1 = head;

            while (ptr1->next != lptr) {
                if (ptr1->balance < ptr1->next->balance) {
                    // Swap data
                    swap(ptr1->id, ptr1->next->id);
                    swap(ptr1->name, ptr1->next->name);
                    swap(ptr1->email, ptr1->next->email);
                    swap(ptr1->phone, ptr1->next->phone);
                    swap(ptr1->balance, ptr1->next->balance);
                    swapped = true;
                }
                ptr1 = ptr1->next;
            }
            lptr = ptr1;
        } while (swapped);

        cout << "Customers sorted by Balance (High to Low) successfully!\n";
    }

    // Helper function to get customer balance
    int getBalance(int ID) {
        Node* temp = head;
        while (temp != nullptr) {
            if (temp->id == ID) {
                return temp->balance;
            }
            temp = temp->next;
        }
        return -1;
    }

    // Update balance for transactions
    void updateBalance(int ID, int amount) {
        Node* temp = head;
        while (temp != nullptr) {
            if (temp->id == ID) {
                temp->balance += amount;
                return;
            }
            temp = temp->next;
        }
    }

    // Get total number of customers
    int getLength() {
        return length;
    }

    // Save customers to file
    void saveToFile(string filename = "customers.txt") {
        ofstream file(filename);
        if (!file) {
            cout << "Error opening file for writing!\n";
            return;
        }

        Node* temp = head;
        while (temp != nullptr) {
            file << temp->id << ","
                << temp->name << ","
                << temp->email << ","
                << temp->phone << ","
                << temp->balance << "\n";
            temp = temp->next;
        }
        file.close();
        cout << "Customer data saved to " << filename << " successfully!\n";
    }

    // Load customers from file
    void loadFromFile(string filename = "customers.txt") {
        ifstream file(filename);
        if (!file) {
            cout << "No previous data found. Starting fresh.\n";
            return;
        }

        string line;
        int count = 0;
        while (getline(file, line)) {
            stringstream ss(line);
            string idStr, name, email, phoneStr, balanceStr;

            getline(ss, idStr, ',');
            getline(ss, name, ',');
            getline(ss, email, ',');
            getline(ss, phoneStr, ',');
            getline(ss, balanceStr, ',');

            int id = stoi(idStr);
            int phone = stoi(phoneStr);
            int balance = stoi(balanceStr);

            addlast(id, name, email, phone, balance);
            count++;
        }
        file.close();
        cout << "Loaded " << count << " customers from " << filename << "\n";
    }
};


// ==================== TRANSACTION HISTORY (Double Linked List) ====================
class Transaction_History {
    class Node {
    public:
        int deposit;
        int withdraw;
        int transfer;
        int id;
        Node* next;
        Node* prev;

        Node() {
            next = nullptr;
            prev = nullptr;
            deposit = 0;
            withdraw = 0;
            transfer = 0;
            id = 0;
        }
    };

    Node* head;
    Node* tail;
    int length;

public:
    Transaction_History() {
        head = nullptr;
        tail = nullptr;
        length = 0;
    }

    bool isempty() {
        return head == nullptr;
    }

    void addTransaction(int ID, int Deposit, int Withdraw, int Transfer) {
        Node* newnode = new Node();
        newnode->deposit = Deposit;
        newnode->withdraw = Withdraw;
        newnode->transfer = Transfer;
        newnode->id = ID;

        if (isempty()) {
            head = tail = newnode;
            newnode->next = nullptr;
            newnode->prev = nullptr;
        }
        else {
            tail->next = newnode;
            newnode->prev = tail;
            newnode->next = nullptr;
            tail = newnode;
        }
        length++;
        cout << "Transaction recorded successfully!\n";
    }

    void viewTransactions(int ID) {
        Node* temp = head;
        bool found = false;

        cout << "\n========== Transaction History for ID: " << ID << " ==========\n";
        while (temp != nullptr) {
            if (temp->id == ID) {
                found = true;
                cout << "Deposit: $" << temp->deposit << " | Withdrawal: $" << temp->withdraw << " | Transfer: $" << temp->transfer << "\n";
            }
            temp = temp->next;
        }

        if (!found) {
            cout << "No transactions found for this ID!\n";
        }
        cout << "====================================================\n\n";
    }

    // Linear Search in Transactions
    bool linearSearchTransaction(int ID) {
        Node* temp = head;
        int comparisons = 0;
        while (temp != nullptr) {
            comparisons++;
            if (temp->id == ID) {
                cout << "Transaction Linear Search: Found after " << comparisons << " comparisons.\n";
                return true;
            }
            temp = temp->next;
        }
        cout << "Transaction Linear Search: Not found after " << comparisons << " comparisons.\n";
        return false;
    }

    // Get all transactions
    void displayAllTransactions() {
        if (isempty()) {
            cout << "No transactions in the system!\n";
            return;
        }

        Node* temp = head;
        cout << "\n========== All Transactions ==========\n";
        while (temp != nullptr) {
            cout << "ID: " << temp->id << " | Deposit: $" << temp->deposit << " | Withdrawal: $" << temp->withdraw << " | Transfer: $" << temp->transfer << "\n";
            temp = temp->next;
        }
        cout << "======================================\n\n";
    }

    // Save transactions to file
    void saveToFile(string filename = "transactions.txt") {
        ofstream file(filename);
        if (!file) {
            cout << "Error opening file for writing!\n";
            return;
        }

        Node* temp = head;
        while (temp != nullptr) {
            file << temp->id << ","
                << temp->deposit << ","
                << temp->withdraw << ","
                << temp->transfer << "\n";
            temp = temp->next;
        }
        file.close();
        cout << "Transaction data saved to " << filename << " successfully!\n";
    }

    // Load transactions from file
    void loadFromFile(string filename = "transactions.txt") {
        ifstream file(filename);
        if (!file) {
            cout << "No previous transaction data found.\n";
            return;
        }

        string line;
        int count = 0;
        while (getline(file, line)) {
            stringstream ss(line);
            string idStr, depositStr, withdrawStr, transferStr;

            getline(ss, idStr, ',');
            getline(ss, depositStr, ',');
            getline(ss, withdrawStr, ',');
            getline(ss, transferStr, ',');

            int id = stoi(idStr);
            int deposit = stoi(depositStr);
            int withdraw = stoi(withdrawStr);
            int transfer = stoi(transferStr);

            addTransaction(id, deposit, withdraw, transfer);
            count++;
        }
        file.close();
        cout << "Loaded " << count << " transactions from " << filename << "\n";
    }
};


// ==================== LOAN APPLICATIONS (Queue) ====================
class Loan_Applications {
    class Node {
    public:
        int loan;
        int customerID;
        Node* next;

        Node() {
            loan = 0;
            customerID = 0;
            next = nullptr;
        }
    };

    Node* front;
    Node* rear;
    int length;

public:
    Loan_Applications() {
        front = rear = nullptr;
        length = 0;
    }

    bool isempty() {
        return (front == nullptr && rear == nullptr);
    }

    void enqueueLoan(int CustomerID, int Loan) {
        Node* newnode = new Node();
        newnode->loan = Loan;
        newnode->customerID = CustomerID;

        if (isempty()) {
            front = rear = newnode;
        }
        else {
            rear->next = newnode;
            rear = newnode;
        }
        length++;
        cout << "Loan request of $" << Loan << " for Customer ID " << CustomerID << " has been added to queue.\n";
    }

    void dequeueLoan() {
        if (isempty()) {
            cout << "There are no pending loan requests!\n";
        }
        else if (front == rear) {
            int pend_loan = front->loan;
            int custID = front->customerID;
            delete front;
            rear = front = nullptr;
            length--;
            cout << "Loan of $" << pend_loan << " for Customer ID " << custID << " has been processed and approved!\n";
        }
        else {
            Node* pendloan = front;
            int pend_loan = front->loan;
            int custID = front->customerID;
            front = front->next;
            delete pendloan;
            length--;
            cout << "Loan of $" << pend_loan << " for Customer ID " << custID << " has been processed and approved!\n";
        }
    }

    void displayPendingLoans() {
        if (isempty()) {
            cout << "No pending loan requests.\n";
            return;
        }

        Node* temp = front;
        cout << "\n========== Pending Loan Requests ==========\n";
        while (temp != nullptr) {
            cout << "Customer ID: " << temp->customerID << " | Loan Amount: $" << temp->loan << "\n";
            temp = temp->next;
        }
        cout << "===========================================\n\n";
    }

    // Save loans to file
    void saveToFile(string filename = "loans.txt") {
        ofstream file(filename);
        if (!file) {
            cout << "Error opening file for writing!\n";
            return;
        }

        Node* temp = front;
        while (temp != nullptr) {
            file << temp->customerID << ","
                << temp->loan << "\n";
            temp = temp->next;
        }
        file.close();
        cout << "Loan data saved to " << filename << " successfully!\n";
    }

    // Load loans from file
    void loadFromFile(string filename = "loans.txt") {
        ifstream file(filename);
        if (!file) {
            cout << "No previous loan data found.\n";
            return;
        }

        string line;
        int count = 0;
        while (getline(file, line)) {
            stringstream ss(line);
            string custIDStr, loanStr;

            getline(ss, custIDStr, ',');
            getline(ss, loanStr, ',');

            int custID = stoi(custIDStr);
            int loan = stoi(loanStr);

            Node* newnode = new Node();
            newnode->customerID = custID;
            newnode->loan = loan;

            if (isempty()) {
                front = rear = newnode;
            }
            else {
                rear->next = newnode;
                rear = newnode;
            }
            length++;
            count++;
        }
        file.close();
        cout << "Loaded " << count << " loan requests from " << filename << "\n";
    }
};



// ==================== CURRENCY EXCHANGE TELLER (Stack) ====================
class Currency_Teller {
    class Transaction {
    public:
        string sourceCurrency;
        string targetCurrency;
        double sourceAmount;
        double targetAmount;
        int customerID;
        Transaction* next;

        Transaction() {
            sourceCurrency = "";
            targetCurrency = "";
            sourceAmount = 0.0;
            targetAmount = 0.0;
            customerID = 0;
            next = nullptr;
        }
    };

    Transaction* top;
    int length;

    // Currency data
    string currencies[10] = { "AED", "AUD", "CAD", "CHF", "EGP",
                             "EUR", "GBP", "JPY", "SAR", "USD" };
    string currencyNames[10] = { "UAE Dirham", "Australian Dollar", "Canadian Dollar",
                                "Swiss Franc", "Egyptian Pound", "Euro",
                                "British Pound", "Japanese Yen", "Saudi Riyal", "US Dollar" };
    double exchangeRates[10] = { 13.48, 31.80, 35.40, 56.20, 1.0,
                                53.80, 62.50, 0.33, 13.20, 49.50 };

public:
    Currency_Teller() {
        top = nullptr;
        length = 0;
    }

    bool isempty() {
        return top == nullptr;
    }

    // Convert string to uppercase
    string toUpper(string str) {
        for (int i = 0; i < str.length(); i++) {
            str[i] = toupper(str[i]);
        }
        return str;
    }

    // Find currency index
    int findCurrencyIndex(string currency) {
        currency = toUpper(currency);
        for (int i = 0; i < 10; i++) {
            if (currencies[i] == currency) {
                return i;
            }
        }
        return -1;
    }

    // Display available currencies
    void displayAvailableCurrencies() {
        cout << "\n========== Available Currencies ==========\n";
        for (int i = 0; i < 10; i++) {
            cout << currencies[i] << " - " << currencyNames[i] << " (1 " << currencies[i] << " = " << exchangeRates[i] << " EGP)\n";
        }
        cout << "==========================================\n\n";
    }

    // Push exchange transaction (Stack operation)
    void pushExchange(int customerID, string sourceCurr, string targetCurr, double amount) {
        sourceCurr = toUpper(sourceCurr);
        targetCurr = toUpper(targetCurr);

        int sourceIndex = findCurrencyIndex(sourceCurr);
        int targetIndex = findCurrencyIndex(targetCurr);

        if (sourceIndex == -1) {
            cout << "Error: Source currency '" << sourceCurr << "' not found!\n";
            displayAvailableCurrencies();
            return;
        }

        if (targetIndex == -1) {
            cout << "Error: Target currency '" << targetCurr << "' not found!\n";
            displayAvailableCurrencies();
            return;
        }

        if (amount <= 0) {
            cout << "Error: Amount must be positive!\n";
            return;
        }

        // Calculate exchange
        double amountInEGP = amount * exchangeRates[sourceIndex];
        double result = amountInEGP / exchangeRates[targetIndex];

        // Create transaction node
        Transaction* newTransaction = new Transaction();
        newTransaction->customerID = customerID;
        newTransaction->sourceCurrency = sourceCurr;
        newTransaction->targetCurrency = targetCurr;
        newTransaction->sourceAmount = amount;
        newTransaction->targetAmount = result;

        // Push to stack
        if (isempty()) {
            top = newTransaction;
            newTransaction->next = nullptr;
        }
        else {
            newTransaction->next = top;
            top = newTransaction;
        }
        length++;

        // Display result
        cout << "\n========================================\n";
        cout << "   CURRENCY EXCHANGE SUCCESSFUL\n";
        cout << "========================================\n";
        cout << "Customer ID: " << customerID << "\n";
        cout << "Exchanged: " << amount << " " << sourceCurr << " (" << currencyNames[sourceIndex] << ")\n";
        cout << "Received: " << result << " " << targetCurr << " (" << currencyNames[targetIndex] << ")\n";
        cout << "Exchange Rate: 1 " << sourceCurr << " = " << (exchangeRates[sourceIndex] / exchangeRates[targetIndex]) << " " << targetCurr << "\n";
        cout << "========================================\n\n";
    }

    // Pop (Process/Remove most recent exchange)
    void popExchange() {
        if (isempty()) {
            cout << "No exchange transactions to process!\n";
            return;
        }

        Transaction* temp = top;
        cout << "\n========== Processing Recent Exchange ==========\n";
        cout << "Customer ID: " << top->customerID << "\n";
        cout << "Exchange: " << top->sourceAmount << " " << top->sourceCurrency << " → " << top->targetAmount << " " << top->targetCurrency << "\n";
        cout << "Transaction removed from history.\n";
        cout << "================================================\n\n";

        top = top->next;
        delete temp;
        length--;
    }

    // Display all exchange history (Stack view)
    void displayExchangeHistory() {
        if (isempty()) {
            cout << "No exchange transactions in history!\n";
            return;
        }

        Transaction* temp = top;
        cout << "\n========== Exchange History (Most Recent First) ==========\n";
        int count = 1;
        while (temp != nullptr) {
            cout << count << ". Customer ID: " << temp->customerID << " | "
                << temp->sourceAmount << " " << temp->sourceCurrency << " → "
                << temp->targetAmount << " " << temp->targetCurrency << "\n";
            temp = temp->next;
            count++;
        }
        cout << "==========================================================\n\n";
    }

    // View top exchange without removing
    void viewTopExchange() {
        if (isempty()) {
            cout << "No exchange transactions in history!\n";
            return;
        }

        cout << "\n========== Most Recent Exchange ==========\n";
        cout << "Customer ID: " << top->customerID << "\n";
        cout << "Exchange: " << top->sourceAmount << " " << top->sourceCurrency << " → "
            << top->targetAmount << " " << top->targetCurrency << "\n";
        cout << "==========================================\n\n";
    }

    // Save exchange history to file
    void saveToFile(string filename = "exchanges.txt") {
        ofstream file(filename);
        if (!file) {
            cout << "Error opening file for writing!\n";
            return;
        }

        Transaction* temp = top;
        while (temp != nullptr) {
            file << temp->customerID << ","
                << temp->sourceCurrency << ","
                << temp->targetCurrency << ","
                << temp->sourceAmount << ","
                << temp->targetAmount << "\n";
            temp = temp->next;
        }
        file.close();
        cout << "Exchange data saved to " << filename << " successfully!\n";
    }

    // Load exchange history from file
    void loadFromFile(string filename = "exchanges.txt") {
        ifstream file(filename);
        if (!file) {
            cout << "No previous exchange data found.\n";
            return;
        }

        string line;
        int count = 0;
        while (getline(file, line)) {
            stringstream ss(line);
            string custIDStr, sourceCurr, targetCurr, sourceAmtStr, targetAmtStr;

            getline(ss, custIDStr, ',');
            getline(ss, sourceCurr, ',');
            getline(ss, targetCurr, ',');
            getline(ss, sourceAmtStr, ',');
            getline(ss, targetAmtStr, ',');

            int custID = stoi(custIDStr);
            double sourceAmt = stod(sourceAmtStr);
            double targetAmt = stod(targetAmtStr);

            Transaction* newTransaction = new Transaction();
            newTransaction->customerID = custID;
            newTransaction->sourceCurrency = sourceCurr;
            newTransaction->targetCurrency = targetCurr;
            newTransaction->sourceAmount = sourceAmt;
            newTransaction->targetAmount = targetAmt;

            if (isempty()) {
                top = newTransaction;
                newTransaction->next = nullptr;
            }
            else {
                newTransaction->next = top;
                top = newTransaction;
            }
            length++;
            count++;
        }
        file.close();
        cout << "Loaded " << count << " exchange transactions from " << filename << "\n";
    }
};


// ==================== BANK BRANCHES (Binary Search Tree) ====================
class Bank_Branches {
    class Node {
    public:
        int branchID;
        string branchName;
        string location;
        Node* left;
        Node* right;

        Node() {
            branchID = 0;
            branchName = "";
            location = "";
            left = nullptr;
            right = nullptr;
        }
    };

    Node* root;

    // Helper function to insert recursively
    Node* insertNode(Node* node, int ID, string Name, string Location) {
        if (node == nullptr) {
            Node* newnode = new Node();
            newnode->branchID = ID;
            newnode->branchName = Name;
            newnode->location = Location;
            return newnode;
        }

        if (ID < node->branchID) {
            node->left = insertNode(node->left, ID, Name, Location);
        }
        else if (ID > node->branchID) {
            node->right = insertNode(node->right, ID, Name, Location);
        }
        else {
            cout << "Branch ID already exists!\n";
        }
        return node;
    }

    // Helper function to find minimum value node
    Node* minValueNode(Node* node) {
        Node* current = node;
        while (current && current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

    // Helper function to delete recursively
    Node* deleteNode(Node* node, int ID) {
        if (node == nullptr) {
            return node;
        }

        if (ID < node->branchID) {
            node->left = deleteNode(node->left, ID);
        }
        else if (ID > node->branchID) {
            node->right = deleteNode(node->right, ID);
        }
        else {
            // Node found
            if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                return temp;
            }
            else if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                return temp;
            }

            // Node with two children
            Node* temp = minValueNode(node->right);
            node->branchID = temp->branchID;
            node->branchName = temp->branchName;
            node->location = temp->location;
            node->right = deleteNode(node->right, temp->branchID);
        }
        return node;
    }

    // Helper function to search
    Node* searchNode(Node* node, int ID) {
        if (node == nullptr || node->branchID == ID) {
            return node;
        }

        if (ID < node->branchID) {
            return searchNode(node->left, ID);
        }
        return searchNode(node->right, ID);
    }

    // Helper function for in-order traversal
    void inorder(Node* node) {
        if (node != nullptr) {
            inorder(node->left);
            cout << "Branch ID: " << node->branchID << " | Name: " << node->branchName << " | Location: " << node->location << "\n";
            inorder(node->right);
        }
    }

public:
    Bank_Branches() {
        root = nullptr;
    }

    void addBranch(int ID, string Name, string Location) {
        root = insertNode(root, ID, Name, Location);
        cout << "Branch added successfully!\n";
    }

    void removeBranch(int ID) {
        root = deleteNode(root, ID);
        cout << "Branch with ID " << ID << " removed successfully!\n";
    }

    void searchBranch(int ID) {
        Node* result = searchNode(root, ID);
        if (result != nullptr) {
            cout << "\n========== Branch Found ==========\n";
            cout << "Branch ID: " << result->branchID << "\n";
            cout << "Name: " << result->branchName << "\n";
            cout << "Location: " << result->location << "\n";
            cout << "==================================\n\n";
        }
        else {
            cout << "Branch not found!\n";
        }
    }

    void displayBranches() {
        if (root == nullptr) {
            cout << "No branches in the system!\n";
            return;
        }
        cout << "\n========== All Bank Branches ==========\n";
        inorder(root);
        cout << "=======================================\n\n";
    }

    // Save branches to file (in-order traversal)
    void saveToFileHelper(Node* node, ofstream& file) {
        if (node != nullptr) {
            saveToFileHelper(node->left, file);
            file << node->branchID << ","
                << node->branchName << ","
                << node->location << "\n";
            saveToFileHelper(node->right, file);
        }
    }

    void saveToFile(string filename = "branches.txt") {
        ofstream file(filename);
        if (!file) {
            cout << "Error opening file for writing!\n";
            return;
        }

        saveToFileHelper(root, file);
        file.close();
        cout << "Branch data saved to " << filename << " successfully!\n";
    }

    // Load branches from file
    void loadFromFile(string filename = "branches.txt") {
        ifstream file(filename);
        if (!file) {
            cout << "No previous branch data found.\n";
            return;
        }

        string line;
        int count = 0;
        while (getline(file, line)) {
            stringstream ss(line);
            string idStr, name, location;

            getline(ss, idStr, ',');
            getline(ss, name, ',');
            getline(ss, location);

            int id = stoi(idStr);
            root = insertNode(root, id, name, location);
            count++;
        }
        file.close();
        cout << "Loaded " << count << " branches from " << filename << "\n";
    }
};


// ==================== MAIN MENU ====================
int main() {
    Customer_Accounts customers;
    Transaction_History transactions;
    Loan_Applications loans;
    Currency_Teller teller;
    Bank_Branches branches;

    // Load all data from files at startup
    cout << "\n========== Loading Data ==========\n";
    customers.loadFromFile();
    transactions.loadFromFile();
    loans.loadFromFile();
    teller.loadFromFile();
    branches.loadFromFile();
    cout << "==================================\n";

    int choice;

    do {
        cout << "\n";
        cout << "=============================================\n";
        cout << "=   ROYAL BANK - MANAGEMENT SYSTEM          =\n";
        cout << "=============================================\n";
        cout << "=  1.  Customer Management                   =\n";
        cout << "=  2.  Transaction Management                =\n";
        cout << "=  3.  Loan Applications                     =\n";
        cout << "=  4.  Currency Exchange Teller              =\n";
        cout << "=  5.  Bank Branches                         =\n";
        cout << "=  6.  Save All Data                         =\n";
        cout << "=  0.  Exit                                  =\n";
        cout << "=============================================\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            int subChoice;
            cout << "\n--- Customer Management ---\n";
            cout << "1. Add Customer\n";
            cout << "2. Remove Customer\n";
            cout << "3. Display Customer\n";
            cout << "4. Display All Customers\n";
            cout << "5. Search Customer (Linear)\n";
            cout << "6. Search Customer (Binary)\n";
            cout << "7. Sort Customers by ID\n";
            cout << "8. Sort Customers by Balance\n";
            cout << "Enter choice: ";
            cin >> subChoice;

            if (subChoice == 1) {
                int id, phone, balance;
                string name, email;
                cout << "Enter ID: "; cin >> id;
                cin.ignore();
                cout << "Enter Name: "; getline(cin, name);
                cout << "Enter Email: "; cin >> email;
                cout << "Enter Phone: "; cin >> phone;
                cout << "Enter Initial Balance: "; cin >> balance;
                customers.addCustomer(id, name, email, phone, balance);
            }
            else if (subChoice == 2) {
                int id;
                cout << "Enter Customer ID to remove: "; cin >> id;
                customers.removeCustomer(id);
            }
            else if (subChoice == 3) {
                int id;
                cout << "Enter Customer ID to display: "; cin >> id;
                customers.display(id);
            }
            else if (subChoice == 4) {
                customers.displayCustomers();
            }
            else if (subChoice == 5) {
                int id;
                cout << "Enter Customer ID to search: "; cin >> id;
                if (customers.linearSearch(id)) {
                    customers.display(id);
                }
            }
            else if (subChoice == 6) {
                int id;
                cout << "Enter Customer ID to search: "; cin >> id;
                if (customers.binarySearch(id)) {
                    customers.display(id);
                }
            }
            else if (subChoice == 7) {
                customers.sortByID();
            }
            else if (subChoice == 8) {
                customers.sortByBalance();
            }
            break;
        }

        case 2: {
            int subChoice;
            cout << "\n--- Transaction Management ---\n";
            cout << "1. Add Deposit\n";
            cout << "2. Add Withdrawal\n";
            cout << "3. Add Transfer\n";
            cout << "4. View Transaction History\n";
            cout << "5. View All Transactions\n";
            cout << "6. Search Transaction by Customer ID\n";
            cout << "Enter choice: ";
            cin >> subChoice;

            if (subChoice == 1) {
                int id, amount;
                cout << "Enter Customer ID: "; cin >> id;
                cout << "Enter Deposit Amount: "; cin >> amount;
                transactions.addTransaction(id, amount, 0, 0);
                customers.updateBalance(id, amount);
            }
            else if (subChoice == 2) {
                int id, amount;
                cout << "Enter Customer ID: "; cin >> id;
                cout << "Enter Withdrawal Amount: "; cin >> amount;
                transactions.addTransaction(id, 0, amount, 0);
                customers.updateBalance(id, -amount);
            }
            else if (subChoice == 3) {
                int id, amount;
                cout << "Enter Customer ID: "; cin >> id;
                cout << "Enter Transfer Amount: "; cin >> amount;
                transactions.addTransaction(id, 0, 0, amount);
                customers.updateBalance(id, -amount);
            }
            else if (subChoice == 4) {
                int id;
                cout << "Enter Customer ID: "; cin >> id;
                transactions.viewTransactions(id);
            }
            else if (subChoice == 5) {
                transactions.displayAllTransactions();
            }
            else if (subChoice == 6) {
                int id;
                cout << "Enter Customer ID to search: "; cin >> id;
                if (transactions.linearSearchTransaction(id)) {
                    transactions.viewTransactions(id);
                }
            }
            break;
        }

        case 3: {
            int subChoice;
            cout << "\n--- Loan Applications ---\n";
            cout << "1. Apply for Loan\n";
            cout << "2. Process Loan (Approve)\n";
            cout << "3. View Pending Loans\n";
            cout << "Enter choice: ";
            cin >> subChoice;

            if (subChoice == 1) {
                int id, amount;
                cout << "Enter Customer ID: "; cin >> id;
                cout << "Enter Loan Amount: "; cin >> amount;
                loans.enqueueLoan(id, amount);
            }
            else if (subChoice == 2) {
                loans.dequeueLoan();
            }
            else if (subChoice == 3) {
                loans.displayPendingLoans();
            }
            break;
        }

        case 4: {
            int subChoice;
            cout << "\n--- Currency Exchange Teller ---\n";
            cout << "1. Exchange Currency\n";
            cout << "2. View Available Currencies\n";
            cout << "3. View Exchange History\n";
            cout << "4. View Most Recent Exchange\n";
            cout << "5. Process/Remove Recent Exchange\n";
            cout << "Enter choice: ";
            cin >> subChoice;

            if (subChoice == 1) {
                int custID;
                string sourceCurr, targetCurr;
                double amount;
                cout << "Enter Customer ID: "; cin >> custID;
                cout << "Enter Source Currency (e.g., USD): "; cin >> sourceCurr;
                cout << "Enter Target Currency (e.g., EGP): "; cin >> targetCurr;
                cout << "Enter Amount: "; cin >> amount;
                teller.pushExchange(custID, sourceCurr, targetCurr, amount);
            }
            else if (subChoice == 2) {
                teller.displayAvailableCurrencies();
            }
            else if (subChoice == 3) {
                teller.displayExchangeHistory();
            }
            else if (subChoice == 4) {
                teller.viewTopExchange();
            }
            else if (subChoice == 5) {
                teller.popExchange();
            }
            break;
        }

        case 5: {
            int subChoice;
            cout << "\n--- Bank Branches ---\n";
            cout << "1. Add Branch\n";
            cout << "2. Remove Branch\n";
            cout << "3. Search Branch\n";
            cout << "4. Display All Branches\n";
            cout << "Enter choice: ";
            cin >> subChoice;

            if (subChoice == 1) {
                int id;
                string name, location;
                cout << "Enter Branch ID: "; cin >> id;
                cin.ignore();
                cout << "Enter Branch Name: "; getline(cin, name);
                cout << "Enter Location: "; getline(cin, location);
                branches.addBranch(id, name, location);
            }
            else if (subChoice == 2) {
                int id;
                cout << "Enter Branch ID to remove: "; cin >> id;
                branches.removeBranch(id);
            }
            else if (subChoice == 3) {
                int id;
                cout << "Enter Branch ID to search: "; cin >> id;
                branches.searchBranch(id);
            }
            else if (subChoice == 4) {
                branches.displayBranches();
            }
            break;
        }

        case 6: {
            cout << "\n========== Saving All Data ==========\n";
            customers.saveToFile();
            transactions.saveToFile();
            loans.saveToFile();
            teller.saveToFile();
            branches.saveToFile();
            cout << "All data saved successfully!\n";
            cout << "=====================================\n";
            break;
        }

        case 0:
            cout << "\n========== Saving All Data Before Exit ==========\n";
            customers.saveToFile();
            transactions.saveToFile();
            loans.saveToFile();
            teller.saveToFile();
            branches.saveToFile();
            cout << "=================================================\n";
            cout << "\nThank you for using Royal Bank Management System!\n";
            break;

        default:
            cout << "\nInvalid choice! Please try again.\n";
        }

    } while (choice != 0);

    return 0;
}