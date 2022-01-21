// This is a basic program on C++
//
// Try to modify and run it and check out
// the output in the terminal below.
//
// Happy coding! :-)
#include "MyList.h"

#include <iostream>
template<class A, class B> class node;
template<class A, class B> class MyList;

int main() {
    std::cout << "Hello, World!\n";

    MyList<int,float> list;
    list.Insert(1,1.1f);
    list.Insert(2,2.2f);
    list.Print();
    return 0;
}

