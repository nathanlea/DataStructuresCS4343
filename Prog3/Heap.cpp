/************************************************************
* CS 4343: Program 4
* AUTHOR: NATHAN LEA
* CLASS:  DATA STRUCTURES
* DATE:   March 23 2015
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

void buildMaxHeap(int A [], int last);
void swap(int &a, int &b);
void heapSort(int a [], int elements);
void heapifyDownward(int a [], int top, int bottom, int path [], int elements, int length);
bool findPath(int a [], int top, int bottom, int path [], int elements, int length);
void binarySearch(int a [], int path [], int top, int elements);
void shiftElementsUp(int a [], int path [], int position, int top, int elements);
bool isSorted(int a [], int elements);

/****************************************************************
* METHOD: swap
* PARAMS: int &a, int &b
* RETURN: void
*
* Takes two pointers and swaps them, used for swapping array elements
*
* RUNTIME: The function has a run time of O( 1 )
* COMPARISONS: 0
****************************************************************/
void swap(int &a, int &b) {
	a = a + b;
	b = a - b;
	a = a - b;
}

/****************************************************************
* METHOD: heapSort
* PARAMS: int[] a, int elements
* RETURN: void
*
*
* Take in an unsorted unheaped array and the number of
* elements in the heap, then changes the array to a sorted array
*
*
* RUNTIME: The functions standing alone has a O(n/2)
*		   The full run time is O( n*lg(n) ) because it calls
*		   HeapifyDownward n times and since heapifyDownward
*		   is a lg(n) function this woulfd run in lg(n) time
* COMPARISONS: 0
****************************************************************/
void buildMaxHeap(int a [], int max) {
	int size = 0; int path[20];

	//Gets the size of a full heap
	while (size <= max) {
		size = size * 2;
		size++;
	}
	// This processes two counters as to max heap on even smaller heap then building the heaps bigger and bigger
	// to finally have a max heap built
	int half = (int) (size / 2); int top = half - 1;
	int bottomCount = size - 1; int increaseCount = 1;	int length = 1;
	for (; top >= 0; --top) {
		heapifyDownward(a, top, bottomCount, path, max, length);
		bottomCount = bottomCount - increaseCount * 2;
		if (bottomCount < half) {
			bottomCount = size - 1;
			increaseCount = 2 * increaseCount;
			++length;
		}
	}

}

/****************************************************************
* METHOD: heapSort
* PARAMS: int[] a, int elements
* RETURN: void
*
*
* Take in an unsorted unheaped array and the number of
* elements in the heap, then changes the array to a sorted array
*
* RUNTIME: The functions standing alone has a O(n)
*		   The full run time is O(n^2 * lg(n))
*		   because the run time of heapifyDownward is O(n*lg(n))
*		   and heapifyDownward is called n times
* COMPARISONS: 1
****************************************************************/
void heapSort(int a [], int elements) {
	for (int i = (elements - 1); i > 0; --i) {
		buildMaxHeap(a, i);
		swap(a[0], a[i]);
	}
	if (a[0] > a[1])
		swap(a[0], a[1]);
}

/****************************************************************
* METHOD: heapifyDownward
* PARAMS: int[] a, int elements
* RETURN: void
*
* Method takes an unheapified array and makes a max heap
*
* RUNTIME: The function has a run time of O( elements*lg(elements) )
* COMPARISONS: lg(elements)
****************************************************************/
void heapifyDownward(int a [], int top, int bottom, int path [], int elements, int length) {
	if (findPath(a, top, bottom, path, elements, length))
		binarySearch(a, path, top, elements);
}

/****************************************************************
* METHOD: findPath
* PARAMS: int[] a, int top, int path[], int elements, int length
* RETURN: void
*
* Finds the path in the heap from the given top to the given bottom
* with an heap of elements
* Changes the path array to be the path from the top path[0] is the length of the path
* In path it either sets a 1 or 2 for left or right respectively
*
* RUNTIME: The function has a run time of O( lg(elements) )
* PROOF:   The proof of this is because the height of the heap
*		   is at max lg(n) and the most that the path could ever
*		   be is the height and this runs through the loop at max
*		   that many times
* COMPARISONS: O( lg(elements) )
* PROOF:	   The proof of this is because that path is at most
*			   length lg(n) and there is only one comparison for
*			   each element in the path
****************************************************************/
bool findPath(int a [], int top, int bottom, int path [], int elements, int length) {
	//This path finding will be log(n) 
	int levelCounter = 1;
	//cout << endl << top << "     " << elements << "  " << bottom << endl;
	if (length == 1 && bottom > elements) return false;
	for (int i = top; (2 * i) + 1 <= bottom && (2 * i) + 2 <= bottom && 2 * i + 1 < elements; ++levelCounter) {
		//i is the top of the tree then will increase to find the shortest path always equallying either 1 less or 2 less to the child
		int leftChild = (i * 2) + 1; int rightChild = (i * 2) + 2; //Get the right and left childs of the ith element
		//If there is only a right child pick the left
		if (rightChild > bottom) {
			i = leftChild;
			path[levelCounter] = 1;
			break;
		}
		//If left is less than right pick right
		if (a[leftChild] < a[rightChild]) {
			i = rightChild;
			path[levelCounter] = 2;
		}
		//If left is larger than right pick left
		else {
			i = leftChild;
			path[levelCounter] = 1;
		}
	}
	//Set the path[0] to the length of the path
	path[0] = (levelCounter - 1);
	return true;
}

/****************************************************************
* METHOD: binarySearch
* PARAMS: int[] a, int path[], int top, int elements
* RETURN: void
*
* Take the path that findPath choose then chooses the element
* position that is needs to go then inserts the top element
* there and shifts the others above it
*
* RUNTIME: The function has a run time of O( lg(lg(elements)) )
* PROOF:   This function preforms a binarysearch on the path
*		   elements that the top element in question could be bigger
*		   than and since a binarysearch is lg(n) time and the path
*		   is lg(n) the run time of this binarySearch is lg(lg(n))
* COMPARISONS: lg(lg(elements))
* PROOF:   This function preforms a binarysearch on the path
*		   elements that the top element in question could be bigger
*		   than and since a binarysearch is lg(n) comparisons and
*		   the path is lg(n) the most comarisions of this
*		   binarySearch is lg(lg(n))
****************************************************************/
void binarySearch(int a [], int path [], int top, int elements) {
	//Find the middle poitn of the path
	int middle = path[0] % 2 ? ((int) (path[0] / 2)) + 1 : ((int) (path[0] / 2));
	int middle_element;
	//Get the index of the middle element
	for (int i = top, j = 1; j <= middle; j++) {
		i = 2 * i + path[j];
		middle_element = i;
	}
	//pathLength = length of the path
	int pathLength = path[0];
	//LooCounter is used to find how many times down or up the path the looped moved
	int loopCounter = 1;
	while (true) {
		//If path is longer than 1 element keep going up or down the path tree
		if (pathLength > 1) {
			//If the new middle of the path is less than go half down the tree
			if (a[middle_element] < a[top]) {
				int i = top;
				middle = ((int) (middle / 2));
				//Get the element of the new middle of the path
				for (int j = 1; j <= middle; j++, loopCounter++) {
					i = ((int) (i * 2)) + path[j];
				}
				middle_element = i;
			}
			//Else go half down
			else {
				int i = top;
				//Get the midde of the path accounting for where the middle currently is
				middle = middle % 2 ? middle + ((int) (middle / 2)) + 1 : middle + ((int) (middle / 2));
				//if the middle goes beyond the path pull it back inbounds
				if (middle > path[0]) middle = path[0];
				//Get the index of the element from the path reference
				for (int j = 1; j <= middle; j++, loopCounter++) {
					i = 2 * i + path[j];
				}
				middle_element = i;
			}
			pathLength -= loopCounter;
		}
		else {
			//position is where the element should be inserted these cases
			//check if is should go above or below the position
			int position = middle_element;
			if (a[position] < a[top]) {
				//It goes above, get new position
				position = position % 2 ? (position / 2) + 1 : ((position / 2));
				position -= path[path[0]];
				//shift elements up
				shiftElementsUp(a, path, position, top, elements);
				break;
			}
			else {
				//Goes at position, shift elements up
				shiftElementsUp(a, path, position, top, elements);
				break;
			}
		}
	}
}
/****************************************************************
* METHOD: shiftElementsUp
* PARAMS: int[] a, int path[], int position, int top, int elements
* RETURN: void
*
* Insets the element at position then shift evething above that one space up
*
* RUNTIME: The function has a run time of O( lg(n) )
* PROOF:   This function preforms a swap on every element of the path
*		   perimuating it down the heap until the position is reached,
*		   The max that this could be would be when the elements needs to be
*		   last in the path and therefore it would run lg(n) times
* COMPARISONS: 0
****************************************************************/
void shiftElementsUp(int a [], int path [], int position, int top, int elements) {
	for (int i = top, j = 1; j <= path[0]; j++) {
		if (i == position) {
			//Go swap needed should go where it is
			break; //Do nothing
		}
		else if (i > position) {
			//Swap has already been made
			break;
		}
		else {
			//Shift elements up 
			int b = i;
			int c = 2 * i + path[j];
			swap(a[b], a[c]);
			i = c;
		}
	}
}


bool isSorted(int a [], int elements) {
	for (int i = 0; i < elements-1; i++) {
		if (a[i] <= a[i + 1]) continue;
		else return false;
	}
	return true;
}

int main() {

	int a [] = { 58, 51, 86, 97, 35, 9, 5, 99, 81, 1, 54, 77, 87, 46, 91, 52 };
	int a1 [] = { 58, 51, 86, 97, 35, 9, 5, 99, 81, 1, 54, 77, 87, 46, 91, 52 };
	int sizeA = 15;
	int b[] = { 77, 446, 843, 599, 550, 813, 333, 623, 231, 474, 461, 462, 574, 682, 638 };
	int b1[] = { 77, 446, 843, 599, 550, 813, 333, 623, 231, 474, 461, 462, 574, 682, 638 };
	int sizeB = 15;
	int c [] = { 944, 922, 894, 883, 767, 632, 628, 545, 376, 305, 224, 206, 147, 125, 102 };
	int c1[] = { 944, 922, 894, 883, 767, 632, 628, 545, 376, 305, 224, 206, 147, 125, 102 };
	int sizeC = 15;
	int d [] = { 52, 31, 48, 57, 34, 83, 97, 33, 10, 39, 19, 20, 32, 68, 50, 61, 9, 46, 23, 90, 94, 89, 16, 81, 80, 75, 76, 45, 91, 28, 41 };
	int d1[] = { 52, 31, 48, 57, 34, 83, 97, 33, 10, 39, 19, 20, 32, 68, 50, 61, 9, 46, 23, 90, 94, 89, 16, 81, 80, 75, 76, 45, 91, 28, 41 };
	int sizeD = 31;
	int e [] = { 202, 591, 749, 693, 460, 665, 74, 593, 415, 754, 634, 813, 379, 683, 87, 513, 399, 295, 115, 221, 874, 821, 406, 414, 396, 908, 387, 211, 301, 922, 509, 12, 324, 345, 230, 779, 45, 626, 791, 733, 552, 906, 313, 362, 945, 875, 83, 395, 435, 913, 956, 232, 68, 695, 776, 902, 350, 960, 607, 933, 418, 535, 494 };
	int e1[] = { 202, 591, 749, 693, 460, 665, 74, 593, 415, 754, 634, 813, 379, 683, 87, 513, 399, 295, 115, 221, 874, 821, 406, 414, 396, 908, 387, 211, 301, 922, 509, 12, 324, 345, 230, 779, 45, 626, 791, 733, 552, 906, 313, 362, 945, 875, 83, 395, 435, 913, 956, 232, 68, 695, 776, 902, 350, 960, 607, 933, 418, 535, 494 };
	int sizeE = 63;
	
	heapFormatter hf;

	cout << "Testing HeapifyDownward:" << endl;
	cout << "Test 1: Build Max Heap - Random Numbers" << endl;

	buildMaxHeap(a, sizeA);
	hf.formatHeap(a, sizeA);
	
	cout << "Test 2: HeapSort - Random numbers" << endl;
	heapSort(a1, sizeA);
	for (int i = 0; i < sizeA; i++) {
		cout << a1[i] << ",";
	}
	cout << endl;
	cout << " Test Passed: " << isSorted(a1, sizeA)<<endl<<endl;

	cout << "Test 3: Build Max Heap - Sorted Numbers" << endl;
	buildMaxHeap(b, sizeB);
	hf.formatHeap(b, sizeB);

	cout << "Test 4: HeapSort - Sorted Numbers" << endl;
	heapSort(b1, sizeB);
	for (int i = 0; i < sizeB; i++) {
		cout << b1[i] << ",";
	}
	cout << endl;
	cout << " Test Passed: " << isSorted(b1, sizeB) << endl << endl;

	cout << "Test 5: Build Max Heap - Inverse Sorted Numbers" << endl;
	buildMaxHeap(c, sizeC);
	hf.formatHeap(c, sizeC);

	cout << "Test 6: HeapSort - Inverse Sorted Numbers" << endl;
	heapSort(c1, sizeC);
	for (int i = 0; i < sizeC; i++) {
		cout << c1[i] << ",";
	}
	cout << endl;
	cout << " Test Passed: " << isSorted(c1, sizeC) << endl << endl;

	cout << "Test 7: Build Max Heap - Large Heap" << endl;
	buildMaxHeap(d, sizeD);
	hf.formatHeap(d, sizeD);

	cout << "Test 8: HeapSort - Large Heap" << endl;
	heapSort(d1, sizeD);
	for (int i = 0; i < sizeD; i++) {
		cout << d1[i] << ",";
	}
	cout << endl;
	cout << " Test Passed: " << isSorted(d1, sizeD) << endl << endl;

	cout << "Test 9: Build Max Heap - Really Large Heap" << endl;
	buildMaxHeap(e, sizeE);
	hf.formatHeap(e, sizeE);

	cout << "Test 10: HeapSort - Really Large Heap" << endl;
	heapSort(e1, sizeE);
	for (int i = 0; i < sizeE; i++) {
		cout << e1[i] << ",";
	}
	cout << endl;
	cout << " Test Passed: " << isSorted(e1, sizeE) << endl << endl;

	if (isSorted(a1, sizeA) && isSorted(b1, sizeB) && isSorted(c1, sizeC) && isSorted(d1, sizeD) && isSorted(e1, sizeE)) {
		cout << endl << "ALL TESTS PASSED" << endl;
	}
	else {
		cout << endl << "TEST FAILED :(" << endl;
	}

#ifdef _WIN32
	system("pause");
#endif
}