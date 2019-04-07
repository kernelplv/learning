#include "1_3.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    PStash intStash;
    for(int i = 0; i < 25; i++)
        intStash.add(new int(i));
    for(int j=0; j< intStash.count(); j++)
        cout << "intStash[" << j << "] = "
             << *(int*)intStash[j] << endl;
    try {
        cout << intStash[-2] << endl;
    }
    catch(exception& e) {
        cout << e.what() << endl;
    }
    for(int k=0; k < intStash.count(); k++)
        delete intStash.remove(k);
    
}