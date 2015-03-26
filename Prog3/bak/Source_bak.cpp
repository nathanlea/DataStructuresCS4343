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

int main() {
	//make an array then build the heap to fit it.
	int temp [] = {1,5,8,6,4,9,7,3};
	int temp2[] = { 74, 3, 66, 78, 15, 31, 1, 72, 62, 63, 6, 7, 41, 27, 1, 51, 23, 54, 61, 67, 5, 99, 13, 83, 75, 53, 93, 56, 2, 69, 44, 17, 37, 65, 29, 35, 43, 94, 71, 89, 16, 2, 42, 49, 77, 18, 21, 39, 58, 48, 4, 9, 47, 36, 95, 92, 1, 73, 59, 55, 86, 82, 3, 45, 14, 8, 85, 79, 88, 34, 76, 97, 25, 98, 33, 81, 8, 26, 9, 4, 52, 68, 91, 87, 24, 46, 11, 19, 6, 32, 28, 57, 7, 64, 12, 84, 38, 22, 5 };
	int last = 99;
	int input = 0;
	cout << "Which heaping algorithm do you want to run? 1 - Basic 2 - Improved  ";
	cin >> input;
	--input;
	if (input) {
		makeheap(temp2, last);
	}
	else {		
		buildHeap(temp2, last);
	}
	cout << "Number of Comparsions: " << countOfComparisons << endl;
	heapFormatter hf;
	hf.formatHeap(temp2, last);
#ifdef _WIN32
	system("pause");
#endif
}