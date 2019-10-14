// author: Yiang Lu
// ID: 190100771
#include "BinarySearchTree.h"
#include <iostream>
#include <functional>

BinarySearchTree::BinarySearchTree()
{
	root = nullptr;
}
BinarySearchTree::BinarySearchTree(node* tree)
{
	root = tree;
}
BinarySearchTree::~BinarySearchTree()
{
	std::function<void(node*)> TerminateTree = [&TerminateTree](node* tree)
	{
		if (tree == nullptr)
		{
			std::cout << "tree is terminated" << std::endl;
			return;
		}

		if (tree->left != nullptr)
		{
			TerminateTree(tree->left);
		}
		if (tree->right != nullptr)
		{
			TerminateTree(tree->right);
		}

		delete tree;
		tree = nullptr;
	};
	TerminateTree(root);
	std::cout << "~BinarySearchTree() finish" << std::endl;
	_CrtDumpMemoryLeaks();
}
void BinarySearchTree::Insert(int value)
{
	std::function<void(node **, int value)> Insert = [&Insert](node** tree, int value)
	{
		if (tree == nullptr)
		{
			std::cout << "tree pointer empty!" << std::endl;
			return;
		}
		if (*tree == nullptr)
		{
			*tree = new struct node();
			(*tree)->value = value;
			(*tree)->right = nullptr;
			(*tree)->left = nullptr;
			return;
		}

		value > (*tree)->value ? Insert(&(*tree)->right, value) : Insert(&(*tree)->left, value);
		/*
		if (value > (*tree)->value)
		{
			Insert(&(*tree)->right, value);
		}
		if (value <= (*tree)->value)
		{
			Insert(&(*tree)->left, value);
		}*/
	};
	Insert(&root, value);
}
void BinarySearchTree::Print()
{
	std::function<void(node*)> Print = [&Print](node* tree)
	{
		if (tree == nullptr)
		{
			std::cout << "tree is empty!" << std::endl;
			return;
		}

		if (tree->left != nullptr)
		{
			Print(tree->left);
		}
		std::cout << (tree->value) << " ";
		if (tree->right != nullptr)
		{
			Print(tree->right);
		}
	};
	Print(root);
}
bool BinarySearchTree::Search(const int value)
{
	node* ptr = root;
	while (ptr != nullptr)
	{
		if (ptr->value == value) return true;
		else
		{
			ptr = ptr->value > value ? ptr->left : ptr->right;
		}
	}
	return false;
}