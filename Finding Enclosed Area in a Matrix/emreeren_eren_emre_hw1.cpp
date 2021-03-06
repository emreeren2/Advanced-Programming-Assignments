/*
	-This program find an enclosed area in 2D matrix that contains 'x's and 'o's
	-Firstly, user should enter a file name, if entered file name does not found, program gets input untill file founds
	-Then, program gets start coordinates from user, if user enters invalid coordinates, program gets input untill it is valid or -1 -1
	-Program automatically finds a path according to start coordinates. (path consists of only 'x's)
	-Then, program displays a message according to founded path creats enclosed area or not.
	-Finally user should enter -1 -1 when, program asks starting coordinates, to finish the program.
*/
#include<iostream>
#include<string>
#include<sstream>
#include<fstream>
#include<vector>
#include <iomanip> // for setw()
#include"strutils.h" // for atoi()

using namespace std;

//it is a vector for store x and y coordinate
struct coordinates
{
	int x;
	int y;
};

// this function inserts x and y coordinates in the vector
void insertCor(vector<coordinates> & vec, int x, int y)
{
	coordinates c;
	c.x = x;
	c.y = y;
	vec.push_back(c);
}

// this function prints matrix that was read from the txt files
void printMatrix(const vector<vector<char>> & mat)
{
	cout << "Input Matrix:"<<endl; 
    for (int j = 0; j < mat.size(); j++)
    {   
		for (int k = 0; k < mat[0].size(); k++)
        {   
			cout << setw(4) << mat[j][k];
        }
        cout << endl;
    }
	cout <<endl;
}

// this function controls character that in the files (character by character)
// if is valid (character is 'o' or 'x') return true
// else (cahracter is not 'o' or 'x') return false
bool charControl(vector<vector<char>> mat)
{
	bool control = true;
	for(int x = 0; x < mat.size(); x++){
		for(int y = 0; y < mat[0].size(); y++){
					
			if(mat[x][y] != 'x' && mat[x][y] != 'o' ){
				control = false;
			}
		}
	}
	if(!control)
		return false;	
	else 
		return true;
}

// for example vec1 is the first row in the matrix and vec2 is second row in the matrix (it explained better in the main where this function is called)
// this function controls matrix size
// if sizes are sane function returns true
// else it returns false
// in our case, vec1 is temp and vec2 is mat[counter] --> these can be understood in main. (mat[n] is vector that 'n(th)' row)
bool amountControl(vector<char> vec1, vector<char> vec2)
{
	if(vec1.size() != vec2.size())
		return false;
	else
		return true;
}

// this function controls coordinate inputs are valid or not
// for this purpose those inputs were maden string.
bool coordinateControl(const vector<vector<char>> mat, string a, string b)
{
	int row = mat[0].size()-1;
	int col = mat.size()-1;
	int x = atoi(a); // transfer string to integer. if it cannot convert string to integer, it returns 0
	int y = atoi(b);
	bool control = true;

	for(int i = 0; i < a.length(); i++){ // control string character by character
		if(a[i] < '0' ||  a[i] > '9' || x > col || y > row || x <= -1 || y <= -1 ){ // if character is not between '0' and '9' it returns false. if converted string is less or equal to -1 and bigger than matrix size it also returns false
			control = false;														// meaning of -1 --> 1)coordinate input can be -1 (for terminating) 2)if string cannot be converted integer, atoi returns 0
		}
	}

	for(int j = 0; j < b.length(); j++){
		if(b[j] < '0' ||  b[j] > '9' || x > col || y > row || x <= -1 || y <= -1 ){ 
			control = false;
		}
	}

	if(!control)
		return false;
	else
		return true;
}

// this function found x coordinates according to rule
// if x is founded, that coordinates inserted vector that is created before (struct coordinates)
void Path(int x, int y, vector<vector<char>> mat, vector<coordinates> & list, bool & k)
{
	if(mat[x][y] == 'x'){
		
		mat[x][y] = 'k'; // cell should be changed to other character because if it is not changed infinite loop occurs. for example assume there are square enclosed area,
						//  if we in the corner(down left) of the squared enclosed area it should be look upper cell but if cell is not changed to another character program looks right of the cell instead of upper of the cell.
		insertCor(list, x, y);
		
		if( y+1 < mat[0].size() && mat[x][y+1] == 'x'){
			Path(x,y+1,mat, list, k);	
		}
		else if(x+1 < mat.size() && mat[x+1][y] == 'x' ){
			Path(x+1,y,mat,list, k);	
		}
		else if(y-1 >= 0 && mat[x][y-1] == 'x' ){
			Path(x,y-1,mat,list, k);	
		}
		else if( x-1 >= 0 && mat[x-1][y] == 'x'){
			Path(x-1,y,mat,list, k);
		}
	}
	else{
		k = false; // if x cannot be founded in entered coordinate, k will be false. because program should detect 'o' and it should be displays this cell is not occupied. 
	}
}

// this function returns true if enclosed area are found
// else it returns false
bool Area(int x, int y, vector<coordinates> list)
{
	int a = list[list.size()-1].x;
	int b = list[list.size()-1].y;

	if( a == x+1 && b == y && list.size() >= 4       // meaning of 4 --> the smallest enclosed area
		|| a == x && b == y-1  && list.size() >= 4	 // last coordinate should be up, down, right or left side of the starting coordinate
		|| a == x-1 && b == y  && list.size() >= 4
		|| a == x && b == y+1  && list.size() >= 4)
		return true;

	else
		return false;
}

int main()
{
	string c1, c2;
	int xCoordinate, yCoordinate;

	string fileName;
	bool control; // for control fileName is valid or not
	bool control2; // it controls cell contains 'x' or 'o'. Used in Path function. if control2 be false program displays "cell is not occupied" message.
	ifstream input;

	vector<coordinates> list;
	vector<vector<char>> mat;

	int counter = -1; // it helps control matrix is valid or not in terms of its size.
	

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
	while(!input.eof()){

		getline(input, line);
		stringstream ss(line);
		
		char chr;
		vector<char> temp;

		while(ss >> chr){
			temp.push_back(chr);
		}

		if(!charControl(mat)){
			cout << fileName << " includes invalid char(s) "<<endl<<endl;
			return 0;		
		}
		else if(counter > -1){
			if(!amountControl(temp, mat[counter])){ // for example; temps is n(th) row of the matrix and mat[counter] is the (n-1)th row of the matrix. amountControl compares them in terms of their size.
				cout << fileName << " is invalid matrix, does not contain same amount of char each row!"<<endl<<endl;
				return 0;
			}
		}

		mat.push_back(temp);
		counter++; // counter should be incremented  by one for compare other rows. (mat[counter]).
	}

	printMatrix(mat);

	do{
		do{	
			cout << "Please enter starting coordinates, first row X then column Y: ";
			cin >> c1 >> c2;

			if(coordinateControl(mat, c1, c2) == false){
				if(c1 == "-1" && c2 == "-1"){
					cout << "Terminating..."  <<endl<<endl;
					return 0;
				}
				else{
					cout << "Invalid Coordinates"<<endl<<endl;
				}
			}
		}while(!coordinateControl(mat, c1, c2));
		
		xCoordinate  = atoi(c1);
		yCoordinate = atoi(c2);

		Path(xCoordinate, yCoordinate, mat, list, control2); // if there is no 'x' in searched cell control2 is turned false by Path function.

		if(control2 == false){
			cout << "This cell is not occupied!" <<endl;
			control2 = true; // it should be turned true again because if it is not turned true, in every iteration message is shown.
		}
		else{
			if(Area(xCoordinate, yCoordinate, list)){
				cout << "Found an enclosed area. The coordinates of the followed path: "<<endl;
			}
			else{
				cout << "Cannot found an enclosed area starting with given coordinate. The coordinates of the followed path: " <<endl;
			}
		}

		for(int j = 0 ; j < list.size(); j++){
			cout << list[j].x << " " << list[j].y <<endl;
		}
		cout <<endl; 

		for(int j = list.size()-1 ; j >= 0 ; j--){ // vector that created for store path, should be deleted for store other iterations.
			list.pop_back();
		}
	}while(xCoordinate != -1 && yCoordinate != -1);
}