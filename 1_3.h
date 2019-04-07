#pragma once

#include <stdexcept>
#include <cstring>

class PStash {
    int quantity;
    int next;
    
    void** storage;
    void inflate(int increase);
    
    class EOutOfRange : public std::logic_error {
    public:
        EOutOfRange(const std::string& msg="Out of range!") 
            : std::logic_error(msg) {}
    };
    
public:
    PStash() : quantity(0), storage(0), next(0) {}
    ~PStash();
    int add(void* element);
    void* operator[](int index) const throw(EOutOfRange);
    void* remove(int index);
    int count() const { return next; }
};
