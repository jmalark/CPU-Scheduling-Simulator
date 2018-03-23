#ifndef LINKED_LIST_NODE
#define LINKED_LIST_NODE

template <class item_t>
class LinkedListNode
{
  private:
   LinkedListNode<item_t>* next;
   item_t item;

  public:
   LinkedListNode(LinkedListNode<item_t>* next, const item_t& item);

   const item_t& getItem() const;
   void setItem(const item_t& newItem);

   LinkedListNode<item_t>* getNext() const;
   void setNext(LinkedListNode<item_t>* newNext);
};

////////////////////////////////////////////////
//Implementation of LinkedListNode begins here//
////////////////////////////////////////////////

template <class item_t>
LinkedListNode<item_t>::LinkedListNode(LinkedListNode<item_t>* n, const item_t& i)
{
   next = n;
   item = i;
}

template <class item_t>
const item_t& LinkedListNode<item_t>::getItem() const
{
   return item;
}

template <class item_t>
void LinkedListNode<item_t>::setItem(const item_t& newItem)
{
   item = newItem;
}

template <class item_t>
LinkedListNode<item_t>* LinkedListNode<item_t>::getNext() const
{
   return next;
}

template <class item_t>
void LinkedListNode<item_t>::setNext(LinkedListNode<item_t>* newNext)
{
   next = newNext;
}

#endif
