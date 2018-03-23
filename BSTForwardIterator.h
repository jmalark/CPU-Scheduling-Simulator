#ifndef BST_FORWARD_ITERATOR
#define BST_FORWARD_ITERATOR

#include "BSTNode.h"

template <class key_t, class val_t>
class BSTForwardIterator
{
  protected:
   //The node the iterator currently points to
   BSTNode<key_t, val_t>* current;
   //The value representing the non-node
   BSTNode<key_t, val_t>* sentinel;
   
  public:
   BSTForwardIterator(BSTNode<key_t, val_t>* node, BSTNode<key_t, val_t>* sentinel);

   //Points the iterator at the successor of its
   //current node (if current is the sentinel,
   //does nothing).
   virtual void next();

   //Returns true if the iterator has moved past
   //the end of the container (if current is sentinel)
   virtual bool isPastEnd() const;

   //Returns the key of the current node
   virtual const key_t& getKey() const;

   //Returns the value of the current node
   virtual const val_t& getValue() const;
   
   //Sets the value of the current node
   virtual void setValue(const val_t& newVal);

   //Declares BSTMultimap and RBTMultimap as friend classes
   //(so they can access the protected member current)
   template <class k_t, class v_t> friend class BSTMultimap;
   template<class k_t, class v_t> friend class RBTMultimap;
};

////////////////////////////////////////////////////
//Implementation of BSTForwardIterator begins here//
////////////////////////////////////////////////////

//constructor
template <class key_t, class val_t>
  BSTForwardIterator<key_t, val_t>::BSTForwardIterator(BSTNode<key_t, val_t>* node, BSTNode<key_t, val_t>* sentinel)
{current = node;
  this->sentinel = sentinel;
}


   //Points the iterator at the successor of its
   //current node (if current is the sentinel,
   //does nothing).
template <class key_t, class val_t>
   void BSTForwardIterator<key_t, val_t>::next()
{if(current != sentinel && current->getRightChild() != sentinel)
    {current = current->getRightChild();
      while(current->getLeftChild() != sentinel)
	{current = current->getLeftChild();
	}
    }

  else if (current != sentinel)
    {BSTNode<key_t, val_t>* parentNode = current->getParent();

      //if it's a left child it'll skip this
      while(parentNode != sentinel && current == parentNode->getRightChild())
	{current = parentNode;
	  parentNode = parentNode->getParent();
	}
      //if no succesor, current will have become root and will become sentinel
      //if succesor, went up left until it couldn't, current becomes parentNode
      current = parentNode;
    }
}

   //Returns true if the iterator has moved past
   //the end of the container (if current is sentinel)
template <class key_t, class val_t>
   bool BSTForwardIterator<key_t, val_t>::isPastEnd() const
{return current == sentinel;
}

   //Returns the key of the current node
template <class key_t, class val_t>
   const key_t& BSTForwardIterator<key_t, val_t>::getKey() const
{return current->getKey();
}

   //Returns the value of the current node
template <class key_t, class val_t>
   const val_t& BSTForwardIterator<key_t, val_t>::getValue() const
{return current->getValue();
}
   
   //Sets the value of the current node
template <class key_t, class val_t>
   void BSTForwardIterator<key_t, val_t>::setValue(const val_t& newVal)
{current->setValue(newVal);
}








#endif
