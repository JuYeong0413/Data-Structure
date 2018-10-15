//--------------------------------------------------------------------
//
//  Laboratory 6                                        queueArr.cpp
//
//  SOLUTION: Array implementation of the Queue ADT
//
//--------------------------------------------------------------------

#include <assert.h>
#include "queuearr.h"

//--------------------------------------------------------------------

template < class QE >
Queue<QE>::Queue(int maxNumber)

// Creates an empty queue. Allocates enough memory for maxNumber
// elements (defaults to defMaxQueueSize).

: maxSize(maxNumber),
front(-1),
rear(-1)
{
	// pre-lab (Array)
	maxSize = maxNumber + 1;
	front = maxSize - 1;
	rear = maxSize - 1;
	
	element = new QE[maxSize];

	for (int i = 0; i < maxSize; i++) {
		element[i] = NULL;
	}
}

//--------------------------------------------------------------------

template < class QE >
Queue<QE>:: ~Queue()

// Frees the memory used by a queue.

{
	// pre-lab (Array)
	delete[] element;
}

//--------------------------------------------------------------------

template < class QE >
void Queue<QE>::enqueue(const QE &newElement)

// Inserts newElement at the rear of a queue.

{
	// pre-lab (Array)
	if (full()) cout << "Failed -- Queue is full" << endl; // if queue is full
	else {
		rear = (rear + 1) % maxSize;
		element[rear] = newElement;
	}
}

//--------------------------------------------------------------------

template < class QE >
QE Queue<QE>::dequeue()

// Removes the least recently added (front) element from a queue and
// returns it.

{
	// pre-lab (Array)
	if (empty()) { // if queue is empty
		cout << "Failed -- ";
		return 0;
	}
	else {		
		front = (front + 1) % maxSize; // move front index
		QE temp = element[front];
		element[front] = NULL; // remove element
		return temp;
	}
}

//--------------------------------------------------------------------

template < class QE >
void Queue<QE>::clear()

// Removes all the elements from a queue.

{
	// pre-lab (Array)
	if (empty()) cout << "Queue is already empty" << endl;
	else {
		for (int i = 0; i <= rear; i++) {
			element[i] = NULL; // element 초기화
		}

		front = maxSize - 1; // front index 초기화
		rear = maxSize - 1; // rear index 초기화
	}
}

//--------------------------------------------------------------------

template < class QE >
int Queue<QE>::empty() const

// Returns 1 if a queue is empty. Otherwise, returns 0.

{
	// pre-lab (Array)
	if (front == rear) return 1;
	else return 0;
}

//--------------------------------------------------------------------

template < class QE >
int Queue<QE>::full() const

// Returns 1 if a queue is full. Otherwise, returns 0.

{
	return ((rear + 1) % maxSize == front);
}

//--------------------------------------------------------------------

template < class QE >
void Queue<QE>::showStructure() const

// Array implementation. Outputs the elements in a queue. If the
// queue is empty, outputs "Empty queue". This operation is intended
// for testing and debugging purposes only.

{
	int j;   // Loop counter

	if (empty())
		cout << "Empty queue" << endl;
	else
	{
		cout << "front = " << front << "  rear = " << rear << endl;
		cout << "  ";
		for (j = 0; j < maxSize; j++)
			cout << j << " ";
		cout << endl;

		// pre-lab (Array)
		cout << "| ";
		for (int i = 0; i < maxSize; i++)
			cout << element[i] << " "; // print queue element
		cout << endl;

	}
}
template < class QE >
void Queue<QE>::putFront(const QE &newDataItem)

// Inserts newDataItem at the front of a queue.
// The order of the preexisting data items is left unchanged.

{
	//In-Lab. 2
	if (full()) cout << "Queue is full" << endl; // if queue is full
	else {
		element[front] = newDataItem; // insert newDataItem
		front = (front + 8) % maxSize; // front에 insert 했으므로 front index 이동
	}
}

template < class QE >
QE Queue<QE>::getRear()

// Removes the most recently added (rear) data item from a queue and returns it.
// The remainder of the queue is left unchanged.

{
	//In-Lab. 2
	if (empty()) { // if queue is empty
		cout << "Failed -- ";
		return 0;
	}
	else {
		QE temp = element[rear];
		element[rear] = NULL; // remove element
		rear = (rear + 8) % maxSize; // rear에서 element를 remove 했으므로 rear index 이동
		return temp;
	}
}

template < class QE >
int Queue<QE>::getLength()

// Returns the number of data items in a queue.

{
	//In-Lab. 3
	int length; // length variable
	if (empty()) length = 0; // if queue is empty, length is zero
	else if (front >= rear) // front index가 rear index보다 같거나 클 때
		length = maxSize - (front - rear);
	else // front index가 rear index보다 작을 때
		length = rear - front;
	return length;
}
