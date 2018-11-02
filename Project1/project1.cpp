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
			cin.ignore();   // �Է� ���� ����
			cout << "Enter the name of the file: ";
			getline(cin, fileName);

			// �̹� �ҷ��� file�� �ִµ� ���� �ҷ����� ���, ������ list�� ��� clear��Ų �� data�� �޾ƿ´�.
			nameList.clear();
			phoneList.clear();
			bdayList.clear();

			openFile(fileName, nameList, phoneList, bdayList); // open file
			bdayList.show(); // display summary of address book
			break;

		case '+':			// Add entry
			cin.ignore();   // �Է� ���� ����
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
			cin.ignore();   // �Է� ���� ����
			cout << "Remove an entry:" << endl;
			cout << "Name: ";
			getline(cin, deleteName);
			removeEntry(deleteName, nameList, phoneList, bdayList); // remove entry
			saveFile(fileName, nameList, phoneList, bdayList); // save file
			bdayList.show(); // display summary of address book
			break;

		case 'W': case 'w': // Write to a file
			cin.ignore();   // �Է� ���� ����
			cout << "Enter the name of the file: ";
			getline(cin, newFile);
			saveFile(newFile, nameList, phoneList, bdayList); // write file
			cout << "The list is written into " << newFile << endl;
			break;

		case 'M': case 'm': // Select a month
			cin.ignore();   // �Է� ���� ����
			cout << "Enter the selected month: ";
			getline(cin, month);
			selectMonth(month, nameList, phoneList, bdayList); // month�� ������ �ִ� ������� ���� ���
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

	if (!fin) { // ���� ���� �߻���
		cout << "Cannot open " << file << ".txt" << endl;
	}

	int data = 0; // �о�� ������ �̸�, ����ó, ���� �� ��� �ش��ϴ��� �����ϱ� ����
	char buf[100]; // textfile���� �� �پ� �о���� ����

	while (fin.getline(buf, 100)) {
		data++;

		switch (data) { // ������ ù ���� �̸�, �ι�° ���� ����ó, ����° ���� �����̱� ������
						// data�� ���� ���� ������ ���� name list, phone list, birthday list�� insert�Ѵ�.
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
		if (buf[0] == '\0') { // �� ���� ������ �ִ� ��� �� ����� ����(�̸�, ����ó, ����)�� ���
			data = 0;		  // �Էµ� ���̱� ������ data�� ���� �ٽ� 0���� �ٲ��ش�.
		}
	}
	fin.close(); // close file
}

//--------------------------------------------------------------------

// Save file
void saveFile(string file, List &listOfName, List &listOfPhone, List &listOfBday)
{
	ofstream fout(file + ".txt"); // ������ open�Ѵ�. ������ ���� ����

								  // ���������� ���Ͽ� ���� ���� move list cursor to the beginning
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
	if (listOfName.find(name)) { // �ش� name�� ���� ����� nameList�� �ִ� ���
		int index = listOfName.getIndex(); // �ش� data�� �ִ� ��ġ�� index�� ���´�.

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

				   // �Է��� ���� ���� month ����
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

	int count = 0; // �ش� ���� ��ġ�ϴ� ������ ��
	for (int i = 0; i < listOfBday.getSize(); i++) { // bdayList ��ü Ž��
		listOfBday.moveCursor(i); // move cursor index
		string data = listOfBday.getData().substr(0, 2); // birthday �� month�� ���� data�� ����
		int monthNum = stoi(data); // string type�� integer type�� ��ȯ
		if (month == monthNum) { // �ش� ���� ��ġ�ϸ� count ����
			count++;
		}
	}

	cout << "Total number of birthdays in " << inputMonth << ": " << count << endl;

	// Print entry
	if (count != 0) { // �ش��ϴ� ���� ������ �ִ� ����� �ִ� ��쿡 ���
		for (int j = 0; j < listOfBday.getSize(); j++) { // bdayList ��ü Ž��
			listOfBday.moveCursor(j); // move cursor index
			string date = listOfBday.getData().substr(0, 2); // birthday �� month�� ���� data�� ����
			int monthNum = stoi(date); // string type�� integer type�� ��ȯ

			if (month == monthNum) { // �ش� ���� ��ġ�ϴ� entry ���
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