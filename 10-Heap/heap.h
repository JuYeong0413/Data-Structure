//--------------------------------------------------------------------
//
//  Laboratory 13                                             heap.h
//
//  Class declaration for the array implementation of the Heap ADT
//
//--------------------------------------------------------------------

const int defMaxHeapSize = 10;    // Default maximum heap size

template < class HE >
class Heap
{
public:

	// Constructor
	Heap(int maxNumber = defMaxHeapSize);

	// Destructor
	~Heap();

	// Heap manipulation operations
	void insert(const HE &newElement);   // Insert element
	HE removeMax();                        // Remove max pty element
	void clear();                          // Clear heap

	// Heap status operations
	int empty() const;                     // Heap is empty
	int full() const;                      // Heap is full

	// Output the heap structure -- used in testing/debugging
	void showStructure() const;

private:

	// Recursive partner of the showStructure() function
	void showSubtree(int index, int level) const;

	// Data members
	int maxSize,   // Maximum number of elements in the heap
		size;      // Actual number of elements in the heap
	HE *element;   // Array containing the heap elements
};