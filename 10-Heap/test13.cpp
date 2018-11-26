//--------------------------------------------------------------------
//
//  Laboratory 13                                         test13.cpp
//
//  Test program for the operations in the Heap ADT
//
//--------------------------------------------------------------------

#include <iostream>
#include "heap.cpp"

using namespace std;
//--------------------------------------------------------------------
//
// Declaration for the heap element class
//

class TestData
{
public:

	void setPty(int newPty)
	{
		priority = newPty;
	}   // Set the priority

	int pty() const
	{
		return priority;
	}     // Returns the priority

private:

	int priority;                // Priority for the element
};

//--------------------------------------------------------------------

void main()
{
	Heap<TestData> testHeap(8);   // Test heap
	TestData testElement;         // Heap element
	int inputPty;                 // User input priority
	char cmd;                     // Input command

	cout << endl << "Commands:" << endl;
	cout << "  +pty : Insert element" << endl;
	cout << "  -    : Remove highest priority element" << endl;
	cout << "  C    : Clear the heap" << endl;
	cout << "  E    : Empty heap?" << endl;
	cout << "  F    : Full heap?" << endl;
	cout << "  L    : Write levels   (Inactive : In-lab Exercise 3)"
		<< endl;
	cout << "  Q    : Quit the test program" << endl;
	cout << endl;

	do
	{
		testHeap.showStructure();                     // Output heap

		cout << endl << "Command: ";                  // Read command
		cin >> cmd;
		if (cmd == '+')
			cin >> inputPty;

		switch (cmd)
		{
		case '+':                                  // insert
			testElement.setPty(inputPty);
			cout << "Insert : pty = " << testElement.pty()
				<< endl;
			testHeap.insert(testElement);
			break;

		case '-':                                  // removeMax
			testElement = testHeap.removeMax();
			cout << "Removed element : "
				<< " pty = " << testElement.pty() << endl;
			break;

		case 'C': case 'c':                       // clear
			cout << "Clear the heap" << endl;
			testHeap.clear();
			break;

		case 'E': case 'e':                       // empty
			if (testHeap.empty())
				cout << "Heap is empty" << endl;
			else
				cout << "Heap is NOT empty" << endl;
			break;

		case 'F': case 'f':                       // full
			if (testHeap.full())
				cout << "Heap is full" << endl;
			else
				cout << "Heap is NOT full" << endl;
			break;

		case 'Q': case 'q':                   // Quit test program
			break;

		default:                               // Invalid command
			cout << "Inactive or invalid command" << endl;
		}
	} while ((cmd != 'Q') && (cmd != 'q'));
}