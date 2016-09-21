#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H

#include <iostream>
using namespace std;

typedef enum {READ=0, BLACK=1}ColoType;
typedef struct _Node
{
	int key;
	ColoType color;
	struct _Node *leftchild,*rightchild,*parent;
	_Node(){};
	_Node(int i)
	{
		key = i;
		color = READ;
		leftchild = NULL;
		rightchild = NULL;
		parent = NULL;
	}
}Node;

class RBTree
{
private:
	Node *root;
	Node *Nil;
	int size;
public:
	RBTree();
	virtual ~RBTree();
	void InitRoot();
	Node* Insertch(int k);
	bool Insert(int k);
	bool Delete(int k);
	int GetSize();
	void Show();
private:
	void Empty();
	void Insert_fixup(Node *pNode);
	void Delete_fixup(Node *pNode);
	void LeftRotate(Node *PNode);
	void RightRotate(Node *pNode);
	void Empty(Node *pNode);
	void Swap(Node *pNode1, Node *pNode2);
	Node *first(Node *pNode);
	Node *next(Node *pNode);
};

#endif