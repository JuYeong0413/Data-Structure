#include "stackarr.cpp"
#include <iostream>
#include <cstring>
#include <cctype>
using namespace std;

#define _Maxname 20

int Calcul(char* postfix);							// this is function which calculate postfix
int main(void)
{
	while (true) {
		char post[_Maxname];						// this is array that allocated the character of postfix

		cout << "This is calculator" << endl;
		cout << "Please input the postfix: ";
		cin >> post;								// save the postfix on post array

		cout << "result: " << Calcul(post) << endl; // show the result
		cout << endl;
	}

	return 0;
}

int Calcul(char* postfix)
{
	Stack<char> calc(20);
	char op; // operator
	int a, b; // operands
	int result; // result value
	int i = 0; // loop
	
	do {
		if (postfix[i] >= '0' && postfix[i] <= '9') { // if the element is number,
			calc.push(postfix[i]);					  // then push the number to stack
		}
		else { // if the element is operator
			op = postfix[i];
			b = calc.pop() - '0'; // pop the number in the stack (change to integer type)
			a = calc.pop() - '0';

			switch (op) {
			case '+': // add
				result = a + b;
				break;
			case '-': // subtract
				result = a - b;
				break;
			case '*': // multiply
				result = a * b;
				break;
			case '/': // divide
				result = a / b;
				break;
			default:
				cout << "calculation error" << endl;
				break;
			}

			calc.push(result + '0'); // if operation is finished, push the result value to stack
		}							 // (change to character type)

		i++; // increase loop

	} while (postfix[i] != '\0'); // Å½»ö Á¾·á Á¶°Ç

	return calc.pop() - '0'; // return value (integer type)

}
