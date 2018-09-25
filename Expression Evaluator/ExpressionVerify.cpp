#include "stdafx.h"
#include "ExpressionVerify.h"

/**
* Constructor for class that sets expression into class
*/

ExpressionVerify::ExpressionVerify(string e)
{
	setExpression(e);
}

/** 
* Mutator for expression
* @param string respresentation of function
*/
void ExpressionVerify::setExpression(string e) {
	expr = "";
	for(int i = 0; i < e.length(); i++) { //handle whitespaces
		if (!isspace(e[i]))
			expr += e[i];
	}

}

/**
*
* Evaluates function until the using main for loop until expression ends
* The while loops empties the stack which should at this point only contain + or -
* @return value expressionn evaluates to

*/

double ExpressionVerify::getResult() {

	string tempr = ""; //used to construct multidigit numbers
	bool mult = false; //flag to signal stack to multiply right away

	for (int i = 0; i < expr.length(); i++) {
		evaluator(i, tempr, mult);
	}

	while (!nums.empty() && !oper.empty()) {
		addEvaluator();
	}
	
	return nums.top(); //value that remains on the top of the stack is the evaluation
}

/**
*
* Pushes items onto their respective stacks and evaluates * or / right away
*
* @param value of current position in string
* @param temp string variable that is used to handle multidigit numbers
* @param boolean flag that signifies multiplication
*
*/

void ExpressionVerify::evaluator(int &i, string &tempr, bool &mult) {
	if (i == 0 && expr[i] == '-') { // if negative number exists at the beginning of an expression
		tempr += expr[i];
		i++;
	}

	if (isdigit(expr[i])) {  // construct number to be pushed onto stack
		while (isdigit(expr[i])) {
			tempr += expr[i];
			i++;
		}

		nums.push(stoi(tempr)); // push number onto stack
		tempr = ""; // reset to be used for future numbers
		
	}
	
	if (mult) { // evaluates multiplication right away
		double temp = 0;

		if (expr[i] == '(') { // if there is a parenthesis rather than a number, paren has to be evaluated first
			oper.push(expr[i]);
			bool tmult = mult; //preserve the value of mult
			mult = false;
			while (expr[i] != ')') {
				i++;
				evaluator(i, tempr, mult);
			}
			mult = tmult;
			while (oper.top() != '(') {
				addEvaluator();
			}
			oper.pop();
		}
			
		temp = nums.top();
		nums.pop();

		if (oper.top() == '*')
			temp = nums.top() * temp;
		else if (oper.top() == '/') {
			if (temp == 0) {
				cout << "Cannot divide by zero, substituting 1\n";
				temp = 1;
			}
			temp = nums.top() / temp;
		}

		nums.pop();
		nums.push(temp);
		oper.pop();
		mult = false;

	}
	
	if (!isdigit(expr[i])) {
		if (expr[i] == '/' || expr[i] == '*')
			mult = true;

		if (i != 0 && !isdigit(expr[i - 1]) && expr[i] == '-') // handling negative numbers
			tempr += expr[i];

		else if (expr[i] == '(') {
			oper.push(expr[i]);
			while (expr[i] != ')') {
				i++;
				evaluator(i, tempr, mult);
			}
			while (oper.top() != '(') {
				addEvaluator();
			}
			oper.pop();
		}

		else if (expr[i] == '/' || expr[i] == '*' || expr[i] == '+' || expr[i] == '-')
			oper.push(expr[i]);
			
	}
}

/**
*
* Evaluates stack which should have just addition and subtraction operations left
*
*/
void ExpressionVerify::addEvaluator() {

	char o = oper.top();
	if (o == '+') {
		double temp = nums.top();
		nums.pop();
		temp += nums.top();
		nums.pop();
		nums.push(temp);
		oper.pop();
	}
	else if (o == '-') {
		double temp = nums.top();
		nums.pop();
		temp = nums.top() - temp;
		nums.pop();
		nums.push(temp);
		oper.pop();
	}
}


ExpressionVerify::~ExpressionVerify()
{
}
