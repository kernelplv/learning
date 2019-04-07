#include <cstring>
#include <stdexcept>
#include <iostream>

using namespace std;

class sError : public logic_error {
public:
    sError(const string msg="") : logic_error(msg){};
    ~sError() { cout << "sError was deleted" << endl; }
    
    const char* what() { logic_error::what();}
};

static void test() throw(logic_error) {
    throw sError("bla bla");
}

static void test2() throw(logic_error) {
    logic_error* e = new sError("bla bla");
    throw e;
}

int main() {
    
    try {
        test();
    }
    catch(logic_error& e) {
        cout << "catched!" << endl;
        cout << e.what() << endl;
    }
    return 0;
}