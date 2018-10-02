//--------------------------------------------------------------------
//
//                                                       listarr.cpp
//
//  SOLUTION: Array implementation of the List ADT
//
//--------------------------------------------------------------------


#include "listarr.h"

using namespace std;

//--------------------------------------------------------------------

List::List(int maxNumber)

// Creates an empty list. Allocates enough memory for maxNumber
// data items (defaults to defMaxListSize).

: maxSize(maxNumber),
size(0),
cursor(-1)
{
	// pre-lab
	dataItems = new DataType[maxNumber]; 
	for (int i = 0; i < maxNumber; i++) {
		dataItems[i] = NULL;
	}
}

//--------------------------------------------------------------------

List:: ~List()

// Frees the memory used by a list.

{
	// pre-lab
	delete[] dataItems;
}

//--------------------------------------------------------------------

void List::insert(const DataType &newDataItem)
throw (logic_error)

// Inserts newDataItem after the cursor. If the list is empty, then
// newDataItem is inserted as the first (and only) data items in the
// list. In either case, moves the cursor to newDataItem.

{
	// pre-lab
	if (isFull()) { // if the list is full
		cout << "Failed -- List is full." << endl;
	}
	else { // insert newDataItem
		if (isEmpty()) cursor = -1; // remove로 list가 비워진 경우 cursor의 위치는 0이 되기 때문에
									// cursor의 위치를 제대로 맞춰주기 위함
		cursor++;
		dataItems[cursor] = newDataItem;
		size++; // increase size
	}
}

//--------------------------------------------------------------------

void List::remove() throw (logic_error)

// Removes the data items  marked by the cursor from a list. Moves the
// cursor to the next data item item in the list. Assumes that the
// first list data items "follows" the last list data item.

{
	// pre-lab
	if (isEmpty()) { // if the list is empty
		cout << "Failed -- List is empty." << endl;
	}
	else {
		if (cursor == size - 1) { // if the cursor is pointing the last element
			dataItems[cursor] = NULL; // remove the data item
			cursor = 0; // last list data item 다음은 first list data item이기 때문에
						// cursor을 0으로 옮겨준다.
		}
		else {
			dataItems[cursor] = NULL; // remove the data item
			for (int i = cursor; i < size - 1; i++) {
				// data item을 하나씩 앞으로 옮긴다.
				dataItems[i] = dataItems[i + 1];
				dataItems[i + 1] = NULL;
			}
		}

		size--; // decrease size
	}

}

//--------------------------------------------------------------------

void List::replace(const DataType &newDataItem)
throw (logic_error)

// Replaces the item marked by the cursor with newDataItem and
// leaves the cursor at newDataItem.

{
	// Requires that the list is not empty
	// pre-lab
	if (isEmpty()) { // if the list is empty
		cout << "Failed -- List is empty." << endl;
	}
	else { // replace the item
		dataItems[cursor] = newDataItem;
	}

}

//--------------------------------------------------------------------

void List::clear()

// Removes all the data items from a list.

{
	// pre-lab
	for (int i = 0; i < size; i++) { // remove all the data items from the list
		dataItems[i] = NULL;
	}
	size = 0; // reset size to zero
	cursor = -1; // reset cursor to zero

}

//--------------------------------------------------------------------

bool List::isEmpty() const

// Returns 1 if a list is empty. Otherwise, returns 0.

{
	// pre-lab
	if (size == 0) return 1;
	else return 0;
}

//--------------------------------------------------------------------

bool List::isFull() const

// Returns 1 if a list is full. Otherwise, returns 0.

{
	// pre-lab
	if (size == maxSize) return 1;
	else return 0;
}

//--------------------------------------------------------------------
 
int List::gotoBeginning() throw (logic_error)

// Moves the cursor to the beginning of the list.

{
	// pre-lab
	if (isEmpty()) return 0;
	else {
		cursor = 0;
		return 1;
	}

}



//--------------------------------------------------------------------

int List::gotoEnd() throw (logic_error)

// Moves the cursor to the end of the list.

{
	// pre-lab
	if (isEmpty()) return 0;
	else {
		cursor = size - 1;
		return cursor;
	}

}

//--------------------------------------------------------------------

bool List::gotoNext() throw (logic_error)

// If the cursor is not at the end of a list, then moves the
// cursor to the next item in the list and returns true. Otherwise,
// returns false.

{
	// pre-lab
	if (cursor == size - 1 || cursor == -1) {
		// if the cursor is at the end of the list or the list is empty
		return false;
	}
	else {
		cursor++; // move the cursor to the next item in the list
		return true;
	}

}

//--------------------------------------------------------------------

bool List::gotoPrior() throw (logic_error)

// If the cursor is not at the beginning of a list, then moves the
// cursor to the preceeding item in the list and returns true.
// Otherwise, returns false.

{
	// pre-lab
	if (cursor == 0 || cursor == -1) {
		// if the cursor is at the beginning of the list or the list is empty
		return false;
	}
	else {
		cursor--; // move the cursor to the preceeding item in the list
		return true;
	}

}

//--------------------------------------------------------------------

DataType List::getCursor() const throw (logic_error)

// Returns the item marked by the cursor.

{
	// pre-lab
	return dataItems[cursor];

}

//--------------------------------------------------------------------

void List::showStructure() const

// Outputs the data items in a list. If the list is empty, outputs
// "Empty list". This operation is intended for testing/debugging
// purposes only.

{
	// pre-lab
	if (size == 0) cout << "Empty list" << endl;
	else {
		cout << "list size : " << size << endl; // print list size
		cout << "cursor : " << cursor << endl; // print cursor position
		for (int i = 0; i < size; i++) { // print data items in the list
			cout << dataItems[i] << " ";
		}
		cout << endl;
	}

}
 
//--------------------------------------------------------------------


bool List::find(const DataType &searchDataItem) throw (logic_error)

// Searches a list for searchDataItem. Begins the search with the data item marked by the cursor.
// Moves the cursor through the list until either searchDataItem is found(returns true) or the end
// of the list is reached without finding searchDataItem(returns false).Leaves the cursor at the
// last data item visited during the search.

{
	// in-lab
	if (isEmpty()) {
		cout << "List is empty" << endl;
		return 0;
	}
	else {
		for (int i = cursor; i <= size; i++) {
			if (dataItems[i] == searchDataItem) { // if data item is found
				cursor = i; // cursor should point the data item.
				return 1;
			}
			else {
				cursor = i; // move the cursor to the data item visited
							// (cursor가 last data item visited에 위치해야 하기 때문에 계속 옮겨준다)
			}
		}
		return 0; // if data item is not found, return 0
	}
}
