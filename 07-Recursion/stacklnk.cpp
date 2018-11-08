//--------------------------------------------------------------------
//
//  Laboratory 5                                        stacklnk.cpp
//
//  SOLUTION: Linked list implementation of the Stack ADT
//
//--------------------------------------------------------------------

#include <assert.h>
 
#include "stacklnk.h"

//--------------------------------------------------------------------

template < class SE >
StackNode<SE>::StackNode(const SE &elem, StackNode<SE> *nextPtr)

// Creates a stack node containing element elem and next pointer
// nextPtr.

: element(elem),
next(nextPtr)
{}

//--------------------------------------------------------------------

template < class SE >
Stack<SE>::Stack(int ignored)

// Creates an empty stack. The parameter is provided for compatability
// with the array implementation and is ignored.

: top(0)
{}

//--------------------------------------------------------------------

template < class SE >
Stack<SE>:: ~Stack()

// Frees the memory used by a stack.

{
	clear();
}

//--------------------------------------------------------------------

template < class SE >
void Stack<SE>::push(const SE &newElement)

// Inserts newElement onto the top of a stack.

{
	top = new StackNode<SE>(newElement, top);
	assert(top != 0);
}

//--------------------------------------------------------------------

template < class SE >
SE Stack<SE>::pop()

// Removes the topmost element from a stack and returns it.

{
	StackNode<SE> *p;   // Pointer to popped node
	SE temp;            // Temporarily stores popped element

	assert(top != 0);       // Requires that the stack is not empty

	temp = top->element;
	p = top;
	top = top->next;
	delete p;

	return temp;
}

//--------------------------------------------------------------------

template < class SE >
void Stack<SE>::clear()

// Removes all the elements from a stack.

{
	StackNode<SE> *p,      // Points to successive nodes
		*nextP;  // Stores pointer to next node
	p = top;
	while (p != 0)
	{
		nextP = p->next;
		delete p;
		p = nextP;
	}

	top = 0;
}

//--------------------------------------------------------------------

template < class SE >
int Stack<SE>::empty() const

// Returns 1 if a stack is empty. Otherwise, returns 0.

{
	return (top == 0);
}

//--------------------------------------------------------------------

template < class SE >
int Stack<SE>::full() const

// Returns 1 if a stack is full. Otherwise, returns 0. Cannot be
// done cleanly in generic C++ because there is sometimes overhead
// associated with a memory allocation.

{
	return 0;
}

//--------------------------------------------------------------------

template < class SE >
void Stack<SE>::showStructure() const

// Linked list implementation. Outputs the elements in a stack. If
// the stack is empty, outputs "Empty stack". This operation is
// intended for testing and debugging purposes only.

{
	StackNode<SE> *p;   // Iterates through the stack

	
	if (top == 0)
		cout << "Empty stack" << endl;
	else
	{
		cout << "top ";
		for (p = top; p != 0; p = p->next)
			
			cout << p->element << " ";
		cout << "bottom" << endl;
	}
}