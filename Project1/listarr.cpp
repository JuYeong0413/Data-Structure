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
			cursor = 0; // last list data item 다음은 first list data item이기 때문에
						// cursor을 0으로 옮겨준다.
		}
		else {
			dataItems[cursor] = ""; // remove the data item
			for (int i = cursor; i < size - 1; i++) {
				// data item을 하나씩 앞으로 옮긴다.
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

		int month[12] = { 0, }; // birthday month를 나타내는 배열

		for (int i = 0; i < size; i++) { // bdayList를 처음부터 탐색
			string date = dataItems[i].substr(0, 2); // birthday 중 month에 대한 data만 추출
			int monthNum = stoi(date); // string type을 integer type로 변환

			// monthNum에 따라 해당 월의 값을 증가시킨다.
			// month 배열의 값은 birthday가 해당 월에 속하는 사람의 수를 나타낸다.
			// 배열의 index는 0부터 시작하기 때문에 배열의 month-1번째에 month의 값을 저장한다.
			switch (monthNum) {
			case 1: // 1월
				month[0]++;
				break;
			case 2: // 2월
				month[1]++;
				break;
			case 3: // 3월
				month[2]++;
				break;
			case 4: // 4월
				month[3]++;
				break;
			case 5: // 5월
				month[4]++;
				break;
			case 6: // 6월
				month[5]++;
				break;
			case 7: // 7월
				month[6]++;
				break;
			case 8: // 8월
				month[7]++;
				break;
			case 9: // 9월
				month[8]++;
				break;
			case 10: // 10월
				month[9]++;
				break;
			case 11: // 11월
				month[10]++;
				break;
			case 12: // 12월
				month[11]++;
				break;
			default:
				break;
			}
			
		}

		// 출력을 위한 부분
		for (int j = 0; j < 12; j++) { // month 배열 탐색
			if (month[j] != 0) { // data가 존재하는 경우에만 출력
				// month 배열에 저장되어 있는 값은 birthday가 해당 월에 속하는 사람의 수를 나타낸다.
				// 배열의 index는 0부터 시작하기 때문에 배열의 month-1번째에 data가 저장되어 있다.
				switch (j) {
				case 0: // 1월
					cout << "\t" << "January: " << month[j] << endl;
					break;
				case 1: // 2월
					cout << "\t" << "February: " << month[j] << endl;
					break;
				case 2: // 3월
					cout << "\t" << "March: " << month[j] << endl;
					break;
				case 3: // 4월
					cout << "\t" << "April: " << month[j] << endl;
					break;
				case 4: // 5월
					cout << "\t" << "May: " << month[j] << endl;
					break;
				case 5: // 6월
					cout << "\t" << "June: " << month[j] << endl;
					break;
				case 6: // 7월
					cout << "\t" << "July: " << month[j] << endl;
					break;
				case 7: // 8월
					cout << "\t" << "August: " << month[j] << endl;
					break;
				case 8: // 9월
					cout << "\t" << "September: " << month[j] << endl;
					break;
				case 9: // 10월
					cout << "\t" << "October: " << month[j] << endl;
					break;
				case 10: // 11월
					cout << "\t" << "November: " << month[j] << endl;
					break;
				case 11: // 12월
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
							// (cursor가 last data item visited에 위치해야 하기 때문에 계속 옮겨준다)
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