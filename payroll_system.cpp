/*Assignment 2
Employee Payroll System*/
#include<iostream>
#include <iomanip>
using namespace std;

class Employee {
protected:
  string Emp_name, Emp_id, Address;
  string Mail_id, Mobile_no;
  double Basic_pay;
  
public:
  Employee(string name, string id, string address, string mail, string mobile, double basic) {
    Emp_name = name;
    Emp_id = id;
    Address = address;
    Mail_id = mail;
    Mobile_no = mobile;
    Basic_pay = basic;
  }
  void generateSalarySlip(string designation) {
    double DA = Basic_pay*0.95;
    double HRA = Basic_pay*0.10;
    double PF = Basic_pay*0.12;
    double Other = Basic_pay*0.002;
    
    double Gross = Basic_pay + DA + HRA + Other;
    double Net = Gross - PF;
    
    cout << "\n====================== SALARY SLIP ======================\n";
    cout << "Designation: " << designation << endl;
    cout << "Employee Name: " << Emp_name << endl;
    cout << "Employee ID: " << Emp_id << endl;
    cout << "Address: " << Address << endl;
    cout << "Mail ID: " << Mail_id << endl;
    cout << "Mobile No: " << Mobile_no << endl;
    
    cout << fixed << setprecision(2);
    cout << "\nBasic Pay: " << Basic_pay << endl;
    cout << "DA (95%): " << DA << endl;
    cout << "HRA (10%): " << HRA << endl;
    cout << "Other Allowances (0.2%): " << Other << endl;
    cout << "PF (12%): " << PF << endl;
    cout << "Gross Salary: " << Gross << endl;
    cout << "Net Salary: " << Net << endl;
    cout << "===========================================================\n";
  }
};

class Programmer : public Employee {
public:
  Programmer(string n, string id, string a, string m, string mob, double b) : Employee(n, id, a, m, mob, b) {}
};
class TeamLead : public Employee {
public:
  TeamLead(string n, string id, string a, string m, string mob, double b) : Employee(n, id, a, m, mob, b) {}
};
class AssisstantProjectManager : public Employee {
public:
  AssisstantProjectManager(string n, string id, string a, string m, string mob, double b) : Employee(n, id, a, m, mob, b) {}
};
class ProjectManager : public Employee {
public:
  ProjectManager(string n, string id, string a, string m, string mob, double b) : Employee(n, id, a, m, mob, b) {}
};
int main(){
  Programmer p("Vedant", "E101", "Pune", "vedant123@gmail.com", "9876543210", 130000);
  TeamLead t("Prithvi", "E102", "Mumbai", "prithvi123@gmail.com", "9876543211", 150000);
  AssisstantProjectManager a("Harsh", "E103", "Pune", "harsh123@gmail.com", "987654322", 170000);
  ProjectManager pm("Avadhoot", "E104", "Pune", "avadhu123@gmail.com", "987654323", 190000);
  
  p.generateSalarySlip("Programmer");
  t.generateSalarySlip("Team Lead");
  a.generateSalarySlip("Assisstant Project Manager");
  pm.generateSalarySlip("Project Manager");
  
  return 0;
}