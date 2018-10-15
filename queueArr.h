//--------------------------------------------------------------------
//
//  Laboratory 6                                          queueArr.h
//
//  Class declaration for the array implementation of the Queue ADT
//
//--------------------------------------------------------------------

const int defMaxQueueSize = 10;   // Default maximum queue size

template < class QE >
class Queue
{
public:

	// Constructor
	Queue(int maxNumber = defMaxQueueSize);

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
 
	void putFront(const QE &newDataItem); //Lab 2
	QE getRear(); //Lab 2
	int getLength(); //Lab 3

private:

	// Data members
	int maxSize,   // Maximum number of elements in the queue
		front,     // Index of the front element
		rear;      // Index of the rear element
	QE *element;   // Array containing the queue elements
};