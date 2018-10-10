#include <iostream>
using namespace std;

template<class DT> //Forward declaration of the List class
class List;

template<class DT>
class ListNode	//Facilitator class for the List class
{
private:
	ListNode( const DT &nodeData, ListNode *nextPtr );

	//Data members
	DT dataItem; //List data item
	ListNode *next; //Pointer to the next list node

	friend class  List<DT>;
};

//------------------------

template<class DT>
class List
{
public:
	//Constructor
	List(int ignored = 0);
	//Destructor
	~List();
	//List manipulation operations
	void insertBefore(const DT &newDataItem)
		throw (logic_error); //Insert before cursor
	void insert(const DT &newData)
		throw ( bad_alloc ); //Insert after cursor
	void remove() 
		throw (logic_error);
	void replace(const DT &newData) 
		throw (logic_error);
	void clear();

	//List status operations
	bool isEmpty() const;
	bool isFull() const;

	//List iteration operations
	bool gotoBeginning() 
		throw(logic_error);
	bool gotoEnd() 
		throw(logic_error);
	bool gotoNext() 
		throw (logic_error);

	bool gotoPrior() 
		throw(logic_error);

	DT getCursor() const 
		throw (logic_error);

	//Output the list structure - used in testing/debugging
	void showStructure() const;

private:

	//Data members
	ListNode<DT> *head,		//Pointer to the beginning of the list
				 *cursor;	//Cursor pointer
};