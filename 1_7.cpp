#include <cstring>
#include <stdexcept>
#include <iostream>

using namespace std;

class sError : logic_error {
    sError(const string msg="") : logic_error(msg){};
    ~sError() { cout << "sError was deleted" << endl; }
    
    const char* what() const { ::what();}
}

void test() throw(logic_error) {
    throw sError("bla bla")
}

int main() {
    
}