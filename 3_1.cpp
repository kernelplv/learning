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

class test_rstr : public Test {
    string s;
public:
    test_rstr() : s(string("12345")) {};
    void run() {
        rstr(s);
        test_(s == "54321");
    }
};

int main() {
    Test* t = new test_rstr();
    t->run();
    t->report();
    return 0;
    
}
