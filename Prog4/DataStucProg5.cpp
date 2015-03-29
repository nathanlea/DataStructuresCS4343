/************************************************************
* CS 4343: Program 5
* AUTHOR: NATHAN LEA
* CLASS:  DATA STRUCTURES
* DATE:   April 1 2015
*
* PROGRAM: Tree
*
* COMPILE: 'g++ -std=c++0x *.cpp -o Tree'
* RUN: Tree
*
************************************************************/
#include <stdlib.h>
#include <iostream>
#include <regex>
#include <queue>
#include <stack>
#include "ExpTree.h"
using namespace std;

void makeTree(string input, expTree* tree);
void postfix(expTree* tree, queue<char>* posFixQ);
int evaulate(queue<char>* Q);
int calculate(int a, int b, char q);

void makeTree(string input, expTree* tree) {
	expTree* currentLeaf = tree;
	for (int i = 0; i < input.size(); i++) {
		char currentChar = input.at(i);
		if (currentChar >= 48 && currentChar <= 57) {
			currentLeaf->setValue(currentChar);
			//48 - 57
			//its a number
			//put the number in the child position
			//cout << currentChar << endl;
		}
		else {
			//check and see if supported operation
			//put in parent position
			//
			//cout << currentChar << endl;
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
void postfix(expTree* tree, queue<char>* posFixQ) {
	if (!tree->hasLeft && !tree->hasRight) {
		posFixQ->push(tree->getValue());
		cout << tree->getValue()<< " ";
		return;
	}
	postfix(tree->getLeftChild(), posFixQ);
	postfix(tree->getRightChild(), posFixQ);
	posFixQ->push(tree->getValue());
	cout << tree->getValue() << " ";
}

int evaulate(queue<char>* Q) {
	int result = 0;
	stack<int>* S = new stack<int>;
	int size = Q->size();
	for (int i = 0; i < size; i++) {
		char q = Q->front();
		Q->pop();
		if (q == '+' || q == '-' || q == '*' || q == '/') {
			int a = S->top();
			S->pop();
			int b = S->top();
			S->pop();
			result = calculate(a, b, q);
			S->push(result);
		}
		else {
			S->push(q-48);
		}
	}
	return S->top();
}

int calculate(int a, int b, char q) {
	if (q == '+'){		return a + b; }
	else if (q == '-') {return b - a; }
	else if (q == '*'){ return a * b; }
	else if (q == '/'){ return b / a; }
	else {	cout << "HELP!" << endl;  }
	return -1;
}


int main() {
	//get expression
	expTree* a = new expTree;
	char str[] = "( ( 5 + ( ( 1 + 2 ) * 4 ) ) - 3 )";
	char str1[] = "(((((2 * 2) / 2) + 5) * 6) + 6)";
	auto input = regex_replace(str1, std::regex("\\s"), "");
	makeTree(input, a);
	queue<char>* Q = new queue<char>;
	postfix(a, Q);
	int result = evaulate(Q);
	cout << result <<endl;
	//make into tree
	//postfix 
	//evaluate expression

#ifdef _WIN32
	system("pause");
#endif
}