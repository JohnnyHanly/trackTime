// Binary tree abstract base class
// Created by Frank M. Carrano and Tim Henry.
// Modified by: Tim Bly
// Compiled withe Microsoft Visual Studio 2012 on Windows 8.1 64 bit
 
#ifndef _BINARY_TREE
#define _BINARY_TREE

#include "BinaryNode.h"
#include "Queue.h"
#include <stack>

template<class ItemType>
class BinaryTree
{
protected:
	BinaryNode<ItemType>* rootPtr;		// ptr to root node
	int count;							// number of nodes in tree

public:
	// "admin" functions
	BinaryTree() { rootPtr = 0; count = 0; }
	BinaryTree(const BinaryTree<ItemType> & tree){ rootPtr = copyTree(tree.rootPtr); }
	virtual ~BinaryTree() { destroyTree(rootPtr); rootPtr=0; count = 0; }
	BinaryTree & operator = (const BinaryTree & sourceTree);
   
	// common functions for all binary trees
 	bool isEmpty() const	{return (count == 0);}
	int size() const	    {return count;}
	int getHeight() { return getHeightHelper(rootPtr); }
	ItemType getRootItem() const {return rootPtr->getItem();}

	void clear()			{destroyTree(rootPtr); rootPtr = 0; count = 0;}
	void preOrder(void visit(ItemType &)) const {_preorder(visit, rootPtr);}
	// overloaded to process an indented list, overloaded function takes an int parameter as well to increment and
	// process with the process function before processing the data with visit function.
	void preOrder(void visit(ItemType &), void process(int &), int indent) const {_preorder(visit, process, rootPtr, indent);}
	void inOrder(void visit(ItemType &)) const  {_inorder(visit, rootPtr);}
	//overloaded to do a conditional traversal, overloaded function only visits those items greater than passed item
	void inOrder(void visit(ItemType &), ItemType & item) const {_inorder(visit, rootPtr, item); }
	void postOrder(void visit(ItemType &)) const{_postorder(visit, rootPtr);}
	void breadthFirst(void visit(ItemType &)) const{_breadthfirst(visit, rootPtr);}
	// Iterative traversals
	void iterativeInOrder(void visit(ItemType &)) const {_iterativeinorder(visit, rootPtr);}
	void iterativePreOrder(void visit(ItemType &)) const {_iterativepreorder(visit, rootPtr);}
	void iterativePostOrder(void visit(ItemType &)) const {_iterativepostorder(visit, rootPtr);}

	// abstract functions to be implemented by derived class
	virtual bool insert(const ItemType & newData) = 0; 
	virtual bool remove(const ItemType & data) = 0; 
	virtual bool getEntry(const ItemType & anEntry, ItemType & returnedItem) const = 0;

private:   

	int getHeightHelper(BinaryNode<ItemType>* nodePtr) const;
	// delete all nodes from the tree
	void destroyTree(BinaryNode<ItemType>* nodePtr);

	// copy from the tree rooted at nodePtr and returns a pointer to the copy
	BinaryNode<ItemType>* copyTree(const BinaryNode<ItemType>* nodePtr);

	// internal traverse
	void _preorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;
	void _preorder(void visit(ItemType &), void process(int &), BinaryNode<ItemType>* nodePtr, int indent) const;
	void _inorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;
	void _inorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr, ItemType & item) const;
	void _postorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;
	void _breadthfirst(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;
   
	//iterative traversals
	void _iterativeinorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;
	void _iterativepreorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;
	void _iterativepostorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;
}; 

//////////////////////////////////////////////////////////////////////////


template<class ItemType>
int BinaryTree<ItemType>::getHeightHelper(BinaryNode<ItemType>* nodePtr) const
{
	if(nodePtr == nullptr)
		return 0;
	else
		return 1 + max(getHeightHelper(nodePtr->getLeftPtr()), getHeightHelper(nodePtr->getRightPtr()));
}



template<class ItemType>
BinaryNode<ItemType>* BinaryTree<ItemType>::copyTree(const BinaryNode<ItemType>* nodePtr) 
{
	BinaryNode<ItemType>* newNodePtr = nullptr;

	if(nodePtr != nullptr)
	{
		newNodePtr = new BinaryNode<ItemType>(nodePtr->getItem(), nullptr, nullptr);
		newNodePtr->setLeftPtr(copyTree(nodePtr->getLeftPtr()));
		newNodePtr->setRightPtr(copyTree(nodePtr->getRightPtr()));
	}    
    return newNodePtr;
}  

template<class ItemType>
void BinaryTree<ItemType>::destroyTree(BinaryNode<ItemType>* nodePtr)
{
	if(nodePtr)
	{
		destroyTree(nodePtr->getLeftPtr());
		destroyTree(nodePtr->getRightPtr());
		delete nodePtr;
	}
	return;
}  

template<class ItemType>
void BinaryTree<ItemType>::_preorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const
{
	if (nodePtr != 0)
	{
		ItemType item = nodePtr->getItem();
		visit(item);
		_preorder(visit, nodePtr->getLeftPtr());
		_preorder(visit, nodePtr->getRightPtr());
	} 
}  

template<class ItemType>
void BinaryTree<ItemType>::_preorder(void visit(ItemType &), void process(int &), BinaryNode<ItemType>* nodePtr, int indent) const
{
	if(nodePtr != 0)
	{
		ItemType item = nodePtr->getItem();
		process(indent);
		visit(item);
		++indent;
		_preorder(visit, process, nodePtr->getLeftPtr(), indent);
		_preorder(visit, process, nodePtr->getRightPtr(), indent);
	}
}

template<class ItemType>
void BinaryTree<ItemType>::_iterativepreorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const
{
	BinaryNode<ItemType> *curPtr = nodePtr;
	stack<BinaryNode<ItemType>*> nodeStack;
	bool done = false;
	if(curPtr == nullptr)
		return;

	nodeStack.push(curPtr);

	while(!nodeStack.empty())
	{
		curPtr = nodeStack.top();
		visit(curPtr->getItem());
		nodeStack.pop();
		if(curPtr->getRightPtr())
			nodeStack.push(curPtr->getRightPtr());
		if(curPtr->getLeftPtr())
			nodeStack.push(curPtr->getLeftPtr());
	}

}



template<class ItemType>
void BinaryTree<ItemType>::_inorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const
{
	if(nodePtr != 0)
	{
		_inorder(visit, nodePtr->getLeftPtr());
		ItemType item = nodePtr->getItem();
		visit(item);
		_inorder(visit, nodePtr->getRightPtr());
	}
}  

template<class ItemType>
void BinaryTree<ItemType>::_inorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr, ItemType & item) const
{
	if(nodePtr != 0)
	{
		_inorder(visit, nodePtr->getLeftPtr(), item);
		ItemType nodeItem = nodePtr->getItem();
		if(nodeItem > item)
			visit(nodeItem);
		_inorder(visit, nodePtr->getRightPtr(), item);
	}
}

template<class ItemType>
void BinaryTree<ItemType>::_iterativeinorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const
{
	BinaryNode<ItemType> *curPtr = nodePtr;
	stack<BinaryNode<ItemType>*> *nodeStack = new stack<BinaryNode<ItemType>*>();
	bool done = false;

	while(!done)
	{
		if(curPtr != nullptr)
		{
			nodeStack->push(curPtr);
			curPtr = curPtr->getLeftPtr();
		}
		else
		{
			if(!nodeStack->empty())
			{
				curPtr = nodeStack->top();
				visit(curPtr->getItem());
				nodeStack->pop();
				curPtr = curPtr->getRightPtr();
			}
			else
				done = true;
		}
	}
	delete nodeStack;
}


template<class ItemType>
void BinaryTree<ItemType>::_postorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const
{
	if(nodePtr != 0)
	{
		_postorder(visit, nodePtr->getLeftPtr());
		_postorder(visit, nodePtr->getRightPtr());
		ItemType item = nodePtr->getItem();
		visit(item);
	}
}  




template<class ItemType>
void BinaryTree<ItemType>::_iterativepostorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const
{
	BinaryNode<ItemType> *curPtr = nodePtr;
	stack<BinaryNode<ItemType>*> nodeStack;
	if(curPtr == nullptr)
		return;

	do
	{
		while(curPtr)
		{
			if(curPtr->getRightPtr())
				nodeStack.push(curPtr->getRightPtr());
			nodeStack.push(curPtr);
			curPtr = curPtr->getLeftPtr();
		}

		curPtr = nodeStack.top();
		nodeStack.pop();

		if(curPtr->getRightPtr() && !nodeStack.empty() && nodeStack.top() == curPtr->getRightPtr())
		{
			nodeStack.pop();
			nodeStack.push(curPtr);
			curPtr = curPtr->getRightPtr();
		}
		else
		{
			visit(curPtr->getItem());
			curPtr = nullptr;
		}
	}while(!nodeStack.empty());

}



template<class ItemType>
void BinaryTree<ItemType>::_breadthfirst(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const
{
	BinaryNode<ItemType> *traverse = nullptr;
	
	if(nodePtr == nullptr)
		return;

	Queue<BinaryNode<ItemType>*> *q = new Queue<BinaryNode<ItemType>*>();
	q->enqueue(nodePtr);
	while(!q->isEmpty())
	{
		q->dequeue(traverse);
		visit(traverse->getItem());
		if(traverse->getLeftPtr() != nullptr)
			q->enqueue(traverse->getLeftPtr());
		if(traverse->getRightPtr() != nullptr)
			q->enqueue(traverse->getRightPtr());
	}
	delete q;
}



template<class ItemType>
BinaryTree<ItemType> & BinaryTree<ItemType>::operator=(const BinaryTree<ItemType> & sourceTree)
{
	if(this != &sourceTree)
	{
		this->clear();
		this = copyTree(sourceTree);
		count = sourcetree->size();
	}
	return *this;
}  


#endif

