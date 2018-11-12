//--------------------------------------------------------------------
//
//  Laboratory 8                                           ListDbl.h
//
//  Class declarations for the circular, doubly linked list
//  implementation of the List ADT
//
//--------------------------------------------------------------------

template < class LE >
class List;
template < class LE >
class ListNode;


template < class LE >
class ListNode                 // Facilitator class for the List class
{
private:

	// Constructor
	ListNode (const LE &elem, ListNode *priorPtr, ListNode *nextPtr);

	// Data members
	LE			element;	// List element
	ListNode	*prior,		// Pointer to the previous element
				*next;		// Pointer to the next element

	friend class List<LE>;
};

//--------------------------------------------------------------------

template < class LE >
class List
{
public:
		
	List(int ignored = 0);	// Constructor	
	~List();				// Destructor

	// List manipulation operations
	void insert(const LE &newElement);		// Insert after cursor
	void remove();                          // Remove element
	void replace(const LE &newElement);		// Replace element
	void clear();                           // Clear list

	// List status operations
	int empty() const;                      // List is empty
	int full() const;                       // List is full

	// List iteration operations
	int gotoBeginning();                    // Go to beginning
	int gotoEnd();                          // Go to end
	int gotoNext();                         // Go to next element
	int gotoPrior();                        // Go to prior element
	LE getCursor() const;                   // Return element

	// Output the list structure -- used in testing/debugging
	void showStructure() const;

	// In-lab opertions
	void reverse();
	int length();
	int position();

private:

	// Data members
	ListNode<LE>	*head,     // Pointer to the beginning of the list
					*cursor;   // Cursor pointer
};