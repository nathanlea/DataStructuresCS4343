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



expTree* expTree::getLeftChild() {
	return leftChild;
}
expTree* expTree::getRightChild() {
	return rightChild;
}
void expTree::getParent(expTree* par) {
	parent = par;
}
expTree* expTree::setParent() {
	return parent;
}
void expTree::setNumber(int input) {
	number = input;
}
int expTree::getNumber(){
	return number;
}
void expTree::setValue(char input) {
	value = input;
}
char expTree::getValue(){
	return value;
}
void expTree::clearChildren(){
	leftChild = NULL; rightChild = NULL;
	hasLeft = false; hasRight = false;
}
void expTree::setLeftChild(expTree* tree) {
	leftChild=tree;
	hasLeft = true;
}
void expTree::setRightChild(expTree* tree) {
	rightChild=tree;
	hasRight = true;
}
void expTree::newLeftChild() {
	leftChild = new expTree();
	leftChild->getParent(this);
	hasLeft = true;
}
void expTree::newRightChild() {
	rightChild = new expTree();
	rightChild->getParent(this);
	hasRight = true;
}
