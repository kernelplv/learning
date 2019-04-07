#include <iostream>
#include "Test.h"
#include "Suite.h"
#include <string>
#include <algorithm>

using namespace TestSuite;
using namespace std;

void rstr(string& s) {
    reverse(s.begin(),s.end());
}

void toline(string& s) {
    for (char& c : s) {
        c = tolower(c);
    }
}

class test_rstr : public Test {
    string s;
public:
    test_rstr() : s(string("12345")) {};
    void run() {
        rstr(s);
        test_(s == "54321");
    }
};

int main(int argc, char** argv) {
    string one("I walked down the canyon with the moving mountain bikers.");
    string two("The bikers passed by me too close for comfort.");
    string three("I went hiking insted.");
    
    one.replace(2,4,one.substr(one.find("mov"),3));
    one.erase(one.find("moving"),7);
    
    two.insert(3, one.substr(one.size()-17,9));
    two.insert(0,one.substr(1,1));
    
    three.insert(0, two.substr(two.find("close") + 2, 2) + one.substr(1,1) );
    swap(three.at(0),three.at(1));
    three.at(0) = toupper(three.front()); 
    three.insert(0,one.substr(1,1));
    
    cout << one + two + three << endl;
    return 0;
    
}
