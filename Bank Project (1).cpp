#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

struct Customer {
    int id;
    string name;
    string address;
    double balance;
    double loanAmount = 0.0; 
};


vector<Customer> customers;


const string ADMIN_USERNAME = "admin";
const string ADMIN_PASSWORD = "password123";


void adminMenu();
void customerMenu();
void addCustomer();
void viewCustomers();
void updateCustomer();
void deleteCustomer();
void withdrawBalance();
void addBalance();
void viewBalance();
void loanCalculator();
void applyForLoan();
bool authenticateAdmin();
void mainMenu();

int main() {
    mainMenu(); 
    return 0;   
}

void mainMenu() {
    int choice;
    do {
        cout << "\n=== Bank Management System ===" << endl;
        cout << "1. Admin Menu" << endl;
        cout << "2. Customer Menu" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                if (authenticateAdmin()) {
                    adminMenu();
                } else {
                    cout << "Invalid credentials. Access denied!" << endl;
                }
                break;
            case 2: customerMenu(); break;
            case 3: cout << "Exiting the system. Goodbye!" << endl; break;
            default: cout << "Invalid choice. Please try again!" << endl;
        }
    } while (choice != 3);
}

double calculateMonthlyPayment(double principal, double annualRate, int years) {
    double monthlyRate = annualRate / 12 / 100; 
    int totalMonths = years * 12;              
    double factor = 1.0;

    
    for (int i = 0; i < totalMonths; i++) {
        factor *= (1 + monthlyRate);
    }

   
    double monthlyPayment = principal * (monthlyRate * factor) / (factor - 1);
    return monthlyPayment;
}

bool authenticateAdmin() {
    string username, password;
    cout << "\nEnter Admin Username: ";
    cin >> username;
    cout << "Enter Admin Password: ";
    cin >> password;

    if (username == ADMIN_USERNAME && password == ADMIN_PASSWORD) {
        cout << "Admin login successful!" << endl;
        return true;
    }
    return false;
}


void adminMenu() {
    int choice;
    do {
        cout << "\n=== Admin Menu ===" << endl;
        cout << "1. Add Customer" << endl;
        cout << "2. View All Customers" << endl;
        cout << "3. Update Customer" << endl;
        cout << "4. Delete Customer" << endl;
        cout << "5. Logout" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addCustomer(); break;
            case 2: viewCustomers(); break;
            case 3: updateCustomer(); break;
            case 4: deleteCustomer(); break;
            case 5: cout << "Logging out from Admin Menu." << endl; break;
            default: cout << "Invalid choice. Please try again!" << endl;
        }
    } while (choice != 5);
}


void customerMenu() {
    int choice;
    do {
        cout << "\n=== Customer Menu ===" << endl;
        cout << "1. Withdraw Balance" << endl;
        cout << "2. Add Balanace" << endl;
        cout << "3. View Balance" << endl;
        cout << "4. Loan Calculator" << endl;
        cout << "5. Apply for Loan" << endl;
        cout << "6. Logout" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: withdrawBalance(); break;
            case 2: addBalance(); break;
            case 3: viewBalance(); break;
            case 4: loanCalculator(); break;
            case 5: applyForLoan(); break;
            case 6: cout << "Logging out from Customer Menu." << endl; break;
            default: cout << "Invalid choice. Please try again!" << endl;
        }
    } while (choice != 6);
}

void addCustomer() {
    Customer cust;
    cout << "Enter Customer ID: ";
    cin >> cust.id;
    cin.ignore(); 
    cout << "Enter Customer Name: ";
    getline(cin, cust.name);
    cout << "Enter Customer Address: ";
    getline(cin, cust.address);
    cout << "Enter Initial Balance: ";
    cin >> cust.balance;

    customers.push_back(cust);
    cout << "Customer added successfully!" << endl;
}

void viewCustomers() {
    if (customers.empty()) {
        cout << "No customers to display!" << endl;
        return;
    }
    cout << "\n=== Customer List ===" << endl;
    for (const auto& cust : customers) {
        cout << "ID: " << cust.id 
             << ", Name: " << cust.name 
             << ", Address: " << cust.address 
             << ", Balance: $" << fixed << setprecision(2) << cust.balance << endl;
    }
}

void updateCustomer() {
    int id;
    cout << "Enter Customer ID to update: ";
    cin >> id;

    for (auto& cust : customers) {
        if (cust.id == id) {
            cout << "Enter New Name: ";
            cin.ignore();
            getline(cin, cust.name);
            cout << "Enter New Address: ";
            getline(cin, cust.address);
            cout << "Enter New Balance: ";
            cin >> cust.balance;

            cout << "Customer updated successfully!" << endl;
            return;
        }
    }
    cout << "Customer with ID " << id << " not found!" << endl;
}


void deleteCustomer() {
    int id;
    cout << "Enter Customer ID to delete: ";
    cin >> id;

    for (auto it = customers.begin(); it != customers.end(); ++it) {
        if (it->id == id) {
            customers.erase(it);
            cout << "Customer deleted successfully!" << endl;
            return;
        }
    }
    cout << "Customer with ID " << id << " not found!" << endl;
}


void withdrawBalance() {
    int id;
    double amount;
    cout << "Enter Customer ID: ";
    cin >> id;

    for (auto& cust : customers) {
        if (cust.id == id) {
            cout << "Enter Amount to Withdraw: ";
            cin >> amount;

            if (amount > cust.balance) {
                cout << "Insufficient balance!" << endl;
            } else {
                cust.balance -= amount;
                cout << "Withdrawal successful. New Balance: $" << cust.balance << endl;
            }
            return;
        }
    }
    cout << "Customer with ID " << id << " not found!" << endl;
}


void addBalance() {
    int id;
    double amount;
    cout << "Enter Customer ID: ";
    cin >> id;

    for (auto& cust : customers) {
        if (cust.id == id) {
            cout << "Enter Amount to Add: ";
            cin >> amount;

            cust.balance += amount;
            cout << "Balance updated successfully. New Balance: $" << cust.balance << endl;
            return;
        }
    }
    cout << "Customer with ID " << id << " not found!" << endl;
}


void viewBalance() {
    int id;
    cout << "Enter Customer ID: ";
    cin >> id;

    for (const auto& cust : customers) {
        if (cust.id == id) {
            cout << "Customer Balance: $" << fixed << setprecision(2) << cust.balance << endl;
            return;
        }
    }
    cout << "Customer with ID " << id << " not found!" << endl;
}


void applyForLoan() {
    int id;
    double loanAmount;
    cout << "Apply for Loan" << endl;
    cout << "Enter Customer ID: ";
    cin >> id;

    for (auto& cust : customers) {
        if (cust.id == id) {
            cout << "Enter Loan Amount: $";
            cin >> loanAmount;

            cust.loanAmount += loanAmount;
            cust.balance += loanAmount;
            cout << "\n** Loan approved! New Balance: $" << fixed << setprecision(2) << cust.balance 
                 << ", Loan Amount: $" << cust.loanAmount << " **" << endl;
            return;
        }
    }
    cout << "\n** Customer with ID " << id << " not found! **" << endl;
}


void loanCalculator() {
    double principal, annualRate;
    int years;

    cout << "\n=== Loan Calculator ===" << endl;
    cout << "Enter loan amount (principal): $";
    cin >> principal;
    cout << "Enter annual interest rate (in %): ";
    cin >> annualRate;
    cout << "Enter loan term (in years): ";
    cin >> years;

    double monthlyPayment = calculateMonthlyPayment(principal, annualRate, years);
    double totalPayment = monthlyPayment * years * 12;
    double totalInterest = totalPayment - principal;

    cout << "\n--- Loan Summary ---" << endl;
    cout << "Loan Amount (Principal): $" << fixed << setprecision(2) << principal << endl;
    cout << "Annual Interest Rate: " << annualRate << "%" << endl;
    cout << "Loan Term: " << years << " years" << endl;
    cout << "Monthly Payment: $" << monthlyPayment << endl;
    cout << "Total Payment: $" << totalPayment << endl;
    cout << "Total Interest: $" << totalInterest << endl;
}
