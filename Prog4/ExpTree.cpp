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
* METHOD: getLeftChild
* PARAMS: void
* RETURN: expTree*
*
* returns the leftChild of the current node
*
****************************************************************/
expTree* expTree::getLeftChild() {
	return leftChild;
}
/****************************************************************
* METHOD: getRightChild
* PARAMS: void
* RETURN: expTree*
*
* returns the rightChild of the current node
*
****************************************************************/
expTree* expTree::getRightChild() {
	return rightChild;
}
/****************************************************************
* METHOD: getParent
* PARAMS: expTree* par
* RETURN: void
*
* sets the parent of the current node
*
****************************************************************/
void expTree::setParent(expTree* par) {
	parent = par;
}
/****************************************************************
* METHOD: getParent
* PARAMS: void
* RETURN: expTree*
*
* returns the parent of the current node
*
****************************************************************/
expTree* expTree::getParent() {
	return parent;
}
/****************************************************************
* METHOD: setValue
* PARAMS: int input
* RETURN: void
*
* set the value of the node
*
****************************************************************/
void expTree::setValue(int input) {
	value = input;
}
/****************************************************************
* METHOD: getValue
* PARAMS: void
* RETURN: int
*
* return the value of the node
*
****************************************************************/
int expTree::getValue(){
	return value;
}
/****************************************************************
* METHOD: clearChildren
* PARAMS: void
* RETURN: void
*
* clears the child of the current node
*
****************************************************************/
void expTree::clearChildren(){
	leftChild = NULL; rightChild = NULL;
	hasLeft = false; hasRight = false;
}
/****************************************************************
* METHOD: setLeftChild
* PARAMS: expTree*
* RETURN: void
*
* sets the left child of the current node
*
****************************************************************/
void expTree::setLeftChild(expTree* tree) {
	leftChild=tree;
	hasLeft = true;
}
/****************************************************************
* METHOD: setRightChild
* PARAMS: expTree*
* RETURN: void
*
* sets the rightChild of the current node
*
****************************************************************/
void expTree::setRightChild(expTree* tree) {
	rightChild=tree;
	hasRight = true;
}
/****************************************************************
* METHOD: newLeftChild
* PARAMS: void
* RETURN: void
*
* Creates a new leaf and sets it to the leftChild of the current Node
*
****************************************************************/
void expTree::newLeftChild() {
	leftChild = new expTree();
	leftChild->setParent(this);
	hasLeft = true;
}
/****************************************************************
* METHOD: newRightChild
* PARAMS: void
* RETURN: void
*
* Creates a new leaf and sets it to the rightChild of the curret Node
*
****************************************************************/
void expTree::newRightChild() {
	rightChild = new expTree();
	rightChild->setParent(this);
	hasRight = true;
}
