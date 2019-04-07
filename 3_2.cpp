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

int main(int argc, char* argv[]) {
    string normal(argv[3]);
    string reversed = string("");
    reversed = normal;
    rstr(reversed);
    cout << normal << endl << reversed << endl;
    normal == reversed ?
    cout << "It is palindrom!" : cout << "It is not palindrom!\n";
    

    return 0;
    
}
