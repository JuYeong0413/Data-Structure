//--------------------------------------------------------------------
//
//  Laboratory 12                                         test12.cpp
//
//  Test program for the operations in the Binary Search Tree ADT
//
//--------------------------------------------------------------------

#include <iostream>
#include "bstree.cpp"
using namespace std;
 

class TestData
{
public:

	void setKey(int newKey)
	{
		keyField = newKey;
	}   // Set the key

	int key() const
	{
		return keyField;
	}     // Returns the key

private:

	int keyField;                // Key for the element
};

//--------------------------------------------------------------------

void main()
{
	BSTree<TestData, int> testTree;   // Test binary search tree
	TestData testElement;            // Binary search tree element
	int inputKey;                    // User input key
	char cmd;                        // Input command

	cout << endl << "Commands:" << endl;
	cout << "  +key : Insert (or update) element" << endl;
	cout << "  ?key : Retrieve element" << endl;
	cout << "  -key : Remove element" << endl;
	cout << "  K    : Write keys in ascending order" << endl;
	cout << "  C    : Clear the tree" << endl;
	cout << "  E    : Empty tree?" << endl;
	cout << "  F    : Full tree?" << endl;
	cout << "  H    : Height of tree" << endl;
	cout << "  <    : Output less than the searchKey" << endl;
	cout << "  Q    : Quit the test program" << endl;
	cout << endl;

	do
	{
		testTree.showStructure();                     // Output tree

		cout << endl << "Command: ";                  // Read command
		cin >> cmd;
		if (cmd == '+' || cmd == '?' ||
			cmd == '-' || cmd == '<')
			cin >> inputKey;

		switch (cmd)
		{
		case '+':                                  // insert
			testElement.setKey(inputKey);
			cout << "Insert : key = " << testElement.key()
				<< endl;
			testTree.insert(testElement);
			break;

		case '?':                                  // retrieve
			if (testTree.retrieve(inputKey, testElement))
				cout << "Retrieved : key = "
				<< testElement.key() << endl;
			else
				cout << "Not found" << endl;
			break;

		case '-':                                  // remove
			if (testTree.remove(inputKey))
				cout << "Removed element" << endl;
			else
				cout << "Not found" << endl;
			break;

		case 'K': case 'k':                       // writeKeys
			cout << "Keys:" << endl;
			testTree.writeKeys();
			break;

		case 'C': case 'c':                       // clear
			cout << "Clear the tree" << endl;
			testTree.clear();
			break;

		case 'E': case 'e':                       // empty
			if (testTree.empty())
				cout << "Tree is empty" << endl;
			else
				cout << "Tree is NOT empty" << endl;
			break;

		case 'F': case 'f':                       // full
			if (testTree.full())
				cout << "Tree is full" << endl;
			else
				cout << "Tree is NOT full" << endl;
			break;

		case 'h': case 'H':
			cout << "Height of Tree: " << testTree.height() << endl;
			break;

		case 'Q': case 'q':                   // Quit test program
			break;

		case '<':
			cout << "Ouput less than " << inputKey << endl;
			testTree.writeLessThan(inputKey);
			break;

		default:                               // Invalid command
			cout << "Inactive or invalid command" << endl;
			break;
		}
	} while ((cmd != 'Q') && (cmd != 'q'));

}

