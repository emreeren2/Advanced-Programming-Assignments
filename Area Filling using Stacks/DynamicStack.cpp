/*Begin: code taken from DynamicStringStack.cpp */
#include <iostream>
#include "DynamicStack.h"
using namespace std;

//Constructor
DynamicStack::DynamicStack()
{
	top = NULL;
}

StackNode* DynamicStack::GetTopPointer(DynamicStack myStack)
{
	return myStack.top;
}

//Push back elements to the stack
void DynamicStack::push(int R, int C)
{
	StackNode *newNode;

	newNode = new StackNode;
	newNode->row = R;
	newNode->col = C;
	
	if(isEmpty())
	{
		top = newNode;
		newNode->next = NULL;
	}
	else
	{
		newNode->next = top;
		top = newNode;
	}
}
//Pop up elements from the stack
void DynamicStack::pop(int &R, int &C)
{
	StackNode *temp;

	if(isEmpty())
	{
		cout<<"Stack is empty!\n";
	}

	else 
	{
		R = top->row;
		C = top->col;
		temp = top->next;
		delete top;
		top = temp;
	}
}

//If the stack is empty check function
bool DynamicStack::isEmpty()
{
	bool status;

	if(top==NULL)
		status=true;

	else 
		status=false;

	return status;
}
/*End: code taken from DynamicStringStack.cpp */