#pragma once

class LinkedList
{
private:
	// Struct for the node
	struct LinkedNode
	{
		double value;
		struct LinkedNode *next;
	};

	// The head node
	LinkedNode *head;

public:

	// Constructor
	LinkedList()
	{ 
		head = nullptr;
	}

	// Functions
	void insertNode(double);
	void displayList() const;
	void destroyList() const;
};
