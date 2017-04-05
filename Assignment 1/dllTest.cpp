//Charlie Ang 
//April 11, 2016
//CSC 2431 Spring 2016
//Assignment 1

#include <iostream>
using namespace std;

#include "doublyLinkedList.h"

//prototypes
void print(doublyLinkedList list);


int main()
{
	doublyLinkedList first;

	//create a list with 6 elements for testing
	first.insertElement(20);
	first.insertElement(10);
	first.insertElement(30);
	first.insertElement(40);
	first.insertElement(25);
	first.insertElement(5);
	
	int pos;
	
	first.locateElement(30, pos);	//5

	first.deleteElement(pos);	//deletes element 30 --> 5 10 20 25 40 

	cout << "first, printed with client print:  " << endl;
	print(first);	//5 10 20 25 40 

	//create a copy of 5-element list
	doublyLinkedList second(first);	//second = 5 10 20 25 40 

	//test all 3 cases for delete
	second.deleteElement(1);	//10 20 25 40	
	second.deleteElement(4);	//10 20 25
	second.deleteElement(2);	//10 25

	cout << "\nsecond, printed with client print:  " << endl;
	print(second);	//10 25

	//test copy constructor
	doublyLinkedList third(first);	//5 10 20 25 40 

	//test == and !=
	cout << boolalpha;
	cout << "\ntesting == " << endl;
	cout << (first == first) << endl;	//true
	cout << (first == second) << endl;	//false	
	cout << (first == third) << endl;	//true 

	cout << "\ntesting != " << endl;
	cout << (first != first) << endl;	//false
	cout << (first != second) << endl;	//true
	cout << (first != third) << endl;	//false

	//test print functions
	cout << "\ntesting printFront on first: " << endl;
	first.printFront();	//5 10 20 25 40
	
	cout << "\ntesting printBack on first: " << endl;
	first.printBack();	//40 25 20 10 5


	//test reverse
	first.reverse();

	cout << "\ntesting printFront on first after reverse: " << endl;
	first.printFront();	//40 25 20 10 5

	cout << "\ntesting printBack on first after reverse: " << endl;
	first.printBack(); //5 10 20 25 40 


	return 0;
}


//Client function to print a list of listItemType
//Parameters: the list to print (posList)
//Returns: nothing
void print(doublyLinkedList list)
{
	for (int i = 1; i <= list.getLength(); i++)
	{
		listItemType x;
		list.retrieveElement(i, x);
		cout << x << endl;
	}
}

