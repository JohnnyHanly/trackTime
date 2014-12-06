// A class template for holding a linked list.
// The node type is also a class template.

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

//*********************************************
// The ListNode class creates a type used to  *
// store a node of the linked list.           *
//*********************************************

template <class KeyType, class T>
class ListNode
{
private:
    KeyType searchKey;
    T value;           // Node value
    ListNode<KeyType, T> *next; // Pointer to the next node
public:
    // Constructor
    ListNode (T nodeValue){ value = nodeValue; next = nullptr;}
	ListNode (KeyType newKey, T nodeValue) { searchKey = newKey; value = nodeValue; next = nullptr;}
	void setNext(ListNode<KeyType, T>* nextPtr) { next = nextPtr;}
	void setValue(T valueIn) { value = valueIn; };
	void setSearchKey(KeyType searchKeyIn) { searchKey = searchKeyIn; };
	ListNode<KeyType, T>* getNext() const { return next;}
	T getValue() const {return value;}
	KeyType getSearchKey() const {return searchKey;}
};

//*********************************************
// LinkedList class                           *
//*********************************************

template <class KeyType, class T>
class LinkedList
{
private:
    ListNode<KeyType, T> *head;   // List head pointer
    int count;

public:
    // Constructor
    LinkedList(){ head = nullptr; count = 0; }

   // Destructor
   ~LinkedList();

   // Linked list operations
   ListNode<KeyType, T>* getHead() {return head;}
   int getCount() {return count;}
   void insertNode(KeyType, T);
   LinkedList<KeyType, T>* addNode(ListNode<KeyType, T>* newNode);
   ListNode<KeyType, T>* findItem(KeyType findKey) const;
   bool deleteNode(ListNode<KeyType, T>* deleteMe);
   // search
   // other linked list operations ...
   // ...
   void enhancedDisplay(void visit(T &), void specialVisit(T &, int &), int &index) const;
   void displayList(void visit(T &)) const;
   void displayList(void visit(T &, BinarySearchTree<T> *&), BinarySearchTree<T> *&tree) const;
};

template <class KeyType, class T>
bool LinkedList<KeyType, T>::deleteNode(ListNode<KeyType, T>* deleteMe)
{
	if (count == 0)
	{
		return false;
	}
	if (deleteMe == head)
	{
		head = nullptr;
		--count;
		return true;
	}
	ListNode<KeyType, T>* prev;
	ListNode<KeyType, T>* cur = head;
	while (cur != deleteMe)
	{
		prev = cur;
		cur = cur->getNext();
	}

	prev->setNext(deleteMe->getNext());
	--count;

	return true;
}


template <class KeyType, class T>
LinkedList<KeyType, T>* LinkedList<KeyType, T>::addNode(ListNode<KeyType, T>* newNode)
{
	newNode->setNext(head);
	head = newNode;
	++count;
	return this;
}


template <class KeyType, class T>
ListNode<KeyType, T>* LinkedList<KeyType, T>::findItem(KeyType findKey) const
{
	ListNode<KeyType, T>* nodePtr = head;
	if(nodePtr == nullptr)
		return nodePtr;
	else
	{
		while(nodePtr != nullptr)
		{
			if(nodePtr->getSearchKey() == findKey)
				return nodePtr;
			nodePtr = nodePtr->getNext();
		}
		return nodePtr;
	}
}

//**************************************************
// The insertNode function inserts a node with     *
// newValue copied to its value member.            *
//**************************************************

template <class KeyType, class T>
void LinkedList<KeyType, T>::insertNode(KeyType newKey, T newValue)
{
    ListNode<KeyType, T> *newNode;             // A new node
    ListNode<KeyType, T> *nodePtr;             // To traverse the list

    newNode = new ListNode<KeyType, T>(newKey, newValue); // Allocate a new node and store newValue there.
    nodePtr = head;                      // Position nodePtr at the head of list.

	newNode->setNext(nodePtr);
	newNode = head;

    count++;
}



template <class KeyType, class T>
 void LinkedList<KeyType, T>::enhancedDisplay(void visit(T &), void specialVisit(T &, int &), int &index) const
 {
	 ListNode<KeyType, T>*nodePtr;
	 nodePtr = head;
	 if(nodePtr)
	 {
		 specialVisit(nodePtr->getValue(), index);
		 nodePtr = nodePtr->getNext();
	 }
	 else
	 {
		 T* newItem = new T();
		 specialVisit(*newItem, index);
		 delete newItem;
	 }
	 while(nodePtr)
	 {
		 visit(nodePtr->getValue());
		 nodePtr = nodePtr->getNext();
	 }
 }


//**************************************************
// displayList shows the value stored in each node *
// of the linked list pointed to by head.          *
//**************************************************

template <class KeyType, class T>
void LinkedList<KeyType, T>::displayList(void visit(T &)) const
{
    ListNode<KeyType, T> *nodePtr;  // To move through the list

    // Position nodePtr at the head of the list.
    nodePtr = head;

    // While nodePtr points to a node, traverse
    // the list.
    while (nodePtr)
    {
        visit(nodePtr->getValue());  // Display the value in this node.
        nodePtr = nodePtr->getNext();         // Move to the next node.
    }
}

template <class KeyType, class T>
void LinkedList<KeyType, T>::displayList(void visit(T &,
	BinarySearchTree<T> *&), BinarySearchTree<T> *&tree) const
{
	ListNode<KeyType, T> *nodePtr;
	nodePtr = head;
	while(nodePtr)
	{
		visit(nodePtr->getValue(), tree);
		nodePtr = nodePtr->getNext();
	}
}

//**************************************************
// Destructor                                      *
// This function deletes every node in the list.   *
//**************************************************

template <class KeyType, class T>
LinkedList<KeyType, T>::~LinkedList()
{
   ListNode<KeyType, T> *nodePtr;   // To traverse the list
   ListNode<KeyType, T> *nextNode;  // To point to the next node

   // Position nodePtr at the head of the list.
   nodePtr = head;

   // While nodePtr is not at the end of the list...
   while (nodePtr != NULL)
   {
      nextNode = nodePtr->getNext();
      delete nodePtr;
	  nodePtr = NULL;
      nodePtr = nextNode;
   }
}
#endif
