/************************************************************
* CS 4343: Program 2
* AUTHOR: NATHAN LEA
* CLASS:  DATA STRUCTURES
* DATE:   FEBRUARY 6 2015
*
* PROGRAM: Multiplication
*
* COMPILE: 'g++ -o multipication multipication.cpp'
* RUN: multipication
************************************************************/
#include <iostream>
#include <bitset>
#include <string>
#include <climits>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
using namespace std;

bitset<256> multiplication(bitset<256>, bitset<256>);
bitset<256> bigMultiply(char, char, char, char);
bitset<256> add(bitset<256>, bitset<256>);
bitset<128> bitSplitRight(bitset<128>, int);
void TestMultiplicaiton();
void programTests();


/************************************************************
*
* Basic Multiplication method: 
*
* The Recusion of the multiplication is simple continue to 
* split x and y until the length is 2 bit or less then multiply 
* the two bits and start to progress back up the chain just adding 
* the lower cases and returning the lower sums to sum up the answer
*
* Returns the answer in binary
*
* RETURNS bitset<256>
************************************************************/

bitset<256> multiplication(bitset<128> x, bitset<128> y, int n) {
	int m = 0;

	//m is the ceiling of n
	(n % 2) == 0 ? m = n / 2 : m = (n / 2) + 1;

	if (n <= 2) {
		// Since n is a two bit number we know the number
		// of bit in x and y is two thus just multipling
		// the two bits is simple base case
		return bigMultiply(x[0], x[1], y[0], y[1]);
	}
	else {
		
		//Split x and y
		//To get xL just shift length of the new m
		bitset<128> xL = (bitset<128>)x >> m;
		//To get xR zero the bits above m
		bitset<128> xR = bitSplitRight(x, m);
		//To get yL shift m
		bitset<128> yL = (bitset<128>)y >> m;
		//To get yR zero the bits above m
		bitset<128> yR = bitSplitRight(y, m);


		//Recursion for the highest significance
		bitset<256> high = (multiplication(xL, yL, m) << (2 * m));
		//Recursion for the middle part of the multiplication
		bitset<256> mid1 = multiplication(xL, yR, m);
		bitset<256> mid2 = multiplication(xR, yL, m);
		//Recursion for the lowest part of the recursion
		bitset<256> low = multiplication(xR, yR, m);

		//Add the pieces together
		bitset<256> total = add( high, add( (add(mid1, mid2) << m), low ) );
		//Return total
		return total;
	}
}

/************************************************************
* METHOD: bigMultiply
* RETURN: bitset<256>
*
* Takes in 4 bits and creates 2, 2 bit numbers and multiplies
* them together using bit shifting and &
*
************************************************************/

bitset<256> bigMultiply(char x0, char x1, char y0, char y1) {
	char tempX = (x1 << 1) + x0;
	
	//Multiply the bits using a fast multiplication method
	int X_Y = ((y1 * tempX) << (1 & y1)) + ((y0 * tempX) << (0 & y0));

	bitset<256> mul(X_Y);

	return mul;
}
/************************************************************
* METHOD: add
* RETURN: bitset<256>
*
* Basic adder funtionality for the bitset data type
* Takes in two bitsets and adds them keeping a carry bit 
* and returns the addition
*
************************************************************/
bitset<256> add(bitset<256> a, bitset<256> b) {
	bool carry = 0;
	bitset<256> sum(0);
	for (int k = 0; k < 256; k++) {
		//Using a fast adder add the a b and carry
		sum[k] = a[k] ^ b[k] ^ carry;
		//Find if there is a carry bit propigated to the next add
		carry = (a[k] & b[k]) | (b[k] & carry) | (a[k] & carry);
	}
	return sum;
}
/************************************************************
* METHOD: bitSlpitLeft
* RETURN: bitset<128>
*
* Takes in a bitset and an index and zeros the values up to 
* the index and return the right side of the number
* 
************************************************************/
bitset<128> bitSplitRight(bitset<128> a, int m) {
	bitset<128> b = (bitset<128>) a;
	for (int z = m; z < 2 * m; z++) {
		//Clears the bits to the left of the m
		b.reset(z);
	}
	return b;
}

/************************************************************
*
* Main test method
*
* Allows for human input or for it to run a set of 
* predetermined tests
*
************************************************************/
void TestMultiplicaiton() {
	int n = 0;
	char S = 0;
	string bit_stringX;
	string bit_stringY;
	bitset<256> result;

	cout << "Run program tests, or allow human input? y or n: ";
	cin >> S;
	if (S == 'y' || S == 'Y') {
		programTests();
		return;
	}

	cout << "Enter length of n-bit sequence: ";
	cin >> n;
	cout << endl << "Enter x (ex. 1001): ";
	cin >> bit_stringX;
	cout << endl << "Enter y (ex. 1111): ";
	cin >> bit_stringY;
	cout << endl;

	//Check if the input is as they said
	if (bit_stringX.size() != n || bit_stringY.size() != n) {
		cout << "Incorrect input, exiting." << endl;
#ifdef _WIN32
		system("pause");
#endif
		//Exit if it does not match
		return;
	}

	try {
		//Just in case the user does not put in a straight binary string
		bitset<128> x(bit_stringX);
		bitset<128> y(bit_stringY);


		result = multiplication(x, y, n);
		string output = result.to_string();
		output.erase(0, output.find_first_not_of('0'));
		output.size() == 0 ? output.append("0") : output;
		cout << "X * Y = " << endl;
		cout << output << endl << endl;
#ifdef _WIN32
		system("pause");
#endif
		return;
	}
	catch (exception e){
		cout << "Incorrect input, exiting." << endl;
#ifdef _WIN32
		system("pause");
#endif
		//Exit safely and not crash on incorrect input
		return;
	}
}

/************************************************************
*
* Tests the Multiplication method with a number of bits
*
************************************************************/

void programTests() {
	int n = 0;
	string bit_stringX;
	string bit_stringY;
	string output;
	bitset<256> result;
	bool failedTest = 0;

	//Test 1: 2 bit Multiplication
	n = 2;
	bit_stringX = "01";
	bit_stringY = "11";
	bitset<128> x1(bit_stringX);
	bitset<128> y1(bit_stringY);
	result = multiplication(x1, y1, n);

	cout << "****** Test 1 ******" << endl;
	cout << "X: " << bit_stringX << endl; 
	cout << "Y: " << bit_stringY << endl;
	output = result.to_string();
	output.erase(0, output.find_first_not_of('0'));
	output.size() == 0 ? output.append("0") : output;
	cout << "Result: " << output << endl;

	if (~output.compare("11")) {
		cout << "2 bit Multiplication Passed" << endl;
	}
	else {
		cout << "2 bit Multiplication Failed" << endl;
		failedTest = 1;
	}

	//Test 2: 4 bit Multiplication
	n = 4;
	bit_stringX = "1001";
	bit_stringY = "1110";
	bitset<128> x2(bit_stringX);
	bitset<128> y2(bit_stringY);
	result = multiplication(x2, y2, n);

	cout << "****** Test 2 ******" << endl;
	cout << "X: " << bit_stringX << endl;
	cout << "Y: " << bit_stringY << endl;
	output = result.to_string();
	output.erase(0, output.find_first_not_of('0'));
	output.size() == 0 ? output.append("0") : output;
	cout << "Result: " << output << endl;

	if (~output.compare("1111110")) {
		cout << "4 bit Multiplication Passed" << endl;
	}
	else {
		cout << "4 bit Multiplication Failed" << endl;
		failedTest = 1;
	}

	//Test 3: 6 bit Multiplication
	n = 6;
	bit_stringX = "101101";
	bit_stringY = "111000";
	bitset<128> x3(bit_stringX);
	bitset<128> y3(bit_stringY);
	result = multiplication(x3, y3, n);

	cout << "****** Test 3 ******" << endl;
	cout << "X: " << bit_stringX << endl;
	cout << "Y: " << bit_stringY << endl;
	output = result.to_string();
	output.erase(0, output.find_first_not_of('0'));
	output.size() == 0 ? output.append("0") : output;
	cout << "Result: " << output << endl;

	if (~output.compare("100111011000")) {
		cout << "6 bit Multiplication Passed" << endl;
	}
	else {
		cout << "6 bit Multiplication Failed" << endl;
		failedTest = 1;
	}

	//Test 4: 16 bit Multiplication
	n = 16;
	bit_stringX = "1010101010101111";
	bit_stringY = "0101010101011111";
	bitset<128> x4(bit_stringX);
	bitset<128> y4(bit_stringY);
	result = multiplication(x4, y4, n);

	cout << "****** Test 4 ******" << endl;
	cout << "X: " << bit_stringX << endl;
	cout << "Y: " << bit_stringY << endl;
	output = result.to_string();
	output.erase(0, output.find_first_not_of('0'));
	output.size() == 0 ? output.append("0") : output;
	cout << "Result: " << output << endl;

	if (~output.compare("111000111010110111000111110001")) {
		cout << "16 bit Multiplication Passed" << endl;
	}
	else {
		cout << "16 bit Multiplication Failed" << endl;
		failedTest = 1;
	}

	//Test 5: 50 bit Multiplication
	n = 50;
	bit_stringX = "10100101001001001001001001001001010110101010101111";
	bit_stringY = "11110111011011011011010100100101010101011010101010";
	bitset<128> x5(bit_stringX);
	bitset<128> y5(bit_stringY);
	result = multiplication(x5, y5, n);

	cout << "****** Test 5 ******" << endl;
	cout << "X: " << bit_stringX << endl;
	cout << "Y: " << bit_stringY << endl;
	output = result.to_string();
	output.erase(0, output.find_first_not_of('0'));
	output.size() == 0 ? output.append("0") : output;
	cout << "Result: " << output << endl;

	if (~output.compare("1001111110011101000011101001001000000000101"
		"100010111010010000100000100101000100010101010001000110110")) {
		cout << "50 bit Multiplication Passed" << endl;
	}
	else {
		cout << "50 bit Multiplication Failed" << endl;
		failedTest = 1;
	}

	//Test 6: 128 bit Multiplication
	n = 128;
	bit_stringX = "1010010100100100100100100100100101011010101010111111110111"
		"0110110110110101001001010101010110101010101011111010101010101111011101";
	bit_stringY = "1111011101101101101101011010010100100100100100100100100101"
		"0110101010101111111101110110110110110101001001010101010110101010101011";
	bitset<128> x6(bit_stringX);
	bitset<128> y6(bit_stringY);
	result = multiplication(x6, y6, n);

	cout << "****** Test 6 ******" << endl;
	cout << "X: " << bit_stringX << endl;
	cout << "Y: " << bit_stringY << endl;
	output = result.to_string();
	output.erase(0, output.find_first_not_of('0'));
	output.size() == 0 ? output.append("0") : output;
	cout << "Result: " << output << endl;

	if (~output.compare("100111111001110100001110111001000111001101001111001"
		"1011001001100100000100101000101111011001011000111110101100101100111"
		"0100110010010100000111101010001100011101010000011100011110010101110"
		"11011101001000100100101011101010111011000010110010010110100111010011111")) {
		cout << "128 bit Multiplication Passed" << endl;
	}
	else {
		cout << "128 bit Multiplication Failed" << endl;
		failedTest = 1;
	}

	if (failedTest) {
		cout << endl << endl <<"A test failed" << endl;
	}
	else {
		cout << endl << endl << "All tests were successful!" << endl;
	}
}

/************************************************************
*
* Calls TestMultiplicaiton
*
************************************************************/

int main() {
	TestMultiplicaiton();
}