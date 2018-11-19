//--------------------------------------------------------------------
//
//  Laboratory 11                                            
//
//  Test program for the operations in the Expression Tree ADT
//
//--------------------------------------------------------------------

#include <iostream>
#include "exprtree.h"

using namespace std;

void main()
{
	while (true) {
		ExprTree testExpression;  // Test expression

		cout << endl << "Enter an expression in prefix form : ";

		testExpression.build();
		testExpression.showStructure();
		testExpression.expression();
		cout << " = " << testExpression.evaluate() << endl;

		cout << endl << "Clear the tree" << endl;
		testExpression.clear();
		testExpression.showStructure();
	}
}
