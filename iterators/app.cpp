// This is a basic program on C++
//
// Try to modify and run it and check out
// the output in the terminal below.
//
// Happy coding! :-)
#include "../cslib/MyDefines.h"
#include "MyList.h"

template<class A, class B> class node;
template<class A, class B> class MyList;

int main() {
    std::cout << "Hello, World!\n";

    MyList<int,float> list;
    list.Insert(1,1.1f);
    list.Insert(2,2.2f);
    println("using internal List Print()...");
    list.Print();
    println("print using the iterator...");
    Iterator<int,float> itr(list.begin());
    println(*itr++);
    println(*itr);
    println("Iterator in a loop...");
    for (auto itr=list.begin();itr!=list.end();itr++)
      {
        print("Value = ");
        println(*itr);
      }
    //for (auto itr=list.begin();itr!=list.end();itr++)
      //std::cout<<"value: "<<*itr<<"\n";
    return 0;
}

