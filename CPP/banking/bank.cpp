#include <iostream>
#include <vector>
#include <string>
#include <ctime>

class Customer {
public:
    std::string customerID;
    std::string name;
    std::string address;
    std::string phoneNumber;
    std::string email;

    Customer(std::string id, std::string nm, std::string addr, std::string phone, std::string mail)
        : customerID(id), name(nm), address(addr), phoneNumber(phone), email(mail) {}

    void displayCustomerDetails() const {
        std::cout << "Customer ID: " << customerID << "\nName: " << name << "\nAddress: " << address 
                  << "\nPhone Number: " << phoneNumber << "\nEmail: " << email << std::endl;
    }
};

class Account {
public:
    std::string accountNumber;
    std::string customerID;
    std::string accountType;
    double balance;

    Account(std::string accNum, std::string custID, std::string accType, double bal)
        : accountNumber(accNum), customerID(custID), accountType(accType), balance(bal) {}

    void deposit(double amount) {
        balance += amount;
        std::cout << "Deposit Successful. New Balance: $" << balance << std::endl;
    }

    void withdraw(double amount) {
        if (amount > balance) {
            std::cout << "Insufficient funds!" << std::endl;
        } else {
            balance -= amount;
            std::cout << "Withdrawal Successful. New Balance: $" << balance << std::endl;
        }
    }

    void displayAccountDetails() const {
        std::cout << "Account Number: " << accountNumber << "\nCustomer ID: " << customerID 
                  << "\nAccount Type: " << accountType << "\nBalance: $" << balance << std::endl;
    }
};

class Transaction {
public:
    std::string transactionID;
    std::string accountNumber;
    std::string transactionType;
    double amount;
    std::string date;

    Transaction(std::string transID, std::string accNum, std::string transType, double amt)
        : transactionID(transID), accountNumber(accNum), transactionType(transType), amount(amt) {
        time_t now = time(0);
        char* dt = ctime(&now);
        date = std::string(dt);
    }

    void displayTransactionDetails() const {
        std::cout << "Transaction ID: " << transactionID << "\nAccount Number: " << accountNumber 
                  << "\nTransaction Type: " << transactionType << "\nAmount: $" << amount 
                  << "\nDate: " << date << std::endl;
    }
};

class BankingSystem {
private:
    std::vector<Customer> customers;
    std::vector<Account> accounts;
    std::vector<Transaction> transactions;

public:
    void run() {
        int choice;
        do {
            displayMenu();
            std::cout << "Enter your choice: ";
            std::cin >> choice;
            switch (choice) {
                case 1: addCustomer(); break;
                case 2: createAccount(); break;
                case 3: deposit(); break;
                case 4: withdraw(); break;
                case 5: transferFunds(); break;
                case 6: viewCustomerDetails(); break;
                case 7: viewAccountDetails(); break;
                case 8: viewTransactionHistory(); break;
                case 0: std::cout << "Exiting the system." << std::endl; break;
                default: std::cout << "Invalid choice. Please try again." << std::endl;
            }
        } while (choice != 0);
    }

private:
    void displayMenu() {
        std::cout << "\nBanking System Menu:\n"
                  << "1. Add New Customer\n"
                  << "2. Create New Account\n"
                  << "3. Deposit Funds\n"
                  << "4. Withdraw Funds\n"
                  << "5. Transfer Funds\n"
                  << "6. View Customer Details\n"
                  << "7. View Account Details\n"
                  << "8. View Transaction History\n"
                  << "0. Exit\n";
    }

    void addCustomer() {
        std::string id, name, address, phone, email;
        std::cout << "Enter Customer ID: "; std::cin >> id;
        std::cout << "Enter Name: "; std::cin >> name;
        std::cout << "Enter Address: "; std::cin >> address;
        std::cout << "Enter Phone Number: "; std::cin >> phone;
        std::cout << "Enter Email: "; std::cin >> email;
        customers.emplace_back(id, name, address, phone, email);
        std::cout << "Customer added successfully." << std::endl;
    }

    void createAccount() {
        std::string accNum, custID, accType;
        double initialDeposit;
        std::cout << "Enter Account Number: "; std::cin >> accNum;
        std::cout << "Enter Customer ID: "; std::cin >> custID;
        std::cout << "Enter Account Type (Savings/Checking): "; std::cin >> accType;
        std::cout << "Enter Initial Deposit: "; std::cin >> initialDeposit;
        accounts.emplace_back(accNum, custID, accType, initialDeposit);
        std::cout << "Account created successfully." << std::endl;
    }

    void deposit() {
        std::string accNum;
        double amount;
        std::cout << "Enter Account Number: "; std::cin >> accNum;
        std::cout << "Enter Amount to Deposit: "; std::cin >> amount;
        for (auto& account : accounts) {
            if (account.accountNumber == accNum) {
                account.deposit(amount);
                transactions.emplace_back(generateTransactionID(), accNum, "Deposit", amount);
                return;
            }
        }
        std::cout << "Account not found." << std::endl;
    }

    void withdraw() {
        std::string accNum;
        double amount;
        std::cout << "Enter Account Number: "; std::cin >> accNum;
        std::cout << "Enter Amount to Withdraw: "; std::cin >> amount;
        for (auto& account : accounts) {
            if (account.accountNumber == accNum) {
                account.withdraw(amount);
                transactions.emplace_back(generateTransactionID(), accNum, "Withdrawal", amount);
                return;
            }
        }
        std::cout << "Account not found." << std::endl;
    }

    void transferFunds() {
        std::string fromAccNum, toAccNum;
        double amount;
        std::cout << "Enter Source Account Number: "; std::cin >> fromAccNum;
        std::cout << "Enter Destination Account Number: "; std::cin >> toAccNum;
        std::cout << "Enter Amount to Transfer: "; std::cin >> amount;

        Account* fromAccount = nullptr;
        Account* toAccount = nullptr;

        for (auto& account : accounts) {
            if (account.accountNumber == fromAccNum) {
                fromAccount = &account;
            }
            if (account.accountNumber == toAccNum) {
                toAccount = &account;
            }
        }

        if (fromAccount && toAccount) {
            if (fromAccount->balance >= amount) {
                fromAccount->withdraw(amount);
                toAccount->deposit(amount);
                transactions.emplace_back(generateTransactionID(), fromAccNum, "Transfer", -amount);
                transactions.emplace_back(generateTransactionID(), toAccNum, "Transfer", amount);
                std::cout << "Transfer Successful." << std::endl;
            } else {
                std::cout << "Insufficient funds in source account." << std::endl;
            }
        } else {
            std::cout << "Account not found." << std::endl;
        }
    }

    void viewCustomerDetails() const {
        std::string id;
        std::cout << "Enter Customer ID: "; std::cin >> id;
        for (const auto& customer : customers) {
            if (customer.customerID == id) {
                customer.displayCustomerDetails();
                return;
            }
        }
        std::cout << "Customer not found." << std::endl;
    }

    void viewAccountDetails() const {
        std::string accNum;
        std::cout << "Enter Account Number: "; std::cin >> accNum;
        for (const auto& account : accounts) {
            if (account.accountNumber == accNum) {
                account.displayAccountDetails();
                return;
            }
        }
        std::cout << "Account not found." << std::endl;
    }

    void viewTransactionHistory() const {
        std::string accNum;
        std::cout << "Enter Account Number: "; std::cin >> accNum;
        for (const auto& transaction : transactions) {
            if (transaction.accountNumber == accNum) {
                transaction.displayTransactionDetails();
            }
        }
    }

    std::string generateTransactionID() {
        static int id = 1000;
        return "T" + std::to_string(id++);
    }
};

int main() {
    BankingSystem system;
    system.run();
    return 0;
}
