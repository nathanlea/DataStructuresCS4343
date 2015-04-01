#include <stdlib.h>

class expTree {
	expTree* parent = NULL;
	expTree* leftChild = NULL;
	expTree* rightChild = NULL;
	char value = '?';
	int number = 0;
public:
	bool hasLeft = false;
	bool hasRight = false;
	bool num = false;
	expTree* getLeftChild();
	expTree* getRightChild();
	void getParent(expTree* par);
	expTree* setParent();
	void setValue(char input);
	char getValue();
	void setNumber(int input);
	int getNumber();
	void clearChildren();
	void setLeftChild(expTree* tree);
	void setRightChild(expTree* tree);
        void newLeftChild();
	void newRightChild();
};
