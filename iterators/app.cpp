// This is a basic program on C++
//
// Try to modify and run it and check out
// the output in the terminal below.
//
// Happy coding! :-)
#include "../cslib/MyDefines.h"
#include "Map1List.h"

int main() {
    std::cout << "\n******** Map1List Test ********\n";

    Map1List<int,float> list;
    for (int i=1;i<11;i++)
    {
      list.Insert(10-i,10-i*1.1);
    }
    println("print with Map1List.Print()...");
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

    println("\ndelete key 8");
    list.Delete(8);
    list.Print();

    println("\ndelete key 0");
    list.Delete(0);
    list.Print();

    println("\ndelete key 9");
    list.Delete(9);
    list.Print();
    return 0;
}

