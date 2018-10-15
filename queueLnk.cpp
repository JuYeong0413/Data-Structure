//--------------------------------------------------------------------
//
//  Laboratory 6                                        queueLnk.cpp
//
//  SOLUTION: Linked list implementation of the Queue ADT
//
//--------------------------------------------------------------------

#include <assert.h>
#include "queueLnk.h"

//--------------------------------------------------------------------

template < class QE >
QueueNode<QE>::QueueNode(const QE &elem, QueueNode<QE> *nextPtr)

// Creates a queue node containing element elem and next pointer
// nextPtr.

: element(elem),
next(nextPtr)
{
	next = NULL;
}

//--------------------------------------------------------------------

template < class QE >
Queue<QE>::Queue(int ignored)

// Creates an empty queue. Parameter is provided for compatability
// with the array implementation and is ignored.

: front(0),
rear(0)
{
	front = NULL;
	rear = NULL;
}

//--------------------------------------------------------------------

template < class QE >
Queue<QE>:: ~Queue()

// Frees the memory used by a queue.

{
	// pre-lab (Linked)
	clear();
}

//--------------------------------------------------------------------

template < class QE >
void Queue<QE>::enqueue(const QE &newElement)

// Inserts newElement at the rear of a queue.

{
	// pre-lab (Linked)
	if (full()) cout << "Failed -- Queue is full" << endl;
	else {
		QueueNode<QE>* newNode = new QueueNode<QE>(NULL, NULL);
		newNode->element = newElement;

		if (empty()) { // if queue is empty, insert newElement as the first element in the queue
			front = newNode;
		}
		else {
			rear->next = newNode; // newElement insert 하기 전의 rear의 next는 newNode를 point
		}

		rear = newNode; // rear should point newNode
	}
}

//--------------------------------------------------------------------

template < class QE >
QE Queue<QE>::dequeue()

// Removes the least recently (front) element from a queue and
// returns it.

{
	// pre-lab (Linked)
	if (empty()) {
		cout << "Failed -- ";
		return 0;
	}
	else {
		QueueNode<QE>* tempPtr = new QueueNode<QE>(NULL, NULL);
		QE item = NULL;
		tempPtr = front;
		item = front->element;

		if (front == rear) { // if there is only one element in the queue
			front = NULL;
			rear = NULL;
		}
		else { // if there is two or more element in the queue
			front = front->next; // move front pointer
		}

		tempPtr->next = NULL;
		delete tempPtr; // remove element

		return item;
	}
}

//--------------------------------------------------------------------

template < class QE >
void Queue<QE>::clear()

// Removes all the elements from a queue.

{
	// pre-lab (Linked)
	if (empty()) { // if queue is empty
		cout << "Queue is already empty" << endl;
	}
	else {
		QueueNode<QE>* tempPtr = new QueueNode<QE>(NULL, NULL);

		while (front != NULL) {
			tempPtr = front;
			front = front->next; // 다음 element를 remove 하기 위해 front 이동
			tempPtr->next = NULL;
			delete tempPtr; // remove element
		}

		front = NULL; // reset front pointer
		rear = NULL; // reset rear pointer
	}
}


//--------------------------------------------------------------------

template < class QE >
int Queue<QE>::empty() const

// Returns 1 if a queue is empty. Otherwise, returns 0.

{
	// pre-lab (Linked)
	if (front == NULL) return 1;
	else return 0;
}

//--------------------------------------------------------------------

template < class QE >
int Queue<QE>::full() const

{
	// pre-lab (Linked)
	QueueNode<QE>* newNode = new QueueNode<QE>(NULL, NULL);
	if (newNode == NULL) return true;
	else {
		delete newNode;
		return false;
	}
}

//--------------------------------------------------------------------

template < class QE >
void Queue<QE>::showStructure() const

// Linked list implementation. Outputs the elements in a queue. If
// the queue is empty, outputs "Empty queue". This operation is
// intended for testing and debugging purposes only.

{
	// pre-lab (Linked)
	if (empty()) cout << "Empty queue" << endl; // if queue is empty
	else {
		cout << "front element : " << front->element << endl; // print front element
		cout << "rear element : " << rear->element << endl; // print rear element

		QueueNode<QE>* location = new QueueNode<QE>(NULL, NULL);
		location = front;

		cout << "| ";
		while (location != rear->next) {
			cout << location->element << " "; // print element
			location = location->next;
		}

		cout << endl;
	}
}