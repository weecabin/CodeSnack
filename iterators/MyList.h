#ifndef MYLIST_H
#define MYLIST_H
#include <iostream>

template<class A, class B> class node
{
  public:
  node(){};
  node(A key, B value)
  {
    this->key=key;
    this->value=value;
  }
  A key;
  B value;
  node<A,B> *next;
};

template<class A, class B> class MyList
{
  public:
  ~MyList()
  {
    node<A,B> *temp=first;
    while(temp!=end)
    {
      temp=temp->next;
      delete first;
      first = temp;
    }
    delete end;
  }
  void Print()
  {
    node<A,B>* temp=first;
    while(temp!=end)
    {
      std::cout<<"key:"<<temp->key<<" value:"<<temp->value<<"\n";
      temp=temp->next;
    }
  }
  void Insert(A key, B value)
  {
    if (size++==0)
    {
      first = last = new node<A,B>(key,value);
      end=new node<A,B>; // end node
      first->next = end;
      return;
    }
    node<A,B>* newnode = new node<A,B>(key,value);
    last->next = newnode;
    newnode->next = end;
  }
  private:
  int size=0;
  node<A,B> *first;
  node<A,B> *last;
  node<A,B> *end;
};

#endif