#include "stdafx.h"
#include <iostream>
#include "ExpressionVerify.h"

using namespace std;

int main() {

	string expr = "";

	cout << "Enter your expression: ";
	getline(cin, expr);

	ExpressionVerify test(expr);

	cout << "The expression evaluates to " << test.getResult();

	return 0;

}