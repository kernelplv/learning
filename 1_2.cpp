#include <exception>
#include <iostream>
using namespace std;

class testClass {
    
    class zeroerror : public logic_error {
    public:
        zeroerror(const string& msg="") : logic_error(msg) {}
        const char* what() { return logic_error::what(); }
    };
    
public:
    static void f() throw(zeroerror) {
        throw zeroerror("func f()!");
    }
    static void g() throw(zeroerror) {
        throw zeroerror("func g()!");
    }
};


int main() {
    
    try {
        testClass::f();
        testClass::g();
        
    } 
    catch(exception& e) {
        cout << e.what() << '\n';
    }
    return 0;
}