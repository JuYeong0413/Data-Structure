#include <assert.h>
#include "listrec.h"
#include "stacklnk.cpp"

template < class LE >
List<LE>::List(int ignored)
{
	head = NULL;
	cursor = NULL;
}

template < class LE >
List<LE>::~List()
{
	clear();
}

//--------------------------------------------------------------------

template < class LE >
void List<LE>::insert(const LE &newElement)
{
	ListNode<LE>* newItem = new ListNode<LE>(newElement, NULL);

	if (head == NULL) { // if the list is empty, insert newElement as the first data item in the list
		head = newItem;
		cursor = head;
	}
	else if (cursor->next == NULL) { // insert newElement at the end of the list
		cursor->next = newItem;
		cursor = newItem;
	}
	else { // insert newElement in the middle of the list
		newItem->next = cursor->next; // newItem이 다음 data item을 가리키도록 설정
		cursor->next = newItem; // cursor의 next data item이 newElement가 되도록 설정
		cursor = newItem; // move the cursor to newElement
	}
}

template < class LE >
void List<LE>::clear()
// Removes all the data items in a list.
{
	if (head == NULL) {
		cout << "List is already empty" << endl;
	}
	else {
		ListNode<LE>* tempPtr = new ListNode<LE>(NULL, NULL);
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

template < class LE >
void List<LE>::showStructure() const
{
	if (head == NULL) {
		cout << "Empty list" << endl;
	}
	else {
		ListNode<LE>* location = new ListNode<LE>(NULL, NULL);
		location = head;

		while (location->next != 0) {
			cout << location->element << " | "; // print data item
			location = location->next;
		}

		cout << location->element << endl; // print last data item
	}
}

template < class LE >
void List<LE>::write() const
// Outputs the data items in a list from beginning to end.
// Assumes that objects of type LE can be output to the cout stream.
{
	cout << "List : ";
	writeSub(head);
	cout << endl;
}

template < class LE >
void List<LE>::insertEnd(const LE &newElement)
// Inserts newDataItem at the end of a list. Moves the cursor to newDataItem.
{
	insertEndSub(head, newElement);
}

template < class LE >
void List<LE>::writeMirror() const
// Outputs the data items in a list from beginning to end and back again.
// Assumes that objects of type DT can be output to the cout stream.
{
	cout << "Mirror : ";
	writeMirrorSub(head);
	cout << endl;
}

template < class LE >
void List<LE>::reverse()
// Reverses the order of the data items in a list.
{
	reverseSub(0, head);
}

template < class LE >
void List<LE>::deleteEnd()
// Deletes the data item at the end of a list.
// Moves the cursor to the beginning of the list.
{
	deleteEndSub(head);
	cursor = head;
}

template < class LE >
int List<LE>::length() const
// Returns the number of data items in a list.
{
	return lengthSub(head);
}

//--------------------------------------------------------------------

template < class LE >
ListNode<LE>::ListNode(const LE &elem, ListNode *nextPtr)
{
	element = elem;
	next = nextPtr;
}

//--------------------------------------------------------------------

template < class LE >
void List<LE>::writeSub(ListNode<LE> *p) const
// Recursive partner of the write() function.
// Processes the sublist that begins with the node pointed to by p.
{
	if (p != 0)
	{
		cout << p->element; // print data item
		writeSub(p->next); // continue with next node
	}
}

template < class LE >
void List<LE>::insertEndSub(ListNode<LE> *&p, const LE &newElement)
// Recursive partner of the insertEnd() function.
// Processes the sublist that begins with the node pointed to by p.
{
	if (p != 0)
		insertEndSub(p->next, newElement); // continue searching
	else // end of list
	{
		p = new ListNode<LE>(newElement, 0); // insert newElement
		cursor = p; // move cursor
	}
}

template < class LE >
void List<LE>::writeMirrorSub(ListNode<LE> *p) const
// Recursive partner of the writeMirror() function.
// Processes the sublist that begins with the node pointed to by p.
{
	if (p != 0)
	{
		cout << p->element; // output data item (forward)
		writeMirrorSub(p->next); // continue with next node
		cout << p->element; // output data item (backward)
	}
}

template < class LE >
void List<LE>::reverseSub(ListNode<LE> *p, ListNode<LE> *nextP)
// Recursive partner of the reverse() function.
// Processes the sublist that begins with the node pointed to by nextP.
{
	if (nextP != 0)
	{
		reverseSub(nextP, nextP->next); // continue with next node
		nextP->next = p; // reverse link
	}
	else
		head = p; // move head to the end of the list
}

template < class LE >
void List<LE>::deleteEndSub(ListNode<LE> *&p)
// Recursive partner of the deleteEnd() function.
// Processes the sublist that begins with the node pointed to by p.
{
	if (p->next != 0)
		deleteEndSub(p->next); // continue looking for the last node
	else
	{
		delete p; // delete node
		p = 0; // set p to null
	}
}

template < class LE >
int List<LE>::lengthSub(ListNode<LE> *p) const
// Recursive partner of the getLength() function.
// Processes the sublist that begins with the node pointed to by p.
{
	int length; // length variable

	if (p == 0)
		length = 0; // end of list reached
	else
		length = (lengthSub(p->next) + 1); // number of nodes after this one + 1

	return length;
}

//--------------------------------------------------------------------

template < class LE >
void List<LE>::iterReverse()
{
	ListNode<LE> *a;
	ListNode<LE> *b;
	ListNode<LE> *c;

	a = 0;
	b = head; // set b to the head of the list.

	while (b != 0) { // reverse nodes
		c = b->next;
		b->next = a;
		a = b;
		b = c;
	}

	head = a;
}

template < class LE >
void List<LE>::stackWriteMirror() const
{
	Stack<ListNode<LE>*> *tempStack = new Stack<ListNode<LE>*>(); // Stack of pointers
	ListNode<LE> *p = new ListNode<LE>(NULL, NULL); // Iterates through list
	p = head; // set p to the head of the list.

	while (p != 0) // traverse list from first to last
	{
		tempStack->push(p);
		cout << p->element; // process the list node pointed to by p.
		p = p->next; // advance p to the next node in the list.
	}

	while (!tempStack->empty()) // traverse list from last to first
	{ 
		p = tempStack->pop();
		cout<< p->element; // process the list node pointed to by p.
	}

	cout << endl;
}