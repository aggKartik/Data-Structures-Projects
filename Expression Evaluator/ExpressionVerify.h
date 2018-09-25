/**
* 
* This class evaluates an expression that is passed to it
* Example of expressions:
* (3 + 5) or 45*1+3-4/1 
* The program works with a combination of two essential functions:
*   the evaluator() function pushes items onto respective stacks and evaulatues all parenthesis and multiplications or divisions
*   the addEvaluator() function evaluates all plus or minuses remaining on the stack
*
* Any parenthesis are treated as mini-expressions therefore evaluator and addEvalulator are called for those cases
*
* @author Kartik Aggarwal
* @version 1.5 3/22/2018
*/

#include "stdafx.h"
#include <iostream>
#include <string>
#include <stack>
using namespace std;

#ifndef EXPRESSIONVERIFY_H
#define EXPRESSIONVERIFY_H
class ExpressionVerify
{
public:
	ExpressionVerify(string);
	~ExpressionVerify();
	void setExpression(string);
	double getResult();

private:
	stack<double> nums; //stack that hold's expression's values
	stack<char> oper; //stack that holds expression's operators
	string expr; //contains entire expression
	void evaluator(int &, string &, bool &);
	void addEvaluator(); 

};
#endif