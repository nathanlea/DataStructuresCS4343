/************************************************************
* CS 4343: Program 5
* AUTHOR: NATHAN LEA
* CLASS:  DATA STRUCTURES
* DATE:   April 1 2015
*
* CLASS: ExpTree
*
* COMPILE: 'g++ -std=c++0x *.cpp -o Tree'
* RUN: Tree
*
************************************************************/
#include "ExpTree.h"
#include <stdlib.h>
#include <iostream>
using namespace std;

/****************************************************************
* METHOD:
* PARAMS:
* RETURN:
*
*
*
****************************************************************/
expTree* expTree::getLeftChild() {
	return leftChild;
}
/****************************************************************
* METHOD:
* PARAMS:
* RETURN:
*
*
*
****************************************************************/
expTree* expTree::getRightChild() {
	return rightChild;
}
/****************************************************************
* METHOD:
* PARAMS:
* RETURN:
*
*
*
****************************************************************/
void expTree::setParent(expTree* par) {
	parent = par;
}
/****************************************************************
* METHOD:
* PARAMS:
* RETURN:
*
*
*
****************************************************************/
expTree* expTree::getParent() {
	return parent;
}
/****************************************************************
* METHOD:
* PARAMS:
* RETURN:
*
*
*
****************************************************************/
void expTree::setNumber(int input) {
	number = input;
}
/****************************************************************
* METHOD:
* PARAMS:
* RETURN:
*
*
*
****************************************************************/
int expTree::getNumber(){
	return number;
}
/****************************************************************
* METHOD:
* PARAMS:
* RETURN:
*
*
*
****************************************************************/
void expTree::setValue(char input) {
	value = input;
}
/****************************************************************
* METHOD:
* PARAMS:
* RETURN:
*
*
*
****************************************************************/
char expTree::getValue(){
	return value;
}
/****************************************************************
* METHOD:
* PARAMS:
* RETURN:
*
*
*
****************************************************************/
void expTree::clearChildren(){
	leftChild = NULL; rightChild = NULL;
	hasLeft = false; hasRight = false;
}
/****************************************************************
* METHOD:
* PARAMS:
* RETURN:
*
*
*
****************************************************************/
void expTree::setLeftChild(expTree* tree) {
	leftChild=tree;
	hasLeft = true;
}
/****************************************************************
* METHOD:
* PARAMS:
* RETURN:
*
*
*
****************************************************************/
void expTree::setRightChild(expTree* tree) {
	rightChild=tree;
	hasRight = true;
}
/****************************************************************
* METHOD:
* PARAMS:
* RETURN:
*
*
*
****************************************************************/
void expTree::newLeftChild() {
	leftChild = new expTree();
	leftChild->setParent(this);
	hasLeft = true;
}
/****************************************************************
* METHOD:
* PARAMS:
* RETURN:
*
*
*
****************************************************************/
void expTree::newRightChild() {
	rightChild = new expTree();
	rightChild->setParent(this);
	hasRight = true;
}
