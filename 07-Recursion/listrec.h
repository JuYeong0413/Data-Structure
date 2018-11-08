//--------------------------------------------------------------------
//
//  Laboratory 10                                          listrec.h
//
//  Class declarations for a partial linked list implementation of
//  the List ADT with additional recursive linked list functions
//
//--------------------------------------------------------------------

template < class LE > class ListNode;
template < class LE > class List;


template < class LE >
class ListNode                 // Facilitator class for the List class
{
private:

	// Constructor
	ListNode(const LE &elem, ListNode *nextPtr);

	// Data members
	LE element;        // List element
	ListNode *next;    // Pointer to the next element

	friend class List<LE>;
};

//--------------------------------------------------------------------

template < class LE >
class List
{
public:

	// Constructor
	List(int ignored = 0);

	// Destructor
	~List();

	// List manipulation functions
	void insert(const LE &newElement);      // Insert after cursor
	void clear();                             // Clear list

	// Output the list structure -- used in testing/debugging
	void showStructure() const;

	// Prelab functions
	void write() const;                       // Output list elements
	void insertEnd(const LE &newElement);     // Insert at end
	void writeMirror() const;                 // Mirror view of list
	void reverse();                           // Reverse list
	void deleteEnd();                         // Delete from end
	int length() const;                       // Length of list

	// Bridge functions
	void unknown1() const;                    // Bridge Exercise
	void unknown2();                          // Bridge Exercise

	// In-lab functions
	void iterReverse();                       // In-lab Exercise 1
	void stackWriteMirror() const;            // In-lab Exercise 1
	void cRemove();                           // In-lab Exercise 2
	void aBeforeb();                          // In-lab Exercise 3

private:

	// Recursive partners of the Prelab functions
	void writeSub(ListNode<LE> *p) const;
	void insertEndSub(ListNode<LE> *&p, const LE &newElement);
	void writeMirrorSub(ListNode<LE> *p) const;
	void reverseSub(ListNode<LE> *p, ListNode<LE> *nextP);
	void deleteEndSub(ListNode<LE> *&p);
	int lengthSub(ListNode<LE> *p) const;

	// Recursive partners of the Bridge functions
	void unknown1Sub(ListNode<LE> *p) const;
	void unknown2Sub(ListNode<LE> *&p);

	// Recursive partners of the In-lab functions
	void cRemoveSub(ListNode<LE> *&p);         // In-lab Exercise 2
	void aBeforebSub(ListNode<LE> *&p);        // In-lab Exercise 3

private:

	// Data members
	ListNode<LE> *head,     // Pointer to the beginning of the list
				 *cursor;   // Cursor pointer
};