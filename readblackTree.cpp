#include <iostream>
#include "readblackTree.h"

using namespace std;

RBTree::RBTree()
{
	root = NULL;
	Nil = NULL;
	size = 0;
}

RBTree::~RBTree()
{
	Empty(root);
	delete Nil;
	root = Nil = NULL;
}
void RBTree::InitRoot()
{
	Nil = new Node(-1);
	root = Nil;
	Nil->color = BLACK;
	root->parent = Nil;
}

Node *RBTree::first(Node *pNode)
{
	if(pNode == NULL || pNode == Nil)
	{
		return NULL;
	}
	while(pNode->leftchild != Nil)
	{
		pNode = pNode->leftchild;
	}
	return pNode;
}
Node *RBTree::next(Node *pNode)
{
	if(pNode->rightchild != Nil)
	{
		return first(pNode->rightchild);
	}
	else
	{
		Node *parent = pNode->parent;
		while(parent != Nil && parent->leftchild != pNode)
		{
			pNode = parent;
			parent = parent->parent;
		}
		return parent;
	}
}
void RBTree::Show()
{
	if(root == Nil)
	{
		return;
	}
	for(Node *p = first(root); p != Nil; p = next(p))
	{
		std::cout<<p->key<<"  ";
	}
	std::cout<<"\n";
}

int RBTree::GetSize()
{
	return size;
}

Node *RBTree::Insertch(int key)
{
	Node *pNode = root;
	if(pNode == Nil)
	{
		return NULL;
	}
	while(pNode != Nil)
	{
		if(pNode->key > key)
		{
			pNode = pNode->leftchild;
		}
		else if(pNode->key < key)
		{
			pNode = pNode->rightchild;
		}
		else
		{
			return pNode;		
		}
	}
	return NULL;
}
void RBTree::Swap(Node *pNode1, Node *pNode2)
{
	int tmp = pNode1->key;
	pNode1->key = pNode2->key;
	pNode2->key = tmp;
}
void RBTree::LeftRotate(Node *PNode)
{
	Node *parentNode = PNode->parent;
	Node *rightNode = PNode->rightchild;
	PNode->rightchild = rightNode->leftchild;
	if(rightNode->leftchild != Nil)
	{
		rightNode->leftchild->parent = PNode;
	}
	rightNode->parent = parentNode;
	PNode->parent = rightNode;
	if(parentNode == Nil)
	{
		root = rightNode;
	}
	else if(parentNode->leftchild == PNode)
	{
		parentNode->leftchild = rightNode;
	}
	else
	{
		parentNode->rightchild = rightNode;
	}
	rightNode->leftchild = PNode;

}
void RBTree::RightRotate(Node *pNode)
{
	Node *parentNode = pNode->parent;
	Node *leftNode = pNode->leftchild;
	pNode->leftchild = leftNode->rightchild;
	leftNode->rightchild->parent = pNode;
	leftNode->parent = parentNode;
	pNode->parent = leftNode;

	if(parentNode == Nil)
	{
		root = leftNode;
	}
	else if(parentNode->leftchild == pNode)
	{
		parentNode->leftchild = leftNode;
	}
	else
	{
		parentNode->rightchild = leftNode;
	}
	leftNode->rightchild = pNode;
}
bool RBTree::Insert(int k)
{
	Node*p = new Node(k);
	p->leftchild = Nil;
	p->rightchild = Nil;
	
	Node *pNode = root;
	Node *preNode = Nil;
	while(pNode != Nil)
	{
		preNode = pNode;
		if(pNode->key == k)
		{
			delete p;
			return false;
		}
		else if(pNode->key > k)
		{
			pNode = pNode->leftchild ;
		}
		else
		{
			pNode = pNode->rightchild;
		}
	}
	p->parent = preNode;
	if(preNode == Nil)
	{
		p->color = BLACK;
		root = p;
	}
	else
	{
		if(k < preNode->key)
		{
			preNode->leftchild = p;
		}
		else
		{
			preNode->rightchild = p;
		}
	}
	size++;
	Insert_fixup(p);
	return true;
}

void RBTree::Insert_fixup(Node *pNode)
{
	Node *uncleNode = NULL;
	Node *Gradparent = NULL;
	while(pNode->parent->color == READ)
	{
		Gradparent = pNode->parent->parent;
		if(pNode->parent == Gradparent->leftchild)
		{

			uncleNode = Gradparent->rightchild;
			if(uncleNode->color == READ)
			{
				pNode->parent->color = BLACK;
				uncleNode->color = BLACK;
				Gradparent->color = READ;
				pNode = Gradparent;
			}
			else
			{
				if(pNode == pNode->parent->rightchild)
				{
					pNode = pNode->parent;
					LeftRotate(pNode);
				}
				pNode->parent->color = BLACK;
				pNode->parent->parent->color = READ;
				RightRotate(pNode->parent->parent);
			}
		}
		else
		{
			uncleNode = Gradparent->leftchild;
			if(uncleNode->color == READ)
			{
				uncleNode->color = BLACK;
				pNode->parent->color = BLACK;
				Gradparent->color = READ;
				pNode = Gradparent;
			}
			else
			{
				if(pNode == pNode->parent->leftchild)
				{
					pNode = pNode->parent;
					RightRotate(pNode);
				}
				pNode->parent->color = BLACK;
				pNode->parent->parent->color = READ;
				LeftRotate(pNode->parent->parent);
			}
		}
	}
	root->color = BLACK;
}

bool RBTree::Delete(int k)
{
	Node *ptmp = NULL;
	Node *childNode = NULL;
	Node *preNode = NULL;
	if(root == Nil)
	{
		return false;
	}
	Node *pNode = Insertch(k);
	if(pNode == NULL)
	{
		return false;
	}
	preNode = pNode->parent;
	if(pNode->leftchild != Nil && pNode->rightchild != Nil)
	{
		ptmp = pNode->rightchild;
		while(ptmp->leftchild != Nil)
		{
			ptmp = ptmp->leftchild;
		}
		Swap(pNode,ptmp);
		childNode = ptmp->rightchild;
		if(childNode != Nil)
		{
			childNode->parent = ptmp->parent;
		}
		if(ptmp == ptmp->parent->leftchild)
		{
			ptmp->parent->leftchild = childNode;
		}
		else
		{
			ptmp->parent->rightchild = childNode;
		}
	}
	else if(pNode->leftchild == Nil && pNode->rightchild == Nil)
	{
		if(preNode == Nil)
		{
			delete root;
			root = Nil;
			size--;
			return true;
		}
		else
		{
			if(pNode == preNode->leftchild)
			{
				preNode->leftchild = Nil;
			}
			else
			{
				preNode->rightchild = Nil;
			}
			childNode = Nil;
			childNode->parent = preNode;
			ptmp = pNode;
		}
	}
	else
	{
		if (pNode->leftchild == Nil)
		{
			childNode = pNode->rightchild;
			childNode->parent = preNode;
		}
		else
		{
			childNode = pNode->leftchild;
			childNode->parent = preNode;
		}
		//if(preNode != Nil)
		{
			if(preNode->leftchild == pNode)
			{
				preNode->leftchild = childNode;
			}
			else
			{
				preNode->rightchild = childNode;
			}
		}
		ptmp = pNode;
	}
	if(ptmp->color == BLACK)
	{
		Delete_fixup(childNode);
	}
	if(ptmp->parent == Nil)
	{
		root = childNode;
	}
	delete ptmp;
	size--;
	return true;
}
void RBTree::Delete_fixup(Node *pNode)
{
	Node *pBroNode = NULL;
	while(pNode != root && pNode->color == BLACK)
	{
		if(pNode == pNode->parent->leftchild)
		{
			pBroNode = pNode->parent->rightchild;
			if(pBroNode->color == READ)
			{
				pBroNode->color = BLACK;
				pNode->parent->color = READ;
				LeftRotate(pNode->parent);
				pBroNode = pNode->parent->rightchild;
			}
			if(pBroNode->leftchild->color == BLACK && pBroNode->rightchild->color == BLACK)
			{
				pBroNode->color = READ;
				pNode = pNode->parent;
			}
			else
			{
				if(pBroNode->rightchild->color == BLACK)
				{
					pBroNode->leftchild->color = BLACK;
					pBroNode->color = READ;
					RightRotate(pBroNode);
					pBroNode = pNode->parent->rightchild;
				}
				pBroNode->color = pNode->parent->color;
				pNode->parent->color = BLACK;
				pBroNode->rightchild->color = BLACK;
				LeftRotate(pNode->parent);
				pNode = root;
			}
		}
		else
		{
			pBroNode = pNode->parent->leftchild;
			if(pBroNode->color == READ)
			{
				pBroNode->color = BLACK;
				pNode->parent->color = READ;
				RightRotate(pNode->parent);
				pBroNode = pNode->parent->leftchild;
			}
			if(pBroNode->leftchild->color == BLACK && pBroNode->rightchild->color == BLACK)
			{
				pBroNode->color = READ;
				pNode = pNode->parent;
			}
			else
			{
				if(pBroNode->leftchild->color == BLACK)
				{
					pBroNode->rightchild->color = BLACK;
					pBroNode->color = READ;
					LeftRotate(pBroNode);
					pBroNode = pNode->parent->leftchild;
				}
				pBroNode->color = pNode->parent->color;
				pNode->parent->color = BLACK;
				pBroNode->leftchild->color = BLACK;
				RightRotate(pNode->parent);
				pNode = root;
			}

		}
	}
	pNode->color = BLACK;
}
void RBTree::Empty(Node *pNode)
{
	if(pNode != Nil)
	{
		Empty(pNode->rightchild);
		Empty(pNode->leftchild);
		delete pNode;
	}
}
