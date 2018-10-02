//--------------------------------------------------------------------
//
//  Laboratory 5                                        stackarr.cpp
//
//  SOLUTION: Array implementation of the Stack ADT
//
//--------------------------------------------------------------------

#include <assert.h>
#include "stackarr.h"

//--------------------------------------------------------------------

template < class SE >
Stack<SE>::Stack(int maxNumber)
// Creates an empty stack. Allocates enough memory for maxNumber
// elements (defaults to defMaxStackSize).
: maxSize(maxNumber), top(-1)
{

	element = new SE[maxSize];
	for (int i = 0; i < maxSize; i++) {
		element[i] = NULL;
	}
	
}

//--------------------------------------------------------------------

template < class SE >
Stack<SE>:: ~Stack()
// Frees the memory used by a stack.
{
	
	delete[] element;
	
}

//--------------------------------------------------------------------

template < class SE >
void Stack<SE>::push(const SE &newElement)
// Inserts newElement onto the top of a stack.
{
	if (full()) { // if stack is full
		cout << "Stack is full" << endl;
	}
	else {
		top++;
		element[top] = newElement;
	}
}

//--------------------------------------------------------------------

template < class SE >
SE Stack<SE>::pop()
// Removes the topmost element from a stack and returns it.
{
	if (empty()) { // if stack is empty
		cout << "failed -- ";
		return 0;
	}
	else { // remove element
		SE temp = element[top];
		element[top] = NULL;
		top--;
		return temp;
	}
}

//--------------------------------------------------------------------

template < class SE >
void Stack<SE>::clear()
// Removes all the elements from a stack.
{
	for (int i = 0; i < top; i++) {
		element[i] = NULL;
	}
	top = -1; // reset top position to -1

}

//--------------------------------------------------------------------

template < class SE >
int Stack<SE>::empty() const
// Returns 1 if a stack is empty. Otherwise, returns 0.
{
	if (top == -1) return 1;
	else return 0;
}

//--------------------------------------------------------------------

template < class SE >
int Stack<SE>::full() const
// Returns 1 if a stack is full. Otherwise, returns 0.
{
	if (top == maxSize - 1) return 1;
	else return 0;
}

//--------------------------------------------------------------------

template < class SE >
void Stack<SE>::showStructure() const
// Array implementation. Outputs the elements in a stack. If the
// stack is empty, outputs "Empty stack". This operation is intended
// for testing and debugging purposes only.
{
	if (empty()) { // if stack is empty
		cout << "Empty stack" << endl;
	}
	else {
		for (int i = top; i >= 0; i--) { // print elements in the stack
			cout << element[i] << " ";
			if (i == top) cout << "<- top";
			cout << endl;
		}
		cout << "--" << endl;
	}

}