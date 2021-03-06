#include"emreeren_eren_emre_hw5.h"
#include<iostream>
#include<vector>

using namespace std;

// this function controls is added element already exists in original array
bool existBefore(int* set, int element)
{
	int size =  sizeof(set);

	for(int i = 0; i < size; i++){
		int x = set[i];

		if(x == element){
			return true;
		}
	}
	return false;

}

IntegerSet::IntegerSet() //constructor // taken and modified from Mathvector.cpp
{
	array = 0;
	size = 0;
}

IntegerSet::IntegerSet(int arraySize) // constructor with vector size 
{
	array = new int[arraySize];

	for(int i = 0 ; i < arraySize; i++){
		array[i] = i;
	}
	size = arraySize;
}

IntegerSet::~IntegerSet() // destructor // taken and modified from Mathvector.cpp
{
	size = 0;
	delete[] array;
}

IntegerSet::IntegerSet(const IntegerSet & copy) // copy constructor - deep copy // taken and modified from Mathvector.cpp
{
	size = copy.size;
	array = new int[size];

	for(int i = 0; i < size; i++){
		array[i] = copy.array[i];
	}
}

 IntegerSet& IntegerSet::operator+(int element)
 {
	int *temp = array; // pointer temp points to array
	bool control = false;

	if(size == 0){
		array = new int[++size];
		array[size-1] = element;
		control = true;
	}

	else if(!existBefore(array, element)){
		array = new int[++size];
		array[size-1] = element;
		control = true;
	}

	for(int i = 0; i < size-1; i++){
		array[i] = temp[i]; // assign other elements different than our latest added element
	}

	if(control){
		delete []temp;
	}
	return *this;
 }

IntegerSet IntegerSet::operator*(const IntegerSet &rhs) // intersection of two integer set 
{
	int sizer = 0;
	int i = 0; 
	while(i < rhs.size){
		int counter = 0;
		for(int j = 0; j < size; j ++){
			if(array[j] == rhs.array[i]){ // cotrolling are there any common element that is included by lhs and rhs
				counter++;  // if there is common element count is incremented by 1
			}
		}
		if(counter == 1){ // if common element exist 
			sizer++;
		}
		i++;
	}

	IntegerSet result(sizer); // creating integer set according to sizer	

	int k = 0;
	for(int i = 0; i < size; i++){
		for(int j = 0; j < rhs.size; j++){
			if(array[i] == rhs.array[j]){ // assign common elements into result
				result.array[k] = array[i];
				k++;
			}
		}
	}
	return result;
}

const IntegerSet& IntegerSet::operator=(const IntegerSet & rhs) // taken from MathVector.cpp and modified.
{
	IntegerSet newSet;
	if (this != &rhs) // if they are not already equal
	{
		// first delete left hand side
		size = 0;
		//array = 0;
		delete[] array;

		// create new array for left hand side
		size = rhs.size;
		array = new int[size];

		for(int i = 0; i < size; i++)
		{
			array[i] = rhs.array[i]; // assign content
		}
	}
	return *this;
}

const IntegerSet& IntegerSet::operator+=(const IntegerSet &rhs) // union of tho sets
{
	int *arr = array; // pointer arr points to array
	int i = 0; 
	while(i < rhs.size){
		int counter = 0;
		for(int j = 0; j < size; j ++){
			if(array[j] == rhs.array[i]){ // cotrolling are there any common element that is included by lhs and rhs
				counter++;  // if there is common element count is incremented by 1
			}
		}
		if(counter == 0){ // if common element does not exist 
			array = new int[++size]; // creating new array that size is bigger than before by 1
			array[size-1] = rhs.array[i]; // assign last element as i'th elemnt of rhs
		}
		i++;
		int x = size;
		for(int k = 0; k < size-1; k++){ // putting other elemnts rather than last element.
			array[k] = arr[k];
		}
		arr = array; // updating arr. now it points modified array. ----> to be able to use arr in other iterations
	}
	return *this;
}

// set element in the specified index
void IntegerSet::setElement(int index, int element) // taken from MathVector.cpp and modified
{
	array[index] = element;
}

// set size of the vector
void IntegerSet::setSize(int psize) // taken from MathVector.cpp and modified
{
	size = psize;
	array = new int[size];
}

// get size of the vector
int IntegerSet::getSize() // taken from MathVector.cpp and modified
{
	return size;
}

// get element in the specified index
int IntegerSet::getElement(int index) // taken from MathVector.cpp and modified
{
	return array[index];
}

//********************************************************************************************//
//////////////////////////////----------FREE_FUNCTIONS----------////////////////////////////////

ostream& operator << (ostream& out, IntegerSet set)
{
	int size = set.getSize();

	if(size == 0){
		cout << "{}";
	}
	else{
		cout << "{";
		for(int i = 0; i < size-1; i++){
			out << set.getElement(i) << ", ";
		}
		out << set.getElement(size-1) << "}";
	}
	return out;
}


bool operator != ( IntegerSet& lhs,  IntegerSet& rhs)
{
	int x = lhs.getSize();
	int y = rhs.getSize();
	int counter = 0;

	if(x != y){ // if sizes are not same, they cannot be equal
		return true;
	}
	else{
		for(int i = 0; i < x; i++){
			for(int j = 0; j < y; j++){
				if(lhs.getElement(i) == rhs.getElement(j)){ //lhs[i] == rhs[j]   // if lhs element is equal to rhs element
					counter++;													// counter is incremented by 1
				}
			}
			if(counter != 1){ // counter be 1 if and only if both sets include same element only 1 time 
				return true;  // therefor if counter is not 1 this means that one set includes an element that other set does not include. --> which means sets are not equal
			}
			counter = 0; // reset counter and make comparison with each elements 
		}
		return false; 
	}
}

bool operator <= (const int & element,IntegerSet& lhs) // check there exists single integer element on the left hand side 
{
	for(int i = 0; i < lhs.getSize(); i++){
		if(lhs.getElement(i) == element){
			return true;
		}
	}
	return false;
}

bool operator <=(IntegerSet &lhs, IntegerSet &rhs)
{
	if(rhs.getSize() < lhs.getSize()){ // if set A is subset of set B, firsly B must be bigger than A or equal to A
		return false;				   // so this condistion is not satisfied, function should return false
	}
	else{							   // otherwise, if rhs includes at least each elemnts of lhs, this means that lhs is subset of rhs
		for(int i = 0; i < lhs.getSize(); i++){  
			if(!(lhs.getElement(i) <= rhs)){     // in this part we compare each elements of lhs with rhs (with <= operator that provided above)
				return false;					
			}									 
		}
	}
	return true;
}


IntegerSet operator + (const IntegerSet& lhs, const IntegerSet& rhs)
{
	IntegerSet RHS(rhs);
	int size_rhs = RHS.getSize();

	IntegerSet LHS(lhs);
	int size_lhs = LHS.getSize();

	IntegerSet result(lhs);
	int size = result.getSize();

	IntegerSet arr(lhs);

	int i = 0; 
	while(i < size_rhs){
		int counter = 0;
		for(int j = 0; j < size_lhs; j ++){
			if(LHS.getElement(j) == RHS.getElement(i)){ // cotrolling are there any common element that is included by lhs and rhs
				counter++; // if there is common element count is incremented by 1
			}
		}

		if(counter == 0){ // if common element does not exist 
			result.setSize(++size); // result's size incremented by 1
			result.setElement(size-1, RHS.getElement(i)); // setting last element as i'th element of RHS
		}
		i++; 

		for(int k = 0; k < size-1; k++){
			result.setElement(k, arr.getElement(k)); // putting other elemnts rather than last element.
		}

		arr.setSize(size);
		for(int k = 0; k < size; k++){ // updating arr as equavilent of modified result. ----> to be able to use arr in other iterations
			arr.setElement(k, result.getElement(k));
		}
	}
	return result;
}

//IntegerSet operator += (IntegerSet& lhs, const IntegerSet& rhs)
//{
//	IntegerSet RHS(rhs);
//	int size_rhs = RHS.getSize();
//
//	IntegerSet LHS(lhs);
//	int size_lhs = LHS.getSize();
//
//	IntegerSet result(lhs);
//	int size = result.getSize();
//
//	IntegerSet arr(lhs);
//
//	int i = 0; 
//	while(i < size_rhs){
//		int counter = 0;
//		for(int j = 0; j < size_lhs; j ++){
//			if(LHS.getElement(j) == RHS.getElement(i)){ // cotrolling are there any common element that is included by lhs and rhs
//				counter++; // if there is common element count is incremented by 1
//			}
//		}
//
//		if(counter == 0){ // if common element does not exist 
//			result.setSize(++size); // result's size incremented by 1
//			result.setElement(size-1, RHS.getElement(i)); // setting last element as i'th element of RHS
//		}
//		i++; 
//
//		for(int k = 0; k < size-1; k++){
//			result.setElement(k, arr.getElement(k)); // putting other elemnts rather than last element.
//		}
//
//		arr.setSize(size);
//		for(int k = 0; k < size; k++){ // updating arr as equavilent of modified result. ----> to be able to use arr in other iterations
//			arr.setElement(k, result.getElement(k));
//		}
//	}
//
//	//lhs = result;
//	return result;
//}
