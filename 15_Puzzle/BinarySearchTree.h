// author: Yiang Lu
// ID: 190100771
#pragma once

struct node
{
	int value;
	node* left;
	node* right;
};

class BinarySearchTree
{
public:
	BinarySearchTree();
	BinarySearchTree(node* tree);
	~BinarySearchTree();
	void Insert(int value);
	void Print();
	bool Search(const int value);

private:
	node* root;
};