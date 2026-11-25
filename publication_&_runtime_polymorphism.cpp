#include <iostream>
#include <string>
using namespace std;

class Publication {
protected:
    string title;
    double price;
    int copies;
    static double totalSales;

public:
    Publication(string t, double p, int c) : title(t), price(p), copies(c) {}
    virtual ~Publication() {}

    virtual void saleCopy(int qty = 1) {
        if (qty <= copies) {
            copies -= qty;
            totalSales += qty * price;
            cout << "Sold " << qty << " of \"" << title << "\". Left: " << copies << "\n";
        } else {
            cout << "Not enough copies of \"" << title << "\".\n";
        }
    }

    static void showTotalSales() {
        cout << "Total Publication Sales: Rs." << totalSales << "\n";
    }
};

double Publication::totalSales = 0.0;

class Book : public Publication {
    string author;

public:
    Book(string t, double p, int c, string a) : Publication(t, p, c), author(a) {}

    void orderCopies(int qty) {
        copies += qty;
        cout << "Ordered " << qty << " book copies. Total copies: " << copies << "\n";
    }
};

class Magazine : public Publication {
    int orderQty;

public:
    Magazine(string t, double p, int c, int oq) : Publication(t, p, c), orderQty(oq) {}

    void receiveIssue() {
        copies += orderQty;
        cout << "Received magazine issue (" << orderQty << " copies). Total: " << copies << "\n";
    }
};

int main() {
    Book b("C++ Basics", 450.0, 5, "Bjarne");
    Magazine m("Tech Today", 120.0, 10, 8);

    b.orderCopies(5);
    m.receiveIssue();

    Publication* p1 = &b;
    Publication* p2 = &m;

    p1->saleCopy(3);
    p2->saleCopy(4);

    Publication::showTotalSales();
    return 0;
}