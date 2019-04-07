#include "2_2.h"
#include "Test.h"
#include "Suite.h"
#include <sstream>

using namespace TestSuite;
using namespace std;

class testRational_ : public Test {
    Rational A;
public:
    testRational_() : A(1,2) {};
    void run() {
        test_(A.numerator == 1 and A.denominator == 2);
        
        try {
            Rational(1,0);
            fail_("Not detected! zero denominator! ");
        } catch(underflow_error& e) {
           //*getStream() << "Founded error: \n" << e.what() << std::endl;
           succeed_();
        }
    }
};

class testRational_operator_minus : public Test {
    Rational A;
public:
    testRational_operator_minus() : A(1,2) {};
    void run() {
        test_(-A.numerator == -1);
    }
};

class testRational_bin_operator_plus : public Test {
    Rational A;
    Rational B;
public:
    testRational_bin_operator_plus() : A(1,2), B(1,5) {};
    void run() {
        Rational C = A + B;
        test_(C.numerator == 7 and C.denominator == 10);
    }
};

class testRational_bin_operator_minus : public Test {
    Rational A;
    Rational B;
public:
    testRational_bin_operator_minus() : A(1,2), B(3,4) {};
    void run() {
        Rational C = A - B;
        test_(C == Rational(-1, 4));
    }
};

class testRational_bin_operator_multiply : public Test {
    Rational A;
    Rational B;
public:
    testRational_bin_operator_multiply() : A(1,2), B(3,4) {};
    void run() {
        Rational C = A * B;
        test_(C == Rational(3, 8));
    }
};

class testRational_bin_operator_divide : public Test {
    Rational A;
    Rational B;
public:
    testRational_bin_operator_divide() : A(1,2), B(3,4) {};
    void run() {
        Rational C = A / B;
        test_(C == Rational(4, 6));
    }
};

class testRational_operator_cout : public Test {
    Rational A;
public:
    testRational_operator_cout() : A(1,2) {};
    void run() {
        stringstream SS;
        string S = "";
        SS << A;
        SS >> S;
        test_(S == "1/2");
    }
};

class testRational_operator_cin : public Test {
    Rational A;
public:
    testRational_operator_cin() : A(8,8) {};
    void run() {
        Rational B;
        stringstream SS;
        SS << A;
        SS >> B;
        test_(B.numerator == 8 and B.denominator == 8);
    }
};

class testRational_operator_plus_eq : public Test {
    Rational A;
    Rational B;
public:
    testRational_operator_plus_eq() : A(1,2), B(3,4) {};
    void run() {
        A += B;
        test_(A == Rational(5, 4));
    }
};

class testRational_operator_minus_eq : public Test {
    Rational A;
    Rational B;
public:
    testRational_operator_minus_eq() : A(1,2), B(3,4) {};
    void run() {
        A -= B;
        test_(A == Rational(-1, 4));
    }
};

class testRational_operator_multiply_eq : public Test {
    Rational A;
    Rational B;
public:
    testRational_operator_multiply_eq() : A(1,2), B(3,4) {};
    void run() {
        A *= B;
        test_(A == Rational(3, 8));
    }
};

class testRational_operator_divide_eq : public Test {
    Rational A;
    Rational B;
public:
    testRational_operator_divide_eq() : A(1,2), B(3,4) {};
    void run() {
        A /= B;
        test_(A == Rational(4, 6));
    }
};

class testRational_operator_less : public Test {
    Rational A;
    Rational B;
public:
    testRational_operator_less() : A(1,3), B(1,5) {};
    void run() {
        test_(B < A);
    }
};

class testRational_operator_greater : public Test {
    Rational A;
    Rational B;
public:
    testRational_operator_greater() : A(1,3), B(1,5) {};
    void run() {
        test_(A > B);
    }
};

class testRational_operator_less_eq : public Test {
    Rational A;
    Rational B;
    Rational C;
public:
    testRational_operator_less_eq() : A(1,3), B(1,2), C(5,10) {};
    void run() {
        test_(A <= C);
        test_(B <= C);
    }
};

class testRational_operator_greater_eq : public Test {
    Rational A;
    Rational B;
    Rational C;
public:
    testRational_operator_greater_eq() : A(1,3), B(1,2), C(5,10) {};
    void run() {
        test_(C >= A);
        test_(C >= B);
    }
};

class testRational_operator_eq_eq : public Test {
    Rational A;
    Rational B;
    Rational C;
public:
    testRational_operator_eq_eq() : A(10,20), B(1,2), C(5,10) {};
    void run() {
        test_(A == B and B == C and C == A);
    }
};

class testRational_operator_not_eq : public Test {
    Rational A;
    Rational B;
    Rational C;
public:
    testRational_operator_not_eq() : A(1,3), B(1,2), C(1,4) {};
    void run() {
        test_(A != B != C);
    }
};

int main() {
    Suite S("Tests for Rational class");
    S.addTest(new testRational_());
    S.addTest(new testRational_operator_minus());
    S.addTest(new testRational_bin_operator_plus());
    S.addTest(new testRational_bin_operator_minus());
    S.addTest(new testRational_bin_operator_multiply());
    S.addTest(new testRational_bin_operator_divide());
    S.addTest(new testRational_operator_cout());
    S.addTest(new testRational_operator_cin());
    S.addTest(new testRational_operator_plus_eq());
    S.addTest(new testRational_operator_minus_eq());
    S.addTest(new testRational_operator_multiply_eq());
    S.addTest(new testRational_operator_divide_eq());
    S.addTest(new testRational_operator_less());
    S.addTest(new testRational_operator_greater());
    S.addTest(new testRational_operator_less_eq());
    S.addTest(new testRational_operator_greater_eq());
    S.addTest(new testRational_operator_eq_eq());
    S.addTest(new testRational_operator_not_eq());
    
    S.run();
    long nFail = S.report();
    S.free();
}