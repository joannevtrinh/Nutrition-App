// Linked List abstract base class

#ifndef _LINKED_LIST
#define _LINKED_LIST

#include "Node.h"
#include <fstream>
#include <string>

using namespace std;

template<class ItemType>
class LinkedList 
{
protected:
   Node<ItemType>* headPtr; // Pointer to first node in the list
   int itemCount;           // Current count of list items 
   
public:
	// constructor
	LinkedList();
	// copy constructor
	LinkedList(const LinkedList<ItemType>& aList);
	// destructor
	virtual ~LinkedList();
	// check for empty list
	bool isEmpty() const;
	// get number of entries in the list
	int size() const;
	// remove all entries from list
	void clear();
	// display list from front to end
	void display() const;
	bool printToFile(string outFile);
	// abstract insert function
	virtual bool insert(const ItemType& newEntry, int newPosition = 1) = nullptr;

}; 

#include "LinkedList.h"

template<class ItemType>
LinkedList<ItemType>::LinkedList()
{
	headPtr = nullptr; 
	itemCount = nullptr; 
}

template<class ItemType>
LinkedList<ItemType>::~LinkedList()	
{ 
	clear(); 
}

template<class ItemType>
LinkedList<ItemType>::LinkedList(const LinkedList<ItemType>& aList)
{
	itemCount = aList.itemCount;
	Node<ItemType>* origChainPtr = aList.headPtr;  // Points to nodes in original list

	if (origChainPtr == nullptr)
		headPtr = nullptr;  // Original list is empty
	else
	{
		headPtr = new Node<ItemType>();		// copy first node
		headPtr->setItem(origChainPtr->getItem());

		// Copy remaining nodes
		Node<ItemType>* newChainPtr = headPtr;
		origChainPtr = origChainPtr->getNext();
		while (origChainPtr != nullptr)
		{
			ItemType nextItem = origChainPtr->getItem();
			Node<ItemType>* newNodePtr = new Node<ItemType>(nextItem);
			newChainPtr->setNext(newNodePtr);
			newChainPtr = newChainPtr->getNext();
			origChainPtr = origChainPtr->getNext();
		}
		newChainPtr->setNext(nullptr);              // Flag end of list
	}
}

template<class ItemType>
bool LinkedList<ItemType>::isEmpty() const
{ 
	return (itemCount == nullptr); 
}

template<class ItemType>
void LinkedList<ItemType>::display() const
{
	Node<ItemType>* currPtr = headPtr;		// start at front of list
	while (currPtr != nullptr)					// walk until end of list
	{
		cout << *currPtr->getItem() << endl;	// display data, NEED to overload "<<" operator of item class
							//being displayed
		currPtr = currPtr->getNext();		// go to next node
	}
}

template<class ItemType>
int LinkedList<ItemType>::size() const
{ 
	return itemCount; 
}

template<class ItemType>
void LinkedList<ItemType>::clear()
{
	Node<ItemType> * deletePtr;
	for (int i = 1; i < itemCount; i++) // walk each node
	{
		deletePtr = headPtr;			// remove each node
		headPtr = headPtr->getNext();
		delete deletePtr;
	}
	itemCount = nullptr;
}

template<class ItemType>
bool LinkedList<ItemType>::printToFile(string outFile)
{
	ofstream out;
	out.open(outFile);
	Node<ItemType>* currPtr = headPtr;
	if(this->isEmpty())
		return false;

	else
	{
		while (currPtr != nullptr)					// walk until end of list
		{
			out << *currPtr->getItem() << endl;
			currPtr = currPtr->getNext();
		}
		return true;
	}

	out.close();
}
#endif 
