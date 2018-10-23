#include <assert.h>
#include "ListDbl.h"

template < class LE >
ListNode<LE>::ListNode(const LE &elem, ListNode<LE> *priorPtr, ListNode<LE> *nextPtr)
// 리스트 노드 생성자. 리스트의 노드 간 prior, next를 지정, element를 삽입.
{
	element = elem;
	priorPtr = NULL;
	nextPtr = NULL;
}


//------------ 클래스 생성자/ 소멸자 ------------------


template < class LE >
List<LE>::List(int ignored)
// 리스트의 생성자
// Constructor. Creates an empty list.
// The argument is provided for call compatibility with the array implementation and is ignored.
{
	head = NULL;
	cursor = NULL;
}


template < class LE >
List<LE>::~List()
// 리스트의 소멸자
// Destructor. Deallocates (frees) the memory used to store a list.
{
	clear();
}


//------------ List manipulation operations ------------------


template < class LE >
void List<LE>::insert(const LE &newElement)
// 리스트 삽입 연산
// Inserts newDataItem into a list.
// If the list is not empty, then inserts newDataItem after the cursor.
// Otherwise, inserts newDataItem as the first(and only) data item in the list.
// In either case, moves the cursor to newDataItem.
{
	if (full()) cout << "Failed -- List is full" << endl;
	else {
		ListNode<LE>* newItem = new ListNode<LE>(newElement, NULL, NULL);

		if (empty()) { // if the list is empty, insert newDataItem as the first data item in the list
			head = newItem;
			cursor = head;
		}
		else if (cursor->next == NULL) { // insert newDataItem at the end of the list
			newItem->prior = cursor;
			cursor->next = newItem;
			cursor = newItem;
		}
		else { // insert newDataItem in the middle of the list
			newItem->prior = cursor; // newItem의 이전이 현재 cursor의 data item을 가리키도록 설정
			newItem->next = cursor->next; // newItem이 다음 data item을 가리키도록 설정
			cursor->next->prior = newItem; // cursor의 next의 prior이 newItem이 되도록 설정
			cursor->next = newItem; // cursor의 next가 newItem이 되도록 설정
			cursor = newItem; // move the cursor to newDataItem
		}
	}
}


template < class LE >
void List<LE>::remove()
// 리스트 제거 연산
// Removes the data item marked by the cursor from a list.
// If the resulting list is not empty, then moves the cursor to the data item
// that followed the deleted data item. If the deleted data item was at the end of the list,
// then moves the cursor to the beginning of the list.
{
	if (empty()) cout << "Failed -- list is empty" << endl;
	else {
		ListNode<LE>* cursorPtr = new ListNode<LE>(NULL, NULL, NULL);
		cursorPtr = cursor;

		if (head == cursor) { // list의 맨 앞 data item을 remove하는 경우
			if (head->next == NULL) { // if there is only one data item in the list
				delete cursorPtr; // remove data item
				head = NULL;
				cursor = NULL;
			}
			else {
				cursor = cursor->next; // cursor을 한 칸 이동
				head = cursor;
				cursorPtr->next = NULL;
				cursor->prior = NULL;
				delete cursorPtr; // remove data item
			}
		}
		else if (cursor->next == NULL) { // remove 하려는 data item이 list의 맨 끝에 있을 경우
			cursor->prior->next = NULL;
			gotoBeginning(); // cursor의 위치를 맨 앞으로 옮긴다.
			delete cursorPtr; // remove data item
		}
		else { // remove 하려는 data item이 list의 중간에 있을 경우
			cursor->prior->next = cursor->next;
			cursor->next->prior = cursor->prior;
			cursor = cursor->next; // cursor을 한 칸 이동
			delete cursorPtr; // remove data item
		}
	}
}


template < class LE >
void List<LE>::replace(const LE &newElement)
// 리스트 노드 교체 연산
// Replaces the dataItem marked by the cursor with newDataItem. The cursor remains at newDataItem.
{
	if (empty()) cout << "Failed -- list is empty" << endl;
	else {
		cursor->element = newElement;
	}
}


template < class LE >
void List<LE>::clear()
// 리스트 클리어 연산
// Removes all the data items in a list.
{
	if (head == NULL) {
		cout << "List is already empty" << endl;
	}
	else {
		ListNode<LE>* tempPtr = new ListNode<LE>(NULL, NULL, NULL);
		cursor = head; // 앞부터 remove 하기 위해 cursor의 위치를 head로 이동

		while (cursor->next != NULL) {
			tempPtr = cursor;
			cursor = cursor->next; // 다음 data item을 remove 하기 위해 cursor 이동
			tempPtr->next = NULL;
			cursor->prior = NULL;
			delete tempPtr; // remove data item
		}

		head = NULL; // head 초기화
		cursor = NULL; // cursor 초기화
	}
}


//------------ List status operations ------------------


template < class LE >
int List<LE>::empty() const
// 리스트가 비어있는지 확인, 참이면 1 거짓이면 0 반환
// Returns true if a list is empty. Otherwise, returns false.
{
	return (head == NULL);
}


template < class LE >
int List<LE>::full() const
// 리스트가 가득 차있는지 확인, 참이면 1 거짓이면 0 반환
// Returns true if a list is full. Otherwise, returns false.
{
	ListNode<LE>* location = new ListNode<LE>(NULL, NULL, NULL);
	if (location == NULL) return 1;
	else {
		delete location;
		return 0;
	}
}


//------------ List manipulation operations ------------------


template < class LE >
int List<LE>::gotoBeginning()
// 리스트 맨 앞으로 이동
// Moves the cursor to the beginning of the list.
{
	if (empty()) return 0;
	else {
		cursor = head;
		return 1;
	}
}


template < class LE >
int List<LE>::gotoEnd()
// 리스트 맨 뒤로 이동
// Moves the cursor to the end of the list.
{
	if (empty()) return 0;
	else {
		while (cursor->next != NULL) {
			cursor = cursor->next;
		}
		return 1;
	}
}


template < class LE >
int List<LE>::gotoNext()
// 리스트 다음으로 이동
// If the cursor is not at the end of a list, then moves the cursor to the next data item in
// the list and returns true. Otherwise, returns false.
{
	if (empty() || cursor->next == NULL) return false;
	else {
		cursor = cursor->next;
		return true;
	}
}


template < class LE >
int List<LE>::gotoPrior()
// 리스트 이전으로 이동
// If the cursor is not at the beginning of a list, then moves the cursor to the preceding
// data item in the list and returns true. Otherwise, returns false.
{
	if (empty() || cursor == head) return false;
	else {
		cursor = cursor->prior;
		return true;
	}
}


template < class LE >
LE List<LE>::getCursor() const
// 현재 커서를 가져옴
// Returns a copy of the data item marked by the cursor.
{
	if (head == NULL) {
		cout << "Failed -- List is empty" << endl;
		return false;
	}

	else return cursor->element;
}


//-----------------------------------------------------------


template < class LE >
void List<LE>::showStructure() const
// Output the list structure
// Outputs the data items in a list. If the list is empty, outputs “Empty list”.
// Note that this operation is intended for testing / debugging purposes only.
// It supports only list data items that are one of C++’s predefined data types(int, char, and so forth).
{
	if (empty()) cout << "Empty list" << endl;
	else {
		cout << "head item : " << head->element << endl;
		//cout << "cursor item : " << cursor->element << endl;

		ListNode<LE>* location = new ListNode<LE>(NULL, NULL, NULL);
		location = head;

		cout << "| ";
		while (location->element != NULL) {
			cout << location->element << " "; // print data item

			if (location->next == NULL) break;
			else location = location->next;
		}
		cout << endl;

		// print cursor
		location = head;
		cout << "  ";
		while (location != cursor) {
			cout << "  ";
			location = location->next;
		}
		cout << "^" << endl;
	}
}


//-----------------------------------------------------------


template < class LE >
void List<LE>::reverse()
// In-lab opertions
{
	if (empty()) cout << "Failed -- List is empty" << endl;
	else {
		ListNode<LE>* tempPtr = new ListNode<LE>(NULL, NULL, NULL);
		ListNode<LE>* headPtr = new ListNode<LE>(NULL, NULL, NULL);
		headPtr = head;
		
		while (headPtr != NULL) { // swap next and prior of nodes
			tempPtr = headPtr->prior;
			headPtr->prior = headPtr->next;
			headPtr->next = tempPtr;
			headPtr = headPtr->prior;
		}

		if (tempPtr != NULL) // check empty list and list with one node
			head = tempPtr->prior; // change head
	}
}

//-----------------------------------------------------------

template < class LE >
int List<LE>::length()
// In-lab opertions
{
	int length = 0; // length count
	
	if (empty()) length = 0;
	else {
		ListNode<LE>* location = new ListNode<LE>(NULL, NULL, NULL);
		location = head;

		while (location->element != NULL) { // location을 list의 마지막 element까지 이동
			length++; // increase length count

			if (location->next == NULL) break;
			else location = location->next;
		}
	}

	return length;
}

//-----------------------------------------------------------

template < class LE >
int List<LE>::position()
// In-lab opertions
{
	int position = 1; // cursor position count

	ListNode<LE>* location = new ListNode<LE>(NULL, NULL, NULL);
	location = head;

	while (location->element != cursor->element) { // location을 list의 cursor까지 이동
		position++; // increase cursor position count

		if (location == cursor->next) break;
		else location = location->next;
	}

	return position;
}