// This is a basic program on C++
//
// Try to modify and run it and check out
// the output in the terminal below.
//
// Happy coding! :-)
#include "../cslib/MyDefines.h"
#include "MapList.h"

int main() {
    std::cout << "Hello, World!\n";

    MapList<int,float> list;
    for (int i=1;i<11;i++)
    {
      list.Insert(10-i,10-i*1.1);
    }
    println("print with MapList.Print()...");
    list.Print();
  
    println("print a few values using the iterator...");
    Iterator<int,float> itr(list.begin());
    println(*itr++);
    println(*itr);
  
    println("Iterator in a loop...");
    for (auto itr=list.begin();itr!=list.end();++itr)
      {
        print("Value = ");
        println(*itr);
      }
  
    println("now find key 3");
    itr = list.begin();
    print("key 3 value = ");println(*itr[3]);

    println("Sort the list");
    list.Sort();
    list.Print();

    return 0;
}

