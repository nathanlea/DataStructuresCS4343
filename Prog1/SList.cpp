/************************************************************
* AUTHOR: NATHAN LEA
* CLASS:  DATA STRUCTURES
* DATE:   JANUARY 25 2015
*
* PROGRAM: LINKED LIST
* 
************************************************************/
#include <iostream>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
using namespace std;

/************************************************************
*
* Element Class to be used to store
* value to be used in SList
*
* Stores and returns a single int
************************************************************/
class Element {
	int value;
	bool defined;
	public:
		Element();
		Element(int n);
		int get_value() {return value;}
		bool active() { return defined; }
};
Element::Element( int n ) {
	value = n;
	defined = true;
}
Element::Element( ) {
	value = 0;
	defined = false;
}
/************************************************************
*
*
*
************************************************************/
class SList {
    SList* before;
	SList*	after;
	Element e;
  public:
	SList();
	~SList();
    SList* Create();
    void Make_Null();	
	bool Is_Empty();
	int Size();
	void Chop(int n, SList* L);
	void Catenate(SList* L1, SList* L2);
	SList* Examine_First(SList* L);
	SList* Examine_Last(SList* L);
	SList* Singleton(Element e);	
};
/************************************************************
*
* Constructor for the SList class; initializes the pointers to NULL
*
************************************************************/
SList::SList() {
	before = NULL;
	after = NULL;
}
/************************************************************
*
* Deconstructor for the SList class;
* Clears the pointers in the SList Class
*
************************************************************/
SList::~SList() {
	SList* top;
	if ((this->after || this->before) == 0) {
		top = NULL;
		before = NULL;
		after = NULL;
	}
	else {
		SList* temp = this;
		while (temp->before != NULL) {
			temp = temp->before;
		}
		top = temp;
		while (top != NULL) {
			SList* next = top->after;
			if (next != NULL) {
				top = NULL;
				next->before = NULL;
				top = next;
			}
			else
				return;
		}
	}
}
/************************************************************
* 
* Creates an empty list L
* Returns SList pointer to the new SList
*
************************************************************/
SList* SList::Create() {
	//Clears before and after pointers
	before = NULL;
	after = NULL;
	//Returns new SList
	return this;
}
/************************************************************
*
* Calls the SList:Create
* Does not return the List
*
************************************************************/
void SList::Make_Null() {
	//Calls create, makes blank SList
	Create();
}
/************************************************************
*
* Determines if list is empty
* Returns bool is SList is empty
*
************************************************************/
bool SList::Is_Empty() {
	//If First and Last are NULL and element doesn't exist, List is empty
	if (Examine_First(before) == NULL && Examine_Last(after) == NULL && !e.active() ) { 
		return true;
	}
	else {
		return false;
	}
}
/************************************************************
*
* Computes the number of elements in a list L
* Returns int of the size
*
************************************************************/
int SList::Size() {
	int counter = 0;
	//Get First in list
	SList* first = Examine_First(before);
	//Get Last in list
	SList* last = Examine_Last(after);

	//First doesn't equal NULL then 'first' is the first element in list
	if (first != NULL) {
		//Count first element in list
		++counter;
		while (first->after != NULL) {
			//As long as first->after exists continue counting
			first = first->after;
			//increase counter to count elements in list
			++counter;
		}
	}
	//first == NULL then use last pointer, count backwards up the list
	else if (last != NULL) {
		//increase for last element
		++counter;
		while (last->before != NULL) {
			//as long as the list has element before continue
			last = last->before;
			//increase count of list
			++counter;
		}
	}
	//Special case where the list has no other elements but this one
	//If the element value is set then this element will count else not
	else if (e.active()) {
		++counter;
	}
	//Return count of list
	return counter;
}
/************************************************************
*
* The function value Chop(n, L) is undefined if the integer n satisfies that |n| > Size(L).
* Otherwise, its value is L′, where, if n is nonnegative, then L′ consists of the first n 
* elements of L; otherwise, L′ consists of the last −n elements of L
*
* Returns void; Changes initial pointers
*
************************************************************/
void SList::Chop(int n, SList* L) {

	if (abs(n) > Size()) {
		//If this is true the chop function does nothing.
		return;
	}
	//n > 0 then we are counting in from the start and chopping
	else if (n > 0) {
		//get first element in list
		SList* first = Examine_First(L);
		//decrease n for first element
		--n;
		while (n > 0) {
			//go down the list n-1 elements
			first = first->after;
			--n;
		}
		//Delete anything in the after pointer to clear anything after in the list
		first->after->before = NULL;
		first->after = NULL;		
	}
	//n < 0 then we are counting from the bottom and chopping
	else if (n < 0) {
		//get last element in list
		SList* last = Examine_Last(L);
		//increase n for first element
		++n;
		while (n < 0) {
			//go up the list increasing n until we get to the element to chop
			last = last->before;
			++n;
		}
		//Deletes anything in the before pointer to clear anything before in the list
		last->before->after = NULL;
		last->before = NULL;
	}
	else if (n == 0) {
		//Clear everything is the list
		L->before = NULL;
		L->after = NULL;
	}
}
/************************************************************
*
* The function value Catenate(L1, L2) is a list L such that Chop(Size(L1), L) = L1,
* Chop(−Size(L2), L) = L2, and Size(L) = Size(L1) + Size(L2).
* 
* Returns void; Sets the passed pointers
*
************************************************************/
void SList::Catenate(SList* L1, SList* L2) {
	//Get the last of L1 and the first of L2 and set the pointers to each other.
	
	SList* last = Examine_Last(L1);
	SList* first = Examine_First(L2);

	last->after = first;
	first->before = last;
}
/************************************************************
*
* The function value of Examine First(L) is undefined if L is empty; otherwise,
* it is the first element of L
*
* Returns SList*; Element of the First Element in the list
*
************************************************************/
SList* SList::Examine_First(SList* L) {
	
	//if N equals null then the first element is the present
	if (L == NULL) {
		//return null
		return NULL;
	}
	else {
		//create temp L to not affect pointer passed in
		SList* temp = L;
		while (temp->before != NULL) {
			//go up the list until the before pointer is null
			temp = temp->before;
		}
		//return the first element in this list
		return temp;
	}	
}
/************************************************************
*
* The function value of Examine Last(L) is undefined if L is empty; otherwise,
* it is the last element of L.
*
* Returns SList*; First Element in the list
*
************************************************************/
SList* SList::Examine_Last(SList* L) {
	//if N equals null then the last element is the present
	if (L == NULL) {
		return NULL;
	}
	else {
		//create temp L
		SList* temp = L;
		while (temp->after != NULL) {
			//go down the list until the after pointer is null
			temp = temp->after;
		}
		//return the last element
		return temp;
	}
}
/************************************************************
*
* Forms a list of size 1 that consists of the single element e.
*
* Returns SList*; creates SList and adds Element to list
*
************************************************************/
SList* SList::Singleton(Element a) {
	//set the element to the list element
	e = a;
	//clear pointers
	before = NULL;
	after = NULL;
	//return list
	return this;
}
/************************************************************
*
* Main Test function for SList
*
************************************************************/
int main () {
	bool failedTest = false;
	cout << "SList Test Inialization: " << endl;
	
	//Test 1: blank list: size, is empyt
	cout << "Test 1:\t" << "Blank List" << endl;
	SList t1;
	int size1 = t1.Size();
	bool empty1 = t1.Is_Empty();
	cout << "List Size:  " << size1 << "\t Expected: 0" << endl;
	cout << "List Empty: " << empty1 << "\t Expected: 1" << endl;
	if (size1 == 0 && empty1 == 1) {
		cout << "Test passed!" << endl << endl;
	}
	else { 
		cout << "Test Failed!" << endl << endl;
		failedTest = true;
	}

	//Test 2: list size 1, is empty
	cout << "Test 2:\t" << "List length 1" << endl;
	SList t2;
	Element e2(2);
	t2.Singleton(e2);

	int size2 = t2.Size();
	bool empty2 = t2.Is_Empty();
	cout << "List Size:  " << size2 << "\t Expected: 1" << endl;
	cout << "List Empty: " << empty2 << "\t Expected: 0" << endl;
	if (size2 == 1 && empty2 == 0) {
		cout << "Test passed!" << endl << endl;
	}
	else {
		cout << "Test Failed!" << endl << endl;
		failedTest = true;
	}

	//Test 3: 2 lists size one, cat, size, empty
	cout << "Test 3:\t" << "2 Lists size 1, concatenate together" << endl;
	SList t3a;
	Element e3a(2);
	t3a.Singleton(e3a);

	SList t3b;
	Element e3b(3);
	t3b.Singleton(e3b);

	t3a.Catenate(&t3a, &t3b);

	int size3 = t3a.Size();
	bool empty3 = t3a.Is_Empty();

	cout << "List Size:  " << size3 << "\t Expected: 2" << endl;
	cout << "List Empty: " << empty3 << "\t Expected: 0" << endl;
	if (size3 == 2 && empty3 == 0) {
		cout << "Test passed!" << endl << endl;
	}
	else {
		cout << "Test Failed!" << endl << endl;
		failedTest = true;
	}

	//Test 4: 2 list size one, cat, chop, size, empty
	cout << "Test 4:\t" << "2 List size 1, concatenate together, then chop apart" << endl;
	SList t4a;
	Element e4a(3);
	t4a.Singleton(e4a);

	SList t4b;
	Element e4b(4);
	t4b.Singleton(e4b);

	t4a.Catenate(&t4a, &t4b);

	t4a.Chop(1, &t4a);

	int size4 = t4a.Size();
	bool empty4 = t4a.Is_Empty();

	cout << "List Size:  " << size4 << "\t Expected: 1" << endl;
	cout << "List Empty: " << empty4 << "\t Expected: 0" << endl;
	if (size4 == 1 && empty4 == 0) {
		cout << "Test passed!" << endl << endl;
	}
	else {
		cout << "Test Failed!" << endl << endl;
		failedTest = true;
	}

	//Test 5: 2 list size two, cat, chop, cat, size, empty
	cout << "Test 5:\t" << "2 List size 2, concatenate, chop, concatenate" << endl;

	SList t5a;
	Element e5a(4);
	t5a.Singleton(e5a);

	SList t5b;
	Element e5b(5);
	t5b.Singleton(e5b);

	SList t5c;
	Element e5c(6);
	t5c.Singleton(e5c);

	SList t5d;
	Element e5d(7);
	t5d.Singleton(e5d);
	
	t5a.Catenate(&t5a, &t5b);

	t5c.Catenate(&t5c, &t5d);

	t5a.Catenate(&t5a, &t5c);

	t5a.Chop(2, &t5a);

	t5a.Catenate(&t5a, &t5c);

	int size5 = t5a.Size();
	bool empty5 = t5a.Is_Empty();

	cout << "List Size:  " << size5 << "\t Expected: 4" << endl;
	cout << "List Empty: " << empty5 << "\t Expected: 0" << endl;
	if (size5 == 4 && empty5 == 0) {
		cout << "Test passed!" << endl << endl;
	}
	else {
		cout << "Test Failed!" << endl << endl;
		failedTest = true;
	}

	//Test 6: 2 list size one, chop (0), size, empty
	cout << "Test 6:\t" << "2 List size 1, concatenate, chop(0)" << endl;
	SList t6a;
	Element e6a(3);
	t6a.Singleton(e6a);

	SList t6b;
	Element e6b(4);
	t6b.Singleton(e6b);

	t6a.Catenate(&t6a, &t6b);

	t6a.Chop(0, &t6a);

	int size6 = t6a.Size();
	bool empty6 = t6a.Is_Empty();

	cout << "List Size:  " << size6 << "\t Expected: 1" << endl;
	cout << "List Empty: " << empty6 << "\t Expected: 0" << endl;
	if (size6 == 1 && empty6 == 0) {
		cout << "Test passed!" << endl << endl;
	}
	else {
		cout << "Test Failed!" << endl << endl;
		failedTest = true;
	}

	//Test 7: 2 list size one, cat, 1 list size 1 cat, chop, size, empty
	cout << "Test 7:\t" << "2 List size 1, concatenate, 1 list size 1, concatenate, chop" << endl;

	SList t7a;
	Element e7a(3);
	t7a.Singleton(e7a);

	SList t7b;
	Element e7b(4);
	t7b.Singleton(e7b);

	SList t7c;
	Element e7c(4);
	t7c.Singleton(e7c);

	t7a.Catenate(&t7a, &t7b);

	t7a.Catenate(&t7a, &t7c);

	t7a.Chop(-1, &t7a);
	
	int size7 = t7a.Size();
	bool empty7 = t7a.Is_Empty();

	cout << "List Size:  " << size7 << "\t Expected: 2" << endl;
	cout << "List Empty: " << empty7 << "\t Expected: 0" << endl;
	if (size7 == 2 && empty7 == 0) {
		cout << "Test passed!" << endl << endl;
	}
	else {
		cout << "Test Failed!" << endl << endl;
		failedTest = true;
	}

	if (!failedTest) {
		cout << "Thank You for using SList Test" << endl;
	}
	else {
		cout << "A Test has failed:(" << endl;
	}
	return 0;
}