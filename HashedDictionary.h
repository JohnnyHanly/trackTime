#ifndef _HASHED_DICTIONARY
#define _HASHED_DICTIONARY

#include "HashedDictionaryElement.h"
#include "LinkedList.h"
#include <unordered_map>


template<class KeyType, class ItemType>
class HashedDictionary
{
private:
	HashedDictionaryElement<KeyType, ItemType>* hashTable;
	int itemCount;
	int hashTableSize;
	static const int DEFAULT_SIZE = 31;

public:
	HashedDictionary();
	HashedDictionary(int maxNum);
	~HashedDictionary();
	bool isEmpty() const {return (itemCount == 0);}
	int getNumberOfItems() const {return itemCount;}
	int getTableSize() const {return hashTableSize;}
	int getNumCollisions() const;
	int getNumLinkedLists() const;
	int getNumEmptyElements() const;
	int getLongestIndex(int &biggestCount) const;
	int getHashIndex(const KeyType& key) const;
	bool add(const KeyType& searchKey, const ItemType& newItem);
	bool remove(const KeyType& searchKey); //don't need for this assignment :)
	void clear();
	ListNode<KeyType, ItemType>* getItem(const KeyType& searchKey) const;
	bool contains(const KeyType& searchKey) const;
	void traverse(void visit(ItemType &)) const;
	void traverse(void visit(ItemType&,BinarySearchTree<ItemType> *&), BinarySearchTree<ItemType> *&tree) const;
	void specialTraverse(void visit(ItemType &), void specialVisit(ItemType &, int &), int &index) const;

};


template < class KeyType, class ItemType > bool HashedDictionary < KeyType, ItemType >::remove(const KeyType & searchKey)
{
	int index = getHashIndex(searchKey);
	LinkedList<KeyType, ItemType>* targetList = hashTable[index].getList();
	ListNode<KeyType, ItemType>* targetNode = targetList->findItem(searchKey);
	//targetNode now points at node to be deleted
	targetList->deleteNode(targetNode);
	return true;
}   

template<class KeyType, class ItemType>
HashedDictionary<KeyType, ItemType>::HashedDictionary()
{
	itemCount = 0; 
	hashTableSize = DEFAULT_SIZE;
	hashTable = new HashedDictionaryElement<KeyType, ItemType>[hashTableSize];
}


template<class KeyType, class ItemType>
HashedDictionary<KeyType, ItemType>::HashedDictionary(int maxNum)
{
	itemCount = 0;
	hashTableSize = maxNum;
	hashTable = new HashedDictionaryElement<KeyType, ItemType>[hashTableSize];
}

template<class KeyType, class ItemType>
HashedDictionary<KeyType, ItemType>::~HashedDictionary()
{
	this->clear();
	itemCount = 0;
	hashTableSize = 0;
	hashTable = NULL;
}

template<class KeyType, class ItemType>
int HashedDictionary<KeyType, ItemType>::getNumCollisions() const
{
	int i = 0;
	int collisionCount = 0;


	while(i < hashTableSize)
	{
		if(hashTable[i].getCount() != 0)
			collisionCount += (hashTable[i].getCount()-1);
		++i;
	}
	return collisionCount;
}


template<class KeyType, class ItemType>
int HashedDictionary<KeyType, ItemType>::getNumLinkedLists() const
{
	int i = 0;
	int listCount = 0;
	while(i < hashTableSize)
	{
		if(hashTable[i].getCount() > 1)
			++listCount;
		++i;
	}
	return listCount;
}

template<class KeyType, class ItemType>
int HashedDictionary<KeyType, ItemType>::getNumEmptyElements() const
{
	int i = 0;
	int emptyCount = 0;
	while(i < hashTableSize)
	{
		if(hashTable[i].getCount() == 0)
			++emptyCount;
		++i;
	}
	return emptyCount;
}

template<class KeyType, class ItemType>
int HashedDictionary<KeyType, ItemType>::getLongestIndex(int &biggestCount) const
{
	int i = 0;
	int longestIndex = 0;

	while(i < hashTableSize)
	{
		if(hashTable[i].getCount() > biggestCount)
		{
			longestIndex = i;
			biggestCount = hashTable[i].getCount();
		}
		++i;
	}
	return longestIndex;
}

template<class KeyType, class ItemType>
int HashedDictionary<KeyType, ItemType>::getHashIndex(const KeyType& key) const
{
	std::tr1::unordered_map<KeyType, ItemType> mapper;
	typename std::tr1::unordered_map<KeyType, ItemType>::hasher hashFunction = mapper.hash_function();
	return static_cast<int>(hashFunction(key) % hashTableSize);
}




template <class KeyType, class ItemType>
bool HashedDictionary<KeyType, ItemType>::add(const KeyType& searchKey, const ItemType& newItem)
{
	ListNode<KeyType, ItemType>* addPtr =
		new ListNode<KeyType, ItemType>(searchKey, newItem);

	int itemHashIndex = getHashIndex(searchKey);

	hashTable[itemHashIndex].addEntry(addPtr);
	++itemCount;
	return true;
}

template <class KeyType, class ItemType>
void HashedDictionary<KeyType, ItemType>::clear()
{
	int i = 0;
	while(i < hashTableSize)
	{
		delete hashTable[i].getList();
		hashTable[i].setCount(0);
		++i;
	}
	itemCount = 0;
}

template <class KeyType, class ItemType>
ListNode<KeyType, ItemType>* HashedDictionary<KeyType, ItemType>::getItem(const KeyType& searchKey) const
{
	int i = getHashIndex(searchKey);
	if(hashTable[i].getCount()==0)
		return nullptr;

	ListNode<KeyType, ItemType>* nodePtr = hashTable[i].getList()->findItem(searchKey);
	return nodePtr;
}


template <class KeyType, class ItemType>
bool HashedDictionary<KeyType, ItemType>::contains(const KeyType& searchKey) const
{
	int i = getHashIndex(searchKey);
	if(hashTable[i].getCount() == 0)
		return false;
	else
	{
		if(hashTable[i].getList()->findItem(searchKey))
			return true;
	}
	return false;
}


template <class KeyType, class ItemType>
void HashedDictionary<KeyType, ItemType>::traverse(void visit(ItemType&)) const
{
	int i = 0;
	LinkedList<KeyType, ItemType>* nodePtr;
	while(i < hashTableSize)
	{
		nodePtr = hashTable[i].getList();
		nodePtr->displayList(visit);
		++i;
	}
}

template <class KeyType, class ItemType>
void HashedDictionary<KeyType, ItemType>::traverse(void visit(ItemType&, 
	BinarySearchTree<ItemType> *&), BinarySearchTree<ItemType> *&tree) const
{
	int i = 0;
	LinkedList<KeyType, ItemType>* nodePtr;
	while(i < hashTableSize)
	{
		nodePtr = hashTable[i].getList();
		nodePtr->displayList(visit, tree);
		++i;
	}
}


template <class KeyType, class ItemType>
void HashedDictionary<KeyType, ItemType>::specialTraverse(void visit(ItemType &), void specialVisit(ItemType &, int &), int &index) const
{
	int i = 0;
	LinkedList<KeyType, ItemType>* nodePtr;
	while(i < hashTableSize)
	{
		nodePtr = hashTable[i].getList();
		nodePtr->enhancedDisplay(visit, specialVisit, index);
		++i;
	}
}



#endif
