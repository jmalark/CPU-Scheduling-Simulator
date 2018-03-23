#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <iostream>
#include "List.h"
#include "LinkedListNode.h"

using namespace std;


template <class item_t>
class LinkedList : public List<item_t>
{
 protected:
  LinkedListNode<item_t>* head;
  LinkedListNode<item_t>* tail;
  int size;

  //helper func to go through the Linked list until it gets to the Node of the desired idx
  virtual LinkedListNode<item_t>* getToIdx(int idx) const;

 public:
  LinkedList();
  virtual ~LinkedList();
  
  virtual void pushBack(const item_t& item);
  virtual void popBack();
  virtual const item_t& getBack() const;
  virtual void pushFront(const item_t& item);
  virtual void popFront();
  virtual const item_t& getFront() const;
  virtual const item_t& getItem(int index) const;
  virtual void setItem(int index, const item_t& item);
  virtual void insert(int index, const item_t& item);
  virtual void remove(int index);
  virtual int getSize() const;
  virtual bool isEmpty() const;
  
  virtual void print() const;

  
};

/////////////////////////////////////////////////////////////
/////////////Start Implementation of LinkedList//////////////
/////////////////////////////////////////////////////////////

//constructor
template <class item_t>
LinkedList<item_t>::LinkedList()
{ 
  head = 0;
  tail = 0;
  size = 0;
}

//destructor
template <class item_t>
LinkedList<item_t>::~LinkedList()
{LinkedListNode<item_t>* nodeToDelete = head;
  while(!isEmpty())
    {
      LinkedListNode<item_t>* nextNode = nodeToDelete->getNext();
      delete nodeToDelete;
      nodeToDelete = nextNode;
      --size;
    }

}

template <class item_t>
void LinkedList<item_t>::print() const
{LinkedListNode<item_t>* nodeToPrint = head;
  for(int i = 0; i < size; ++i)
    {
      LinkedListNode<item_t>* nextNode = nodeToPrint->getNext();
      cout << nodeToPrint->getItem() << " ";
      nodeToPrint = nextNode;
    }
  cout << endl;
}


template <class item_t>
LinkedListNode<item_t>* LinkedList<item_t>::getToIdx(int idx) const
{
LinkedListNode<item_t>* node = head;
  for(int i = 0; i < idx; ++i)
    {node  = node->getNext();
    } 
  return node;
}

   //Pushes item to the back of the list
template <class item_t>
void LinkedList<item_t>::pushBack(const item_t& item) 
{if(size == 0)
    {//makes 1 new node, with next pointing to 0
      LinkedListNode<item_t>* newNode = new LinkedListNode<item_t>(0, item);
      head = newNode;
      tail = newNode;
      ++size;
    }
  else
    {LinkedListNode<item_t>* newNode = new LinkedListNode<item_t>(0, item);
      tail->setNext(newNode);
      tail = newNode;
      ++size;
    }
}
 
   //Removes, but does not return, the last item
template <class item_t>
void LinkedList<item_t>::popBack()
{if (size==1)
    {delete tail;
      head = 0;
      tail = 0;
      --size;
    }
 else
   {
     LinkedListNode<item_t>* newTail = getToIdx(size - 2);
     newTail->setNext(0);

     delete tail;
     tail = newTail;
     --size;
    }
}

   //Returns a reference to the last item (does not remove it).
template <class item_t>
const item_t& LinkedList<item_t>::getBack() const
{return tail->getItem();
}   
   //Pushes item to the front of the list
template <class item_t>
void LinkedList<item_t>::pushFront(const item_t& item)
{if(size == 0)
    {//pushBack knows to set head and tail to the new node
      pushBack(item);
    }
  else
    {LinkedListNode<item_t>* newNode = new LinkedListNode<item_t>(head, item);
      head = newNode;
      ++size;
    }

}
   //Removes, but does not return, the first item
template <class item_t>
void LinkedList<item_t>::popFront()
{if(size==1)
    {popBack();
    }
   else
     {
       LinkedListNode<item_t>* nextHead = head->getNext();
       delete head;
       head = nextHead;
       --size;
      }
}
   //Returns a reference to the first item (does not remove it).
template <class item_t>
const item_t& LinkedList<item_t>::getFront() const
{return head->getItem();

}

   //Returns a reference to the item at the given index
template <class item_t>
const item_t& LinkedList<item_t>::getItem(int index) const
{if(index == size - 1)
    {return getBack();
    }
  else
    {LinkedListNode<item_t>* node = getToIdx(index);
      return node->getItem();
    }
}


   //Sets the item at the given index
template <class item_t>
void LinkedList<item_t>::setItem(int index, const item_t& item)
{LinkedListNode<item_t>* nodeAccess = getToIdx(index);
 nodeAccess->setItem(item);
}


   //Inserts the given item at the given index
template <class item_t>
void LinkedList<item_t>::insert(int index, const item_t& item)
{if(index == 0)
    {pushFront(item);
    }
  else if (index == size)
    {pushBack(item);
    }
   else
     {LinkedListNode<item_t>* nodeBefore = getToIdx(index - 1);
      LinkedListNode<item_t>* nodeToShift = nodeBefore->getNext();
      LinkedListNode<item_t>* nodeToInsert = new LinkedListNode<item_t>(nodeToShift, item);
      nodeBefore->setNext(nodeToInsert);
      ++size;
     }
}


   //Removes the item at the given index
template <class item_t>
void LinkedList<item_t>::remove(int index)
{if(index==0)
    {popFront();
    }
  else if(index == size -1)
    {popBack();
    }
  else
    {LinkedListNode<item_t>* nodeBefore = getToIdx(index - 1);
      LinkedListNode<item_t>* node = nodeBefore->getNext();
      LinkedListNode<item_t>* nodeAfter = node->getNext();
      delete node;
      nodeBefore->setNext(nodeAfter);
      --size;  
    }
 
}

   //Returns the number of items in the list
template <class item_t>
int LinkedList<item_t>::getSize() const
{return size;

}


   //Returns true if the list is empty (false otherwise)
template <class item_t>
bool LinkedList<item_t>::isEmpty() const
{return size == 0;

}




#endif  
