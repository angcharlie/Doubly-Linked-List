//Charlie Ang 
//April 11, 2016
//CSC 2431 Spring 2016
//Assignment 1

// Header file for doublyLinkedList, a pointer-based *sorted* by-position doubly list of type
// specified by typedef.

//this typedef defines the type of items in the list (int by default)
typedef int listItemType;

class doublyLinkedList
{
public:
	//CONSTRUCTORS and DESTRUCTOR

	//Default constructor, creates an empty list
	doublyLinkedList();

	//Copy constructor, makes this a copy of list original
	doublyLinkedList(const doublyLinkedList& original);

	//Destructor, free memory for list
	~doublyLinkedList();

	//ACCESSORS

	//Accessor to check if list is empty
	//Parameters: none
	//Returns: true if list is empty, false otherwise (a bool)
	bool isEmpty() const;

	//Accessor to retrieve length of list
	//Parameters: none
	//Returns: length of list (an int)
	int getLength() const;

	//Locate an element in the list.
	//Parameters: the element (key) to locate (listItemType)
	//Returns: the position of the key in the list (an int, -1 if does not exist)
	void locateElement(listItemType key, int& position);
	
	//MUTATORS

	//Mutator to insert element into sorted list.  Automatically inserts at correct position.
	//Parameters: the element to insert into the list (listItemType)
	//Returns: nothing
	void insertElement(listItemType newItem);

	//Mutator to delete element from list by position (starting at 1)
	//Parameters: the position (int) at which to delete 
	//Returns: true if successful, false otherwise (a bool)
	bool deleteElement(int position);

	//Mutator to retrieve an element from list by position (starting at 1)
	//Parameters: the position (int) from which to retrieve an element
	//Returns: true if successful (element is stored in dataItem), false otherwise (a bool)
	bool retrieveElement(int position, listItemType& dataItem) const;

	//Reverse the order of the doubly linked list.
	//Parameters: none
	//Returns: nothing
	void reverse();

	//Prints the list from front to back, one element per line.
	//Parameters: none
	//Returns: nothing
	void printFront();

	//Prints the list from back to front, one element per line.
	//Parameters: none
	//Returns: nothing
	void printBack();


	//OVERLOADED OPERATORS

	//Overloaded equality operator
	//Parameters: the list to compare to this (sortedList)
	//Returns: If lengths match, all elements match (in order), return true
	bool doublyLinkedList::operator== (const doublyLinkedList& right);

	//Overloaded inequality operator
	//Parameters: the list to compare to this (sortedList)
	//Returns: If length mismatch, or all elements do not match (in order), return true
	bool doublyLinkedList::operator!= (const doublyLinkedList& right);



private:
	struct listNode
	{
		listItemType  item;
		listNode     *next;
		listNode	 *back;
	};

	int       size;  // number of items in list

	listNode *head;  // pointer to linked list of items
	listNode *tail;	//pointer to tail of linked list 

	// Private member function that returns a pointer to the position-th node in the linked list.
	// (Private since client should only be able to access by position.)
	listNode *ptrTo(int position) const;

};