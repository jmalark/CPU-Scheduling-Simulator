#ifndef RBT_MULTIMAP
#define RBT_MULTIMAP

#include "BSTMultimap.h"
#include "RBTNode.h"

#include <string>
#include <fstream>
#include <queue>
#include <iostream>
#include <map>

using namespace std;

template <class key_t, class val_t>
class RBTMultimap : public BSTMultimap<key_t, val_t>
{
  protected:
   //Performs the rotate left operation
   //(assumes node has a right child)
   virtual void rotateLeft(BSTNode<key_t, val_t>* node);

   //Performs the rotate right operation
   //(assumes node has a left child)
   virtual void rotateRight(BSTNode<key_t, val_t>* node);

   //Fix up the tree after an insert
   //(assumes insertedNode is red)
   virtual void insertFixup(RBTNode<key_t, val_t>* insertedNode);

   //Fix up the tree after deleting a node
   //ReplacementNode is the node that replaced the deleted node
   //(possibly the sentinel)
   virtual void deleteFixup(RBTNode<key_t, val_t>* replacementNode);

   //Puts replacementNode in nodeToReplace's position in the tree
   //(replacementNode takes its children along with it)
   //Assumes nodeToReplace is a real node (not the sentinel)
   virtual void transplant(BSTNode<key_t, val_t>* nodeToReplace, BSTNode<key_t, val_t>* replacementNode);

  public:


   //Creates an empty red-black tree
   RBTMultimap();
   virtual ~RBTMultimap();

   //Inserts (key, value) into the multimap
   virtual void insert(const key_t& key, const val_t& value);

   //Removes the key/value pair pointed to by pos
   //(if pos is off the end, does nothing)
   //Returns an iterator pointing to the next node after the
   //deleted node
   virtual BSTForwardIterator<key_t, val_t> remove(const BSTForwardIterator<key_t, val_t>& pos);

   //Prints the tree in the "dot" format for visualization
   //using graphviz
   //NOTE: Requires that keys are streamable (values are not printed)
   virtual void printDOT(std::string filename);
};

//////////////////////////////////////////
//RBTMultimap implementation begins here//
//////////////////////////////////////////

template <class key_t, class val_t>
RBTMultimap<key_t, val_t>::RBTMultimap()
{//sentinel is a black RBTNode
  this->sentinel = new RBTNode<key_t, val_t>(key_t(), val_t(), false);
    this->root = this->sentinel;

  }

template <class key_t, class val_t>
RBTMultimap<key_t, val_t>::~RBTMultimap()
{BSTMultimap<key_t, val_t>::clear();
  delete this->sentinel;
}



//Inserts (key, value) into the multimap
template <class key_t, class val_t>
void RBTMultimap<key_t, val_t>::insert(const key_t& key, const val_t& value)
{//color is red
  RBTNode<key_t, val_t>* newNode = new RBTNode<key_t,val_t>(key, value, true);
  newNode->setLeftChild(this->sentinel);
  newNode->setRightChild(this->sentinel);

  //size updates in insertNode
  BSTMultimap<key_t, val_t>::insertNode(newNode);
  insertFixup(newNode);
}

template <class key_t, class val_t>
BSTForwardIterator<key_t, val_t> RBTMultimap<key_t, val_t>::remove(const BSTForwardIterator<key_t, val_t>& pos)
{
  RBTNode<key_t, val_t>* passedInNode = dynamic_cast<RBTNode<key_t, val_t>*>(pos.current);
  RBTNode<key_t, val_t>* deletedNode = passedInNode;
  //if it's trying to remove sentinel, just return pos
  if(passedInNode == this->sentinel)
    {return pos;
    }
  //declare replacement node, it will be properly initialized depending on which if statement it goes into
  RBTNode<key_t, val_t>* replacementNode = 0;
  bool delNodeOrigColor = passedInNode->getColor();
  //find sucessor awhile
  BSTForwardIterator<key_t, val_t> sucessor = pos;
  sucessor.next();
  
  //no left child, replace with right child (even if it's sentinel)
  if(passedInNode->getLeftChild()== this->sentinel)
    {replacementNode = passedInNode->getRightChild();
      transplant(passedInNode, replacementNode);
    }

  //only left child, replace with left child
  else if(passedInNode->getRightChild() == this->sentinel)
    {replacementNode = passedInNode->getLeftChild();
      transplant(passedInNode, replacementNode);
    }

  //2 children
  else
    {
      deletedNode = dynamic_cast<RBTNode<key_t,val_t>*>(sucessor.current);
      delNodeOrigColor = deletedNode->getColor();
      replacementNode = deletedNode->getRightChild();
      

      //if sucessor is just the right child, update replacementNode's parent
      if(deletedNode->getParent() == passedInNode)
	{replacementNode->setParent(deletedNode);
	}

      //sucessor was elsewhere in the tree
      else
	{transplant(deletedNode, replacementNode);
	  deletedNode->setRightChild(passedInNode->getRightChild());
	  (deletedNode->getRightChild())->setParent(deletedNode);
	}
      

      transplant(passedInNode, deletedNode);
      deletedNode->setLeftChild(passedInNode->getLeftChild());
      (deletedNode->getLeftChild())->setParent(deletedNode);
      deletedNode->setColor(passedInNode->getColor());
    }

 
  if(delNodeOrigColor == false)
    {deleteFixup(replacementNode);
    }

  --this->numItems;
  BSTForwardIterator<key_t, val_t> iterator(sucessor.current, this->sentinel);
  delete pos.current;
  return iterator;

}

//node is the oldParent/the old 'top' node (the one that started higher)
template <class key_t, class val_t>
void RBTMultimap<key_t, val_t>::rotateLeft(BSTNode<key_t, val_t>* node)
{  BSTNode<key_t, val_t>* oldRightChild = node->getRightChild();

  //topNode/oldParent/node takes the oldChild's 'inner child' (one closer spacially to oldParent)
  node->setRightChild(oldRightChild->getLeftChild());

  //old child has a child to transfer (it didnt' give oldParent sentinel)
  if (oldRightChild->getLeftChild() != this->sentinel)
    {(oldRightChild->getLeftChild())->setParent(node);
    }

  //updates old child's parent
  oldRightChild->setParent(node->getParent());

  //node was root
  if (node->getParent() == this->sentinel)
    {this->root = oldRightChild;
    }
  //node is a left child
  else if (node == (node->getParent())->getLeftChild())
    {(node->getParent())->setLeftChild(oldRightChild);
    }
  //node is a right child
  else
    {(node->getParent())->setRightChild(oldRightChild);
    }


  oldRightChild->setLeftChild(node);
  node->setParent(oldRightChild);

}
//node is the oldParent/the old 'top' node (the one that started higher)
template <class key_t, class val_t>
void RBTMultimap<key_t, val_t>::rotateRight(BSTNode<key_t, val_t>* node)
{BSTNode<key_t, val_t>* oldLeftChild = node->getLeftChild();
  
//topNode/oldParent/node takes the oldChild's 'inner child' (one closer spacially to oldParent)
  node->setLeftChild(oldLeftChild->getRightChild());

  //old child has a child to transfer (it didn't give oldParent sentinel)
  if(oldLeftChild->getRightChild() != this->sentinel)
    {(oldLeftChild->getRightChild())->setParent(node);
    }

  //updates old child's parent
  oldLeftChild->setParent(node->getParent());

  //node was the root
  if(node->getParent() == this->sentinel)
    {this->root = oldLeftChild;
    }
  //node was a left child
  else if(node == (node->getParent())->getLeftChild())
    {(node->getParent())->setLeftChild(oldLeftChild);
    }
  //node was a right child
  else
    {(node->getParent())->setRightChild(oldLeftChild);
    }
  
  oldLeftChild->setRightChild(node);
  node->setParent(oldLeftChild);



}

//fix after insert, restore red black properties
template <class key_t, class val_t>
void RBTMultimap<key_t, val_t>::insertFixup(RBTNode<key_t, val_t>* insertedNode)
{ RBTNode<key_t, val_t>* nodeToFix = insertedNode;
  
  //while parent is red
  while((nodeToFix->getParent())->getColor() == true)
    {
  RBTNode<key_t, val_t>* parent = nodeToFix->getParent();
  RBTNode<key_t, val_t>* grandparent = parent->getParent();

      //parent is a left child
      if(parent == grandparent->getLeftChild())
	{RBTNode<key_t, val_t>* uncle = grandparent->getRightChild();

	  //red uncle
	  if(uncle->getColor() == true)
	    {//move blackness from grandparent to parent and uncle
	      parent->setColor(false);
	      uncle->setColor(false);
	      grandparent->setColor(true);
	      
	      //update nodeToFix
	      nodeToFix = grandparent;
	    }
	  //black uncle
	  else 
	    { //not in a chain, nodeToFix is a right child (left, left, right)
	      if(nodeToFix == parent->getRightChild())
		{
		  //put them in a chain
		  nodeToFix = parent;
		  rotateLeft(nodeToFix);
		  parent = nodeToFix->getParent();
		  grandparent = parent->getParent();
		}
	      //swap parent and grandparent colors
	      parent->setColor(false);
	      grandparent->setColor(true);

	      //rotate right
	      rotateRight(grandparent);
	      
	
	      
	    }
	  
	}

      //parent is a right child
      else
	{RBTNode<key_t, val_t>* uncle = grandparent->getLeftChild();
	  
	  //uncle is red
	  if(uncle->getColor() == true)
	    {//move blackness from grandparent to parent and uncle
	      parent->setColor(false);
	      uncle->setColor(false);
	      grandparent->setColor(true);
	      //update nodeToFix
	      nodeToFix = grandparent;
	    }
	  //black uncle
	  else
	    {//they aren't in a chain (Right, right, left)
	      if(nodeToFix == parent->getLeftChild())
		{nodeToFix = parent;
		  rotateRight(nodeToFix);
		  parent = nodeToFix->getParent();
		  grandparent = parent->getParent();
		}
	      //swap grandparent and parent colors
	      parent->setColor(false);
	      grandparent->setColor(true);
	      rotateLeft(grandparent);
	    }
	}
  } 

  //make sure the root is black
  dynamic_cast<RBTNode<key_t, val_t>*>(this->root)->setColor(false);

}
template <class key_t, class val_t>
void RBTMultimap<key_t, val_t>::deleteFixup(RBTNode<key_t, val_t>* replacementNode)
{
  RBTNode<key_t, val_t>* nodeToFix = dynamic_cast<RBTNode<key_t, val_t>*>(replacementNode);

  while(nodeToFix != this->root && nodeToFix->getColor()==false)
    {
      //nodeToFix is a left child
      if(nodeToFix == (nodeToFix->getParent())->getLeftChild())
	{//dynamic cast in case sibling is sentinel
	  RBTNode<key_t, val_t>* sibling = dynamic_cast<RBTNode<key_t, val_t>* >((nodeToFix->getParent())->getRightChild());
	  
	  //red sibling
	  if(sibling->getColor()==true)
	    {
	      sibling->setColor(false);
	      (nodeToFix->getParent())->setColor(true);
	      rotateLeft(nodeToFix->getParent());
	      sibling = dynamic_cast<RBTNode<key_t, val_t>*>((nodeToFix->getParent())->getRightChild());	  
	    }
	  
	  //both nephews are black
	  if((sibling->getLeftChild())->getColor() == false && (sibling->getRightChild())->getColor()==false)
	    {
	      sibling->setColor(true);
	      nodeToFix = dynamic_cast<RBTNode<key_t, val_t>*>(nodeToFix->getParent());
	    }
	  
	  //at least one red nephew
	  else
	    {
	      //not in line, sibling is right but red nephew is left
	      if((sibling->getRightChild())->getColor()==false)
		{
		  (sibling->getLeftChild())->setColor(false);
		  sibling->setColor(true);
		  rotateRight(sibling);
		  sibling = dynamic_cast<RBTNode<key_t, val_t>*>((nodeToFix->getParent())->getRightChild());
		}
	      sibling->setColor((nodeToFix->getParent())->getColor());
	      (nodeToFix->getParent())->setColor(false);
	      (sibling->getRightChild())->setColor(false);
	      rotateLeft(nodeToFix->getParent());
	      nodeToFix = dynamic_cast<RBTNode<key_t, val_t>*>(this->root);
	    }
	}//end left child if statement


      //nodeToFix is a right child
      else
	{//dynamic cast in case sibling is sentinel
	  RBTNode<key_t, val_t>* sibling = dynamic_cast<RBTNode<key_t, val_t>*>((nodeToFix->getParent())->getLeftChild());


	  //red sibling
	  if(sibling->getColor()==true)
	    { 
	      sibling->setColor(false);
	      (nodeToFix->getParent())->setColor(true);
	      rotateRight(nodeToFix->getParent());
	      sibling = dynamic_cast<RBTNode<key_t, val_t>*>((nodeToFix->getParent())->getLeftChild());
	      
	    }
	  
	  //both nephews are black
	  if((sibling->getLeftChild())->getColor() == false && (sibling->getRightChild())->getColor()==false)
	    { 
	      sibling->setColor(true);
	     nodeToFix = dynamic_cast<RBTNode<key_t, val_t>*>(nodeToFix->getParent());
	    }
	  
	  //at least one red nephew
	  else
	    {
	      //not in line, sibling is left but red nephew is right
	      if((sibling->getLeftChild())->getColor()==false)
		{
		  (sibling->getRightChild())->setColor(false);
		  sibling->setColor(true);
		  rotateLeft(sibling);
		  sibling = dynamic_cast<RBTNode<key_t, val_t>*>((nodeToFix->getParent())->getLeftChild());
		}
	      	
		sibling->setColor((nodeToFix->getParent())->getColor());
		(nodeToFix->getParent())->setColor(false);
		(sibling->getLeftChild())->setColor(false);
		rotateRight(nodeToFix->getParent());
	      
		nodeToFix = dynamic_cast<RBTNode<key_t, val_t>*>(this->root);
	     
		
	    }
	}//end right child else statement
        

    }//end while loop
  nodeToFix->setColor(false);

}
template <class key_t, class val_t>
void RBTMultimap<key_t, val_t>::transplant(BSTNode<key_t, val_t>* nodeToReplace, BSTNode<key_t, val_t>* replacementNode)
{BSTNode<key_t, val_t>* toReplaceParent = nodeToReplace->getParent();
  
//update the appropriate child of nodeToReplace's parent
  //replacing the root
  if(toReplaceParent==this->sentinel)
      {this->root = replacementNode;
      }
  //nodeToReplace is a left child
  else if(nodeToReplace == toReplaceParent->getLeftChild())
    {
      toReplaceParent->setLeftChild(replacementNode);
    }
  //nodeToReplace is a right child
  else
    {toReplaceParent->setRightChild(replacementNode);
      
    }



  //updates parent here
  replacementNode->setParent(toReplaceParent);
    
}







template <class key_t, class val_t>
void RBTMultimap<key_t, val_t>::printDOT(std::string filename)
{
   using namespace std;
   ofstream fout(filename.c_str());

   long long counter = 1;
   map<RBTNode<key_t, val_t>*, long long> nodeToCounter;
   nodeToCounter[dynamic_cast<RBTNode<key_t, val_t>* >(this->sentinel)] = counter;
   counter++;

   fout << "digraph RBTMultimap {" << endl;

   fout << "\t node" << nodeToCounter[dynamic_cast<RBTNode<key_t, val_t>* >(this->sentinel)] << " [label=\"nil\", style=filled, color=grey, fontcolor=white];" << endl;

   if(this->root != this->sentinel)
   {
      RBTNode<key_t, val_t>* rt = dynamic_cast<RBTNode<key_t, val_t>* >(this->root);
      if(!nodeToCounter[rt])
      {
	 nodeToCounter[rt] = counter;
	 counter++;
      }
      if(!nodeToCounter[rt->getParent()])
      {
	 nodeToCounter[rt->getParent()] = counter;
	 counter++;
      }
      fout << "\t node" << nodeToCounter[rt] << " -> node" << nodeToCounter[rt->getParent()] << " [constraint=false, tailport=n, headport=s";
      if(rt->getParent() == this->sentinel)
      {
	 fout << ", color=grey];" << endl;
      }
      else
      {
	 //The root's parent is something weird!! Make the arrow orange so it sticks out
	 fout << ", color=orange];" << endl;
      }

      map<RBTNode<key_t, val_t>*, bool> printed;
   
      queue<RBTNode<key_t, val_t>* > q;
      q.push(rt);
      while(!q.empty())
      {
	 RBTNode<key_t, val_t>* node = q.front();
	 q.pop();

	 printed[node] = true;
      
	 //Set up node's appearance
	 if(!nodeToCounter[node])
	 {
	    nodeToCounter[node] = counter;
	    counter++;
	 }
	 fout << "\t node" << nodeToCounter[node] << " [label=\"k: " << node->getKey() << "\", style=filled, color=";
	 if(node->getColor())
	 {
	    fout << "red";
	 }
	 else
	 {
	    fout << "black, fontcolor=white";
	 }
	 fout << "];" << endl;

	 //Set up child links
	 //First the left node
	 if(!nodeToCounter[node->getLeftChild()])
	 {
	    nodeToCounter[node->getLeftChild()] = counter;
	    counter++;
	 }
	 fout << "\t node" << nodeToCounter[node] << " -> node" << nodeToCounter[node->getLeftChild()] << " [tailport=sw";    
	 if(node->getLeftChild() == this->sentinel)
	 {
	    fout << ", color=grey";
	 }
	 else if(printed[node->getLeftChild()])
	 {
	    fout << ", color=orange";
	 }
	 else
	 {
	    q.push(node->getLeftChild());
	 }

	 if(node->getLeftChild() != this->sentinel)
	 {
	    if(node->getLeftChild()->getParent() == node)
	    {
	       //The child's parent pointer points right back,
	       //so draw the second arrow
	       fout << ", dir=both];" << endl;
	    }
	    else
	    {
	       //The child node's parent pointer is not correct!
	       //Draw it in orange so it sticks out
	       fout << "];" << endl;
	       if(!nodeToCounter[node->getLeftChild()->getParent()])
	       {
		  nodeToCounter[node->getLeftChild()->getParent()] = counter;
		  counter++;
	       }
	       fout << "\t node" << nodeToCounter[node->getLeftChild()] << " -> node" << nodeToCounter[node->getLeftChild()->getParent()] << " [tailport=n, color=orange];" << endl;
	    }
	 }
	 else
	 {
	    fout << "];" << endl;
	 }

	 //Now the right node
	 if(!nodeToCounter[node->getRightChild()])
	 {
	    nodeToCounter[node->getRightChild()] = counter;
	    counter++;
	 }
	 fout << "\t node" << nodeToCounter[node] << " -> node" << nodeToCounter[node->getRightChild()] << " [tailport=se";    
	 if(node->getRightChild() == this->sentinel)
	 {
	    fout << ", color=grey";
	 }
	 else if(printed[node->getRightChild()])
	 {
	    fout << ", color=orange";
	 }
	 else
	 {
	    q.push(node->getRightChild());
	 }

	 if(node->getRightChild() != this->sentinel)
	 {
	    if(node->getRightChild()->getParent() == node)
	    {
	       //The child's parent pointer points right back,
	       //so draw the second arrow
	       fout << ", dir=both];" << endl;
	    }
	    else
	    {
	       //The child node's parent pointer is not correct!
	       //Draw it in orange so it sticks out
	       fout << "];" << endl;
	       if(!nodeToCounter[node->getRightChild()->getParent()])
	       {
		  nodeToCounter[node->getRightChild()->getParent()] = counter;
		  counter++;
	       }
	       fout << "\t node" << nodeToCounter[node->getRightChild()] << " -> node" << nodeToCounter[node->getRightChild()->getParent()] << " [tailport=n, color=orange];" << endl;
	    }
	 }
	 else
	 {
	    fout << "];" << endl;
	 }
      }
   }
   fout << "}" << endl;
}

#endif
