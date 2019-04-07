#include "Suite.h"
#include "Test.h"
#include <vector>
#include <string>

using namespace TestSuite;
//using namespace std;


class testVector_push_back : public Test {
    vector<int> a;
public:
    testVector_push_back() : a(vector<int>()){};
    void run() {
        a.push_back(12);
        test_(a.back()==12);
    }
};

class testVector_front : public Test {
    vector<char> a;
public:
    testVector_front() : a(vector<char>()) {};
    void run() {
        a.push_back('O');
        a.push_back('K');
        a.push_back('!');
        test_(a.front() == 'O');
    }
};
class testVector_back : public Test {
    vector<char> a;
public:
    testVector_back() : a(vector<char>()){};
    void run() {
        a.push_back('O');
        a.push_back('K');
        a.push_back('!');
        test_(a.back() == '!');
    }
};
class testVector_pop_back : public Test {
    vector<char> a;
public:
    testVector_pop_back() : a(vector<char>()){};
    void run() {
        a.push_back('O');
        a.push_back('K');
        a.push_back('!');
        a.pop_back();
        test_(a.back() == 'K');
    }
};
class testVector_at : public Test {
    vector<char> a;
public:
    testVector_at() : a(vector<char>()){};
    void run() {
        a.push_back('O');
        a.push_back('K');
        a.push_back('!');
        test_(a.at(1) == 'K');
        
        try {
            a.at(25);
            a.at(-1);
            fail_("out of range not detected!");
        } catch(std::out_of_range& e) {
           *getStream() << "Founded error: \n" << e.what() << std::endl;
           succeed_();
        }
    }
};
class testVector_size : public Test {
    vector<char> a;
public:
    testVector_size() : a(vector<char>()){};
    void run() {
        a.push_back('O');
        a.push_back('K');
        a.push_back('!');
        a.pop_back();
        test_(a.size() == 2);
    }
};


int main() {
    Suite suite("My tests for std::vector");
    suite.addTest(new testVector_at());
    suite.addTest(new testVector_back());
    suite.addTest(new testVector_front());
    suite.addTest(new testVector_pop_back());
    suite.addTest(new testVector_push_back());
    suite.addTest(new testVector_size());
    suite.run();
    long nFail = suite.report();
    suite.free();
    
    return 0;
}