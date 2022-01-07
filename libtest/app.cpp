// This is a basic program on C++
//
// Try to modify and run it and check out
// the output in the terminal below.
//
// Happy coding! :-)
#include "../cslib/CircularBuffer.h"
#include <iostream>

int main() {
    CircularBuffer<float> cb;
    cb.SetSize(10);
    std::cout << "Hello, World!\n";
    return 0;
}
