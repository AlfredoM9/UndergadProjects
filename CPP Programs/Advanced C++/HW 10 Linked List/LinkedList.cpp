#include <iostream>
#include "LinkedList.h"

using namespace std;

/******************************************************************************************
FUNCT: insertNode
DESCR: This will accept a double as a parameter. It will then perform insertion sort and 
	   it will insert the new node in the appropriate place.
*******************************************************************************************/
void LinkedList::insertNode(double num)
{
	LinkedNode *newNode;
	LinkedNode *nodePtr;
	LinkedNode *previousNode = nullptr;

	// Create a new node and initialize it
	newNode = new LinkedNode;
	newNode->value = num;

	// If the head is pointing to null
	if (!head)
	{
		// Make it point to the new node
		head = newNode;

		// Make the node point to null
		newNode->next = nullptr;
	} // end if

	else
	{
		// Initialize the pointer with what the pointer is pointing at
		nodePtr = head;

		// Initialize the previous node
		previousNode = nullptr;

		// while the nodeptr doesn't point to null and it is less than the num
		while (nodePtr != nullptr && nodePtr->value < num)
		{
			// Then move to the next node
			previousNode = nodePtr;
			nodePtr = nodePtr->next;
		} // end while

		// If the previous node points to null then it didn't move
		if (previousNode == nullptr)
		{
			// Initialize the head to the new node
			head = newNode;

			// Make it point to what the head of pointing at first
			newNode->next = nodePtr;
		} // end if

		// Otherwise
		else
		{
			// Make the previous node point to the new node
			previousNode->next = newNode;

			// Make the new node point to the node in front of it
			newNode->next = nodePtr;
		} // end else
	} // end outer else
} // end insertNode

/**************************************************************
FUNCT: displayList
DESCR: It will go through the list and display the entire list
****************************************************************/
void LinkedList::displayList() const
{
	// Temporary pointer
	LinkedNode *nodePtr;

	nodePtr = head;

	// While it doesn't point to null
	while (nodePtr)
	{
		// Display node and continue
		cout << nodePtr->value << endl;
		nodePtr = nodePtr->next;
	} // end while
} // end displayList

/**********************************************************************
FUNCT: destroyList
DESCR: This function will go through each node and delete its content
***********************************************************************/
void LinkedList::destroyList() const
{
	// Temporary pointers
	LinkedNode *nodePtr;
	LinkedNode *nextNode;

	nodePtr = head;

	// While the pointer doesn't point to null
	while (nodePtr != nullptr)
	{
		// Make sure to get the connection to the other node before deleteing
		nextNode = nodePtr->next;

		// Then delete
		delete nodePtr;

		// Then get the node that continues
		nodePtr = nextNode;
	} // end while
} // end destroy list