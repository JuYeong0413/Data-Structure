#include <assert.h>
#include "ListDbl.h"

template < class LE >
ListNode<LE>::ListNode(const LE &elem, ListNode<LE> *priorPtr, ListNode<LE> *nextPtr)
// ����Ʈ ��� ������. ����Ʈ�� ��� �� prior, next�� ����, element�� ����.
{
	element = elem;
	priorPtr = NULL;
	nextPtr = NULL;
}


//------------ Ŭ���� ������/ �Ҹ��� ------------------


template < class LE >
List<LE>::List(int ignored)
// ����Ʈ�� ������
// Constructor. Creates an empty list.
// The argument is provided for call compatibility with the array implementation and is ignored.
{
	head = NULL;
	cursor = NULL;
}


template < class LE >
List<LE>::~List()
// ����Ʈ�� �Ҹ���
// Destructor. Deallocates (frees) the memory used to store a list.
{
	clear();
}


//------------ List manipulation operations ------------------


template < class LE >
void List<LE>::insert(const LE &newElement)
// ����Ʈ ���� ����
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
			newItem->prior = cursor; // newItem�� ������ ���� cursor�� data item�� ����Ű���� ����
			newItem->next = cursor->next; // newItem�� ���� data item�� ����Ű���� ����
			cursor->next->prior = newItem; // cursor�� next�� prior�� newItem�� �ǵ��� ����
			cursor->next = newItem; // cursor�� next�� newItem�� �ǵ��� ����
			cursor = newItem; // move the cursor to newDataItem
		}
	}
}


template < class LE >
void List<LE>::remove()
// ����Ʈ ���� ����
// Removes the data item marked by the cursor from a list.
// If the resulting list is not empty, then moves the cursor to the data item
// that followed the deleted data item. If the deleted data item was at the end of the list,
// then moves the cursor to the beginning of the list.
{
	if (empty()) cout << "Failed -- list is empty" << endl;
	else {
		ListNode<LE>* cursorPtr = new ListNode<LE>(NULL, NULL, NULL);
		cursorPtr = cursor;

		if (head == cursor) { // list�� �� �� data item�� remove�ϴ� ���
			if (head->next == NULL) { // if there is only one data item in the list
				delete cursorPtr; // remove data item
				head = NULL;
				cursor = NULL;
			}
			else {
				cursor = cursor->next; // cursor�� �� ĭ �̵�
				head = cursor;
				cursorPtr->next = NULL;
				cursor->prior = NULL;
				delete cursorPtr; // remove data item
			}
		}
		else if (cursor->next == NULL) { // remove �Ϸ��� data item�� list�� �� ���� ���� ���
			cursor->prior->next = NULL;
			gotoBeginning(); // cursor�� ��ġ�� �� ������ �ű��.
			delete cursorPtr; // remove data item
		}
		else { // remove �Ϸ��� data item�� list�� �߰��� ���� ���
			cursor->prior->next = cursor->next;
			cursor->next->prior = cursor->prior;
			cursor = cursor->next; // cursor�� �� ĭ �̵�
			delete cursorPtr; // remove data item
		}
	}
}


template < class LE >
void List<LE>::replace(const LE &newElement)
// ����Ʈ ��� ��ü ����
// Replaces the dataItem marked by the cursor with newDataItem. The cursor remains at newDataItem.
{
	if (empty()) cout << "Failed -- list is empty" << endl;
	else {
		cursor->element = newElement;
	}
}


template < class LE >
void List<LE>::clear()
// ����Ʈ Ŭ���� ����
// Removes all the data items in a list.
{
	if (head == NULL) {
		cout << "List is already empty" << endl;
	}
	else {
		ListNode<LE>* tempPtr = new ListNode<LE>(NULL, NULL, NULL);
		cursor = head; // �պ��� remove �ϱ� ���� cursor�� ��ġ�� head�� �̵�

		while (cursor->next != NULL) {
			tempPtr = cursor;
			cursor = cursor->next; // ���� data item�� remove �ϱ� ���� cursor �̵�
			tempPtr->next = NULL;
			cursor->prior = NULL;
			delete tempPtr; // remove data item
		}

		head = NULL; // head �ʱ�ȭ
		cursor = NULL; // cursor �ʱ�ȭ
	}
}


//------------ List status operations ------------------


template < class LE >
int List<LE>::empty() const
// ����Ʈ�� ����ִ��� Ȯ��, ���̸� 1 �����̸� 0 ��ȯ
// Returns true if a list is empty. Otherwise, returns false.
{
	return (head == NULL);
}


template < class LE >
int List<LE>::full() const
// ����Ʈ�� ���� ���ִ��� Ȯ��, ���̸� 1 �����̸� 0 ��ȯ
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
// ����Ʈ �� ������ �̵�
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
// ����Ʈ �� �ڷ� �̵�
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
// ����Ʈ �������� �̵�
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
// ����Ʈ �������� �̵�
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
// ���� Ŀ���� ������
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
// Outputs the data items in a list. If the list is empty, outputs ��Empty list��.
// Note that this operation is intended for testing / debugging purposes only.
// It supports only list data items that are one of C++��s predefined data types(int, char, and so forth).
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

		while (location->element != NULL) { // location�� list�� ������ element���� �̵�
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

	while (location->element != cursor->element) { // location�� list�� cursor���� �̵�
		position++; // increase cursor position count

		if (location == cursor->next) break;
		else location = location->next;
	}

	return position;
}