#ifndef BSTNODE_H
#define BSTNODE_H

#include <iostream>

using namespace std;

template<class key_t, class val_t>
class BSTNode
{

 protected:
  key_t key;
  val_t val;
  BSTNode<key_t, val_t>* parent;
  BSTNode<key_t, val_t>* leftChild;
  BSTNode<key_t, val_t>* rightChild;

 public:

  virtual ~BSTNode();
  BSTNode(const key_t& keyInput, const val_t& valInput);
  virtual const val_t& getValue() const;
  virtual void setValue(const val_t& newVal);
  virtual const key_t& getKey() const; 
  virtual void setKey(const key_t& newKey);
  virtual BSTNode<key_t, val_t>* getLeftChild() const;
  virtual void setLeftChild(BSTNode<key_t, val_t>* newChild);
  virtual BSTNode<key_t, val_t>* getRightChild() const;
  virtual void setRightChild(BSTNode<key_t, val_t>* newChild);
  virtual BSTNode<key_t, val_t>* getParent() const;
  virtual void setParent(BSTNode<key_t, val_t>* newParent);


};

/////////////////////////////
//Implementation of BSTNode//
/////////////////////////////

template<class key_t,class val_t>
BSTNode<key_t, val_t>::BSTNode(const key_t& keyInput, const val_t& valInput)
{key = keyInput;
  val= valInput;
  parent = 0;
  leftChild = 0;
  rightChild = 0;
}

//destructor that does nothing, exists so RB version can inherit
template<class key_t,class val_t>
BSTNode<key_t, val_t>::~BSTNode()
{
}

template<class key_t,class val_t>
const val_t& BSTNode<key_t, val_t>::getValue() const
{return val;
}

template<class key_t,class val_t>
void BSTNode<key_t, val_t>::setValue(const val_t& newVal)
{val = newVal;
}

template<class key_t,class val_t>
const key_t& BSTNode<key_t, val_t>::getKey() const
{return key;
}

template<class key_t,class val_t> 
 void BSTNode<key_t, val_t>::setKey(const key_t& newKey)
{key = newKey;
}

template<class key_t,class val_t>
  BSTNode<key_t, val_t>* BSTNode<key_t, val_t>::getLeftChild() const
{return leftChild;
}

template<class key_t,class val_t>
  void BSTNode<key_t, val_t>::setLeftChild(BSTNode<key_t, val_t>* newChild)
{leftChild = newChild;
}

template<class key_t,class val_t>
  BSTNode<key_t, val_t>* BSTNode<key_t, val_t>::getRightChild() const
{return rightChild;
}

template<class key_t,class val_t>
  void BSTNode<key_t, val_t>::setRightChild(BSTNode<key_t, val_t>* newChild)
{rightChild = newChild;
}

template<class key_t,class val_t>
  BSTNode<key_t, val_t>* BSTNode<key_t, val_t>::getParent() const
{return parent;
}

template<class key_t,class val_t>
  void BSTNode<key_t, val_t>::setParent(BSTNode<key_t, val_t>* newParent)
{parent = newParent;
}


#endif
