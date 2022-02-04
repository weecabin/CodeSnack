// This is a basic program on C++
//
// Try to modify and run it and check out
// the output in the terminal below.
//
// Happy coding! :-)
#include <iostream>
#include <cstring>
#include "../cslib/MyDefines.h"

template <class A>
class Equal
{
  public:
  bool operator()(A a, A b)
  {
    return a==b;
  }
};

// template specialization
template<>
class Equal<char *>
{
  public:
  bool operator()(char *str1, char *str2)
  {
    if (strlen(str1)!=strlen(str2))
      return false;
    for (int i=0;i<strlen(str1)&&i<strlen(str2);i++)
    {
      if (str2[i]!=str1[i])
        return false;
    }
    return true;
  }
};

template<class A>
class Less
{
  public:
  bool operator()(A a,A b)
  {
    return a<b;
  }
};

// template specialization...
template<>
class Less<char *>
{
  public:
  bool operator()(char *str1, char *str2)
  {
    for (int i=0;i<strlen(str1)&&i<strlen(str2);i++)
    {
      if (str2[i]<str1[i])
        return false;
    }
    return true;
  }
};

template<class A, class Lt = Less<A>, class Eq = Equal<A>>
class Test
{
  public:
  Test(int size,bool sort=false)
  {
    this->sort = sort;
    this->size = size;
    x = new A[size];
    index=0;
  }
  ~Test()
  {
    delete []x;
  }
  void Add(A a)
  {
    //std::cout<<"Adding: "<<a<<"\n";
    x[index++]=a;
    if (++valuesIn==size)valuesIn--;
    if (index>=size)
      index=0;
    for (int i=0;sort && i<valuesIn-1;i++)
      for (int j=i+1;j<valuesIn;j++)
      {
        //std::cout<<"compare: "<<x[i]<<"-"<<x[j]<<"\n";
        if (lt(x[j],x[i]))
        {
          //std::cout<<"swapping: "<<x[i]<<"-"<<x[j]<<"\n";
          A temp = x[j];
          x[j]=x[i];
          x[i]=temp;
        }
      }
  }
  bool Exists(A a)
  {
    for (int i=0;i<valuesIn-1;i++)
    {
      if (eq(x[i],a))
        return true;
    }
    return false;
  }
  void Print()
  {
    for (int i =0;i<size;i++)
      std::cout<<x[i]<<" ";
    std::cout<<"\n";
  }
  private:
  bool sort;
  Lt lt;
  Eq eq;
  A *x;
  int index;
  int size;
  int valuesIn=0;
};

int main() 
{
  std::cout << "Hello, World!\n";

  println("Less<int> li;");
  Less<int> li;
  std::cout<<"li(1,2): "<<li(1,2)<<"\n";
  std::cout<<"li(2,1): "<<li(2,1)<<"\n";

  println("\nLess<char*> lc;");
  Less<char*> lc;
  char str2[]="234";
  char str1[]="123";
  char str3[]="345";
  char str4[]="456";
  char str5[]="567";
  
  std::cout<<"lc(\"123\",\"234\"): "<<lc(str1,str2)<<"\n";
  std::cout<<"lc(\"234\",\"123\"): "<<lc(str2,str1)<<"\n";

  println("\n Test<float> tf(5);");
  Test<float> tf(5);
  println("add 3.3 1.1 2.2 .5 5.2 3.35");
  tf.Add(3.3);
  tf.Add(1.1);
  tf.Add(2.2);
  tf.Add(.5);
  tf.Add(5.2);
  tf.Add(3.35);
  tf.Print();

  std::cout<<"\nTest<char*> tc(5,true);\n";
  Test<char*> tc(5,true);
  tc.Add(str2);
  tc.Add(str1);
  tc.Add(str3);
  tc.Add(str4);
  tc.Add(str5);
  tc.Print();
  char srch[] = "345";
  std::cout<<"find 345 ";
  if (tc.Exists(srch))
    std::cout<<"Yes";
  else
    std::cout<<"No";
  std::cout<<"\n";
}
