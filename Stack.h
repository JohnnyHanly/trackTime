/**~*~*
   Stack template
   Modified by Steven An
*~**/
#ifndef DYNAMICSTACK_H
#define DYNAMICSTACK_H
#include <iostream>
using namespace std;

template <class T>
class Stack
{
private:
   // Structure for the stack nodes
   struct StackNode
   {
      T value;          // Value in the node
      StackNode *next;  // Pointer to next node
   };

   StackNode *top;     // Pointer to the stack top
   int count;

public:
   //Constructor
   Stack(){top = NULL; count = 0;}

   // Destructor
   ~Stack();

   // Stack operations
   bool push(T);
   bool pop(T &);
   bool isEmpty();
   int getCount();
   T getTop();
   void printStack();
};

//prints stack to screen
template<class T>
void Stack<T>::printStack()
{
	if(isEmpty())
  {
    cout << "-------\nSTACK EMPTY\n-------";
    return;
  }
	StackNode *curPtr;
	curPtr = top;
	cout << "\n----------STACK SIZE: " << getCount() << "----------\n";
	cout << "PRINTING STACK FROM TOP --> BOTTOM\n";
	
	while(curPtr != NULL)
	{
		cout << curPtr->value << " ";
		curPtr = curPtr->next;
	}
	
	cout << endl;
}

//returns top item. 
template <class T>
T Stack<T>::getTop()
{
	if(!isEmpty())
		return top->value;
}

//returns number of items in stack
template <class T>
int Stack<T>::getCount()
{
  return count;
}

//d_tor
template <class T>
Stack<T>::~Stack()
{
   StackNode *currNode, *nextNode;

   // Position nodePtr at the top of the stack.
   currNode = top;

   // Traverse the list deleting each node.
   while (currNode) //while (currNode != NULL)
   {
      nextNode = currNode->next;
      delete currNode;
      currNode = nextNode;
   }
}

//pushes item onto stack
template <class T>
bool Stack<T>::push(T item)
{
   StackNode *newNode; // Pointer to a new node

   // Allocate a new node and store num there.
   newNode = new StackNode;
   if (!newNode)
       return false;
   newNode->value = item;

   // Update links and counter
   newNode->next = top;
   top = newNode;

   count++;

   return true;
}

//pops, given the stack isnt empty
template <class T>
bool Stack<T>::pop(T &item)
{
   StackNode *temp; // Temporary pointer

   // empty stack
   if (isEmpty())
       return false;

   // pop value off top of stack
   item = top->value;
   temp = top->next;
   delete top;
   top = temp;
   count--;

   return true;
}

/**~*~*
  Member function isEmpty returns true if the stack
  is empty, or false otherwise.
*~**/
template <class T>
bool Stack<T>::isEmpty()
{
   return count == 0;
}
#endif
