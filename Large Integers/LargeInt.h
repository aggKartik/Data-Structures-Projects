/*
* This class is designed to hold a large integer
* It aggregates a doubly linked list where each node stores an individual digit
* @author Kartik Aggarwal
* @version 1.4
*/

#pragma once
#ifndef LARGEINT_H
#define LARGEINT_H
#include "stdafx.h"
#include "Dlist.h"

using namespace std;
class LargeInt
{
	friend std::ostream& operator<< (std::ostream&, LargeInt&);
	friend istream& operator>> (istream&, LargeInt&);
	
public:
	LargeInt();
	bool operator==(LargeInt&);
	LargeInt& operator+(LargeInt&);
	void display();
	
private:
	Dlist<int> number;

};
#endif

