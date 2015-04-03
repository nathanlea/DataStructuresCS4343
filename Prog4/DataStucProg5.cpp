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
* METHOD: 
* PARAMS: 
* RETURN: 
*
* 
*
****************************************************************/
void makeTree(string input, expTree* tree) {
	expTree* currentLeaf = tree;
	for (unsigned int i = 0; i < input.size(); i++) {
		char currentChar = input.at(i);
		if (currentChar >= 48 && currentChar <= 57) {
			if (currentLeaf->num) {
				int a = currentLeaf->getNumber();
				currentLeaf->setNumber(a * 10 + (currentChar - 48));
			}
			else { //default normal case
				currentLeaf->num = true;
				currentLeaf->setNumber(currentChar-48);
			}
		}
		else if(currentChar !=' ') {
			if (currentChar == '(') {
				currentLeaf->newLeftChild();
				currentLeaf = currentLeaf->getLeftChild();
			}
			else if (currentChar == ')') {
				currentLeaf = currentLeaf->getParent();
			}
			else if (currentChar == '+' || currentChar == '-' || currentChar == '*' || currentChar == '/') {
				currentLeaf = currentLeaf->getParent();
				currentLeaf->setValue(currentChar);
				currentLeaf->newRightChild();
				currentLeaf = currentLeaf->getRightChild();
			}
			else {
				//any other case
				cout << "Unsupported Character, please enter a correct string. \n(Supported operations +, -, *, /)" << endl;
			}
		}
	}
	tree = currentLeaf;

}

/****************************************************************
* METHOD:
* PARAMS:
* RETURN:
*
*
*
****************************************************************/
void postfix(expTree* tree, queue<int>* posFixQ) {
	if (!tree->hasLeft && !tree->hasRight) {
		if (tree->num) { posFixQ->push(tree->getNumber());	}
		else {	posFixQ->push(-1 * tree->getValue());	}	
		return;
	}
	postfix(tree->getLeftChild(), posFixQ);
	postfix(tree->getRightChild(), posFixQ);
	if (tree->num) { posFixQ->push(tree->getNumber());	}
	else {	posFixQ->push(-1 * tree->getValue());	}
}

/****************************************************************
* METHOD:
* PARAMS:
* RETURN:
*
*
*
****************************************************************/
int evaulate(queue<int>* Q) {
	int result = 0;
	stack<int>* S = new stack<int>;
	int size = Q->size();
	for (int i = 0; i < size; i++) {
		int q = Q->front();
		Q->pop();
		int q1 = q * -1;
		if (q1 == '+' || q1 == '-' || q1 == '*' || q1 == '/') {
			int a = S->top();
			S->pop();
			int b = S->top();
			S->pop();
			result = calculate(a, b, q1);
			S->push(result);
		}
		else {
			S->push(q);
		}
	}
	return S->top();
}

/****************************************************************
* METHOD:
* PARAMS:
* RETURN:
*
*
*
****************************************************************/
int calculate(int b, int a, char q) {
	if (q == '+'){		return a + b; }
	else if (q == '-') {return a - b; }
	else if (q == '*'){ return a * b; }
	else if (q == '/'){ return a / b; }
	else {  }
	return -1;
}

/****************************************************************
* METHOD:
* PARAMS:
* RETURN:
*
*
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
