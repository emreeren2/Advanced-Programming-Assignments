#include<string>
using namespace std;



struct creditCardNode
{ 
	string creditCardNo;
	creditCardNode *next;
};

struct expirationNode
{
	 int month, year;
	 creditCardNode *cHead; 
	 expirationNode *next; 
	 expirationNode *prev; 

	 //default constructor;
	 expirationNode::expirationNode()
		 : month(NULL), year(NULL), cHead(NULL), next(NULL), prev(NULL)
	 {}

	//constructor
	 expirationNode::expirationNode(int m, int y, creditCardNode *ch, expirationNode *n, expirationNode *p)
		 : month(m), year(y), cHead(ch), next(n), prev(p)
	 {}
};


class CardList
{
public:

	CardList(); //default constructor that creates an empty list 

	void addToEnd (int month, int year, string num); // insert new node to the end

	void addToBeg (int month, int year, string num); // insert new node to beginning

	void addToMid (int month, int year, string num); // insert new node to middle

	void displayListChronological ();  //displays entire structure in chronological order 

	void displayListReverseChronological ();  //displays entire structure in reverse chronological order 

	void cardSearch (string creditCardNo);  //displays all of the occurrences of the given card number 

	void bubbleSort(); //this function sort creditcards

	void bulkDelete (int month, int year);  //deletes all nodes up to and including given expiration date 

	void deleteAll (); //deletes the entire structure 

	char define (int m, int y); //determine location (end,beginning,middle) of node that will be added according to month and year

	void defineAdd (int m, int y, string num); //it uses "define" and according to return char, it creat node at the beginning, end or middle.

private:

	expirationNode * head; 

	expirationNode * tail; 
};