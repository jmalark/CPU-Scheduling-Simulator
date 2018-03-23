#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

#include "List.h"
#include <iostream>
using namespace std;

template <class item_t>
class ArrayList : public List<item_t>
{
  protected:
   item_t* items;
   int size;
   int capacity;

   //private helper. if the array is full, replaces array with bigger array
   //takes item for case of pushFront
   virtual void isFull(bool toFront,const item_t& item);
   
  public:
   //Creates an empty list with capacity 10
   ArrayList();
   //Creates a list with the given capacity
   ArrayList(int capacity);
   virtual ~ArrayList();

   //Pushes item to the back of the list
   virtual void pushBack(const item_t& item);   
   //Removes, but does not return, the last item
   virtual void popBack();
   //Returns a reference to the last item (does not remove it).
   virtual const item_t& getBack() const;
   
   //Pushes item to the front of the list
   virtual void pushFront(const item_t& item);
   //Removes, but does not return, the first item
   virtual void popFront();
   //Returns a reference to the first item (does not remove it).
   virtual const item_t& getFront() const;

   //Returns a reference to the item at the given index
   virtual const item_t& getItem(int index) const;
   //Sets the item at the given index
   virtual void setItem(int index, const item_t& item);

   //Inserts the given item at the given index
   //(items at index or beyond shift up one position)
   //Inserting just past the last element (i.e. position
   //size) shoud be equivalent to pushBack.
   virtual void insert(int index, const item_t& item);
   //Removes the item at the given index
   //(items beyond index shift down one position)
   virtual void remove(int index);

   //Returns the number of items in the list
   virtual int getSize() const;
   //Returns true if the list is empty (false otherwise)
   virtual bool isEmpty() const;
   //Returns the size of the array that contains the list
   virtual int getCapacity() const;
};

//Creates an empty list with capacity 10
template <class item_t>
ArrayList<item_t>::ArrayList()
{items = new item_t[10];
  size = 0;
  capacity = 10;
}


//Creates a list with the given capacity
template <class item_t>
ArrayList<item_t>::ArrayList(int capacity)
{items = new item_t[capacity];
  size = 0;
  this->capacity = capacity;
}

//deconstructor
template <class item_t>
ArrayList<item_t>::~ArrayList()
{delete[] this->items;
}


//private helper. if the array is full, replaces array with bigger array 
//takes bool representing if something is going to be added to the front
template <class item_t>
void ArrayList<item_t>::isFull(bool toFront, const item_t& item)
{if (size == capacity)
    {//new array is twice as big
      item_t* tempArr = new item_t[capacity * 2];
 
      unsigned j = 0;

      //if the func that called this wants to add something to the front of a too small array
      //it adds it to the bigger array and then copies the old array after it
      if (toFront)
	{j = 1;
	 tempArr[0] = item;	 
	}  

      for (unsigned i = 0; i < size; ++i)
	{tempArr[j] = items[i];
	 ++j;
	}

      //increases size if it added to front
      if (toFront)
	{++size;
	}

      delete[] items;
      items = tempArr;
      capacity = capacity * 2;
    }

}


   //Pushes item to the back of the list
template <class item_t>
void ArrayList<item_t>::pushBack(const item_t& item) 
{isFull(false, item);
  items[size] = item;
  ++size;
  

}
 
   //Removes, but does not return, the last item
template <class item_t>
void ArrayList<item_t>::popBack()
{--size;
}

   //Returns a reference to the last item (does not remove it).
template <class item_t>
const item_t& ArrayList<item_t>::getBack() const
{return getItem(size - 1);

}   
   //Pushes item to the front of the list
template <class item_t>
void ArrayList<item_t>::pushFront(const item_t& item)
{int origCap = capacity;
  isFull(true, item);
  if (capacity == origCap)
    {insert(0, item);
    }

}
   //Removes, but does not return, the first item
template <class item_t>
void ArrayList<item_t>::popFront()
{remove(0);

}
   //Returns a reference to the first item (does not remove it).
template <class item_t>
const item_t& ArrayList<item_t>::getFront() const
{return getItem(0);

}

   //Returns a reference to the item at the given index
template <class item_t>
const item_t& ArrayList<item_t>::getItem(int index) const
{return items[index];

}


   //Sets the item at the given index
template <class item_t>
void ArrayList<item_t>::setItem(int index, const item_t& item)
{items[index] = item;

}


   //Inserts the given item at the given index
   //(items at index or beyond shift up one position)
   //Inserting just past the last element (i.e. position
   //size) shoud be equivalent to pushBack.
template <class item_t>
void ArrayList<item_t>::insert(int index, const item_t& item)
{if (index == size)
    {pushBack(item);
    }
  else if (index == 0 && size ==capacity)
    {isFull(true, item);
    }
  else if (index < size)
    {isFull(false, item);
      for (int i = size; i > index; --i)
	{items[i] = items[i-1];
	}
      items[index] = item;
      ++size;
    }
}


   //Removes the item at the given index
   //(items beyond index shift down one position)
template <class item_t>
void ArrayList<item_t>::remove(int index)
{for (int i = index; i < size - 1; ++i)
    {items[i] = items[i + 1];
    }
  --size;

}

   //Returns the number of items in the list
template <class item_t>
int ArrayList<item_t>::getSize() const
{return size;

}


   //Returns true if the list is empty (false otherwise)
template <class item_t>
bool ArrayList<item_t>::isEmpty() const
{return size == 0;

}
   //Returns the size of the array that contains the list
template <class item_t>
int ArrayList<item_t>::getCapacity() const
{return capacity;
}

#endif
