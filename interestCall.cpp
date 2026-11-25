#include <iostream>
using namespace std;

class InterestCalculator
{
public:
    double calculateInterest(double principal, double rate, double time)
    {
        return (principal * rate * time) / 100;
    }

    double calculateInterest(double principal, double rate)
    {
        return (principal * rate * 1) / 100;
    }

    double calculateInterest(double principal)
    {
        return (principal * 5 * 1) / 100;
    }
};

int main()
{
    InterestCalculator calculator;

    double interest1, interest2, interest3;

    interest1 = calculator.calculateInterest(10000, 5, 2);

    interest2 = calculator.calculateInterest(10000, 6);

    interest3 = calculator.calculateInterest(10000);

    cout << "Interest using Principal, Rate and Time: "
         << interest1 << endl;

    cout << "Interest using Principal and Rate: "
         << interest2 << endl;

    cout << "Interest using Principal only: "
         << interest3 << endl;

    return 0;
}