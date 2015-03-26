/************************************************************
* CS 4343: Program 4
* AUTHOR: NATHAN LEA
* CLASS:  DATA STRUCTURES
* DATE:   March ?? 2015
*
* PROGRAM: Multiplication
*
* COMPILE: 'g++ -std=c++0x *.cpp -o Heap'
* RUN: Heap
*
* HEAP algorithm based on http://users.encs.concordia.ca/~chvatal/notes/hsort.html
************************************************************/

#include <stdlib.h>
#include <iostream>
#include "heapFormatter.h"
using namespace std;

#define	CHAR_BIT 8

void buildHeap(int A[], int last);
void maxHeapify(int A[], int parent, int last);
void heapSort(int A[], int last);
void flyodHeapify(int A[], int last);
void swap(int &a, int &b);
void siftdown(int a [], int n, int vacant, int missing);
void makeheap(int a [], int n);
void heapifyDownward(int a [], int top, int bottom, int elements);
void findPath(int a[], int top, int bottom, int elements, int parent, int path[]);
void binarySearch(int a [], int path [], int top, int parent, int elements);
int elementsToBottom(int a [], int child, int elements);
void shiftElementsUp(int a [], int path [], int position, int top, int elements);
void findParent(int index);


int countOfComparisons = 0;

//Old stuff 2*lg(n) comparions 
void buildHeap(int A[], int last) {
	for (int i = last / 2; i >= 0; i--) {
		maxHeapify(A, i, last);
	}
}

void maxHeapify(int A[], int parent, int last) {
	int child = 2 * parent;
	while (child <= last) {
		++countOfComparisons;
		if (child + 1 <= last && A[child + 1] > A[child]) {
			++child;
		}
		++countOfComparisons;
		if (A[child] > A[parent]) {
			swap(A[child], A[parent]);
		}
		parent = child;
		child = 2 * parent;
	}
}

/************************************************************
*
* 
*
************************************************************/


void makeheap(int a[], int n) {
	int k;

	for (k = n / 2 - 1; k >= 0; k--)
		siftdown(a, n, k, a[k]);
}

void siftdown(int a[], int n, int vacant, int missing) {
	int memo = vacant;
	int child, parent;

	child = 2 * (vacant + 1);
	while (child<n)	{
		++countOfComparisons;
		if(-(int) ((unsigned int) ((int) (a[child] - a[child - 1])) >> (sizeof(int) * CHAR_BIT - 1)))
			child--;
		a[vacant] = a[child];
		vacant = child;
		child = 2 * (vacant + 1);
	}
	if (child == n)	{
		a[vacant] = a[n - 1];
		vacant = n - 1;
	}

	parent = (vacant - 1) / 2;
	while (vacant > memo)	{
		++countOfComparisons;
		if (-(int) ((unsigned int) ((int) (a[parent] - missing)) >> (sizeof(int) * CHAR_BIT - 1)))  {
			a[vacant] = a[parent];
			vacant = parent;
			parent = (vacant - 1) / 2;
		}
		else
			break;
	}
	a[vacant] = missing;
}


void swap(int &a, int &b) {
	a = a + b;
	b = a - b;
	a = a - b;
}


void build_heap(int a[], int max) {
	//Starting from the base we sort the parent n/2 should be the parent
	/*for(int i = (max/2) - 1; i <= 0; i = (somethingToGetNextValue)) {
		heapifyDownward(a, i);
	}*/
	//Start with three elements then call heapify downward then add element to top of array and continue
	int start = max - 3;
	int i = 3;

}

void heapifyDownward(int a [], int top, int bottom, int elements) {
	int parent = (int) (elements / 2); //The floor
	int path[20];
	
	//Find element to switch with
	findPath(a, top, bottom, elements, parent, path); //path is the array to the path of largest elements for this run through the heap
	//cout << &path[0] << endl;
	cout << "PATH Length: " <<path[0] << endl;
	for (int x = 1; x <= path[0]; x++){
		if (path[x] - 1)
			cout << "RIGHT ";
		else
			cout << "LEFT ";
	}
	cout << endl;
	cout << endl;
	for (int x = top,y=1; x < elements; y++) {
		cout << a[x]<< endl;
		x = 2 * x + path[y];
	}
	//Then binary Search
	//which will return the element index of the insert to occur
	//binarySearch(a, path, parent, elements);
	binarySearch(a, path, top, parent, elements);
}
//For the path array returned this will be either one or two for the added index to know at which child we
//need to go for, whether left(1) or right(2)
void findPath(int a[], int top, int bottom, int elements, int parent, int path[]) {
	int indexSwap = -1;
	//int path[20]; //This will allow for 1048576 elements in the heap

	//This path finding will be log(n) :/
	int levelCounter = 1;
	for (int i = top; i < elements; ++levelCounter) {
		//i is the top of the tree then will increase to find the shortest path always equallying either 1 less or 2 less to the child
		int leftChild = (i * 2) + 1;
		int rightChild = (i * 2) + 2;

		if (a[leftChild] < a[rightChild]) {
			//pick right
			i = rightChild;
			path[levelCounter] = 2;
		}
		else {
			//pick left
			i = leftChild;
			path[levelCounter] = 1;
		}
	}
	path[0] = (levelCounter - 1);//Set this to how many level that it took to get to the bottom
	//cout << path << endl;
	//Don't do this here
	//if (leftChild < rightChild) {
	//	indexSwap = binarySearch(a, leftChild, parent, elements);
	//}
	//else
	//	indexSwap = binarySearch(a, rightChild, parent, elements);

	//if (indexSwap != -1) {
	//	//swap(a[indexSwap], a[parent]);
	//	shiftElementsUp(a[indexSwap], a[parent]);
	//} //This should be all that is needed but only for one level.

}

void binarySearch(int a[], int path[], int top, int parent, int elements) {
	//Pick the spot where this should go
	//From here we already know where we are heading with this, right or left
	//We now need to split this array into 2 and decide to go up or down then recursive call
	
	//This might should be adjusted to be the basecase
	//if ((path[1] * 2 + 1) > elements) { //not right
	//	//This is the bottom of the list and just compare with the parent and give the array element that it needs to switch with
	//	if (a[parent] - a[0]) {
	//		return 0; //not right 
	//	}
	//	else
	//		return -1;  //No switch needed
	//}
	//int numberOfNodesToBottom = elementsToBottom( a, 0, elements); //not right

	//find level of half way to the bottom
	//int halfWayToBottom = (2 * 0 + 1) ^ numberOfNodesToBottom; //not right
	int middle = ((int) (path[0]/2)) + 1; //This should be the level that the middle is at with an offset of 1
	int middle_element = -1;
	for (int i = top, j = 1; j<=middle; j++) {
		i = 2 * i + path[j];	
		middle_element = i;
	}
	int pathLength = path[0];
	bool finalLeaf; //true up, false down
	while (true) {
		if (pathLength > 1) {
			if (a[middle_element] < a[top]) {
				//Go half up				
				//TODO get next element
				int i = middle_element;
				for (int j = middle; j >= middle/2; j--) {
					i = ((int)(i/2)) - path[j];
				}
				middle = middle / 2; //Check the math here
				middle_element = i;

				//Only critical in last itteration
				//finalLeaf = true;
			}
			else {
				//Go half down
				//TODO get next element
				int i = top;
				for (int j = 1; j <= middle + (middle / 2); j++) {
					i = i = 2 * i + path[j];
				}
				middle = middle + middle / 2; //Check the math here	
				middle_element = i;

				// Only critical in last itteration
				//finalLeaf = false;
			}
			pathLength = pathLength % 2 ? (pathLength / 2) : (pathLength / 2) - 1;
			//								if odd				if even
		}
		else {
			//TODO get next element
			//Position is the element that is selection from getElement
			int position;
			//if (finalLeaf) {
			//	//Go up one element
			//	//++middle; //This might not be necessary
			//	int i = top;
			//	for (int j = 1; j >= middle / 2; j--) {
			//		i = i = 2 * i + path[j];
			//	}
			//	position = i;

			//}
			//else {
			//	//Go down one element
			//	//--middle; //This might not be necessary...
			//	int i = top;
			//	for (int j = 1; j <= middle + (middle / 2); j++) {
			//		i = 2 * i + path[j];
			//	}
			//	position = i;
			//}
			position = middle_element;
			if (a [position] < a[top]) {
				//Then the insert push a[] down and the element goes above
				--position; //Up one level
				shiftElementsUp(a, path, position, top, elements);
				break;
			}
			else {
				//Then the inset occurs to push a[] above the element
				//last in the list
				shiftElementsUp(a, path, position, top, elements);
				break;
			}
		}
			
	}
	//Then find the child of that path
	//Check if it is less than or equal
	//Less to half down
	//Right go half up
	//Recurse
	//Return the value of the index to preform the swap with
}

int elementsToBottom(int a [], int child, int elements) {
	//This can be shortened with math later (int)log((j-i),2)-1
	//TODO NHL
	int levels = 0;
	for (int i = 0; i < elements; i = (i * 2) + 1) {
		++levels;
	}
	return levels;
}

void shiftElementsUp(int a[], int path[], int position, int top, int elements) {
	//Determine if there is a more than one swap need
	//If only one swap is needed just call swap
	//If more are needed push everything up then insert the element

	cout << "The element should go in position: " << position << endl;


}

void findParent(int index) {

}

int main() {
	//make an array then build the heap to fit it.
	//int temp [] = {1,5,8,6,4,9,7,3};
	//int temp2[] = { 74, 3, 66, 78, 15, 31, 1, 72, 62, 63, 6, 7, 41, 27, 1, 51, 23, 54, 61, 67, 5, 99, 13, 83, 75, 53, 93, 56, 2, 69, 44, 17, 37, 65, 29, 35, 43, 94, 71, 89, 16, 2, 42, 49, 77, 18, 21, 39, 58, 48, 4, 9, 47, 36, 95, 92, 1, 73, 59, 55, 86, 82, 3, 45, 14, 8, 85, 79, 88, 34, 76, 97, 25, 98, 33, 81, 8, 26, 9, 4, 52, 68, 91, 87, 24, 46, 11, 19, 6, 32, 28, 57, 7, 64, 12, 84, 38, 22, 5 };
	//int last = 99;
	//int input = 0;
	//cout << "Which heaping algorithm do you want to run? 1 - Basic 2 - Improved  ";
	//cin >> input;
	//--input;
	//if (input) {
	//	makeheap(temp2, last);
	//}
	//else {		
	//	buildHeap(temp2, last);
	//}
	//cout << "Number of Comparsions: " << countOfComparisons << endl;
	//heapFormatter hf;
	//hf.formatHeap(temp2, last);
	int top = 0;
	int bottom = 19;
	int elements = 20;
	int a [] = {5, 14, 10, 9, 13, 8, 7, 5, 4, 12, 1, 6, 5, 2, 3,2,1,0,1,3,6};

	heapifyDownward(a, top, bottom, elements);
#ifdef _WIN32
	system("pause");
#endif
}