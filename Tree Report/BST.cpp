#include "stdafx.h"
#include "BST.h"

template <class T>
BST<T>::BST(){

	root = nullptr;

}

template <class T>
BST<T>::~BST(){
	deleteTree(root);
}

template <class T>
void BST<T>::preOrder(Node<T>* p) {
	if (p != nullptr) {
		cout << p->info << endl;
		preOrder(p->left);
		preOrder(p->right);
	}
}
template <class T>
void BST<T>::postOrder(Node<T>* p) {
	if (p != nullptr) {
		postOrder(p->left);
		postOrder(p->right);
		cout << p->info << endl;
	}

}

template <class T>
void BST<T>::inOrder(Node<T>* p) {
	if (p != nullptr) {
		inOrder(p->left);
		cout << p->info << endl;
		inOrder(p->right);
	}
}

template <class T>
bool BST<T>::search(T item, Node<T>* p) {

	if (p == nullptr)
		return false;
	if (p->info == item)
		return true;
	if (p->info < item)
		search(item, p->right);
	if (p->info > item)
		search(item, p->right);
}

template <class T>
void BST<T>::insert(T item) {

	Node<T>* temp = new Node<T>;

	temp->info = item;
	temp->left = temp->right = nullptr;
	

	if (root == nullptr)
		root = temp;
	else {
		Node<T>* p = root;
		Node<T>* r = nullptr;

		while (p != nullptr) {
			r = p;
			if (p->info == item) {
				p->counter += 1;
				return;
			}
			else if (p->info > item)
				p = p->left;
			else
				p = p->right;
		}

		if (r -> info < item)
			r->right = temp;
		else
			r->left = temp;
	}

}

template <class T>
void BST<T>::deleteTree(Node<T>* p) {

	if (p != nullptr) {

		if (p->left != nullptr)
			deleteTree(p->left);
		if (p->right != nullptr)
			deleteTree(p->right);

		delete p;

	}


}
