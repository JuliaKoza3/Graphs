// Graphs.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

using namespace std;

//structure representing a node in the queue
struct Element
{
	int data;
	Element* next;

	Element(int data)
	{
		this->data = data;
		this->next = NULL;
	}
};

class Queue {

	Element* top;
	Element* tail;

public:

	//constructor
	Queue()
	{
		this->top = NULL;
		this->tail = NULL;
	}

	//cheack if queue is empty
	bool isEmpty()
	{
		return top == NULL;
	}

	//delet a node from the top of the queue
	void pop() 
	{
		Element* temp;
		if (top == NULL)
		{
			return;
		}
		else
		{
			temp = top;
			top = top->next;
			delete temp;
			if (top == NULL)
			{
				tail = NULL;
			}
		}
	}

	// return the top node from the queue
	int front()  
	{
		if (!isEmpty())
		{
			return top->data;
		}
		else
		{
			exit(1);
		}
	}

	//add element to the back of the queue
	void push(int data)
	{

		Element* newElement = new Element(data);

		if (isEmpty())
		{
			top = tail = newElement;
		}
		else
		{
			tail->next = newElement;
			tail = newElement;
		}

	}

};




// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
