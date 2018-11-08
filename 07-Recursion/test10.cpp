//--------------------------------------------------------------------
//
//  Laboratory 10                                         test10.cpp
//
//  Test program for a set of recursive linked list functions
//
//--------------------------------------------------------------------

// Reads a list of characters and calls the specified recursive routine.

#include <iostream>
#include <Windows.h>
#include "listrec.cpp"
using namespace std;

void SetColor(int color)	// 글자색 변경
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
 
void main()
{
	List<char> testList;   // Test list
	char testElement;      // List element

	cout << endl << "Enter a list of characters : ";
	cin.get(testElement);
	while (testElement != '\n')
	{
		testList.insert(testElement);
		cin.get(testElement);
	}
	testList.showStructure();


	// ***** Pre-lab : Call a recursive routine by uncommenting the call you wish to execute.
	

	SetColor(10); cout << endl << "[ PART A ] : insertEnd " << endl; SetColor(7);
	testList.write();
	testList.insertEnd('!');
	cout << "Structure : ";	testList.showStructure();

	SetColor(10); cout << endl << "[ PART B ] : writeMirror " << endl; SetColor(7);
	testList.writeMirror();
	cout << "Structure : ";	testList.showStructure();

	SetColor(10); cout << endl << "[ PART C ] : reverse " << endl; SetColor(7);
	testList.reverse();
	cout << "Structure : ";	testList.showStructure();

	SetColor(10); cout << endl << "[ PART D ] : deleteEnd" << endl; SetColor(7);
	testList.deleteEnd();
	cout << "Structure : ";	testList.showStructure();

	SetColor(10); cout << endl << "[ PART E ] : length " << endl; SetColor(7);
	cout << "length = " <<  testList.length() << endl;
	cout << "Structure : ";	testList.showStructure();


	// ***** In-lab  
	

	SetColor(11); cout << endl << "[ PART A ] : iterReverse " << endl; SetColor(7);
	testList.iterReverse();
	cout << "Structure : ";	testList.showStructure();

	SetColor(11); cout << endl << "[ PART B ] : stackWriteMirror " << endl; SetColor(7);
	testList.stackWriteMirror();	
	cout << "Structure : ";	testList.showStructure();

	system("pause");
}