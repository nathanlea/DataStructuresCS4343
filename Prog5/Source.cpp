/************************************************************
* CS 4343: LONGEST DISTANCE
* AUTHOR: NATHAN LEA
* CLASS:  DATA STRUCTURES
* DATE: 1 MAY 2015
*
* PROGRAM: MaxDist
*
* COMPILE: 'g++ -std=c++0x *.cpp -o MaxDist'
* RUN: MaxDist
*
************************************************************/
#include "Graph.cpp"
#include <stdlib.h>
#include <iostream>
#include <queue>
#include <stack>
#include <climits>
using namespace std;

float MAX_DIST = -1;


void swap(int x, int y, graph* arr[]) {
	graph* temp = arr[x];
	arr[x] = arr[y];
	arr[y] = temp;
}

void getDist(graph* arr[], int size) {
	float max = 0;
	for (int i = 0; i < (size - 1); i++) {
		max += arr[i]->distanceBetween(arr[i+1]);
	}
	if (max>MAX_DIST){
		MAX_DIST = max;
	}
}

/****************************************************************
* METHOD:
* PARAMS: 
* RETURN: 
*
*
****************************************************************/
void permute(int k, int size, graph* arr[]){
	int i;

	if (k == 0)
		getDist(arr, size);
		//compare distances
	else {
		for (i = k - 1; i >= 0; i--){
			swap(i, k - 1, arr);
			permute(k - 1, size, arr);
			swap(i, k - 1, arr);
		}
	}
	return;
}


int main() {

	//make some vectors	
	//Get 10 random points to find the longest path...
	graph* POINTS [10];
	for (int i = 0; i < 10; i++) {
		int r1 = rand();
		int r2 = rand();
		POINTS[i] = new graph(r1, r2);
	}
	
	//Five points to use for testing
	//1, 4
	//6, 2
	//2, 8
	//3, 9
	//8, 7
	graph* a = new graph(1, 4);
	graph* b = new graph(6, 2); 
	graph* c = new graph(2, 8); 
	graph* d = new graph(3, 9); 
	graph* e = new graph(8, 7);

	graph* perms[5] = { a, b, c, d, e };

	permute(10, 10, POINTS);

	cout << "Max dist = " << MAX_DIST << endl;

/*
	cout << "Distance between a & c";
	cout << "   " << a->distanceBetween(c) << endl;
	cout << "Distance between a & b";
	cout << "   " << a->distanceBetween(b) << endl;
	cout << "Distance between c & b";
	cout << "   " << c->distanceBetween(b) << endl;
*/


#ifdef _WIN32
	system("pause");
#endif
}
