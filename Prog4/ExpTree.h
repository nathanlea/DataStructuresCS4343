#include <stdlib.h>

class expTree {
	expTree* parent = NULL;
	expTree* leftChild = NULL;
	expTree* rightChild = NULL;

	char value = '?';
public:
	bool hasLeft = false;
	bool hasRight = false;
	expTree* getLeftChild();
	expTree* getRightChild();
	void getParent(expTree* par);
	expTree* getParent();
	void setValue(char input);
	char getValue();
	void clearChildren();
	void setLeftChild(expTree* tree);
	void setRightChild(expTree* tree);
	void expTree::newLeftChild();
	void expTree::newRightChild();
};