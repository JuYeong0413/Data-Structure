//--------------------------------------------------------------------
//
//  Laboratory 5                                          stackarr.h
//
//  Class declaration for the array implementation of the Stack ADT
//
//--------------------------------------------------------------------

const int defMaxStackSize = 10;   // Default maximum stack size

template < class SE >
class Stack
{
public:

	// Constructor
	Stack(int maxNumber = defMaxStackSize);

	// Destructor
	~Stack();

	// Stack manipulation operations
	void push(const SE &newElement);	  // Push element
	SE pop();                             // Pop element
	void clear();                         // Clear stack

	// Stack status operations
	int empty() const;                    // Stack is empty
	int full() const;                     // Stack is full

	// Output the stack structure -- used in testing/debugging
	void showStructure() const;

private:

	// Data members
	int maxSize,   // Maximum number of elements in the stack
		top;       // Index of the top element
	SE *element;   // Array containing the stack elements
};
