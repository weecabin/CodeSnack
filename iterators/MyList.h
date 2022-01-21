#ifndef MYLIST_H
#define MYLIST_H
#include <iostream>

template<class A, class B> class Node
{
  public:
  Node(){};
  Node(A key, B value)
  {
    this->key=key;
    this->value=value;
  }
  A key;
  B value;
  Node<A,B> *next=nullptr;
};

template<class A, class B>
class Iterator
{
    // constructor that takes in a pointer from the linked list
    public:
    Iterator() noexcept : current_node(nullptr){};
    Iterator(Node<A,B> *node) noexcept : current_node(node){};

    // incrementing means going through the list
    Iterator &operator++() noexcept
    {
        if (current_node != nullptr)
        {
            previous_node = current_node;
            current_node = current_node->next;
        }
        return *this;
    };

    // post fixing is bad in general but it has it's usages
    Iterator operator++(int) noexcept
    {
        Iterator tempIter = *this;// we make a copy of the iterator
        ++*this;                   // we increment and updata previous_node in the process
        return tempIter;           // we return the copy before increment
    };

    // we need to be able to compare nodes
    bool operator!=(const Iterator &other) const noexcept
    {
        return this->current_node != other.current_node;
    };

    // debug dump value 
    void Print()
    {
      std::cout<<current_node->value;
    };

    // return the data from the node (dereference operator)
    B operator*() noexcept
    {
        //std::cout<<this->current_node->value<<"\n";
        return this->current_node->value;
    };

    Iterator operator[](A key)
    { 
      Node<A,B> *temp = current_node;
      while(temp->next!=nullptr)
      {
        //println(temp->key);
        if (temp->key==key)
          break;
        temp=temp->next;
      }
      return Iterator(temp);
    }

private:
    Node<A,B> *previous_node = nullptr;
    Node<A,B> *current_node = nullptr;
};

template<class A, class B> class MyList
{
  public:
  ~MyList()
  {
    Node<A,B> *temp=first;
    while(temp!=emptynode)
    {
      temp=temp->next;
      delete first;
      first = temp;
    }
    delete emptynode;
  }
  void Print()
  {
    Node<A,B>* temp=first;
    while(temp!=emptynode)
    {
      std::cout<<"key:"<<temp->key<<" value:"<<temp->value<<"\n";
      temp=temp->next;
    }
  }
  void Insert(A key, B value)
  {
    if (size++==0)
    {
      first = last = new Node<A,B>(key,value);
      emptynode=new Node<A,B>; // empty end node
      first->next = emptynode;
      return;
    }
    Node<A,B>* newnode = new Node<A,B>(key,value);
    last->next = newnode;
    last = newnode;
    newnode->next = emptynode;
  }
  Iterator<A,B> begin()
  {
    return Iterator<A,B>(first);
  }
  Iterator<A,B> end()
  {
    return Iterator<A,B>(emptynode);
  }
  private:
  int size=0;
  Node<A,B> *first;
  Node<A,B> *last;
  Node<A,B> *emptynode;
};

#endif