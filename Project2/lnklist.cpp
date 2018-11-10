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
		ListNode<DT>* tempPtr1 = new ListNode<DT>("", NULL);
		ListNode<DT>* tempPtr2 = new ListNode<DT>("", NULL);
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
void List<DT>::clear()
{
	// Removes all the data items in a list.
	if (head == NULL) {
		cout << "List is already empty" << endl;
	}
	else {
		ListNode<DT>* tempPtr = new ListNode<DT>("", NULL);
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

	ListNode<DT>* location = new ListNode<DT>("", NULL);
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
void List<DT>::showStructure() const
{
	// Outputs the data items in a list.
	// If the list is empty, outputs "Empty list".
	// Note that this operation is intended for testing/debugging purposes only.
	// It supports only list data items that are one of C++'s predefined data types (int, char, and so forth).
	
	if (isEmpty()) cout << "Empty list" << endl;
	else {
		//cout << "head item : " << head->dataItem << endl;
		//cout << "cursor item : " << cursor->dataItem << endl;
		
		ListNode<DT>* location = new ListNode<DT>("", NULL);
		location = head;

		while (location->dataItem != "") {
			cout << location->dataItem << " "; // print data item

			if (location->next == NULL) break;
			else location = location->next;
		}
		cout << endl;
	}
}

//------------------------------------------------


template<class DT>
ListNode<DT>::ListNode(const DT &nodeData, ListNode *nextPtr)
{
	dataItem = nodeData;
	next = nextPtr;
	friendList = new List<DT>();
}

//------------------------------------------------


template < class DT >
bool List<DT>::find(const DT &data)
{
	// Find data in the list

	bool found = false;
	ListNode<DT>* location = new ListNode<DT>("", NULL);
	location = head;

	while (location != NULL) { // search from the beginning
		if (location->dataItem == data) { // if data is found in the list
			cursor = location;
			found = true;
			break;
		}
		else location = location->next; // move cursor to the next data item
	}
	return found;
}

template < class DT >
void List<DT>::beFriend(const DT &data1, const DT &data2)
{
	// Command F

	if (data1 == data2) // if data1 and data2 are same
		return; // nothing happens

	if (!find(data1) || !find(data2)) { // if there is no data
		if (!find(data1)) cout << "Failed -- Cannot find " << data1 << " in the list" << endl;
		else if (!find(data2)) cout << "Failed -- Cannot find " << data2 << " in the list" << endl;
	}
	else if (find(data1) && find(data2)) {
		find(data1); // find data1 and move the cursor
		cursor->friendList->insert(data2); // add data2 to the list of data1's friendList
		find(data2); // find data2 and move the cursor
		cursor->friendList->insert(data1); // add data1 to the list of data2's friendList
		cout << data1 << " and " << data2 << " are now friends" << endl;
	}
}

template < class DT >
void List<DT>::unFriend(const DT &data1, const DT &data2)
{
	// Command U

	if (data1 == data2) // if data1 and data2 are same
		return; // nothing happens

	if (!find(data1) || !find(data2)) { // if there is no data
		if (!find(data1)) cout << "Failed -- Cannot find " << data1 << " in the list" << endl;
		else if (!find(data2)) cout << "Failed -- Cannot find " << data2 << " in the list" << endl;
	}
	else if (find(data1) && find(data2)) {
		find(data1); // find data1 and move the cursor
		cursor->friendList->find(data2); // find data2 from data1's friendList and move the cursor
		cursor->friendList->remove(); // remove data2
		find(data2); // find data2 and move the cursor
		cursor->friendList->find(data1); // find data1 from data2's friendList and move the cursor
		cursor->friendList->remove(); // remove data1
		cout << data1 << " and " << data2 << " are no longer friends" << endl;
	}
}

template < class DT >
void List<DT>::print(const DT &data)
{
	// Command L

	ListNode<DT> *person = new ListNode<DT>("", NULL);
	
	if (find(data)) {
		person = cursor;
		person->friendList->showStructure();
	}
	else { // if data is not in the list
		cout << "Failed -- Cannot find " << data << " from the list" << endl;
	}
}

template < class DT >
void List<DT>::check(const DT &data1, const DT &data2)
{
	// Command Q

	ListNode<DT> *person = new ListNode<DT>("", NULL);

	if (data1 == data2) // if data1 and data2 are same
		return; // nothing happens

	if (!find(data1) || !find(data2)) { // if there is no data
		if (!find(data1)) cout << "Failed -- Cannot find " << data1 << " in the list" << endl;
		else if (!find(data2)) cout << "Failed -- Cannot find " << data2 << " in the list" << endl;
	}
	else if (find(data1)) {
		person = cursor;
		if (person->friendList->find(data2)) cout << "Yes" << endl;
		else cout << "No" << endl;
	}
}