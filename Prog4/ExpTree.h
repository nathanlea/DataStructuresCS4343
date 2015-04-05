#include <stdlib.h>

class expTree {
	expTree* parent = NULL;
	expTree* leftChild = NULL;
	expTree* rightChild = NULL;
	int value = 0;
public:
	bool hasLeft = false;
	bool hasRight = false;
	bool num = false;
	expTree* getLeftChild();
	expTree* getRightChild();
	void setParent(expTree* par);
	expTree* getParent();
	void setValue(int input);
	int getValue();
	void clearChildren();
	void setLeftChild(expTree* tree);
	void setRightChild(expTree* tree);
        void newLeftChild();
	void newRightChild();
};
