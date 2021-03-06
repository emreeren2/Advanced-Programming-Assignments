#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include"LinkedList.h"

using namespace std;

// display menu and get choice from user
int menu() 
{
	int choice;

	cout << "1) Upload Card(s) from a File" <<endl;
	cout << "2) Display List Chronological" <<endl;
	cout << "3) Display List Reverse Chronological" <<endl;
	cout << "4) Card Search" <<endl;
	cout << "5) Bulk Delete " <<endl;
	cout << "6) Exit" <<endl;

	cout << "Please choose option from the menu: ";
	cin >> choice;

	return choice;
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


int main()
{
	CardList expirationNode;

	int choice;
	ifstream input;
	string line;
	string fileName;
	string cardNum, card;
	string m, y;
	int month, year, M, Y;

	bool control = true;
	bool control2 = true;

	do{
		cout <<endl;
		choice = menu();

		switch(choice)
		{
			case 1: //if user press 1 (uploading cards)

				cout << "Please enter filename: ";
				cin >> fileName;

				input.open(fileName);

				if(input.fail()){
					cout << "Cannot find a file named " << fileName <<endl;
					break;
				}

				cout<<endl;
				while (getline(input,line))
				{

					istringstream ss(line);

					ss >> cardNum >> month >> year;

					expirationNode.defineAdd(month,year,cardNum);
				}
				input.close();
				input.clear();
				input.seekg(0);

				expirationNode.bubbleSort();
				break;

			case 2: expirationNode.displayListChronological();  //if user press 2 (display choronological)
					break;

			case 3: expirationNode.displayListReverseChronological(); //if user press 3 (display reverse choronological)
					break;

			case 4:  //if user press 4 (card search)
				cout << "Please enter the credit card number:";
				cin >> card;
				if (!cardControl(card))
				{
					cout << "Invalid format!" <<endl;
				}
				else
				{
					expirationNode.cardSearch(card);
				}
					break;

			case 5: //if user press 5 (bulk delte)
				cout << "Please enter month and year: ";
				cin >> m >> y;
				if (!dateControl(m) || !dateControl(y) || !monthControl(m))
				{
					cout << "Invalid format!"<<endl;
				}
				else
				{
					M = stoi(m);
					Y = stoi(y);
					expirationNode.bulkDelete(M, Y);
				}
					break;

			case 6:	expirationNode.deleteAll(); //if user press 6 (exit)
					break;

			default: cout << "Invalid operation! " <<endl; //if user press integer that is not between 1-6
		}
	}while(choice != 6);
	return 0;
}