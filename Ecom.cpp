#include <iostream>
using namespace std;

class Payment {
public:
    virtual void pay(double amount) = 0; // Pure virtual function for runtime polymorphism
    virtual ~Payment() {}
};

class CreditCard : public Payment {
public:
    void pay(double amount) override {
        cout << "Paid Rs. " << amount << " using Credit Card.\n";
    }
};

class UPI : public Payment {
public:
    void pay(double amount) override {
        cout << "Paid Rs. " << amount << " via UPI.\n";
    }
};

class NetBanking : public Payment {
public:
    void pay(double amount) override {
        cout << "Paid Rs. " << amount << " through Net Banking.\n";
    }
};

int main() {
    int choice;
    double amount;

    cout << "Enter amount: ";
    cin >> amount;
    cout << "1. Credit Card\n2. UPI\n3. Net Banking\nChoose payment method: ";
    cin >> choice;

    Payment* mode = nullptr;
    if (choice == 1) mode = new CreditCard();
    else if (choice == 2) mode = new UPI();
    else if (choice == 3) mode = new NetBanking();
    else {
        cout << "Invalid choice!\n";
        return 0;
    }

    mode->pay(amount); 
    delete mode;
    return 0;
}