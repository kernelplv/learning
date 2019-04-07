#include <cstdlib>
#include <cstring>
#include <iostream>

using namespace std;

class MyNew {
    static const int psize = 5;
    
    static MyNew* data[];
    
    static int hold_mem;
    
public:
    string name;
    MyNew(string name="fake"): name(name) {}
    ~MyNew(){}
    void who() { cout << "I am " << name << endl; }
    void* operator new(size_t) throw(bad_alloc);
    void static clear();
    
};  int MyNew::hold_mem = 0;
    MyNew* MyNew::data[psize] = {0};

void* MyNew::operator new(size_t sz) throw(bad_alloc) {
    if(hold_mem < psize) {
        data[hold_mem] = (MyNew*)malloc(sz);
        cout << "memory given" << endl;
        hold_mem++;
        return data[hold_mem - 1];
    }
    throw bad_alloc();
}
void MyNew::clear() {
    for (int i = 0; i < psize; i++) {
        if(data[i]) {
            delete data[i];
            hold_mem--;
        }
    }
    *data = 0;
    cout << "all data is cleared, hold_mem:" << hold_mem << endl;
}

int main() {
    int k = 3;
    while(k--) {
        try {
            MyNew* o1 = new MyNew("1");
            MyNew* o2 = new MyNew("2");
            MyNew* o3 = new MyNew("3");
            MyNew* o4 = new MyNew("4");
            MyNew* o5 = new MyNew("5");
            o1->who();
            o2->who();
            o3->who();
            o4->who();
            o5->who();
            
            MyNew* o6 = new MyNew("6");
            o6->who();
        }
        catch(bad_alloc) {
            cout << "bad alloc" << endl;
            MyNew::clear();
        }
    }
        return 0;
}