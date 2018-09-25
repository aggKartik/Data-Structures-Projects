/*
* This class is a doubly linked list implementation
* @author Kartik Aggarwal
* @version 2.0
*/


#pragma once
#ifndef DLIST_H
#define DLIST_H
template <class T>
struct Node {

	Node<T>* previous;
	T info;
	Node<T>* next;
};
template <class T>
class Dlist
{
private:
	Node<T> *first;
	int length;
	Node<T> *last;

public:
	Dlist();
	~Dlist();
	Dlist(const Dlist<T>&);
	Dlist<T> operator = (Dlist<T>&);
	void makeEmpty(Node<T>*);
	void insertItem(T); //insert at the front
	void insertItemEnd(T); //insert at the back
	void deleteItem(T);
	bool isEmpty() { return length == 0; }
	int getLength() { return length; }
	void display();
	Node<T>* begin() { return first; }
	Node<T>* end() { return last; }



	
};

#endif