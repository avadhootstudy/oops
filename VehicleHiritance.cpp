#include <iostream>
#include <string>
using namespace std;


class Vehicle
{
protected:
    string brand;
    string model;

public:

    Vehicle(string b, string m) : brand(b), model(m)
    {
    }

    void displayVehicle()
    {
        cout << "Brand: " << brand << "\nModel: " << model << endl;
    }
};


class Car : public Vehicle
{
protected:
    int seatingCapacity;
    string fuelType;

public:

    Car(string b, string m, int seats, string fuel)
        : Vehicle(b, m), seatingCapacity(seats), fuelType(fuel)
    {
    }
    void displayCar()
    {
        displayVehicle(); 

        cout << "Seating Capacity: " << seatingCapacity
             << " seats" << endl;

        cout << "Fuel Type: " << fuelType << endl;
    }
};

class ElectricCar : public Car
{
private:
    float batteryCapacity;
    float chargingTime;    

public:

    ElectricCar(string b, string m, int seats, string fuel,
                float battery, float time)
        : Car(b, m, seats, fuel),
          batteryCapacity(battery),
          chargingTime(time)
    {
    }

    void displayElectricCar()
    {
        cout << "=== Electric Car Specifications ===" << endl;

        displayCar(); 

        cout << "Battery Capacity: " << batteryCapacity
             << " kWh" << endl;

        cout << "Charging Time: " << chargingTime
             << " hours" << endl;
    }
};

int main()
{
    ElectricCar myTesla("Tesla", "Model S Plaid", 5,
                        "Electric", 100.0, 1.5);

    myTesla.displayElectricCar();

    return 0;
}