/*
  This class is a Binary Search Tree
  @author Kartik Aggarwal
  @date 5/22/2018
*/
#pragma once
#include <iostream>
#include <string>

using namespace std;

template <class T>
	struct Node {
	T info;
	Node* left;
	Node* right;
	int counter =0 ;
};
template <class T>
#ifndef BST_H
#define BSH_H
class BST
{
protected:
	Node<T>* root;
	void preOrder(Node<T>*);
	void postOrder(Node<T>*);
	void inOrder(Node<T>*);
	bool search(T, Node<T>*);

public:
	BST();
	~BST();
	void preOrder() { preOrder(root); }
	void postOrder() { postOrder(root); }
	void inOrder() { inOrder(root); }
	bool search(T item) { search(item ,root); }
	void insert(T);
	void deleteTree(Node<T>*);

};


#endif // !BST_H