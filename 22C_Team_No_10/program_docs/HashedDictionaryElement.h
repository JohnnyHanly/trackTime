// class used to store elements within the hashDictionary
// pointer to a linkedList is used, then the data, then gets pointed at by the linkedList
#ifndef _HASHED_DICTIONARY_ELEMENT
#define _HASHED_DICTIONARY_ELEMENT

#include "LinkedList.h"

template<class KeyType, class ItemType>
class HashedDictionaryElement
{
private:
	int count;
	LinkedList<KeyType, ItemType>* linkedListArr;

public:
	HashedDictionaryElement() { count = 0; linkedListArr = new LinkedList<KeyType, ItemType>();}
	int getCount() const {return count;}
	void setCount(int newCount) { count = newCount;}
	void setList(LinkedList<KeyType, ItemType>* newList) { linkedListArr = newList; }
	LinkedList<KeyType, ItemType>* getList() const {return linkedListArr;}
	void addEntry(ListNode<KeyType, ItemType>* newNode)
	{
		linkedListArr = linkedListArr->addNode(newNode);
		count = linkedListArr->getCount();
	}
};

#endif
