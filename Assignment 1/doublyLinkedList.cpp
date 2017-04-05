//Charlie Ang 
//April 11, 2016
//CSC 2431 Spring 2016
//Assignment 1

// Implementation file for doublyLinkedList.h, a pointer-based by-position doubly list of type
// specified in header.

#include "doublyLinkedList.h"     // header file
#include <iostream>
#include <cstddef>		// for NULL
#include <cassert>     // for assert()

using namespace std;

//Default constructor, creates an empty list
doublyLinkedList::doublyLinkedList()	// Default Constructor
: size(0), head(NULL)
{
}

//Destructor, free memory for list
doublyLinkedList::~doublyLinkedList()	// Destructor
{
	bool success;

	while (!isEmpty())
	{
	success = deleteElement(1);  // Repeatedly delete item 1
	}
}


//Accessor to check if list is empty
//Parameters: none
//Returns: true if list is empty, false otherwise (a bool)
bool doublyLinkedList::isEmpty() const
{
	return (size == 0);
}


//Accessor to retrieve length of list
//Parameters: none
//Returns: length of list (an int)
int doublyLinkedList::getLength() const
{
	return size;
}


//Copy constructor, makes this a copy of list original
doublyLinkedList::doublyLinkedList(const doublyLinkedList& original)
: size(original.size)
{
	if (original.head == NULL)
		head = NULL;  // original list is empty

	else
	{
		// copy first node
		head = new listNode;
		assert(head != NULL);  // check allocation

		head->item = original.head->item;

		// copy rest of list
		listNode *newPtr = head;  // new list pointer
		newPtr->next = NULL;
		newPtr->back = NULL;

		// newPtr points to last node in new list 
		// origPtr points to nodes in original list
		for (listNode *origPtr = original.head->next; origPtr != NULL; origPtr = origPtr->next)
		{
			newPtr->next = new listNode;
			newPtr->next->back = newPtr;
			assert(newPtr->next != NULL);

			newPtr = newPtr->next;	//traverse 

			newPtr->item = origPtr->item;	//copy item over 
		}
		tail = newPtr;	//tail at very end of list
		newPtr->next = NULL;	//null at end 
	}
}


// Locates a specified node in a linked list
// Parameters: the number of the desired node (starting at 1, an int)
// Returns: Returns a pointer to the desired node, or NULL if position out of range.
doublyLinkedList::listNode *doublyLinkedList::ptrTo(int position) const
{
	if ((position < 1) || (position > getLength()))
		return NULL;

	else  // count from the beginning of the list
	{
		listNode *cur = head;

		for (int skip = 1; skip < position; ++skip)
			cur = cur->next;

		return cur;
	}
}


//Mutator to retrieve an element from list by position (starting at 1)
//Parameters: the position (int) from which to retrieve an element
//Returns: true if successful (element is stored in dataItem), false otherwise (a bool)
bool doublyLinkedList::retrieveElement(int position, listItemType& dataItem) const
{
	bool success = ((position >= 1) && (position <= getLength()));

	if (success)
	{
		// get pointer to node, then data in node
		listNode *cur = ptrTo(position);

		dataItem = cur->item;
	}
	return success;
}



//Mutator to insert element into sorted list.  Automatically inserts at correct position.
//Parameters: the element to insert into the list (listItemType)
//Returns: nothing
void doublyLinkedList::insertElement(listItemType newItem)
{
	listNode *prev = NULL;
	listNode *cur = head;

	while ((cur != NULL) && (newItem > cur->item))
	{
		prev = cur;
		cur = cur->next;
	}

	listNode *newPtr = new listNode;
	newPtr->item = newItem;
	newPtr->next = NULL;
	newPtr->back = NULL;

	if (isEmpty())
	{
		tail = newPtr; //list is empty then tail is equal to head 
	}
		
	if ((prev == NULL))	//inserting at beginning
	{
		newPtr->next = cur;
		if (cur != NULL)
		{
			cur->back = newPtr; 
		}
		head = newPtr;
	}
	else
	{
		if (cur != NULL)	//inserting in middle 
		{
			newPtr->next = cur;
			cur->back = newPtr;
			prev->next = newPtr;
			newPtr->back = prev;
		}
		else //inserting at end 
		{
			newPtr->next = cur;	//cur is null since at end of list
			prev->next = newPtr;
			newPtr->back = prev;
			tail = newPtr;
		}	
	}
	size++;
}


//Locate an element in the list.
//Parameters: the element (key) to locate (listItemType)
//Returns: the position of the key in the list (an int, -1 if does not exist)
void doublyLinkedList::locateElement(listItemType key, int& position)
{
	listNode *cur = head;
	
	position = 1;

	while (cur != NULL && cur->item != key)
	{
		cur = cur->next;
		position++;
	}

	if (cur == NULL)
		position = -1;
}

//Mutator to delete element from list by position (starting at 1)
//Parameters: the position (int) at which to delete 
//Returns: true if successful, false otherwise (a bool)
bool doublyLinkedList::deleteElement(int position)
{
	listNode *cur;

	bool success = ((position >= 1) && (position <= getLength()));

	if (success)
	{
		--size;

		if (position == 1)	//delete from beginning
		{
			// delete the first node from the list
			cur = head;  // save pointer to node
			head = head->next;
			if (head != NULL)
			{
				head->back = NULL;
			}
			else
			{
				tail = NULL;
			}
		}

		else
		{
			listNode *prev = ptrTo(position - 1);

			// delete the node after the node 
			//    to which Prev points

			cur = prev->next;  // save pointer to node
			prev->next = cur->next;
			if (cur->next != NULL)
			{
				cur->next->back = prev;
			}

			if (cur == tail)
			{
				tail = prev; //move tail back
			}
		}

		// return node to system
		cur->next = NULL;
		delete cur;
		cur = NULL;
	}
	return success;
}


//Overloaded equality operator
//Parameters: the list to compare to this (sortedList)
//Returns: If lengths match, all elements match (in order), return true
bool doublyLinkedList::operator== (const doublyLinkedList& right)
{
	//shortcut in case comparing same two sortedLists
	if (&right == this)
		return true;

	//check sizes are the same
	if (getLength() != right.getLength())
		return false;

	//temporary variables for comparison
	listItemType mine;
	listItemType theirs;

	//compare each element
	for (int i = 1; i <= getLength(); i++)
	{
		//use public methods to get each element
		retrieveElement(i, mine);
		right.retrieveElement(i, theirs);

		//return false after any mismatch
		if (mine != theirs)
			return false;
	}

	//if code gets here, all elements must be the same
	return true;
}


//Overloaded inequality operator
//Parameters: the list to compare to this (sortedList)
//Returns: If length mismatch, or all elements do not match (in order), return true
bool doublyLinkedList::operator!= (const doublyLinkedList& right)
{
	return !(*this == right);

}

//Reverse the order of the doubly linked list.
//Parameters: none
//Returns: nothing
void doublyLinkedList::reverse()
{
	listNode *front = head;

	doublyLinkedList copy(*this);	//create copy of list
	listNode *end = copy.ptrTo(getLength());	//points to end (tail) of copy list

	while (front != NULL)
	{
		front->item = end->item;

		front = front->next;	//move forward along list
		end = end->back;	//move backward along list
	}
}


//Prints the list from front to back, one element per line.
//Parameters: none
//Returns: nothing
void doublyLinkedList::printFront()
{
	listNode *cur;
	cur = head;	//cur points to head of list
	while (cur != NULL)
	{
		cout << cur->item << endl;
		cur = cur->next;
	}
}


//Prints the list from back to front, one element per line.
//Parameters: none
//Returns: nothing
void doublyLinkedList::printBack()
{
	listNode *cur;
	cur = tail;
	while (cur != NULL)
	{
		cout << cur->item << endl;
		cur = cur->back;
	}
}
