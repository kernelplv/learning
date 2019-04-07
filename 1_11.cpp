#include <stdexcept>
#include <iostream>

using namespace std;

class Garage {
    
public:
    Garage();
    
    class Car {
    public:
        Car() throw(logic_error) { new Motor;};
        
        class Motor {
        public:
            Motor() throw(logic_error){ throw R("R error!");}
            class R : public logic_error {
            public:
                R(const string msg="R") : logic_error(msg){};
            };
        };
    };
};

Garage::Garage() {
    try {
        new Car;
    }
    catch(exception& e) {
        cout << "catched! Error: " << e.what() << endl;
        throw logic_error("Garage constructor error");
    }
}

int main() {
    try {
        new Garage();
    }
    catch(exception& e){
        cout << "Garage error catched! Error: " << e.what() << endl;
    }
    return 0;
}