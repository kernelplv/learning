#pragma once
#include <stdexcept>
class TerminateDemo {
public:
    ~TerminateDemo() throw(std::logic_error);
};