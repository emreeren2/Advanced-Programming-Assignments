#ifndef _EMREEREN_EREN_EMRE_HW5_H
#define _EMREEREN_EREN_EMRE_HW5_H

#include<iostream>
using namespace std;

class IntegerSet
{
private:
	int *array;
	int size;

public:
	IntegerSet(); // creates an integer set object with number of elements = 0. 
	IntegerSet(int); // creates an integer set object and allocates enough memory (according to given parameter) 
	~IntegerSet(); // destructer
	IntegerSet(const IntegerSet &); // copy constructor

	IntegerSet& operator +(int elmt); // + operator for adding element
	IntegerSet operator *(const IntegerSet &); // * operator									
	const IntegerSet& operator =(const IntegerSet &); // = operator						
	const IntegerSet& operator +=(const IntegerSet &); // += operator								

	void setElement(int, int); // set element in specified index
	int  getElement(int); // get element in specified index
	void setSize(int); // set size of the vector
	int  getSize(); // get size of the vector
};

ostream& operator <<  ( ostream & os, IntegerSet set); 
bool operator !=      ( IntegerSet& lhs,  IntegerSet& rhs); // != operator
bool operator <=      ( const int &elmt, IntegerSet& lhs ); // check single integer element on the left hand side 
bool operator <=      ( IntegerSet&, IntegerSet&); // check lhs is subset of rhs
IntegerSet operator + ( const IntegerSet& rhs, const IntegerSet& lhs); // + operator for merge two set
//IntegerSet operator +=( IntegerSet& rhs, const IntegerSet& lhs);

#endif