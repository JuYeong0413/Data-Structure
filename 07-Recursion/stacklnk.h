//--------------------------------------------------------------------
//
//  Laboratory 5                                          stacklnk.h
//
//  Class declarations for the linked list implementation of the
//  Stack ADT
//
//--------------------------------------------------------------------

template < class SE >
class Stack;
template < class SE >
class StackNode;

template < class SE >
class StackNode               // Facilitator class for the Stack class
{
private:

	// Constructor
	StackNode(const SE &elem, StackNode *nextPtr);

	// Data members
	SE element;         // Stack element
	StackNode *next;    // Pointer to the next element

	friend class Stack<SE>;
};

//--------------------------------------------------------------------

template < class SE >
class Stack
{
public:

	// Constructor
	Stack(int ignored = 0);

	// Destructor
	~Stack();

	// Stack manipulation operations
	void push(const SE &newElement);    // Push element
	SE pop();                             // Pop element
	void clear();                         // Clear stack

	// Stack status operations
	int empty() const;                    // Stack is empty
	int full() const;                     // Stack is full

	// Output the stack structure -- used in testing/debugging
	void showStructure() const;

	// In-lab operation
	Stack(const Stack &valueStack);     // Copy constructor

private:

	// Data member
	StackNode<SE> *top;   // Pointer to the top element
};