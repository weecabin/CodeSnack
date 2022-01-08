// This is a basic program on C++
//
// Try to modify and run it and check out
// the output in the terminal below.
//
// Happy coding! :-)
#include "../cslib/CircularBuffer.h"
#include <iostream>

int main() {
    std::cout << "Created buffer of 10 floats, then added more than 10\n";
    CircularBuffer<float> cb;
    cb.SetSize(10);
    for (float i=1.1;i<20;i+=1.1)
      cb.Push(i);
    cb.Print();
    
    return 0;
}