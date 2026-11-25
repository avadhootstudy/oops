#include<iostream>
using namespace std;

class Vehicle {
private:
  string registrationNumber;
  string ownerName;
  string vehicleType;
  
public:
  Vehicle(string regNo, string owner, string type) {
    registrationNumber = regNo;
    ownerName = owner;
    vehicleType = type;
  }
  void display() {
    cout << "Vehicle Registration Details" << endl;
    cout << "Registration Number: " << registrationNumber << endl;
    cout << "Owner Name: " << ownerName << endl;
    cout << "Vehicle Type: " << vehicleType << endl;
  }
};

int main() {
    Vehicle v1("MH12AB1234", "Avadhoot Jagtap", "Car");
  
    v1.display();
    cout<<endl;
  
    Vehicle v2("MH12AK7890", "Ban Sir", "Car");
  
    v2.display();
  
    return 0;
}