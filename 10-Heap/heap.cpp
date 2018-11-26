#include <assert.h>
#include "heap.h"

template < class HE >
Heap<HE>::Heap(int maxNumber = defMaxHeapSize)
// Constructor. Creates an empty heap.
// Allocates enough memory for a heap containing maxNumber data items.
{
	maxSize = maxNumber;
	size = 0;
	element = new HE[maxSize];
	for (int i = 0; i < maxSize; i++) {
		element[i].setPty(0);
	}
}

template < class HE >
Heap<HE>::~Heap()
// Destructor. Deallocates (frees) the memory used to store a heap.
{
	delete[] element;
}

template < class HE >
void Heap<HE>::insert(const HE &newElement)
// Inserts newDataItem into a heap. Inserts this data item as the bottom rightmost data
// item in the heap and moves it upward until the properties that define a heap are restored.
{
	if (full()) cout << "Full heap" << endl;
	else {
		
		element[size] = newElement; // 일단 array의 맨 마지막 index에 넣는다.

		int bottom = size;
		int parent = (bottom - 1) / 2;
		while (bottom > 0) {
			parent = (bottom - 1) / 2;
			if (element[parent].pty() < element[bottom].pty()) {
				HE temp;
				temp = element[parent];
				element[parent] = element[bottom];
				element[bottom] = temp;
			}
			bottom = (bottom - 1) / 2;
		}

		size++;
	}
}

template < class HE >
HE Heap<HE>::removeMax()
// Removes the data item with the highest priority (the root) from a heap and returns it.
// Replaces the root data item with the bottom rightmost data item and moves this data
// item downward until the properties that define a heap are restored.
{
	HE item;
	if (empty()) {
		cout << "Failed -- Empty heap" << endl;
		item.setPty(0);
	}
	else {
		item = element[0];
		element[0] = element[size - 1]; // bottom rightmost data를 root로 가져온다.
		element[size - 1].setPty(0);
		size--;
		
		int root = 0;
		int bottom = size - 1;
		int maxChild = 0;
		int rightChild, leftChild;
		leftChild = 2 * root + 1;
		rightChild = 2 * root + 2;

		while (leftChild <= bottom) {
			if (leftChild == bottom)
				maxChild = leftChild;
			else {
				if (element[leftChild].pty() <= element[rightChild].pty())
					maxChild = rightChild;
				else
					maxChild = leftChild;
			}

			if (element[root].pty() < element[maxChild].pty()) {
				HE temp;
				temp = element[root];
				element[root] = element[maxChild];
				element[maxChild] = temp;
			}

			root = 2 * root + 1;
			leftChild = 2 * root + 1;
			rightChild = 2 * root + 2;
		}
	}

	return item;
}

template < class HE >
void Heap<HE>::clear()
// Removes all the data items in a heap.
{
	for (int i = 0; i < size; i++) {
		element[i].setPty(0);
	}

	size = 0;
}

template < class HE >
int Heap<HE>::empty() const
// Returns true if a heap is empty. Otherwise, returns false.
{
	return (size == 0);
}

template < class HE >
int Heap<HE>::full() const
// Returns true if a heap is full. Otherwise, returns false.
{
	return (size == maxSize);
}

template < class HE >
void Heap<HE>::showStructure() const
// Outputs the priorities of the data items in a heap in both array and tree form.
// The tree is output with its branches oriented from left(root) to right(leaves) -
// that is, the tree is output rotated counterclockwise 90 degrees from its conventional orientation.
// If the heap is empty, outputs "Empty heap".
// Note that this operation is intended for testing / debugging purposes only
{
	if (empty()) cout << "Empty heap" << endl;
	else {
		cout << endl << "size = " << size << endl;

		for (int i = 0; i < maxSize; i++) {
			cout << i << "\t";
		}
		cout << endl;
		
		for (int i = 0; i < size; i++) {
			cout << element[i].pty() << "\t";
		}
		cout << endl << endl;

		showSubtree(0, 0);
	}
}

//--------------------------------------------------------------------

template < class HE >
void Heap<HE>::showSubtree(int index, int level) const
{
	int i;

	if (index < maxSize) {
		if (element[index].pty() != 0) {
			showSubtree(2 * index + 2, level + 1);

			for (i = 0; i < level; i++) {
				cout << '\t';
			}
			cout << " " << element[index].pty();
			if ((2 * index + 1) < maxSize && (2 * index + 2) < maxSize) {
				if ((element[2 * index + 1].pty() != 0) && (element[2 * index + 2].pty() != 0)) {
					cout << "<";
				}
				else if (element[2 * index + 2].pty() != 0) {
					cout << "/";
				}
				else if (element[2 * index + 1].pty() != 0) {
					cout << "\\";
				}
			}
			else {
				if ((2 * index + 2) == maxSize) {
					if (element[2 * index + 1].pty() != 0) {
						cout << "\\";
					}
				}
			}
			cout << endl;
			showSubtree(2 * index + 1, level + 1);
		}
	}
}