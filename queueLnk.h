//--------------------------------------------------------------------
//
//  Laboratory 6                                          queueLnk.h
//
//  Class declarations for the linked list implementation of the
//  Queue ADT
//
//--------------------------------------------------------------------

template < class QE >
class Queue;

template < class QE >
class QueueNode;

template < class QE >
class Queue
{
public:

	// Constructor
	Queue(int ignored = 0);

	// Destructor
	~Queue();

	// Queue manipulation operations
	void enqueue(const QE &newElement);    // Enqueue element
	QE dequeue();                            // Dequeue element
	void clear();                            // Clear queue

	// Queue status operations
	int empty() const;                       // Queue is empty
	int full() const;                        // Queue is full

	// Output the queue structure -- used in testing/debugging
	void showStructure() const;

private:

	// Data members
	QueueNode<QE> *front,   // Pointer to the front element
		*rear;    // Pointer to the rear element
};

template < class QE >
class QueueNode               // Facilitator class for the Queue class
{
private:

	// Constructor
	QueueNode(const QE &elem, QueueNode *nextPtr);

	// Data members
	QE element;          // Queue element
	QueueNode *next;     // Pointer to the next element

	friend class Queue<QE>;
};

//--------------------------------------------------------------------
