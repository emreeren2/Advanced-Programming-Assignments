// This program firstly stores blacklisted credit cards via reading text file.
// Then, it is organized according to their expiration dates.
// After enter the file name successfully from user, program displays what it did when it stores the list
// Then, program shows a menu whic is;  1. Display List
//										2. Card Search
//										3. Delete Cards (with respect to Expiration Date) 
//										4. Exit 

#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<string>

using namespace std;

struct node
{
	int month, year;
	vector<string> cards;
	node *next;

	
	//default constructur
	node::node()
		:  month(NULL), year(NULL), cards(NULL), next(NULL)
	{}

	//constructor
	node::node(int m, int y,string c, node *p) 
			  : month(m), year(y), next(p)
	{
		cards.push_back(c);
		next = NULL;
	}
	
};

char menu() 
{
	char choice;

	cout << "1)Display List" <<endl;
	cout << "2)Card Search via Credit Number" <<endl;
	cout << "3)Delete Card with respect to Expiration Date" <<endl;
	cout << "4)Exit" <<endl;

	cout <<endl;

	cout << "Please choose option from the menu: ";
	cin >> choice;

	return choice;
}

// This function takes 2 pointer as a parameter. First one is pointer that points to be deleted node
// Second one is a pointer that points first node of the linked list. 
void deleteNode (node *toBeDeleted, node *&head) //  (*****inspired by "ptrfunc.cpp"*****) (modified)
{
	node * ptr;
	ptr = head;
		
	while (ptr->next != toBeDeleted){
		ptr = ptr->next;
	}
	ptr->next = toBeDeleted->next;
	
	delete toBeDeleted;
}

// This function deletes whole linked list after user enter '4'. In order to prevent memory leakage.
void DeleteList( node *&head) // this function is taken from "2.2-pointers-linkedlists.ppt" (lectrue slide)
{ 
	if (head != NULL) {
		DeleteList(head->next);
		delete head;
	}
}

// This function controls etered date valid or not. For this purpose dates that will be entered, are taken as string
// If string includes non integer character, it returns false, else it returns true.
bool dateControl(string k)
{
	for(int i = 0; i < k.length(); i++){
		if(k.at(i) < '0' || k.at(i) > '9'){
			return false;
		}
	}
	return true;
}

// This function controls month variable. Firstly this function convert string to integer via stoi().
// If converted month bigger tahn '12' or smaller than '1' it returns false, else it returns true
bool monthControl(string month)
{
	int m = stoi(month);

	if(m < 1 || m > 12){
		return false;
	}
	else{
		return true;
	}
}

// This function takes a pointer and 2 strings as parameters. Pointer points starting node of the linked list,
// and strings are month and year variable. 
// This function controls entered month and year variable exist in linked list. If exist function returns true, else returns false.
bool dateExist(node *h, string month, string year)
{
	node *p = h;
	int m = stoi(month);
	int y = stoi(year); 

	while(p != NULL){
		if(p->month == m && p->year == y){
			return true;
		}
		p = p->next;
	}
	return false;
}

// This function controls entered credir card numbers are valid or not. 
// It takes string as parameter which is 16 digit card number.
bool cardControl(string num)
{
	if(num.length() != 16){
		return false;
	}
	else{
		for(int i = 0; i < num.length(); i++){
			if(num.at(i) < '0' || num.at(i) > '9'){
				return false;
			}
		}
		return true;
	}
}

// This function looks linked list for finding node that includes entered credit card number.
// For this purpose, it takes 2 pointer and a string as a parameters. One pointer points head of the linked list
// and second one is a pointer that points the founded node which includes entered card number.
// Finally string parameter represents card number.
bool lookList(node *head, string num, node *&f)
{
	node *p = head;

	while(p != NULL){
		for (int i = 0; i < p->cards.size(); i++){
			if(p->cards[i] == num){
				f = p;
				return true;
			}
		}
		p = p->next;
	}
	return false;
}

// If user enters 2, this function works.
// This function looks entered card number is valid or not, if valid it looks are there any number that linked list includes
// if linked list has entered card number, function displays entered card number's expiration date. (According to conditions it displays appropriate messages)
void cardSearch(node *h) //case2
{
	node *p = h;
	node *found = NULL;
	string cardNo;
	cout <<endl;

	do{
		cout << "Please enter the credit card number: ";
		cin >> cardNo;

		if(!cardControl(cardNo)){
			cout << "Invalid format!" <<endl;
			
		}
		else{
			if(!lookList(h, cardNo, found)){
				cout << "There is no credit card with given credit card number: "<< cardNo <<endl;
			}
			else{
				cout << "There exists a credit card given number " << cardNo << "with expiration date: " 
					<< found->month << " " << found->year<<endl<<endl;
				found = NULL;
				break;
			}
		}
	}while(!cardControl(cardNo));
}

// If user enters 3, this function works.
// This function looks entered month and year is valid or not, if valid, function looks entered parameters exists in linked list.
// if list has node that includes entered paramteres, firslty card number(s) in that node will be displayed as deleted cards,
// then that node is deleted in linked list.
void deleteCard(node *head) //case3
{
	string month, year;
	int m, y;
	cout <<endl;

	do{
	cout << "Please enter month and year: ";
	cin >> month >> year;

		if(dateControl(month) == false || dateControl(year) == false || monthControl(month) == false){
			cout << "Invalid Date!" <<endl;
		}
		else{

			if(!dateExist(head, month, year)){
				cout << "\nThere is no node with expiration date " << month << " " << year << ", nothing deleted!" <<endl;
			}
			else{
				m = stoi(month);
				y = stoi(year);

				int counter = 1;
				cout << "Node with expiration date " << m << " "<< y << " and the following credit cards have been deleted!"<<endl;

				node *p = head;
				while(p != NULL){	
					if(p->month == m && p->year == y){	
						for(int i = 0; i < p->cards.size(); i++){
							cout <<  counter << ") " <<p->cards[i] <<endl;
							p->cards[i].pop_back();
							counter++;		
						}
						cout<<endl;
						deleteNode(p, head);
						break;
					}
					p = p->next;
				}
			}
		}
	}while(!dateControl(month) || !dateControl(year) || !monthControl(month));
}

// this function is used by "bubbleSort" function in order to swap nodes according to their expiration dates.
void swap(node *a, node *b) 
{ 
    int tempY = a->year; 
    a->year = b->year; 
    b->year = tempY; 

	int tempM = a->month;
	a->month = b->month;
	b->month = tempM;

	vector<string> tempC = a->cards;
	a->cards = b->cards;
	b->cards = tempC;
} 


bool ifexist(node *h, int m, int y) //look if expression day already exists
{	
	node *p = h;

	while(p != NULL){	
		if(p->month == m && p->year == y ){
			return true;
		}
		p = p->next;
	}
	return false;
}

// This function sort linked list according to its expiration dates.
// This function modifies linked list according to its expiration dates. (after linked list enters this function it stays sorted till end of the program)
// Basically this function controls nodes pair by pair and swap them according to their expiration dates
// This function is taken from "https://www.geeksforgeeks.org/bubble-sort-for-linked-list-by-swapping-nodes/" but modified accordingly.
void bubbleSort(node *&head)  // referance koydum
{ 
    int swapped; 
    node *ptr; 
    node *x = NULL; 

    do
    { 
        swapped = 0; 
        ptr = head; 
  
        while (ptr->next != x) 
        { 
            if ( (ptr->year > ptr->next->year) || (ptr->year == ptr->next->year && ptr->month > ptr->next->month) )  
            {  
                swap(ptr, ptr->next); 
                swapped = 1; 
            } 
            ptr = ptr->next; 
        } 
        x = ptr; 
    } 
    while (swapped); 
} 

// If user enters 3, this function works.
// This function displays linked lists as sorted
void displaySorted(node *h)
{
	node *x = h;
	if (x->next == NULL){
		cout << "\nList is empty!" <<endl;
	}
	else{
		while(x != NULL){
			if(x->month != 0 && x->year != 0){ //because my first node is empty node and program should not display it (i assumed that this method is more efficent because computer does not look if node is first or not when it will deleted)
				cout << "\nExpiration Date: " << x->month << " " << x->year << endl;;
		
				int counter = 1;
				for(int i = 0; i < x->cards.size(); i++){
					cout << counter << ") cards:" << x->cards[i] <<endl;
					counter++;
				}
				cout << "-------------------" <<endl;
			}
			x = x->next;
		}
	}
}

int main()
{
	char choice;
	string fileName;
	ifstream input;
	bool control;

	node *head = NULL;
	node *p = NULL;
	node *tail = NULL;
	node *c = NULL; //control

	int month, year;
	string cardNum;

	do{		
		control = true;
		cout << "Please enter filename: ";
		cin >> fileName;

		input.open(fileName);

		if(input.fail()){
			cout << "Cannot find a file named " << fileName <<endl;
			control = false;
		}
	}while(control == false);
	
	string line;
	head = new node();
	p = head;
	tail = head;
	c = NULL;  

	while(!input.eof()){

		getline(input, line);
		stringstream ss(line);

		bool read = ( ss >> cardNum >> month >> year );
		
		if(!read){ // if file cannot be read bool becomes false
			head->month = 0;
			head->year = 0;
		}
		else{

			if(!ifexist(head,month,year)){
				p->month = month;
				p->year = year;
				p->cards.push_back(cardNum);
				cout << "New node is created with expiration date: " << p->month << " " << p->year <<endl;
				cout << "Credit card " << cardNum << " added to node " << p->month << " " << p->year <<endl;
				cout << "***************" <<endl;
	
				c = p; 
				tail = new node();
				p->next = tail;
				p = tail;
			}

			else{
				node *ptr = head;
				while(ptr != NULL){
					if(ptr->month == month && ptr->year == year ){
						ptr->cards.push_back(cardNum);

						cout << "Node with expiration date " <<  ptr->month << " " <<  ptr->year << " already exists "<<endl;
						cout << "Credit card " <<  cardNum << " added to node " << ptr->month << " " << ptr->year <<endl;
						cout << "***************" <<endl;
						break;
					}
					ptr = ptr->next;
				}
				delete tail;
				tail = new node();
				c->next = tail;
				p = tail;
			}
		}
	}
	bubbleSort(head); // eftsoon file is read, linked list becomes sorted.
	
	do{
		cout <<endl;
		choice = menu();

		switch(choice){
			case '1': displaySorted(head);
					break;

			case '2': cardSearch(head); //via card num
					break;

			case '3': deleteCard(head); //via expiration date
					break;
		
			default: cout << "Terminating!!!" <<endl<<endl;
					DeleteList(head);
					return 0;
		}
	}while(choice != '4');
}