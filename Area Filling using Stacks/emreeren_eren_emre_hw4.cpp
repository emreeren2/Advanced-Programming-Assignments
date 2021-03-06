#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include"DynamicStack.h"

using namespace std;

// This function controls that entered coordinate is valid or not.
// it is used in getnumRowCol function
bool controlRowCol(string num)
{
	for (int i = 0; i < num.length(); i++){
		
		if (num[i] < '0' || num[i] > '9'){
			return false;
		}
	}

	if (stoi(num) < 3)
		return false;

	else
		return true;
}

// It gets number(size) from user. It is continuing to get input while not valid input is entered.
// if user enter valid input string num is converted to integer size for this way we can use size in our main
void getnumRowCol(string type, int & size)
{
	string num;
	bool c;

	do{
		c = true;
		cout << "Enter the number of " << type << ": ";
		cin >> num;

		if (!controlRowCol(num)){
			cout << num << " is not valid!" <<endl;
			c = false;
		}
	} while (c == false);

	size = stoi(num); // if user enters valid coroordinate, this coordinate converted to integer, and we are able to use it in main because of 'int & size' decleration.
}

/* Begin: code taken from matrix.cpp */
void PrintMatrix(char **matrix, int Rsize, int Csize) // it prints matrix
{
	for(int i=0; i<Rsize; i++)
	{
		for (int j = 0; j < Csize; j++)
		{
			cout << matrix[i][j];
		}
		cout <<endl;
	}
}
/* End: code taken from matrix.cpp */

// This function controls that entered coordinates are valid or not.
// it is used in getCoordinate function
bool controlCoordinate(string row, string col, int row_size, int col_size)
{
	for (int i = 0; i < row.length(); i++){
		
		if (row[i] < '0' || row[i] > '9'){
			return false;
		}
	}

	for (int i = 0; i < col.length(); i++){
		
		if (col[i] < '0' || col[i] > '9'){
			return false;
		}
	}

	if (stoi(row) >= row_size || stoi(col) >= col_size)
		return false;

	else
		return true;
}

// This function gets coordinates from user. It is continuing to get input while not valid input is entered
void getCoordinate(int &row, int &column, int row_size, int col_size)
{
	bool control = true;
	string row_num, column_num; // taken as string because controling them is esair.

	do{
		control = true;
		cout << "Enter the starting point: ";
		cin >> row_num >> column_num;

		if(controlCoordinate(row_num, column_num, row_size, col_size) == false){
			cout << "Invalid coordinate!" <<endl;
			control = false;
		}
	}while(control == false);

	row = stoi(row_num);		// if user enters valid coroordinates, this coordinates converted to integer, and 'row' and 'column' (which has reference paramter)
	column = stoi(column_num);  // variable gets this valid coordinates. We are able to use that valid coordinates in our main because, reference paramter is used.
	
}

// This function is used for getting character that enclosed area will be filled, is valid or not valid.
// It takes input while not valid input is entered
void getFillingChar(char &chr)
{
	bool c = true;

	do{
		c = true;
		cout << "Enter the filling char: ";
		cin >> chr;

		if(chr == 'x' || chr == 'X'){
			cout << "Filling char is not valid!" <<endl;
			c = false;
		}
	}while(c == false);
}

/* It starts from the starting coordinate and fill it with the filling character. 
After that it moves towards an empty neighbor in one of four directions (north, east, south, west). 
If it can move in one of those directions,  current cell is pushed to stack, and then move.
it does the same until there is no empty neighbors. 
If it stucks, it goes back with pop coordinates from stack and do that untill find an available cell with an empty neighbor. */
// Basically, it finds path that surrounded with 'x' then filled this path with entered character.
void fillArea(char **&matrix, int R, int C, char chr, DynamicStack &stack)
{
	stack.push(R,C);
	matrix[R][C] = chr;

	do{	

		if(matrix[R-1][C] == ' ' || matrix[R][C+1] == ' ' || matrix[R+1][C] == ' ' || matrix[R][C-1] == ' ' ){

			while (matrix[R][C+1] == ' ' ){ // look east
				C = C+1;
				stack.push(R,C);
				matrix[R][C] = chr;
			}
			while (matrix[R+1][C] == ' '){ // look south
				R = R+1;
				stack.push(R,C);
				matrix[R][C] = chr;
			}
			while (matrix[R][C-1] == ' ' ){ // look west
				C = C-1;
				stack.push(R,C);
				matrix[R][C] = chr;
			}
			while (matrix[R-1][C] == ' ' ){ // look north
				R = R-1;
				stack.push(R,C);
				matrix[R][C] = chr;
			}
		}

		else{
			do{ 

				stack.pop(R,C);

				while(matrix[R-1][C] == ' ' ){
					R = R-1;
					stack.push(R,C);	
					matrix[R][C] = chr;
				}
		
				while(matrix[R][C-1] == ' '){
					C = C-1;
					stack.push(R,C);	
					matrix[R][C] = chr;
				}

				while(matrix[R+1][C] == ' '){
					R = R+1;
					stack.push(R,C);	
					matrix[R][C] = chr;
				}

				while(matrix[R][C+1] == ' ' ) { 
					C = C+1;
					stack.push(R,C);	
					matrix[R][C] = chr;
				}
			}while(!stack.isEmpty());
		}
	}while(!stack.isEmpty());
}

/*Begin: code taken from ptrfunc.cpp */
void DeleteMatrix(char ** matrix, int size) 
{
	for(int i=0; i<size; i++)
	{
		delete [] matrix[i];
	}
	delete [] matrix;
}
/* End: code taken from ptrfunc.cpp */


int main()
{
	DynamicStack Stack;

	string fileName;
	ifstream input;
	bool control1;

	int rowSize, colSize;

	getnumRowCol("rows", rowSize);
	getnumRowCol("colums", colSize);

	do{
		control1 = true;

		cout << "Please enter file name: ";
		cin >> fileName;

		input.open(fileName);

		if(input.fail()){
			cout << "Cannot open a file named " << fileName << endl;
			control1 = false;
		}
	}while(control1 == false);


	char *dArray = new char[colSize]; 
	char **dMatrix = new char*[rowSize];

	string line;
	char chr;
	int i = 0, j = 0;
	while(getline(input,line)){

		istringstream iss(line);

		i = 0;
		char *dArray = new char[colSize]; 
		while(iss >> chr || i < colSize){
			dArray[i] = line[i];
			i++;
		}

		dMatrix[j] = dArray;
		j++;
	}

	//PrintMatrix(dMatrix, rowSize, colSize);

	int row, column;
	getCoordinate(row, column, rowSize, colSize);

	if(dMatrix[row][column] == 'X'){
		cout << "Starting point is already occupied."<<endl;
		cout << "Terminating... "<<endl;
		return 0;
	}
	else{
		char fillingChr;
		getFillingChar(fillingChr);

		fillArea(dMatrix, row, column, fillingChr, Stack);
	}
	
	PrintMatrix(dMatrix, rowSize, colSize);
	DeleteMatrix(dMatrix, rowSize);
	return 0;
}