#include "lnklist.h"
using namespace std;

template<class DT>
List<DT>::List(int ignored)
{
	// Constructor. Creates an empty list.
	// The argument is provided for call compatibility with the array implementation and is ignored.

	head = NULL;
	cursor = NULL;
	
}

//------------------------------------------------

template<class DT>
List<DT>::~List()
{
	// Destructor. Deallocates (frees) the memory used to store a list.
	
	clear();

}

//------------------------------------------------


template<class DT>
void List<DT>::insert(const DT &newData)
{
	// Inserts newDataItem into a list. If the list is not empty,
	// then inserts newDataItem after the cursor.
	// Otherwise, inserts newDataItem as the first (and only) data item in the list.
	// In either case, moves the cursor to newDataItem.
	
	if (isFull()) cout << "Failed -- list is full" << endl;
	else {
		ListNode<DT>* newItem = new ListNode<DT>(newData, NULL);

		if (isEmpty()) { // if the list is empty, insert newDataItem as the first data item in the list
			head = newItem;
			cursor = head;
		}
		else if (cursor->next == NULL) { // insert newDataItem at the end of the list
			cursor->next = newItem;
			cursor = newItem;
		}
		else { // insert newDataItem in the middle of the list
			newItem->next = cursor->next; // newItem이 다음 data item을 가리키도록 설정
			cursor->next = newItem; // cursor의 next data item이 newDataItem이 되도록 설정
			cursor = newItem; // move the cursor to newDataItem
		}
	}
}

//------------------------------------------------


template<class DT>
void List<DT>::remove()
{
	// Removes the data item marked by the cursor from a list.
	// If the resulting list is not empty,
	// then moves the cursor to the next data item that followed the deleted data item.
	// If the deleted data item was at the end of the list,
	// then moves the cursor to the beginning of the list.
	
	if (isEmpty()) cout << "Failed -- list is empty" << endl;
	else {
		ListNode<DT>* tempPtr1 = new ListNode<DT>(NULL, NULL);
		ListNode<DT>* tempPtr2 = new ListNode<DT>(NULL, NULL);
		tempPtr1 = head;
		tempPtr2 = cursor;

		if (head == cursor) { // list의 맨 앞 data item을 remove하는 경우
			if (head->next == NULL) { // if there is only one data item in the list
				delete tempPtr2; // remove data item
				head = NULL;
				cursor = NULL;
			}
			else {
				cursor = cursor->next; // cursor을 한 칸 이동
				head = cursor;
				tempPtr1->next = NULL;
				tempPtr2 = NULL;
				delete tempPtr2; // remove data item
			}
		}
		else if (cursor->next == NULL) { // remove 하려는 data item이 list의 맨 끝에 있을 경우
			while (tempPtr1->next != tempPtr2) { // tempPtr1이 cursor 앞의 data item을 가리키도록 한다.
				tempPtr1 = tempPtr1->next;
			}
			gotoBeginning(); // cursor의 위치를 맨 앞으로 옮긴다.
			tempPtr1->next = NULL;
			delete tempPtr2; // remove data item
		}
		else { // remove 하려는 data item이 list의 중간에 있을 경우
			while (tempPtr1->next != tempPtr2) { // tempPtr1이 cursor 앞의 data item을 가리키도록 한다.
				tempPtr1 = tempPtr1->next;
			}
			tempPtr1->next = tempPtr2->next; // tempPtr1이 cursor 다음의 data item을 가리키도록 한다.
			cursor = cursor->next; // cursor을 한 칸 이동
			tempPtr2->next = NULL;
			delete tempPtr2; // remove data item
		}
		
	}
}


//------------------------------------------------


template<class DT>
void List<DT>::replace(const DT &newData)
{
	// Replaces the data item marked by the cursor with newDataItem.
	// The cursor remains at newDataItem.

	if (isEmpty()) cout << "Failed -- list is empty" << endl;
	else {
		cursor->dataItem = newData;
	}
}

//------------------------------------------------


template<class DT>
void List<DT>::clear()
{
	// Removes all the data items in a list.
	if (head == NULL) {
		cout << "List is already empty" << endl;
	}
	else {
		ListNode<DT>* tempPtr = new ListNode<DT>(NULL, NULL);
		cursor = head; // 앞부터 remove 하기 위해 cursor의 위치를 head로 이동

		while (cursor->next != NULL) {
			tempPtr = cursor;
			cursor = cursor->next; // 다음 data item을 remove 하기 위해 cursor 이동
			tempPtr->next = NULL;
			delete tempPtr; // remove data item
		}

		head = NULL;
		cursor = NULL;
	}
}

//------------------------------------------------


template<class DT>
bool List<DT>::isEmpty() const
{
	// Returns true if a list is empty. Otherwise, returns false.

	if (head == NULL) return true;
	else return false;
}

//------------------------------------------------


template<class DT>
bool List<DT>::isFull() const
{
	// Returns true if a list is full. Otherwise, returns false.

	ListNode<DT>* location = new ListNode<DT>(NULL, NULL);
	if (location == NULL) return true;
	else {
		delete location;
		return false;
	}
}

//------------------------------------------------


template<class DT>
bool List<DT>::gotoBeginning()
{
	// Moves the cursor to the beginning of the list.
	
	if (isEmpty()) return false;
	else {
		cursor = head;
		return true;
	}
}

//------------------------------------------------


template<class DT>
bool List<DT>::gotoEnd()
{
	// Moves the cursor to the end of the list.

	if (isEmpty()) return false;
	else {
		while (cursor->next != NULL) {
			cursor = cursor->next;
		}
		return true;
	}
}

//------------------------------------------------


template<class DT>
bool List<DT>::gotoNext() 
{
	// If the cursor is not at the end of a list,
	// then moves the cursor to mark the next data item in the list and returns true.
	// Otherwise, returns false.

	if (isEmpty() || cursor->next == NULL) return false;
	else {
		cursor = cursor->next;
		return true;
	}
}

//------------------------------------------------


template<class DT>
bool List<DT>::gotoPrior()
{
	// If the cursor is not at the beginning of a list,
	// then moves the cursor to mark the preceding data item in the list and returns true.
	// Otherwise, returns false.

	if (isEmpty() || cursor == head) return false;
	else {
		ListNode<DT>* location = new ListNode<DT>(NULL, NULL);
		location = head;
		while (location->next != cursor) { // location이 cursor 전의 data item을 가리키도록 한다.
			location = location->next;
		}
		cursor = location;
		return true;
	}
}

//------------------------------------------------


template<class DT>
DT List<DT>::getCursor() const
{
	// Returns a copy of the data item marked by the cursor.
	if (head == NULL) {
		cout << "Failed -- List is empty" << endl;
		return false; // return 0
	}

	else return cursor->dataItem;
}

//------------------------------------------------


template<class DT>
void List<DT>::showStructure() const
{
	// Outputs the data items in a list.
	// If the list is empty, outputs "Empty list".
	// Note that this operation is intended for testing/debugging purposes only.
	// It supports only list data items that are one of C++'s predefined data types (int, char, and so forth).
	
	if (isEmpty()) cout << "Empty list" << endl;
	else {
		cout << "head item : " << head->dataItem << endl;
		//cout << "cursor item : " << cursor->dataItem << endl;
		
		ListNode<DT>* location = new ListNode<DT>(NULL, NULL);
		location = head;

		while (location->dataItem != NULL) {
			cout << location->dataItem << " "; // print data item

			if (location->next == NULL) break;
			else location = location->next;
		}
		cout << endl;
		
		// print cursor
		location = head;
		while (location != cursor) {
			cout << "  ";
			location = location->next;
		}
		cout << "^" << endl;
	}
}

//------------------------------------------------


template<class DT>
ListNode<DT>::ListNode(const DT &nodeData, ListNode *nextPtr)
{
	dataItem = nodeData;
	next = nextPtr;
}

//------------------------------------------------


template<class DT>
void List<DT>::insertBefore(const DT &newDataItem)
{
	// Inserts newDataItem into a list.
	// If the list is not empty, then inserts newDataItem immediately before the cursor.
	// Otherwise, inserts newDataItem as the first (and only) data item in the list.
	// In either case, moves the cursor to newDataItem.

	if (isFull()) cout << "Failed -- List is full" << endl;
	else if (isEmpty()) insert(newDataItem);
	else {
		ListNode<DT>* newItem = new ListNode<DT>(NULL, NULL);
		newItem->dataItem = newDataItem;

		if (head == cursor) { // 만약 newItem을 list의 맨 앞에 insert 하는 경우
			newItem->next = cursor;
			head = newItem;
		}
		else {
			ListNode<DT>* location = new ListNode<DT>(NULL, NULL);
			location = head;
			while (location->next != cursor) { // location이 cursor 전의 data item을 가리키도록 한다.
				location = location->next;
			}

			newItem->next = cursor; // newDataItem의 next data item이 cursor가 가리키는 data item으로 설정
			location->next = newItem; // cursor 전의 data item이 newDataItem을 가리키도록 설정
		}

		cursor = newItem; // move the cursor to newDataItem
	}
}