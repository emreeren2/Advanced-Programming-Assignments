#include <iostream>
#include <string>

#include "LinkedList.h"

using namespace std;


//-----------------------------------------HELPER FUNCTIONS-----------------------------------------//

// it looks if expression day already exists
bool isExist(expirationNode *h, int month, int year)	
{
	expirationNode *ptr = h;
	while (ptr != NULL)
	{
		if (ptr->year == year && ptr->month == month)
		{
			return true;
		}
		ptr = ptr->next;
	}
	return false;
}

// it looks card number is inserted or not at given month and year value.
// it will be used in "defineAdd"
bool isInserted(expirationNode *ptr, string card, int month, int year)
{
	creditCardNode *cp = ptr->cHead;
	expirationNode *p = ptr;
	while (ptr != NULL)
	{
		creditCardNode *cp = ptr->cHead;
		while (cp != NULL)
		{
			if (cp->creditCardNo == card && ptr->month == month && ptr->year == year)
			{
				return true;
			}
			cp = cp->next;
		}
		p = ptr;
		ptr = ptr->next;
	}
	return false;
}

// it compares 16 digit number(string)
// it takes two string that has 16 digit.
// compares these two number character by character.
bool compareCardNum(string s, string k)	//return true -> s is bigger than k
{
	for (int i = 0; i < 16; i++)
	{
		if (s[i] > k[i])
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	return false;
}

// this function is used by "bubbleSort" function in order to swap nodes according to their card number.
void swap(creditCardNode *a, creditCardNode *b) 
{ 
	string temp = a->creditCardNo; 
	a->creditCardNo = b->creditCardNo; 
	b->creditCardNo = temp; 
} 
//----------------------------HELPER FUNCTIONS END---------------------------//

CardList::CardList()
{
	head = NULL;
	tail = NULL;
}

// it creates a node that will be placed at the end of the list
void CardList::addToEnd(int month, int year, string cardNum)
{
	if(!isExist(head, month, year))
	{
		expirationNode *ptr = new expirationNode();
		ptr->month = month;
		ptr->year = year;

		creditCardNode *s = ptr->cHead;
		s = new creditCardNode();
		s->creditCardNo = cardNum;
		s->next = NULL;
		ptr->cHead = s;

		ptr->prev = tail;
		tail->next = ptr;
		tail = ptr;
	}
}

// it creates a node that will be placed at the beginning of the list
void CardList::addToBeg(int month, int year, string cardNum)
{
	//List is empty
	if(head == NULL)
	{
		expirationNode *ptr = new expirationNode();
		ptr->month = month;
		ptr->year = year;
		
		creditCardNode *s = ptr->cHead;
		s = new creditCardNode();
		s->creditCardNo = cardNum;
		s->next = NULL;
		ptr->cHead = s;

		head = ptr;
		tail = head;
	}
	else 
	{
		expirationNode *ptr = new expirationNode();
		ptr->month = month;
		ptr->year = year;

		creditCardNode *s = ptr->cHead;
		s = new creditCardNode();
		s->creditCardNo = cardNum;
		s->next = NULL;
		ptr->cHead = s;

		head->prev = ptr;
		ptr->next = head;
		ptr->prev = NULL;
		head = ptr;
	}
}

// it creates a node that will be placed somewhere between two nodes
void CardList::addToMid(int month, int year, string cardNum)
{
	expirationNode *ptr = head;
	expirationNode *sup = NULL; //support
	creditCardNode *s = ptr->cHead;

	if(!isExist(head,month,year))
	{
		while (ptr != NULL)
		{
			if (ptr->year > year || (ptr->year == year && ptr->month > month))
			{
				ptr = new expirationNode();

				ptr->next = sup->next;
				ptr->prev = sup;
				sup->next = ptr;
				ptr->next->prev = ptr;

				ptr->year = year;
				ptr->month = month;

				creditCardNode *s = ptr->cHead;
				s = new creditCardNode();
				s->creditCardNo = cardNum;
				s->next = NULL;
				ptr->cHead = s;

				break;
			}

			sup = ptr;
			ptr = ptr->next;
		}
	}
}

// this function determines where node should be added
char CardList::define(int m, int y)	
{
	expirationNode *ptr = head;
	
	if (head == NULL)
	{
		return 'b'; // add to beggining
	}

	else if (y < head->year || (y == head->year && m < head->month))
	{
		return 'b'; // add to beggining
	}
	
	else if (tail == NULL)
	{
		return 'e'; // add to end 
	}

	else if (y > tail->year || (y == tail->year && m > tail->month))
	{
		return 'e'; // add to end
	}

	else
	{
		return 'm'; // add to middle
	}
}

// where node should be added is determined upper function "define"
// according to its return value, this function creates a node and add this node to linked list
// with help of the functions addToEnd, addToBeg, addToEnd
void CardList::defineAdd(int m, int y, string num)
{
	if (!isExist(head, m, y)) // if there is no node same as "int m" and "int y" values new node is created.
	{
		cout << num << " " << m << " " << y << ": added to a new expiration date node" <<endl;
		if (define(m,y) == 'b')
		{
			addToBeg(m,y,num);
		}
		else if (define(m,y) == 'm')
		{
			addToMid(m,y,num);
		}
		else if (define(m,y) == 'e')
		{
			addToEnd(m,y,num);
		}
	}
	else // if there exists a node that taken as parameters m and y
	{
		if (isInserted(head, num, m, y)) // if exists a node(expiration) also has same credit card number with "string num" it shows a message according to this circumstance.
		{	
			cout << num << " " << m << " " << y << ": this card was already inserted" <<endl;
		}
		else // if there exists a node(expiration) but there is no same credit card number with "string num", it create node(creditCard) adds "num" to existed node.
		{
			cout << num << " " << m << " " << y << ": inserted to an existing expiration date node"<< endl;
		
			expirationNode *ptr = head;
			creditCardNode *s = NULL;
			creditCardNode *p = s; // support it points back node 

			while (ptr != NULL)
			{
				s = ptr->cHead;
				if (ptr->month == m && ptr->year == y)
				{
					s = new creditCardNode();
					s->creditCardNo = num;
					s->next = ptr->cHead;
					ptr->cHead = s;
				}
				ptr = ptr->next;
			}
		}		
	}
}

// This function sort linked list according to its creditcard number.
// This function modifies linked list according to its credit card numbers. 
// Basically this function controls nodes pair by pair and swap them according to their expiration dates
// This function is taken from "https://www.geeksforgeeks.org/bubble-sort-for-linked-list-by-swapping-nodes/" but modified accordingly.
void CardList::bubbleSort()
{ 
    int swapped; 
	expirationNode *h = head;
	creditCardNode *ptr = h->cHead; 
	creditCardNode *x = NULL; 

	while(h != NULL)
	{
		do
		{ 
			swapped = 0; 
			ptr = h->cHead; 
  
			while (ptr->next != NULL && ptr->next != x) 
			{ 
				if ( compareCardNum(ptr->creditCardNo, ptr->next->creditCardNo))  
				{  
					swap(ptr, ptr->next); 
					swapped = 1; 
				} 
				ptr = ptr->next; 
			} 
			x = ptr; 
		} 
		while (swapped);
		
		h = h->next;
	}
} 

// display list chronological
// it starts from private data head to end of the linked list
void CardList::displayListChronological()
{
	expirationNode * ptr = head;
	creditCardNode * c = NULL;

	cout<<endl;
	if(head == NULL)
	{
		cout << "List is empty!" << endl;
	}
	else
	{
		while(ptr != NULL) // it displays month and year that is in expirationNode
		{	
			cout << "Expiration Date: "<< ptr->month << " " << ptr->year << endl;

			c = ptr->cHead;
			int counter = 1;
			while (c != NULL) // it displays a values that in creditCard node
			{
				cout << counter << ") " << c->creditCardNo <<endl;
				c = c->next;
				counter++;
			}
			cout << "-------------------" <<endl;
			ptr = ptr->next;
		}
	}
}

// display list reverse chronological
// it starts from private data tail to beginning of the linked list
void CardList::displayListReverseChronological()
{
	expirationNode * ptr = tail;
	creditCardNode * c = NULL;

	cout<<endl;
	if(head == NULL)
	{
		cout << "List is empty!" << endl;
	}
	else
	{	
		while(ptr != head->prev) // it displays month and year that is in expirationNode
		{
			cout << "Expiration Date: "<< ptr->month << " " << ptr->year << endl;
			
			c = ptr->cHead;
			int counter = 1;
			while (c != NULL) // it displays a values that in creditCard node
			{
				cout << counter << ") " << c->creditCardNo <<endl;
				c = c->next;
				counter++;
			}
			cout << "-------------------" <<endl;
			ptr = ptr->prev;
		}
	}
}

// searching card according to card number.
// if there exists a entered card, program shows which expirationNodes this card be in
// if there is no entered card in linked lists, program shows message accordingly.
void CardList::cardSearch (string card)
{
	expirationNode *ptr = head;

	cout<<endl;
	int counter = 0;
	while (ptr != NULL)
	{
		creditCardNode *c = ptr->cHead;
		while (c != NULL)
		{
			if (c->creditCardNo == card)
			{
				cout << "There exists a credit card given number " << card << " with expiration date: " << ptr->month << " " << ptr->year <<endl;
				counter++;
			}
			c = c->next;
		}
		ptr = ptr->next;
	}
	if (counter == 0)
	{
		cout << "There is no credit card with given credit card number: " << card <<endl;
	}
}

// this function delete all nodes that before entered month and year values.
void CardList::bulkDelete(int month, int year)
{
	expirationNode *ptr = head;
	expirationNode *de = NULL; // (deleted expirationNode)

	creditCardNode *cH = NULL;
	creditCardNode *dc = cH; // (deleted creditcardNode)

	cout<<endl;
	while (ptr->year < year || (ptr->year == year && ptr->month <= month)) //condition provides to be able to delete all nodes before entered year and month
	{
		cH = ptr->cHead;
		cout << "Node with expiration date "<< ptr->month << " " << ptr->year << " and the following credit cards have been deleted! "<<endl; 
		
		int counter = 1;
		while (cH != NULL) // be able to delete whole creditcard nodes in an expirationNode
		{
			cout << counter << ") " << cH->creditCardNo <<endl; 
			counter++;
			dc = cH;
			cH = dc->next;
			delete dc;
			ptr->cHead = cH;
		}
		de = ptr;
		head = ptr->next;
		ptr = head;
		de->next = NULL;

		if (head != NULL)
		{
			delete de;
		}
		else
		{
			break;
		}
	}

}

// This function deletes whole linked lists after user enter '6'. In order to prevent memory leakage.
void CardList::deleteAll()
{
	expirationNode *ptr = head;
	expirationNode *y = NULL;

	creditCardNode *s = NULL;
	creditCardNode *x = NULL;

	if (head == NULL)
	{
		cout << "All the nodes have been deleted! "
				"\nTerminating!!! "<<endl<<endl;	
	}

	else
	{
		while (ptr != NULL)
		{
			s = ptr->cHead;
			while (s != NULL)
			{
				x = s;
				s = x->next;
				delete x;
				ptr->cHead = s;
			}
			
			y = ptr;
			head = ptr->next;
			y->next = NULL;
			ptr = head;
			
			if (head != NULL)
			{
				delete y;
			}
			else
			{
				break;
			}
		}
		cout << "All the nodes have been deleted! "
				"\nTerminating!!! "<<endl<<endl;	
	}
}
