#include <iostream>
using namespace std;

template<class DT> // Forward declaration of the List class
class List;

template<class DT>
class ListNode	// Facilitator class for the List class
{
private:
	ListNode( const DT &nodeData, ListNode *nextPtr );

	// Data members
	DT dataItem; // List data item
	ListNode *next; // Pointer to the next list node
	List<DT> *friendList; // List of friends

	friend class  List<DT>;
};

//------------------------

template<class DT>
class List
{
public:
	// Constructor
	List(int ignored = 0);
	// Destructor
	~List();
	// List manipulation operations
	void insert(const DT &newData)
		throw ( bad_alloc ); // Insert after cursor
	void remove() 
		throw (logic_error);
	void clear();

	// List status operations
	bool isEmpty() const;
	bool isFull() const;

	// List iteration operations
	bool gotoBeginning() 
		throw(logic_error);

	// Output the list structure - used in testing/debugging
	void showStructure() const;

	bool find(const DT &data) // Find data in the list
		throw (logic_error);

	void beFriend(const DT &data1, const DT &data2) // Command F
		throw (logic_error);

	void unFriend(const DT &data1, const DT &data2) // Command U
		throw (logic_error);

	void print(const DT &data); // Command L

	void check(const DT &data1, const DT &data2) // Command Q
		throw (logic_error);

private:

	// Data members
	ListNode<DT> *head,		// Pointer to the beginning of the list
				 *cursor;	// Cursor pointer
};