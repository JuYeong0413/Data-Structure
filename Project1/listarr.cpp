//--------------------------------------------------------------------
//
//                                                       listarr.cpp
//
//  SOLUTION: Array implementation of the List ADT
//
//--------------------------------------------------------------------


#include "listarr.h"
#include <string>

using namespace std;

//--------------------------------------------------------------------

List::List(int maxNumber)

// Creates an empty list. Allocates enough memory for maxNumber
// data items (defaults to defMaxListSize).

: maxSize(maxNumber),
size(0),
cursor(-1)
{
	dataItems = new DataType[maxNumber]; 
	for (int i = 0; i < maxNumber; i++) {
		dataItems[i] = "";
	}
}

//--------------------------------------------------------------------

List:: ~List()

// Frees the memory used by a list.

{
	delete[] dataItems;
}

//--------------------------------------------------------------------

void List::insert(const DataType &newDataItem)
throw (logic_error)

// Inserts newDataItem at the end of the list. If the list is empty, then
// newDataItem is inserted as the first (and only) data items in the
// list. In either case, moves the cursor to newDataItem.

{
	if (isFull()) { // if the list is full
		cout << "Failed -- List is full." << endl;
	}
	else { // insert newDataItem
		gotoEnd(); // moves the cursor to the end of the list
		cursor++;
		dataItems[cursor] = newDataItem;
		size++; // increase size
	}
}

//--------------------------------------------------------------------

void List::remove() throw (logic_error)

// Removes the data item marked by the cursor from a list. Moves the
// cursor to the next data item item in the list. Assumes that the
// first list data items "follows" the last list data item.

{
	if (isEmpty()) { // if the list is empty
		cout << "Failed -- List is empty." << endl;
	}
	else {
		if (cursor == size - 1) { // if the cursor is pointing the last element
			dataItems[cursor] = ""; // remove the data item
			cursor = 0; // last list data item ������ first list data item�̱� ������
						// cursor�� 0���� �Ű��ش�.
		}
		else {
			dataItems[cursor] = ""; // remove the data item
			for (int i = cursor; i < size - 1; i++) {
				// data item�� �ϳ��� ������ �ű��.
				dataItems[i] = dataItems[i + 1];
				dataItems[i + 1] = "";
			}
		}
		size--; // decrease size
	}
}

//--------------------------------------------------------------------

void List::clear()

// Removes all the data items from a list.

{
	for (int i = 0; i < size; i++) { // remove all the data items from the list
		dataItems[i] = "";
	}
	size = 0; // reset size to zero
	cursor = -1; // reset cursor to zero
}

//--------------------------------------------------------------------

bool List::isEmpty() const

// Returns 1 if a list is empty. Otherwise, returns 0.

{
	if (size == 0) return 1;
	else return 0;
}

//--------------------------------------------------------------------

bool List::isFull() const

// Returns 1 if a list is full. Otherwise, returns 0.

{
	if (size == maxSize) return 1;
	else return 0;
}

//--------------------------------------------------------------------
 
int List::gotoBeginning() throw (logic_error)

// Moves the cursor to the beginning of the list.

{
	if (isEmpty()) return 0;
	else {
		cursor = 0;
		return 1;
	}
}

//--------------------------------------------------------------------

int List::gotoEnd() throw (logic_error)

// Moves the cursor to the end of the list.

{
	if (isEmpty()) return 0;
	else {
		cursor = size - 1;
		return 1;
	}
}

//--------------------------------------------------------------------

bool List::gotoNext() throw (logic_error)

// If the cursor is not at the end of a list, then moves the
// cursor to the next item in the list and returns true. Otherwise, returns false.

{
	if (cursor == size - 1 || cursor == -1) {
		// if the cursor is at the end of the list or the list is empty
		return false;
	}
	else {
		cursor++; // move the cursor to the next item in the list
		return true;
	}

}

//--------------------------------------------------------------------

DataType List::getData() const throw (logic_error)

// Returns the item marked by the cursor.

{
	return dataItems[cursor];
}

//--------------------------------------------------------------------

void List::show() const

// Display the summary of address book
// Since the program should print number of birthdays in each of 12 months,
// this member function is called using bdayList.

{
	cout << "Total number of entries in the list: " << size << endl;
	if(!isEmpty()) {
		cout << "Number of birthdays in" << endl;

		int month[12] = { 0, }; // birthday month�� ��Ÿ���� �迭

		for (int i = 0; i < size; i++) { // bdayList�� ó������ Ž��
			string date = dataItems[i].substr(0, 2); // birthday �� month�� ���� data�� ����
			int monthNum = stoi(date); // string type�� integer type�� ��ȯ

			// monthNum�� ���� �ش� ���� ���� ������Ų��.
			// month �迭�� ���� birthday�� �ش� ���� ���ϴ� ����� ���� ��Ÿ����.
			// �迭�� index�� 0���� �����ϱ� ������ �迭�� month-1��°�� month�� ���� �����Ѵ�.
			switch (monthNum) {
			case 1: // 1��
				month[0]++;
				break;
			case 2: // 2��
				month[1]++;
				break;
			case 3: // 3��
				month[2]++;
				break;
			case 4: // 4��
				month[3]++;
				break;
			case 5: // 5��
				month[4]++;
				break;
			case 6: // 6��
				month[5]++;
				break;
			case 7: // 7��
				month[6]++;
				break;
			case 8: // 8��
				month[7]++;
				break;
			case 9: // 9��
				month[8]++;
				break;
			case 10: // 10��
				month[9]++;
				break;
			case 11: // 11��
				month[10]++;
				break;
			case 12: // 12��
				month[11]++;
				break;
			default:
				break;
			}
			
		}

		// ����� ���� �κ�
		for (int j = 0; j < 12; j++) { // month �迭 Ž��
			if (month[j] != 0) { // data�� �����ϴ� ��쿡�� ���
				// month �迭�� ����Ǿ� �ִ� ���� birthday�� �ش� ���� ���ϴ� ����� ���� ��Ÿ����.
				// �迭�� index�� 0���� �����ϱ� ������ �迭�� month-1��°�� data�� ����Ǿ� �ִ�.
				switch (j) {
				case 0: // 1��
					cout << "\t" << "January: " << month[j] << endl;
					break;
				case 1: // 2��
					cout << "\t" << "February: " << month[j] << endl;
					break;
				case 2: // 3��
					cout << "\t" << "March: " << month[j] << endl;
					break;
				case 3: // 4��
					cout << "\t" << "April: " << month[j] << endl;
					break;
				case 4: // 5��
					cout << "\t" << "May: " << month[j] << endl;
					break;
				case 5: // 6��
					cout << "\t" << "June: " << month[j] << endl;
					break;
				case 6: // 7��
					cout << "\t" << "July: " << month[j] << endl;
					break;
				case 7: // 8��
					cout << "\t" << "August: " << month[j] << endl;
					break;
				case 8: // 9��
					cout << "\t" << "September: " << month[j] << endl;
					break;
				case 9: // 10��
					cout << "\t" << "October: " << month[j] << endl;
					break;
				case 10: // 11��
					cout << "\t" << "November: " << month[j] << endl;
					break;
				case 11: // 12��
					cout << "\t" << "December: " << month[j] << endl;
					break;
				default:
					break;
				}
			}
		}
		cout << endl;
	}
}

//--------------------------------------------------------------------

bool List::find(const DataType &searchDataItem) throw (logic_error)

// Searches a list for searchDataItem. Begins the search from the front.
// Moves the cursor through the list until either searchDataItem is found(returns true) or the end
// of the list is reached without finding searchDataItem(returns false).
// Leaves the cursor at the last data item visited during the search.

{
	if (isEmpty()) { // if the list is empty
		return 0;
	}
	else {
		for (int i = 0; i <= size; i++) { // search data item from the front
			if (dataItems[i] == searchDataItem) { // if data item is found
				cursor = i; // cursor should point the data item.
				return 1;
			}
			else {
				cursor = i; // move the cursor to the data item visited
							// (cursor�� last data item visited�� ��ġ�ؾ� �ϱ� ������ ��� �Ű��ش�)
			}
		}
		return 0; // if data item is not found, return 0
	}
}

//--------------------------------------------------------------------

void List::moveCursor(int point)

// Move the list cursor to point

{
	cursor = point;
}

//--------------------------------------------------------------------

int List::getSize()

// Returns the size of the list

{
	return size;
}

//--------------------------------------------------------------------

int List::getIndex()

// Returns the cursor index

{
	return cursor;
}