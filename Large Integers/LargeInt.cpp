#include "stdafx.h"
#include "LargeInt.h"
#include "Dlist.cpp"

LargeInt::LargeInt()
{
	number;
}

ostream& operator<< (ostream& out, LargeInt& num) {

	//insert iterator here
	Node<int>* ptr = num.number.begin();
	while (ptr != nullptr) {
		out << ptr->info;
		ptr = ptr->next;
	}

	return out;
}

istream& operator>> (istream& in, LargeInt& num){

	char c = 'a';
	int temp = 0;
	if (in.peek() == '\n') //consume newline character
		in.get();
	while (in.peek() != '\n') {
		c = in.get();
		temp = c - 48;
		num.number.insertItemEnd(temp);
	}
   	
	return in;
}

void LargeInt::display() {
	number.display();
}

/*
 * This function checks if two LargeInt Objects contain the same value
 * @param LargeInt& otherp another LargeInt Object
 * @return true or false identfying if they are equivalent or not 
*/
bool LargeInt::operator==(LargeInt& otherp){
	bool found = false;
	if (otherp.number.getLength() != number.getLength())
		return false;
	else {

		Node<int>* p2 = otherp.number.begin();
		Node<int>* p1 = number.begin();


		while (p1 != nullptr && !found) {
			if (p1->info != p2->info)
				found = true;
			p1 = p1->next;
			p2 = p2->next;
		}
	}

	return !found;

}
/*
 * This function overloads the + operator for the LargeInt class
 * @param LargeInt& otherp another LargeInt object to be added
 * @return A LargeInt reference containing sum of two objects
 */

LargeInt& LargeInt::operator+(LargeInt& otherp) {

	LargeInt* x = new LargeInt;
	int temp = 0;
	int carry = 0;
	
	Node<int>* p1 = number.end();
	Node<int>* p2 = otherp.number.end();

	while (p1 != nullptr && p2 != nullptr) {

		temp = p1->info + p2->info + carry;

		if (temp >= 10) {
			x->number.insertItem(temp - 10);
			carry = 1;
		}
		else {
			x->number.insertItem(temp);
			carry = 0;
		}
		p1 = p1->previous;
		p2 = p2->previous;
	}

	// two while loops handle any remaining numbers on bottom or top list
	while (p1 != nullptr) {
		temp = p1->info + carry;
		if (temp >= 10) {
			x->number.insertItem(temp - 10);
			carry = 1;
		}
		else {
			x->number.insertItem(temp);
			carry = 0;
		}
		p1 = p1->previous;
	}

	while (p2 != nullptr) {
		temp = p2->info + carry;
		if (temp >= 10) {
			x->number.insertItem(temp - 10);
			carry = 1;
		}
		else {
			x->number.insertItem(temp);
			carry = 0;
		}
		p2 = p2->previous;
	}
	if(carry == 1)
	x->number.insertItem(carry);
	
	//cout << x;
	return *x;
}