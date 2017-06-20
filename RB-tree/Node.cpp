// ќписание методов класса Node

#include "stdafx.h"
#include "Node.h"

extern Node *rootNode;

Node::~Node()
{
	{ if (value != NULL) delete value; }
}

void Node::restoreR()
{
	if (parent == NULL)
	{
		color = 0;
		return;
	}
	if (parent->color == 0)
	{
		return;
	}
	if (parent->color == 1 && parent->getBrother()->color == 1)
	{
		parent->color = 0;
		parent->getBrother()->color = 0;
		parent->parent->color = 1;
		parent->parent->restoreR();
		return;
	}
	if (parent == parent->parent->rChild)
	{
		if (this == parent->lChild)
		{
			this->rotateRight();
			this->rotateLeft();
			color = 0;
			rChild->color = 1;
		}
		else
		{
			parent->rotateLeft();
			parent->color = 0;
			parent->lChild->color = 1;
		}
	}
	else if (parent == parent->parent->lChild)
	{
		if (this == parent->rChild)
		{
			this->rotateLeft();
			this->rotateRight();
			color = 0;
			lChild->color = 1;
		}
		else
		{
			parent->rotateRight();
			parent->color = 0;
			parent->rChild->color = 1;
		}
	}
}

void Node::restoreB()
{
	if (parent == NULL) return;
	else if (getBrother()->color)
	{
		if (this == parent->lChild)
		{
			getBrother()->rotateLeft();
			parent->color = 1;
			parent->parent->color = 0;
			restoreB();
		}
	}
	else
	{
		if (!getBrother()->lChild->color && !getBrother()->rChild->color)
		{
			parent->color = 0;
			getBrother()->color = 1;
			parent->restoreB();
		}
		else if (getBrother()->lChild->color && !getBrother()->rChild->color)
		{
			getBrother()->color = 1;
			getBrother()->lChild->color = 0;
			getBrother()->lChild->rotateRight();
			restoreB();
		}
		else
		{
			getBrother()->color = parent->color;
			getBrother()->rChild->color = 0;
			parent->color = 0;
			if (this == parent->lChild)
			{
				getBrother()->rotateLeft();
			}
			else
			{
				getBrother()->rotateRight();
			}
		}
	}
}

void Node::rotateLeft() // ѕоворот поддерева влево.
{
	Node *proxy = parent;

	if (parent->parent == NULL) // ≈сли родительский узел есть, находим в нем указатель на исходный узел и присваеваем ему значение правго подузла исходного узла.
	{
		rootNode = this;
	}
	else if (parent->parent->lChild == parent)
	{
		parent->parent->lChild = this;
	}
	else
	{
		parent->parent->rChild = this;
	}

	parent = parent->parent;
	proxy->parent = this;
	lChild->parent = proxy;
	proxy->rChild = lChild;
	lChild = proxy;
}

void Node::rotateRight()
{
	Node *proxy = parent;

	if (parent->parent == NULL) // ≈сли родительский узел есть, находим в нем указатель на исходный узел и присваеваем ему значение правго подузла исходного узла.
	{
		rootNode = this;
	}
	else if (parent->parent->lChild == parent)
	{
		parent->parent->lChild = this;
	}
	else
	{
		parent->parent->rChild = this;
	}

	parent = parent->parent;
	proxy->parent = this;
	rChild->parent = proxy;
	proxy->lChild = rChild;
	rChild = proxy;
}

Node* Node::getBrother()
{
	if (parent == NULL) return NULL;
	else if (parent->lChild == this) return parent->rChild;
	else return parent->lChild;
}

// ќткрытые методы.

bool Node::addKey(int key)
{
	if (value == NULL)
	{
		value = new int(key);
		color = 1;
		lChild = new Node();
		lChild->parent = this;
		rChild = new Node();
		rChild->parent = this;
		this->restoreR();
		return 1;
	}
	else if (key == *value) return 0;
	else
	{
		if (key > *value) return rChild->addKey(key);
		else return lChild->addKey(key);
	}

}

void Node::remove(int key)
{
	Node *proxy = NULL;
	bool proxyColor;
	int pkey = 0;

	if (value == NULL) return;
	if (key == *value)
	{
		if (lChild->value == NULL && rChild->value == NULL)
		{
			delete value;
			value = NULL;
			lChild = NULL;
			rChild = NULL;
			proxyColor = color;
			color = 0;
			if (!proxyColor) restoreB();
			return;
		}
		else if (lChild->value != NULL && rChild->value == NULL)
		{
			proxy = lChild;
			proxyColor = color;
			*value = *(lChild->value);
			color = lChild->color;
			rChild = lChild->rChild;
			lChild = lChild->lChild;
			lChild->parent = this;
			rChild->parent = this;
			proxy->~Node();
			if (!proxyColor) restoreB();
		}
		else if (rChild->value != NULL && lChild->value == NULL)
		{
			proxy = rChild;
			*value = *(rChild->value);
			color = rChild->color;
			lChild = lChild->lChild;
			rChild = lChild->rChild;
			lChild->parent = this;
			rChild->parent = this;
			proxy->~Node();
			if (!proxyColor) restoreB();
		}
		else
		{
			proxy = rChild;
			while (proxy->lChild->value != NULL) proxy = proxy->lChild;
			pkey = *value;
			*value = *(proxy->value);
			*(proxy->value) = pkey;
			proxy->remove(pkey);
			return;
		}
	}
	else if (key > *value) rChild->remove(key);
	else lChild->remove(key);
}

bool Node::search(int key)
{
	if (*value == NULL) return 0;
	else if (*value == key) return 1;
	else
	{
		if (key > *value) return rChild->search(key);
		else return lChild->search(key);
	}
}

void Node::output(std::ofstream &fout)
{
	if (parent == NULL)
	{
		fout << "digraph RBtree {" << std::endl;
		fout << *value;
		if (color) fout << " [color=red];" << std::endl;
		else fout << " [color=black];" << std::endl;
		lChild->output(fout);
		rChild->output(fout);
		fout << "}" << std::endl;
		fout.close();
	}
	else if (value == NULL)
	{
		if (this == parent->lChild)
		{
			fout << "lLeaffrom" << *(parent->value) << " [color=black];" << std::endl;
			fout << *(parent->value) << "->" << "lLeaffrom" << *(parent->value) << std::endl;
		}
		else
		{
			fout << "rLeaffrom" << *(parent->value) << " [color=black];" << std::endl;
			fout << *(parent->value) << "->" << "rLeaffrom" << *(parent->value) << std::endl;
		}
		
	}
	else
	{
		fout << *value;
		if (color) fout << " [color=red];" << std::endl;
		else fout << " [color=black];" << std::endl;
		fout << *(parent->value) << "->" << *value << ";" << std::endl;
		lChild->output(fout);
		rChild->output(fout);
	}
}
