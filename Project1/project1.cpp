#include <iostream>
#include <fstream>
#include <string>
#include "listarr.h"
using namespace std;

// Function declarations
void openFile(string file, List &listOfName, List &listOfPhone, List &listOfBday);
void saveFile(string file, List &listOfName, List &listOfPhone, List &listOfBday);
void removeEntry(string name, List &listOfName, List &listOfPhone, List &listOfBday);
void selectMonth(string inputMonth, List &listOfName, List &listOfPhone, List &listOfBday);

int main()
{
	// lists of adress book(name, phone, birthday)
	List nameList(20);
	List phoneList(20);
	List bdayList(20);

	char cmd; // Input command
	string fileName, newFile; // File name

	string name;
	string phone;
	string birthday;

	string month;
	string deleteName;

	do
	{
		cout << endl << "Commands:" << endl;
		cout << "  R  : read from a file" << endl;
		cout << "  +  : add a new entry" << endl;
		cout << "  -  : remove an entry" << endl;
		cout << "  W  : write to a file" << endl;
		cout << "  M  : select a month" << endl;
		cout << "  Q  : quit the program" << endl;

		cin >> cmd;

		switch (cmd)
		{
		case 'R': case 'r': // Read from a file
			cin.ignore();   // 입력 버퍼 비우기
			cout << "Enter the name of the file: ";
			getline(cin, fileName);

			// 이미 불러온 file이 있는데 새로 불러오는 경우, 현재의 list를 모두 clear시킨 후 data를 받아온다.
			nameList.clear();
			phoneList.clear();
			bdayList.clear();

			openFile(fileName, nameList, phoneList, bdayList); // open file
			bdayList.show(); // display summary of address book
			break;

		case '+':			// Add entry
			cin.ignore();   // 입력 버퍼 비우기
			cout << "Add an entry:" << endl;
			cout << "Name: ";
			getline(cin, name);
			nameList.insert(name); // insert name in the list
			
			cout << "Phone: ";
			getline(cin, phone);
			phoneList.insert(phone); // insert phone in the list
			
			cout << "Birthday: ";
			getline(cin, birthday);
			bdayList.insert(birthday); // insert birthdy in the list

			saveFile(fileName, nameList, phoneList, bdayList); // save file
			bdayList.show(); // display summary of address book
			break;

		case '-':			// Remove entry
			cin.ignore();   // 입력 버퍼 비우기
			cout << "Remove an entry:" << endl;
			cout << "Name: ";
			getline(cin, deleteName);
			removeEntry(deleteName, nameList, phoneList, bdayList); // remove entry
			saveFile(fileName, nameList, phoneList, bdayList); // save file
			bdayList.show(); // display summary of address book
			break;

		case 'W': case 'w': // Write to a file
			cin.ignore();   // 입력 버퍼 비우기
			cout << "Enter the name of the file: ";
			getline(cin, newFile);
			saveFile(newFile, nameList, phoneList, bdayList); // write file
			cout << "The list is written into " << newFile << endl;
			break;

		case 'M': case 'm': // Select a month
			cin.ignore();   // 입력 버퍼 비우기
			cout << "Enter the selected month: ";
			getline(cin, month);
			selectMonth(month, nameList, phoneList, bdayList); // month에 생일이 있는 사람들의 정보 출력
			break;

		case 'Q': case 'q': // Quit the program
			break;

		default:			// Invalid command
			cout << "Invalid command" << endl;
		}

	} while (cmd != 'Q' && cmd != 'q');

	return 0;
}

//--------------------------------------------------------------------
// Function definitions

// Open file
void openFile(string file, List &listOfName, List &listOfPhone, List &listOfBday)
{
	ifstream fin(file + ".txt");

	if (!fin) { // 열기 오류 발생시
		cout << "Cannot open " << file << ".txt" << endl;
	}

	int data = 0; // 읽어온 정보가 이름, 연락처, 생일 중 어디에 해당하는지 구분하기 위함
	char buf[100]; // textfile에서 한 줄씩 읽어오기 위함

	while (fin.getline(buf, 100)) {
		data++;

		switch (data) { // 정보의 첫 줄은 이름, 두번째 줄은 연락처, 세번째 줄은 생일이기 때문에
						// data의 값을 통해 정보를 각각 name list, phone list, birthday list에 insert한다.
		case 1:
			listOfName.insert(buf); // insert name in the list
			break;
		case 2:
			listOfPhone.insert(buf); // insert phone in the list
			break;
		case 3:
			listOfBday.insert(buf); // insert birthday in the list
			break;
		default:
			break;
		}
		if (buf[0] == '\0') { // 한 줄의 공백이 있는 경우 한 사람의 정보(이름, 연락처, 생일)가 모두
			data = 0;		  // 입력된 것이기 때문에 data의 값을 다시 0으로 바꿔준다.
		}
	}
	fin.close(); // close file
}

//--------------------------------------------------------------------

// Save file
void saveFile(string file, List &listOfName, List &listOfPhone, List &listOfBday)
{
	ofstream fout(file + ".txt"); // 파일을 open한다. 없으면 새로 생성

								  // 순차적으로 파일에 쓰기 위해 move list cursor to the beginning
	listOfName.gotoBeginning();
	listOfPhone.gotoBeginning();
	listOfBday.gotoBeginning();

	// write the current list into the file by moving list cursor
	for (int i = 0; i < listOfName.getSize(); i++) {
		fout << listOfName.getData() << endl; // write name
		listOfName.gotoNext();
		fout << listOfPhone.getData() << endl; // write phone
		listOfPhone.gotoNext();
		fout << listOfBday.getData() << endl << endl; // write birthday
		listOfBday.gotoNext();
	}
	fout.close(); // close file
}

//--------------------------------------------------------------------

// Remove entry
void removeEntry(string name, List &listOfName, List &listOfPhone, List &listOfBday)
{
	if (listOfName.find(name)) { // 해당 name을 가진 사람이 nameList에 있는 경우
		int index = listOfName.getIndex(); // 해당 data가 있는 위치의 index를 얻어온다.

		listOfName.remove(); // remove data from nameList

		listOfPhone.moveCursor(index); // move cursor to index
		listOfPhone.remove(); // remove data item from phoneList

		listOfBday.moveCursor(index); // move cursor to index
		listOfBday.remove(); // remove data item from bdayList
	}

	else cout << "Cannot find the entry." << endl;
}

//--------------------------------------------------------------------

// Display list of the names and phone numbers of friends whose birthdays are within the month
void selectMonth(string inputMonth, List &listOfName, List &listOfPhone, List &listOfBday)
{
	int month = 0; // month variable

				   // 입력한 월에 따라 month 결정
	if (inputMonth.compare("January") == 0) month = 1;
	else if (inputMonth.compare("February") == 0) month = 2;
	else if (inputMonth.compare("March") == 0) month = 3;
	else if (inputMonth.compare("April") == 0) month = 4;
	else if (inputMonth.compare("May") == 0) month = 5;
	else if (inputMonth.compare("June") == 0) month = 6;
	else if (inputMonth.compare("July") == 0) month = 7;
	else if (inputMonth.compare("August") == 0) month = 8;
	else if (inputMonth.compare("September") == 0) month = 9;
	else if (inputMonth.compare("October") == 0) month = 10;
	else if (inputMonth.compare("November") == 0) month = 11;
	else if (inputMonth.compare("December") == 0) month = 12;

	int count = 0; // 해당 월과 일치하는 생일의 수
	for (int i = 0; i < listOfBday.getSize(); i++) { // bdayList 전체 탐색
		listOfBday.moveCursor(i); // move cursor index
		string data = listOfBday.getData().substr(0, 2); // birthday 중 month에 대한 data만 추출
		int monthNum = stoi(data); // string type을 integer type로 변환
		if (month == monthNum) { // 해당 월과 일치하면 count 증가
			count++;
		}
	}

	cout << "Total number of birthdays in " << inputMonth << ": " << count << endl;

	// Print entry
	if (count != 0) { // 해당하는 월에 생일이 있는 사람이 있는 경우에 출력
		for (int j = 0; j < listOfBday.getSize(); j++) { // bdayList 전체 탐색
			listOfBday.moveCursor(j); // move cursor index
			string date = listOfBday.getData().substr(0, 2); // birthday 중 month에 대한 data만 추출
			int monthNum = stoi(date); // string type을 integer type로 변환

			if (month == monthNum) { // 해당 월과 일치하는 entry 출력
				listOfName.moveCursor(j);
				cout << listOfName.getData() << endl; // print name
				listOfPhone.moveCursor(j);
				cout << listOfPhone.getData() << endl; // print phone
				listOfBday.moveCursor(j);
				cout << listOfBday.getData() << endl << endl; // print birthday
			}
		}
	}
}