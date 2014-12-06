// Node for a binary tree
// Created by Frank M. Carrano and Tim Henry.
// Modified by: Tim Bly
// Compiled withe Microsoft Visual Studio 2012 on Windows 8.1 64 bit
// Class provides an entry point for the nodes on the tree
#ifndef _BINARY_NODE
#define _BINARY_NODE

template<class ItemType>
class BinaryNode
{
private:
	ItemType              item;         // Data portion
	BinaryNode<ItemType>* leftPtr;		// Pointer to left child
	BinaryNode<ItemType>* rightPtr;		// Pointer to right child

public:
	// constructors
	BinaryNode() { item = new ItemType(); leftPtr = nullptr; rightPtr = nullptr; } // default constructor
	BinaryNode(const ItemType & anItem)	{item = anItem; leftPtr = nullptr; rightPtr = nullptr;} // overloaded constructor
	BinaryNode(const ItemType & anItem,
		       BinaryNode<ItemType>* left,
			   BinaryNode<ItemType>* right) {item = anItem; leftPtr = left; rightPtr = right;} // overloaded constructor
	// accessors
	void setItem(const ItemType & anItem) {item = anItem;}
	void setLeftPtr(BinaryNode<ItemType>* left) {leftPtr = left;}
    void setRightPtr(BinaryNode<ItemType>* right) {rightPtr = right;}
	// mutators
	ItemType getItem() const	 {return item;}
	BinaryNode<ItemType>* getLeftPtr() const  {return leftPtr;}
	BinaryNode<ItemType>* getRightPtr() const {return rightPtr;}

	bool isLeaf() const {return (leftPtr == 0 && rightPtr == 0);}
};

#endif
