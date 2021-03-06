#include<iostream>
#include<string>

using namespace std;


// this function was taken and modified accordingly from https://www.geeksforgeeks.org/how-to-swap-two-bits-in-a-given-integer/
void swap(unsigned int & chr, unsigned int p1, unsigned int p2)
{
	unsigned int bit1 = (chr >> p1) & 1; // Move p1'th to rightmost side 
	unsigned int bit2 =  (chr >> p2) & 1; // Move p2'th to rightmost side
	unsigned int x = (bit1 ^ bit2); // XOR the two bits
	x = (x << p1) | (x << p2); // Put the xor bit back to their original positions
	chr = chr ^ x; //XOR 'x' with the original number so that the two sets are swapped
}


unsigned char P(const char & chr)
{
	unsigned int result = chr;
	
	swap(result, 7, 6); swap(result, 6, 4); swap(result, 5, 4); // swapping 7th bit with 6th, 6th with 4th and 5th with 4th
	swap(result, 3, 2); swap(result, 2, 0); swap(result, 1, 0); // swapping 3rd bit with 2nd, 2nd with 0th and 1st with 0th
	return result;					
}


int main()
{
	cout << "*** Welcome to the Simple Data Encryption Application ***\n ";

	string plaintext, key;
	unsigned char chr;

	cout << "Please enter the encryption key: ";
	getline(cin,key);

	cout << "Please enter the plaintext to be encrypted: ";	
	while (getline(cin,plaintext))
	{
		cout << "Ciphertext: ";
		for (int i = 0; i < plaintext.length(); i++)
		{
			chr = P(plaintext[i]); // putting plaintext to function P and asign it another char
			chr = chr ^ key[i % (key.length())]; // XOR operation between key and manipulated char // modulo operator used because key should repeat itself
			cout << hex << (int) chr;
		}
		cout <<endl<<endl;
		cout << "Please enter the plaintext to be encrypted: ";	
	}	
	return 0;
}