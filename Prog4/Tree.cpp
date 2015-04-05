/************************************************************
* CS 4343: Program 5
* AUTHOR: NATHAN LEA
* CLASS:  DATA STRUCTURES
* DATE:   April 8 2015
*
* PROGRAM: Tree
*
* COMPILE: 'g++ -std=c++0x *.cpp -o Tree'
* RUN: Tree
*
************************************************************/
#include <stdlib.h>
#include <iostream>
#include <queue>
#include <stack>
#include <climits>
#include "ExpTree.h"
using namespace std;

void makeTree(string input, expTree* tree);
void postfix(expTree* tree, queue<char>* posFixQ);
int evaulate(queue<char>* Q);
int calculate(int a, int b, char q);
int expressionTree(string str);

/****************************************************************
* METHOD: makeTree
* PARAMS: string input, expTree* tree
* RETURN: void
*
* Take an expression and turns into an expression tree
*
****************************************************************/
void makeTree(string input, expTree* tree) {
	expTree* currentLeaf = tree;
	bool lastWasNum = false; //Adds support for multi-digit numbers
	for (unsigned int i = 0; i < input.size(); i++) {
		char currentChar = input.at(i); //Get the current char in the String
		if (currentChar >= 48 && currentChar <= 57) { //If ascii value is numberical digit
			if (lastWasNum) { //If the last char read in was a number do some math to get the correct mulitdigit number
				int a = currentLeaf->getValue(); //Get the last int read in
				currentLeaf->setValue(a * 10 + (currentChar - 48)); //Multiply that number by 10 and add the current number
			}
			else { //Normal case new integer case
				lastWasNum = true; //Set reading an int to true
				currentLeaf->setValue(currentChar-48); //Set the int value of the char to the currentLeaf
			}
		}
		else if(currentChar !=' ') { //If space ignore
			if (currentChar == '(') { //If '(' go one level deeper
				lastWasNum = false; //Not number
				currentLeaf->newLeftChild(); //Make new left Child
				currentLeaf = currentLeaf->getLeftChild(); //Set that left child to currentLeaf
			}
			else if (currentChar == ')') { // If ')' go one level up
				lastWasNum = false; //Not number
				currentLeaf = currentLeaf->getParent(); // Get the parent of the currentLeaf to go up one level
			}
			else if (currentChar == '+' || currentChar == '-' || currentChar == '*' || currentChar == '/') { //If operator
				currentLeaf = currentLeaf->getParent(); //Get parent
				currentLeaf->setValue(-1 * currentChar); //Negate the asci value of the currentChar sine negative aren't possible
				currentLeaf->newRightChild(); //Get ready for next input, get the right child
				currentLeaf = currentLeaf->getRightChild(); //Set the right to the currentLeaf
				lastWasNum = false; //Not number
			}
			else {
				//any other case
				cout << "Unsupported Character, please enter a correct string. \n(Supported operations +, -, *, /)" << endl;
				return;
			}
		}
	}
	tree = currentLeaf; //set the created tree to the passed in one

}

/****************************************************************
* METHOD: posfix
* PARAMS: expTree* tree, queue<int>* posFixQ
* RETURN: void
*
* Traverses the tree and places the elements with posfix traversal
* into the queue
*
****************************************************************/
void postfix(expTree* tree, queue<int>* posFixQ) {
	if (!tree->hasLeft && !tree->hasRight) { //If no parents
		posFixQ->push(tree->getValue());//Push value to queue
		return;
	}
	postfix(tree->getLeftChild(), posFixQ); //Recure Left
	postfix(tree->getRightChild(), posFixQ); //Recure Right
	posFixQ->push(tree->getValue()); //Once visited childs then push value
}

/****************************************************************
* METHOD: evaluate
* PARAMS: queue<int>* Q
* RETURN: int
*
* Takes the postfix traversal and places elements into the stack 
* until reaches a non number then pulls two elements out does 
* the operation and puts back in stack, return the evauluation 
* of the expTree
*
****************************************************************/
int evaulate(queue<int>* Q) {
	int result = 0;
	stack<int>* S = new stack<int>;
	int size = Q->size();
	for (int i = 0; i < size; i++) {
		int q = Q->front(); Q->pop();//Get and pop the front element of the queue		
		int q1 = q * -1; //negate to see if operator, if q1 is positive then is operator
		if (q1 > 0) { //If operator, operate
			int a = S->top(); S->pop(); //Get and pop element
			int b = S->top(); S->pop(); //Get and pop element
			result = calculate(a, b, q1); //Caluculate result from 2 elements and operand
			S->push(result); //push result to stacks
		}
		else { //If number push to stack
			S->push(q); //Push number to stack
		}
	}
	return S->top(); //return value of function
}

/****************************************************************
* METHOD: calculate
* PARAMS: int b, int a, char q
* RETURN: int
*
* Simple operator class, find what operator to use does the 
* calculation and returns
*
****************************************************************/
int calculate(int b, int a, char q) {
	if		(q == '+') { return a + b; }
	else if (q == '-') { return a - b; }
	else if (q == '*') { return a * b; }
	else if (q == '/') { return a / b; }
	else {  }
	return -1;
}

/****************************************************************
* METHOD: expressionTree
* PARAMS: string str
* RETURN: int
*
* Helper class for main, calls the 3 methods to correct make and
* evaulate the tree, returns the calculated expression
*
****************************************************************/
int expressionTree(string str) {
	expTree* a = new expTree;
	queue<int>* Q = new queue<int>;
	makeTree(str, a);
	postfix(a, Q);
	return evaulate(Q);
}


int main() {
	string str1 = "( ( 5 + ( ( 1 + 2 ) * 4 ) ) - 3 )"; int answer1 = 14;
	string str2 = "(((((122 * 2) / 2) + 15) * 6) + 66)"; int answer2 = 888;
	string str3 = "((5+3)*2)"; int answer3 = 16;
	string str4 = "(5+3)"; int answer4 = 8;

	cout << "Test 1:   " << "(5+3)" << endl;
	cout << "Answer: " << answer4;
	int result4 = expressionTree(str4);
	cout << "  Result: " << result4 << "      ";
	if (result4 == answer4)
		cout << "Test Passed" << endl;
	else
		cout << "Test Failed" << endl;

	cout << "Test 2:   " << "((5+3)*2)" << endl;
	cout << "Answer: " << answer3;
	int result3 = expressionTree(str3);
	cout << "  Result: " << result3 << "    ";
	if (result3 == answer3)
		cout << "Test Passed" << endl;
	else
		cout << "Test Failed" << endl;

	cout << "Test 3:   " << "(((((122 * 2) / 2) + 15) * 6) + 66)" << endl;
	cout << "Answer: " << answer2;
	int result2 = expressionTree(str2);
	cout << "  Result: " << result2 << "  ";
	if (result2 == answer2)
		cout << "Test Passed" << endl;
	else
		cout << "Test Failed" << endl;

	cout << "Test 4:   " << "((5 + ((1 + 2) * 4)) - 3)" << endl;
	cout << "Answer: " << answer1;
	int result1 = expressionTree(str1);
	cout << "  Result: " << result1 << "    ";
	if (result1 == answer1)
		cout << "Test Passed" << endl;
	else
		cout << "Test Failed" << endl;

	if ((result1 == answer1) && (result2 == answer2) && (result3 == answer3) && (result4 == answer4))
		cout << endl << "Program Passed!" << endl;
	else
		cout << endl << "Program Failed." << endl;

#ifdef _WIN32
	system("pause");
#endif
}
