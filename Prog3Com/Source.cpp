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

void buildHeap(int A [], int last);
void maxHeapify(int A [], int parent, int last);
void heapSort(int A [], int last);
void flyodHeapify(int A [], int last);
void swap(int &a, int &b);
void siftdown(int a [], int n, int vacant, int missing);
void makeheap(int a [], int n);
void heapSort(int a [], int elements);
void heapifyDownward(int a [], int elements);
bool findPath(int a [], int top, int bottom, int path [], int elements, int length);
void binarySearch(int a [], int path [], int top, int elements);
void shiftElementsUp(int a [], int path [], int position, int top, int elements);


int countOfComparisons = 0;

//Old stuff 2*lg(n) comparions 
void buildHeap(int A [], int last) {
	for (int i = last / 2; i >= 0; i--) {
		maxHeapify(A, i, last);
	}
}

void maxHeapify(int A [], int parent, int last) {
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


void makeheap(int a [], int n) {
	int k;

	for (k = n / 2 - 1; k >= 0; k--)
		siftdown(a, n, k, a[k]);
}

void siftdown(int a [], int n, int vacant, int missing) {
	int memo = vacant;
	int child, parent;

	child = 2 * (vacant + 1);
	while (child < n)	{
		++countOfComparisons;
		if (-(int) ((unsigned int) ((int) (a[child] - a[child - 1])) >> (sizeof(int) * CHAR_BIT - 1)))
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


void build_heap(int a [], int max) {
	//Starting from the base we sort the parent n/2 should be the parent
	/*for(int i = (max/2) - 1; i <= 0; i = (somethingToGetNextValue)) {
		heapifyDownward(a, i);
		}*/
	//Start with three elements then call heapify downward then add element to top of array and continue
	int start = max - 3;
	int i = 3;

}

void heapSort(int a [], int elements) {
	for (int i = (elements - 1); i > 0; --i) {
		heapifyDownward(a, i);
		swap(a[0], a[i]);
	}
	if (a[0] > a[1])
		swap(a[0], a[1]);
}

void heapifyDownward(int a [], int elements) {
	int size = 0;
	int path[20];

	while (size <= elements) {
		size = size * 2;
		size++;
	}
	int half = (int) (size / 2);
	int top = half - 1;
	int bottomBottom = half + 1;
	int bottomCount = size - 1;
	int increaseCount = 1;
	int length = 1;
	for (; top >= 0; --top) {
		if (findPath(a, top, bottomCount, path, elements, length))
			binarySearch(a, path, top, elements);
		bottomCount = bottomCount - increaseCount * 2;
		if (bottomCount < half) {
			bottomCount = size - 1;
			increaseCount = 2 * increaseCount;
			++length;
		}
	}
	//Find element to switch with
	//path is the array to the path of largest elements for this run through the heap
	//Then binary Search
	//hf.formatHeap(a, 31);

}
//For the path array returned this will be either one or two for the added index to know at which child we
//need to go for, whether left(1) or right(2)
bool findPath(int a [], int top, int bottom, int path [], int elements, int length) {
	//This path finding will be log(n) 
	int levelCounter = 1;
	//cout << endl << top << "     " << elements << "  " << bottom << endl;
	if (length == 1 && bottom > elements) return false;
	for (int i = top; (2 * i) + 1 <= bottom && (2 * i) + 2 <= bottom && 2 * i + 1 < elements; ++levelCounter) {
		//i is the top of the tree then will increase to find the shortest path always equallying either 1 less or 2 less to the child
		//cout << endl << top << "     " << bottom << "  " << i << endl;
		int leftChild = (i * 2) + 1;
		int rightChild = (i * 2) + 2;
		if (rightChild > bottom) { //This is the case if there is only a right child
			//pick left
			i = leftChild;
			path[levelCounter] = 1;
			break;
		}
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
	return true;
}

void binarySearch(int a [], int path [], int top, int elements) {
	//Pick the spot where this should go
	//From here we already know where we are heading with this, right or left
	//We now need to split this array into 2 and decide to go up or down then recursive call(or irritive)
	//find level of half way to the bottom
	//Then find the child of that path
	//Check if it is less than or equal
	//Less to half down
	//Right go half up
	//Recurse
	//Return the value of the index to preform the swap with
	//int middle = ((int) (path[0]/2)) + 1; //This should be the level offset that the middle is at with an offset of 1
	int middle = path[0] % 2 ? ((int) (path[0] / 2)) + 1 : ((int) (path[0] / 2));
	int middle_element = -1;
	for (int i = top, j = 1; j <= middle; j++) {
		i = 2 * i + path[j];
		middle_element = i;
	}
	int pathLength = path[0];
	int loopCounter = 1;
	while (true) {
		if (pathLength > 1) {
			//if (!(middle == path[0] || middle == 0)) {
			if (a[middle_element] < a[top]) {
				//Go half up			
				int i = top;
				middle = middle % 2 ? ((int) (middle / 2)) : ((int) (middle / 2));
				for (int j = 1; j <= middle; j++, loopCounter++) {
					i = ((int) (i * 2)) + path[j];
				}
				middle_element = i;
			}
			else {
				//Go half down
				//cout << "Going half down: current comparing element: " << middle_element;
				int i = top;
				middle = middle % 2 ? middle + ((int) (middle / 2)) + 1 : middle + ((int) (middle / 2));
				if (middle > path[0]) middle = path[0];
				for (int j = 1; j <= middle; j++, loopCounter++) {
					i = 2 * i + path[j];
				}
				middle_element = i;
				//cout << "New comparing element: " << middle_element << endl;
			}
			//								if odd				if even
			//pathLength = pathLength % 2 ? (pathLength / 2) : (pathLength / 2) - 1;//-1;		
			pathLength -= loopCounter;
		}
		else {
			//Position is the element that is selection from getElement
			int position = middle_element;
			if (a[position] < a[top]) {
				position = position % 2 ? (position / 2) + 1 : ((position / 2));
				position -= path[path[0]];
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
}

void shiftElementsUp(int a [], int path [], int position, int top, int elements) {
	//Determine if there is a more than one swap need
	//If only one swap is needed just call swap
	//If more are needed push everything up then insert the element
	//Position is the index where the element shall go

	for (int i = top, j = 1; j <= path[0]; j++) {
		if (i == position) {
			break; //Do nothing
		}
		else if (i > position) {
			//Swap has already been made
			break;
		}
		else {
			int b = i;
			int c = 2 * i + path[j];
			swap(a[b], a[c]);
			i = c;
		}
	}
}


int main() {
	//make an array then build the heap to fit it.
	//int temp [] = {1, 5, 8, 6, 4, 9, 7, 3};
	int temp2 [] = { 74, 3, 66, 78, 15, 31, 1, 72, 62, 63, 6, 7, 41, 27, 1, 51, 23, 54, 61, 67, 5, 99, 13, 83, 75, 53, 93, 56, 2, 69, 44, 17, 37, 65, 29, 35, 43, 94, 71, 89, 16, 2, 42, 49, 77, 18, 21, 39, 58, 48, 4, 9, 47, 36, 95, 92, 1, 73, 59, 55, 86, 82, 3, 45, 14, 8, 85, 79, 88, 34, 76, 97, 25, 98, 33, 81, 8, 26, 9, 4, 52, 68, 91, 87, 24, 46, 11, 19, 6, 32, 28, 57, 7, 64, 12, 84, 38, 22, 5 };
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

	//int b[] = { 58, 51, 86, 97, 35, 9, 5, 99, 81, 1, 54, 77, 87, 46, 91, 52 };
	//int a[] = { 83, 49, 79, 78, 30, 17, 47, 43, 96, 5, 97, 36, 23, 26, 85, 88 };
	//int b[] = { 52, 31, 48, 57, 34, 83, 97, 33, 10, 39, 19, 20, 32, 108, 88 };
	//int b [] = { 52, 31, 48, 57, 34, 83, 97, 33, 10, 39, 19, 20, 32, 68, 50, 61, 9, 46, 23, 90, 94, 89, 16, 81, 80, 75, 76, 45, 91, 28, 41 };
	int b [] = { 202, 591, 749, 693, 460, 665, 74, 593, 415, 754, 634, 813, 379, 683, 87, 513, 399, 295, 115, 221, 874, 821, 406, 414, 396, 908, 387, 211, 301, 922, 509, 12, 324, 345, 230, 779, 45, 626, 791, 733, 552, 906, 313, 362, 945, 875, 53, 395, 435, 913, 956, 232, 68, 695, 776, 902, 350, 960, 607, 933, 418, 535, 494 };
	//int b [] = { 52, 31, 48, 57, 34, 83, 97, 33, 10, 39, 19, 20, 32, 68, 50, 61, 9, 46, 23, 90, 94, 89, 16, 81, 80, 75, 76, 45 };

	//for (int top = 0, elements = 3; elements <= size+1 ; elements++) {

	// 14 13 12 11 10  9  8  7  6  5  4  3  2  1  0
	// 30 28 26 24 22 20 18 16 30 26 22 18 30 22 30

	//  6  5  4 3  2  1  0
	// 14 12 10 8 14 10 14

	// 2 1 0
	// 6 4 6
	int top = 0;
	int bottom = 15;
	int size = 63;
	heapSort(b, size);
	//heapifyDownward(b, size);

	for (int i = 0; i < size; i++) {
		cout << b[i] << " ";
	}
	cout << endl;

	//heapFormatter hf;
	//hf.formatHeap(b, 31);

#ifdef _WIN32
	system("pause");
#endif
}