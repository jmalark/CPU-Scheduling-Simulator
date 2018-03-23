#ifndef BSTMULTIMAP_H
#define BSTMULTIMAP_H

#include "BSTNode.h"
#include <queue>
#include <iostream>
#include "BSTForwardIterator.h"


using namespace std;

template<class key_t, class val_t>
class BSTMultimap
{protected:
  BSTNode<key_t, val_t>* root;
  BSTNode<key_t, val_t>* sentinel;
  int numItems;
  virtual void transplant(BSTNode<key_t, val_t>* toDelete, BSTNode<key_t,val_t>* takeDeletePlace);
  virtual void insertNode(BSTNode<key_t, val_t>* newNode);
  


 public:

  BSTMultimap();
  virtual void clear();
  virtual ~BSTMultimap();
  virtual void insert(const key_t& key, const val_t& val);
  virtual int getSize();
  virtual bool isEmpty() const;
  virtual void printTree();
  virtual bool contains(const key_t& key) const;
  virtual BSTForwardIterator<key_t, val_t> getMin() const;
  virtual BSTForwardIterator<key_t, val_t> getMax() const;
  virtual BSTForwardIterator<key_t, val_t> findFirst(const key_t& key) const;
  virtual BSTForwardIterator<key_t, val_t> findLast(const key_t& key) const;
  virtual BSTForwardIterator<key_t, val_t> remove(const BSTForwardIterator<key_t, val_t>& pos);
  

};

/////////////////////////////////
//Implementation of BSTMultimap//
/////////////////////////////////

//default and only constructor
template<class key_t,class val_t>
BSTMultimap<key_t, val_t>::BSTMultimap()
{sentinel = 0;
  root = sentinel;
  numItems = 0;
}

//destructor
template<class key_t,class val_t>
BSTMultimap<key_t, val_t>::~BSTMultimap()
{clear();
}

//what destructor calls, deletes all nodes
template<class key_t,class val_t>
void BSTMultimap<key_t, val_t>::clear()
{queue<BSTNode<key_t, val_t>*> queue;
  if(root != sentinel)
    {queue.push(root);
    }
  
  while (!queue.empty())
    {auto curNode = queue.front();
      queue.pop();
      if(curNode->getLeftChild() != sentinel)
	{ queue.push(curNode->getLeftChild());
	}
      if(curNode->getRightChild() != sentinel)
	{
	  queue.push(curNode->getRightChild());
	}
      delete curNode; 
    }
  numItems = 0;
  root = sentinel;
}


template<class key_t,class val_t>
  void BSTMultimap<key_t, val_t>::insert(const key_t& key, const val_t& val)
{BSTNode<key_t, val_t>* newNode = new BSTNode<key_t, val_t>(key, val);
  newNode->setLeftChild(sentinel);
  newNode->setRightChild(sentinel);

  //size updates in insert node
  insertNode(newNode);
  
  
}

template<class key_t,class val_t>
void BSTMultimap<key_t, val_t>::insertNode(BSTNode<key_t, val_t>* newNode)
{BSTNode<key_t, val_t>* parentHolder = sentinel;
  BSTNode<key_t, val_t>* nodeToCompare = root;
  ++numItems;
  
  //if empty, skips the while loop, makes newNode's parent the sentinel
  while(nodeToCompare != sentinel)
    {parentHolder = nodeToCompare;
      
      //due to loop conditions, parentHolder will never be sentinel here
      if(newNode->getKey() < nodeToCompare->getKey())
	{nodeToCompare = nodeToCompare->getLeftChild();
	}
      //nodes with keys >= to nodeToCompare's key go to the right
      else
	{nodeToCompare = nodeToCompare->getRightChild();
	}
    }//end while loop
  
  newNode->setParent(parentHolder);
  
  //if the tree had been empty, the new node is now the root
  if(parentHolder == sentinel)
    {root = newNode;
    }
  //if newNode's key < the key of the node it has to descend from, it's a left child
  else if(newNode->getKey() < parentHolder->getKey())
    {parentHolder->setLeftChild(newNode);
    }
  //if key was >=, it's a right child
  else
    {parentHolder->setRightChild(newNode);
    }
}




template<class key_t,class val_t>
  int BSTMultimap<key_t, val_t>::getSize()
{return numItems;
}

template<class key_t,class val_t>
  bool BSTMultimap<key_t, val_t>::isEmpty() const
{return root == sentinel;
}


template<class key_t,class val_t>
  bool BSTMultimap<key_t, val_t>::contains(const key_t& key) const
{//start search at root
  BSTNode<key_t, val_t>* curNode = root;
//tree wasn't empty, it hasn't reached the bottom yet, and key not yet found
 while(curNode != sentinel && curNode->getKey() != key)
   {if(key < curNode->getKey())
       {curNode = curNode->getLeftChild();
       }
     else
       {curNode = curNode->getRightChild();
       }
   }

 if(curNode == sentinel)
   {return false;
   }
 else
   {return true;
   }
}


template<class key_t,class val_t>
BSTForwardIterator<key_t, val_t> BSTMultimap<key_t, val_t>::getMin() const
{if(isEmpty())
    {BSTForwardIterator<key_t, val_t> iterator(sentinel, sentinel);
      return iterator;
    }
  BSTNode<key_t, val_t>* min = root;
  while(min->getLeftChild() != sentinel)
    {min = min->getLeftChild();
    }
  BSTForwardIterator<key_t, val_t> iterator(min, sentinel);
  return iterator;
}
template<class key_t,class val_t>
BSTForwardIterator<key_t, val_t> BSTMultimap<key_t, val_t>::getMax() const
{if(isEmpty())
    {BSTForwardIterator<key_t, val_t> iter(sentinel, sentinel);
      return iter;
    }

  BSTNode<key_t, val_t>* max = root;
  while(max->getRightChild() != sentinel)
    {max = max->getRightChild();
    }
  BSTForwardIterator<key_t, val_t> iter(max, sentinel);
  return iter;

}
template<class key_t,class val_t>
BSTForwardIterator<key_t, val_t> BSTMultimap<key_t, val_t>::findFirst(const key_t& key) const
{//start at root
  BSTNode<key_t, val_t>* curNode = root;
  
  //find instance of key
//tree wasn't empty, it hasn't reached the bottom yet, and key not yet found
  while(curNode != sentinel && curNode->getKey() != key)
   {if(key < curNode->getKey())
       { curNode = curNode->getLeftChild();	 
       }
     else
       {curNode = curNode->getRightChild();
       }
   }
 
 

 //if the key wasn't in the tree
 if(curNode == sentinel)
   {BSTForwardIterator<key_t, val_t> iter(curNode, sentinel);
    return iter;
   }
 BSTNode<key_t, val_t>* checkNode = curNode->getLeftChild();

 //while it can still go left and find the same key
 while(checkNode!= sentinel && checkNode->getKey() == key)
   {curNode = checkNode;
    checkNode = checkNode->getLeftChild();   
   }

 if(checkNode!=sentinel && (checkNode->getRightChild())->getKey()==key)
   {curNode = checkNode->getRightChild();
   }

 BSTForwardIterator<key_t, val_t> iter(curNode, sentinel);
     return iter;
  
}
template<class key_t,class val_t>
BSTForwardIterator<key_t, val_t> BSTMultimap<key_t, val_t>::findLast(const key_t& key) const
{//start at root
  BSTNode<key_t, val_t>* curNode = root;

//tree wasn't empty, it hasn't reached the bottom yet, and key not yet found
 while(curNode != sentinel && curNode->getKey() != key)
   {if(key < curNode->getKey())
       {curNode = curNode->getLeftChild();
       }
     else
       {curNode = curNode->getRightChild();
       }
   }

 //if the key wasn't in the tree
 if(curNode == sentinel)
   {BSTForwardIterator<key_t, val_t> iter(curNode, sentinel);
    return iter;
   }

 BSTNode<key_t, val_t>* checkNode = curNode->getRightChild();

 //while it can still go right and find the same key
 while(checkNode!= sentinel && checkNode->getKey() == key)
   {curNode = checkNode;
    checkNode = checkNode->getRightChild();   
   }

 if(checkNode!=sentinel && (checkNode->getLeftChild())->getKey()==key)
   {curNode = checkNode->getLeftChild();
   }


 BSTForwardIterator<key_t, val_t> iter(curNode, sentinel);
     return iter;

}

template <class key_t, class val_t>
BSTForwardIterator<key_t, val_t> BSTMultimap<key_t, val_t>::remove(const BSTForwardIterator<key_t, val_t>& pos)
{//in case it wants to remove from an empty tree/remove sentinel
if(pos.isPastEnd())
  {return pos;
  }

  //gets sucessor awhile (iterator form)
  BSTForwardIterator<key_t, val_t> sucessor = pos;
  sucessor.next();



  //make the node* pointing to the node to delete more accessible
  BSTNode<key_t, val_t>* toDelete = pos.current;

  //no left child, replace toDelete with rightChild (even if it's sentinel)
  if(toDelete->getLeftChild() == sentinel)
    {transplant(toDelete, toDelete->getRightChild());
    }

  //only left child exists, transplant toDelete with leftChild
  else if(toDelete->getRightChild() == sentinel)
    {transplant(toDelete, toDelete->getLeftChild());
    }

  //2 children
  else
    {//replacement isn't the right child of toDelete
     if(sucessor.current->getParent() != toDelete)
       {//replace replacement (which can only have 1 or 0 right children)
	 transplant(sucessor.current, sucessor.current->getRightChild());
	 
	 sucessor.current->setRightChild(toDelete->getRightChild());
	 sucessor.current->getRightChild()->setParent(sucessor.current);
       }

	
     transplant(toDelete, sucessor.current);
     sucessor.current->setLeftChild(toDelete->getLeftChild());
     sucessor.current->getLeftChild()->setParent(sucessor.current);	
    }
    
    delete pos.current;
    --numItems;
    return sucessor;
}

//assumes you aren't sending it to delete sentinel, aka toDelete != sentinel
template <class key_t, class val_t>
void BSTMultimap<key_t, val_t>::transplant(BSTNode<key_t, val_t>* toDelete ,BSTNode<key_t,val_t>* takeDeletePlace)
{
  BSTNode<key_t, val_t>* toDeleteParent = toDelete->getParent();
  
//update the appropriate child of toDelete's parent
  //deleting the root
  if(toDeleteParent==sentinel)
      {root = takeDeletePlace;
      }
  //toDelete is a left child
  else if(toDelete == toDeleteParent->getLeftChild())
    {toDeleteParent->setLeftChild(takeDeletePlace);
    }
  //deleting a right child
  else
    {toDeleteParent->setRightChild(takeDeletePlace);
      
    }



  //non-sentinel replacement nodes update their parent here
  if(takeDeletePlace != sentinel)
    {takeDeletePlace->setParent(toDeleteParent);
    }

}

template<class key_t,class val_t>
  void BSTMultimap<key_t, val_t>::printTree()
{queue<BSTNode<key_t, val_t>*> queue;
  queue.push(root);
  
  
  while (!queue.empty())
    {auto curNode = queue.front();
      cout << "key:" <<curNode->getKey() <<"\t val:"<<curNode->getValue();
      if(curNode->getLeftChild() != sentinel)
	{ queue.push(curNode->getLeftChild());
	}
      if(curNode->getRightChild() != sentinel)
	{
	  queue.push(curNode->getRightChild());
	}
     queue.pop();
     cout<<endl;
    }
     
    
}



#endif
