// classes example
#include <iostream>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
using namespace std;

/**********************************
*
* Element Class to be used to store
* value to be used in SList
*
* Stores and returns a single int
***********************************/
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
/**********************************
*
*
*
***********************************/
class SList {
    SList* before;
	SList*	after;
	Element e;
  public:
	SList();
    SList* Create();
    void Make_Null();
	//~SList () {delete before; delete after;}
	bool Is_Empty();
	int Size();
	void Chop(int n, SList* L);
	void Catenate(SList* L1, SList* L2);
	SList* Examine_First(SList* L);
	SList* Examine_Last(SList* L);
	SList* Singleton(Element e);	
};
//This just should create a blank list, probably nothing else.
SList::SList() {
	before = NULL;
	after = NULL;
}	
/**********************************
* 
* As in List; creates an empty list L
*
***********************************/
SList* SList::Create() {
	before = NULL;
	after = NULL;
	return this;
}
/**********************************
*
*
*
***********************************/
void SList::Make_Null() {
	Create();
}
/**********************************
*
* Decides if list L is empty
*
***********************************/
bool SList::Is_Empty() {
	//NHL TODO Add the case if this is a single element or empty
	if (Examine_First(before) == NULL && Examine_Last(after) == NULL && !e.active() ) { 
		return true;
	}
	else {
		return false;
	}
}
/**********************************
*
* Computes the number of elements in a list L
*
***********************************/
int SList::Size() {
	int counter = 0;
	SList* first = Examine_First(before);
	SList* last = Examine_Last(after);

	//cout << "Size set up" << endl;
	if (first != NULL) {
		//cout << "First != NULL" << endl;
		counter++;
		while (first->after != NULL) {
			first = first->after;
			counter++;
			//cout << "counter " << counter << endl;
		}
	}
	else if (last != NULL) {
		counter++;
		while (last->before != NULL) {
			last = last->before;
			counter++;
		}
	}
	//NHL TODO If there is only this element in the list, is it empyt or one element.
	else if (e.active()) {
		counter++;
	}
	return counter;
}
/**********************************
*
* The function value Chop(n, L) is undefined if the integer n satisfies that |n| > Size(L).
* Otherwise, its value is L′, where, if n is nonnegative, then L′ consists of the first n 
* elements of L; otherwise, L′ consists of the last −n elements of L
*
***********************************/
void SList::Chop(int n, SList* L) {

	if (abs(n) > Size()) {
		//If this is true the chop function does nothing.
		return;
	}
	else if (n > 0) {
		SList* first = Examine_First(L);
		--n;
		while (n > 0) {
			first = first->after;
			--n;
		}
		//Delete anything in the after pointer to clear anything after in the list
		first->after = NULL;
	}
	else if (n < 0) {
		SList* last = Examine_Last(L);
		++n;
		while (n < 0) {
			last = last->before;
			++n;
		}
		//Deletes anything in the before pointer to clear anything before in the list
		last->before = NULL;
	}
	else if (n == 0) {
		//Clear everything is the list
		L->before = NULL;
		L->after = NULL;
	}
}
/**********************************
*
* The function value Catenate(L1, L2) is a list L such that Chop(Size(L1), L) = L1,
* Chop(−Size(L2), L) = L2, and Size(L) = Size(L1) + Size(L2).
*
***********************************/
void SList::Catenate(SList* L1, SList* L2) {
	//Get the last of L1 and the first of L2 and set the pointers to each other.
	
	SList* last = Examine_Last(L1);
	SList* first = Examine_First(L2);

	last->after = first;
	first->before = last;

}
/**********************************
*
* The function value of Examine First(L) is undefined if L is empty; otherwise,
* it is the first element of L
*
***********************************/
SList* SList::Examine_First(SList* L) {
	
	//cout << "Examine First" << endl;
	if (L == NULL) {
		return NULL;
	}
	else {
		SList* temp = L;
		while (temp->before != NULL) {
			temp = temp->before;
		}
		return temp;
	}
	
}
/**********************************
*
* The function value of Examine Last(L) is undefined if L is empty; otherwise,
* it is the last element of L.
*
***********************************/
SList* SList::Examine_Last(SList* L) {

	//cout << "Examine Last" << endl;
	if (L == NULL) {
		return NULL;
	}
	else {
		SList* temp = L;
		while (temp->after != NULL) {
			temp = temp->after;
		}
		return temp;
	}
}
/**********************************
*
* Forms a list of size 1 that consists of the single element e.
*
***********************************/
SList* SList::Singleton(Element a) {
	e = a;
	before = NULL;
	after = NULL;
	//cout << "Singleton Complete" << endl;
	return this;
	//memset(before, 0, sizeof(SList));
	//memset(after,  0, sizeof(SList));
}
/**********************************
*
*
*
***********************************/
int main () {
	Element e(1);
	Element f(2);
	Element g(3);
	Element h(4);

	SList a;
	SList b;
	SList c;
	SList d;
	a.Singleton(e);
	b.Singleton(f);
	c.Singleton(g);
	d.Singleton(h);
	a.Catenate(&a, &b);
	a.Catenate(&c, &a);
	a.Catenate(&d, &a);
	cout << "Size: " << a.Size() << endl;
	cout << "Is Empty: " << a.Is_Empty() << endl << endl;
	cout << "Chopped!" << endl;
	a.Chop(2, &a);
	cout << "Size: " << a.Size() << endl;
	return 0;
}