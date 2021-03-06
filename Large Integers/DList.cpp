#include "stdafx.h"
#include "Dlist.h"
#include <iostream>
using namespace std;

template <class T>
Dlist<T>::Dlist() {

	length = 0;
	first = nullptr;
	last = nullptr;

}

template <class T>
Dlist<T>::Dlist(const Dlist& otherList){
	length = otherList.length;
	if (otherList.first == nullptr)
		first = last = nullptr;                       
	else
	{
		first = new Node<T>;
		first->info = otherList.first->info;
		Node<T>* tempOther = otherList.first->next;
		Node<T>* temp = first;
		while (tempOther != nullptr)
		{
			temp->next = new Node<T>;
			temp->next->info = tempOther->info;
			temp->next->previous = temp;
			temp = temp->next;                                      
			tempOther = tempOther->next;                            
		}
		last = temp;
		temp->next = nullptr;
	}
}


template <class T>
Dlist<T>::~Dlist() {

	makeEmpty(first);
}

template <class T>
void Dlist<T>::makeEmpty(Node<T>* p) {

	while (p != nullptr) {
		Node<T>* temp = p;
		p = p->next;
		delete temp;
		temp = nullptr;
	}
	last = nullptr;
	length = 0;
	first = nullptr;

}

/**
	This function inserts an Item at the start of a list
*/
template <class T>
void Dlist<T>::insertItem(T item) {
	
	Node<T>* temp = new Node<T>; //
	temp->info = item;           // Setup node that is to be inserted
	temp->previous = nullptr;    //
	temp->next = nullptr;        //
	

	if (first == nullptr) { //If list is empty
		first = temp;
		last = first;
		length++;
	}
	else {
		
		temp->next = first;
		first->previous = temp;
		last = first;
		first = temp;
		length++;
	}
}

/*
This function inserts an item at the end of a list
*/
template <class T>
void Dlist<T>::insertItemEnd(T item) {

	Node<T>* temp = new Node<T>; //
	temp->info = item;           // Setup node that is to be inserted
	temp->previous = nullptr;    //
	temp->next = nullptr;        //

	if(first == nullptr) {
		first = temp;
		last = first;
		length++;
	}
	else {
		temp->previous = last; 
		last->next = temp;
		last = temp;
		length++;
	}

}

template <class T>
void Dlist<T>::deleteItem(T item) {

	Node<T> *temp;

	Node<T> *p = first;

	if (p != nullptr && first->info == item) {
		temp = first;
		first = first->next;
		if (first->next != nullptr)
			first->next->previous = nullptr;
		if (first == last)
			last = nullptr;
		delete temp;
		length--;
	}
	else if (p != nullptr && last->info == item) {

		temp = last;
		last = temp->previous;
		temp->previous->next = nullptr;
		delete temp;
		length--;

	}
	else {
		bool found = false;
		while (p != nullptr && !found) {

			if (p->info == item) {
				temp = p;
				p->previous->next = p->next;
				p->next->previous = p->previous;
				delete temp;
				length--;
				found = true;
			}
			p = p->next;
		}
	}
}
/**
* This function displays all the elements of the doubly linked list	
*/
template <class T>
void Dlist<T>::display() {

	Node<T>* current = first;

	while (current != nullptr) {
		cout << current->info << " -> " << flush;
		current = current->next;
	}

}

template <class T>
Dlist<T> Dlist<T>::operator = (Dlist<T>& otherList) {

	makeEmpty(first);
	length = otherList.length;

	if (otherList.first == nullptr)
		first = last = nullptr;
	else
	{
		first = new Node<T>;
		first->info = otherList.first->info;
		Node<T>* tempOther = otherList.first->next;
		Node<T>* temp = first;
		while (tempOther != nullptr)
		{
			temp->next = new Node<T>;
			temp->next->info = tempOther->info;
			temp->next->previous = temp;
			temp = temp->next;
			tempOther = tempOther->next;
		}
		last = temp;
		temp->next = nullptr;
	}
	return *this;
}

template <class T>
ListIterator<Node<T>> Dlist<T>::IteratorInitFront()
{
	return ListIterator<Node<T>>(first);
}

template <class T>
ListIterator<Node<T>> Dlist<T>::IteratorEnd()
{
	return ListIterator<Node<T>>(last);
}

