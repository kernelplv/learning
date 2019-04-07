#include "1_6.h"
#include <cstdio>
#include <exception>
#include <iostream>
#include <memory>

using namespace std;

void my_terminator() {
    cout << "My terminator activated!" << endl;
    exit(0);
}

TerminateDemo::~TerminateDemo() throw(logic_error) {
    throw runtime_error("runtime error != logic error");
}

int main() {
    set_terminate(my_terminator);
    shared_ptr<TerminateDemo> D = make_shared<TerminateDemo>();
    cout << D.use_count() << endl;
}