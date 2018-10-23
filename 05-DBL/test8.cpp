//--------------------------------------------------------------------
//
//  Laboratory 8                                           test8.cpp
//
//  Test program for the operations in the List ADT
//
//--------------------------------------------------------------------

#include <iostream>
#include "ListDbl.cpp"

using namespace std;

void main()
{
	List<char> testList;   // Test list
	char testElement;      // List element
	char cmd;              // Input command

	cout << endl << "Commands:" << endl;
	cout << "  +x  : Insert x after the cursor" << endl;
	cout << "  -   : Remove the element marked by the cursor" << endl;
	cout << "  =x  : Replace the element marked by the cursor with x" << endl;
	cout << "  @   : Display the element marked by the cursor" << endl;
	cout << "  <   : Go to the beginning of the list" << endl;
	cout << "  >   : Go to the end of the list" << endl;
	cout << "  N   : Go to the next element" << endl;
	cout << "  P   : Go to the prior element" << endl;
	cout << "  C   : Clear the list" << endl;
	cout << "  E   : Empty list?" << endl;
	cout << "  F   : Full list?" << endl;
	cout << "  R   : Reverse the list"<< endl;
	cout << "  #   : Display list size and cursor position"<< endl;
	cout << "  Q   : Quit the test program" << endl;
	cout << endl;

	do
	{
		testList.showStructure();                     // Output list

		cout << endl << "Command: ";                  // Read command
		cin >> cmd;
		if (cmd == '+' || cmd == '=')
			cin >> testElement;

		switch (cmd)
		{
		case '+':                                  // insert
			cout << "Insert " << testElement << endl;
			testList.insert(testElement);
			break;

		case '-':                                  // remove
			cout << "Remove the element marked by the cursor"
				<< endl;
			testList.remove();
			break;

		case '=':                                  // replace
			cout << "Replace the element marked by the cursor "
				<< "with " << testElement << endl;
			testList.replace(testElement);
			break;

		case '@':                                  // getCursor
			cout << "Element marked by the cursor is "
				<< testList.getCursor() << endl;
			break;

		case '<':                                  // gotoBeginning
			if (testList.gotoBeginning())
				cout << "Go to the beginning of the list" << endl;
			else
				cout << "Failed -- list is empty" << endl;
			break;

		case '>':                                  // gotoEnd
			if (testList.gotoEnd())
				cout << "Go to the end of the list" << endl;
			else
				cout << "Failed -- list is empty" << endl;
			break;

		case 'N': case 'n':                       // gotoNext
			if (testList.gotoNext())
				cout << "Go to the next element" << endl;
			else
				cout << "Failed -- either at the end of the list "
				<< "or the list is empty" << endl;
			break;

		case 'P': case 'p':                       // gotoPrior
			if (testList.gotoPrior())
				cout << "Go to the prior element" << endl;
			else
				cout << "Failed -- either at the beginning of the "
				<< "list or the list is empty" << endl;
			break;

		case 'C': case 'c':                       // clear
			cout << "Clear the list" << endl;
			testList.clear();
			break;

		case 'E': case 'e':                       // empty
			if (testList.empty())
				cout << "List is empty" << endl;
			else
				cout << "List is NOT empty" << endl;
			break;

		case 'F': case 'f':                       // full
			if (testList.full())
				cout << "List is full" << endl;
			else
				cout << "List is NOT full" << endl;
			break;

		case 'R': case 'r':                   // In-lab Exercise 2
			cout << "Reverse the list" << endl;
			testList.reverse();
			break;

		case '#':                              // In-lab Exercise 3
			cout << "size = " << testList.length();

			if (!testList.empty())
				cout << "  position = " << testList.position();

			cout << endl;
			break;

		case 'Q': case 'q':                   // Quit test program
			break;

		default:                               // Invalid command
			cout << "Inactive or invalid command" << endl;
		}
	} while (cmd != 'Q'  &&  cmd != 'q');
}
