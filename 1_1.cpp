#include <csignal>
#include <cstring>
#include <cerrno>
#include <stdexcept>
#include <stdio.h>
#include <iostream>

using namespace std;

namespace mErr
{
    volatile sig_atomic_t SignalStatus;
}


class mError : public runtime_error {
public:
    mError(const string& msg="") : runtime_error(msg) {}
    const char* what();
    
    static void One();
    static void Two();
    static void Three();
    static void Four();
};

const char* mError::what() { return ::what(); }
void mError::One() { throw 5; }
void mError::Two() { errno = ENOTSUP; throw 'A'; }
void mError::Four() { throw mError("who are you?"); }

void signal_handler(int signal){
    mErr::SignalStatus = signal;
}

void mError::Three() {
    signal(SIGINT, signal_handler);
    raise(SIGINT);
    throw "signal error check";
}

int main(int argc, char **argv)
{
    try
    {
        //mError::One();
        //mError::Two();
        mError::Three();
        //mError::Four();
        
    }   catch(int i)
        {
            cout << "one: " << i << endl;
        }
        catch(mError e)
        {
            cout << "four: " << e.what() << endl;
        }
        catch(const char* e)
        {
            cout << e << endl << mErr::SignalStatus << endl;
        }
        catch(...)
        {
            cout << "unexpected! " << strerror(errno) << endl;
        }
    
	return 0;
}
