#include <iostream>
using namespace std;

class Learner {
public:
    void attendClass() {
        cout << "Attending university classes and studying.\n";
    }
};

class Participant {
public:
    void joinEvent() {
        cout << "Joining clubs and university events.\n";
    }
};

class Student : public Learner, public Participant {
public:
    void showRole() {
        cout << "Student role active:\n";
        attendClass();
        joinEvent();
    }
};

int main() {
    Student s;
    s.showRole();
    return 0;
}