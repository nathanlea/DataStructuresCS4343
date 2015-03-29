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
#include <regex>
#include <queue>
#include <stack>
#include <climits>
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
			if (currentLeaf->num) {
				int a = currentLeaf->getNumber();
				currentLeaf->setNumber(a * 10 + (currentChar - 48));
			}
			else { //default normal case
				currentLeaf->num = true;
				currentLeaf->setNumber(currentChar-48);
			}
		}
		else {
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
void postfix(expTree* tree, queue<int>* posFixQ) {
	if (!tree->hasLeft && !tree->hasRight) {
		if (tree->num) { posFixQ->push(tree->getNumber());	}
		else {	posFixQ->push(INT_MIN + tree->getValue());	}		
		//cout << tree->getValue()<< " ";
		return;
	}
	postfix(tree->getLeftChild(), posFixQ);
	postfix(tree->getRightChild(), posFixQ);
	if (tree->num) { posFixQ->push(tree->getNumber());	}
	else {	posFixQ->push(INT_MIN + tree->getValue());	}
}

int evaulate(queue<int>* Q) {
	int result = 0;
	stack<int>* S = new stack<int>;
	int size = Q->size();
	for (int i = 0; i < size; i++) {
		int q = Q->front();
		Q->pop();
		int q1 = q - INT_MIN;
		if (q1 == '+' || q1 == '-' || q1 == '*' || q1 == '/') {
			int a = S->top();
			S->pop();
			int b = S->top();
			S->pop();
			result = calculate(a, b, q);
			S->push(result);
		}
		else {
			S->push(q);
		}
	}
	return S->top();
}

int calculate(int b, int a, char q) {
	if (q == '+'){		return a + b; }
	else if (q == '-') {return a - b; }
	else if (q == '*'){ return a * b; }
	else if (q == '/'){ return a / b; }
	else {  }
	return -1;
}


int main() {
	//get expression
	expTree* a = new expTree;
	char str[] = "( ( 5 + ( ( 1 + 2 ) * 4 ) ) - 3 )";
	char str1[] = "(((((12 * 2) / 2) + 15) * 6) + 66)";
	char str2 [] = "(((((122 * 2) / 2) + 15) * 6) + 66)";
	auto input = regex_replace(str2, std::regex("\\s"), "");
	makeTree(input, a);
	queue<int>* Q = new queue<int>;
	postfix(a, Q);
	int result = evaulate(Q);
	cout << result <<endl;
#ifdef _WIN32
	system("pause");
#endif
}