#include <iostream>
#include "stdafx.h"
#include "Dlist.cpp"
#include "LargeInt.h"

using namespace std;

int main() {

	LargeInt x;
	LargeInt y;

	cout << "Enter first number: ";
	cin >> x;

	cout << "\nEnter second number: ";
	cin >> y;

	cout << endl;

	bool tr = x == y;
	cout << "Are both your numbers the name? 1 -yes 0 -no: " << tr << endl;

	cout << "First number: " << x << endl;
	cout << "Second number: " << y << endl;

	cout << "Both Added: " << (x + y);

	return 0;
}