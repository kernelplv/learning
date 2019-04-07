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
    string normal(argv[1]);
    string univers = string("");
    
    
    //unifying
    cout << "normal: " << normal << endl;
    
    toline(normal);
    cout << "lined: " << normal << endl;

    normal.erase( remove_if( 
                    normal.begin(), 
                    normal.end(),
                    [](unsigned char x) {
                        return x ==' ' or x == ',';
                        }
                    ),
                    normal.end() );
    cout << "cleared: " << normal << endl;
    
    univers = normal;
    rstr(univers);
    
    cout << "NORM: " << normal << endl;
    cout << "UNIV: " << univers << endl;
    //cout << normal << endl << univers << endl;
    normal == univers ?
    cout << "It is palindrom!\n" : cout << "It is not palindrom!\n";
    

    return 0;
    
}
