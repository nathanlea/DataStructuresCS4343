#include <cmath>
#include <stdlib.h>
using namespace std;


class graph {
	struct vector {
		int u;
		int v;
	} v;

	int tempi = 5;
	int tempj = 10;
public:
	//vector* getVector();
	//void setVector(vector* v);
	//float distanceBetween(graph* v2);
	//void setCoords(int x, int y);
	graph::graph(int x, int y) {
		setCoords(x, y);
	}

	//Get Vector
	graph::vector* graph::getVector() {
		return &(graph::v);
	}
	//Set Vector
	void graph::setVector(vector* v2){
		(graph::v) = (vector)*v2;
	}
	void graph::setCoords(int x, int y) {
		vector* g = new vector();
		g->u = x;
		g->v = y;
		setVector(g);
	}
	//Distance Between
	float graph::distanceBetween(graph* c) {
		vector* tempv1 = c->getVector();
		int temp1 = abs(v.u - tempv1->u);
		int temp2 = abs(v.v - tempv1->v);
		return (float) sqrt(pow(abs(v.u - c->getVector()->u), 2) + pow(abs(v.v - c->getVector()->v), 2));
	}
};