#ifndef RBT_NODE
#define RBT_NODE

#include "BSTNode.h"

template <class key_t, class val_t>
class RBTNode : public BSTNode<key_t, val_t>
{
  protected:
   //False for black
   //True for red
   bool color;

  public:
   //Children, parent initialized to zero
   RBTNode(const key_t& key, const val_t& value, bool color);

   RBTNode<key_t, val_t>* getParent() const;
   RBTNode<key_t, val_t>* getLeftChild() const;
   RBTNode<key_t, val_t>* getRightChild() const;

   virtual void setColor(bool newColor);
   virtual bool getColor() const;
};

/////////////////////////////////////////
//Implementation of RBTNode begins here//
/////////////////////////////////////////

template <class key_t, class val_t>
RBTNode<key_t, val_t>::RBTNode(const key_t& key, const val_t& value, bool color) : BSTNode<key_t, val_t>(key, value)
{
   this->color = color;
}

template <class key_t, class val_t>
RBTNode<key_t, val_t>* RBTNode<key_t, val_t>::getParent() const
{
   return dynamic_cast<RBTNode<key_t, val_t>* >(this->parent);
}

template <class key_t, class val_t>
RBTNode<key_t, val_t>* RBTNode<key_t, val_t>::getLeftChild() const
{
   return dynamic_cast<RBTNode<key_t, val_t>* >(this->leftChild);
}

template <class key_t, class val_t>
RBTNode<key_t, val_t>* RBTNode<key_t, val_t>::getRightChild() const
{
   return dynamic_cast<RBTNode<key_t, val_t>* >(this->rightChild);
}

template <class key_t, class val_t>
bool RBTNode<key_t, val_t>::getColor() const
{
   return color;
}

template <class key_t, class val_t>
void RBTNode<key_t, val_t>::setColor(bool newColor)
{
   color = newColor;
}

#endif
