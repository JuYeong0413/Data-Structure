#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include "bstree.cpp"
using namespace std;

class TestData
{
public:

	void setKey(string newKey)
	{
		keyField = newKey;
	}   // Set the key

	string key() const
	{
		return keyField;
	}   // Returns the key

private:

	string keyField; // Key for the element
};

//--------------------------------------------------------------------

int main()
{
	char str[100];
	char *input[3] = { NULL, };
	int loop = 0;
	string str1 = "";
	string str2 = "";
	string str3 = "";

	BSTree<TestData, string> testTree; // Test binary search tree
	TestData testElement1;             // Binary search tree element
	TestData testElement2;             // Binary search tree element

	while (true)
	{
		cin.getline(str, 100, '\n');
		char *ptr = strtok(str, " ");

		while (ptr != NULL) {
			input[loop] = ptr;
			loop++;
			ptr = strtok(NULL, " ");
		}

		if (input[0] != NULL) str1 = input[0];
		if (input[1] != NULL) str2 = input[1];
		if (input[2] != NULL) str3 = input[2];

		if (tolower(str1[0]) == 'p') { // Print
			for (int i = 0; i < str1[i]; i++) str1[i] = tolower(str1[i]);
			if (str1.compare("print") == 0) testTree.showStructure();
		}
		else if (tolower(str1[0]) == 'f') { // Fire
			for (int i = 0; i < str1[i]; i++) str1[i] = tolower(str1[i]);
			if (str1.compare("fire") == 0) {
				if (testTree.retrieve(str2, testElement1))
					testTree.remove(str2);
			}
		}
		else if (tolower(str2[0]) == 'h') { // Hire
			for (int i = 0; i < str2[i]; i++) str2[i] = tolower(str2[i]);
			if (str2.compare("hires") == 0) {
				testElement2.setKey(str3);
				if (testTree.retrieve(str1, testElement1))
					testTree.insert(testElement2);
			}
		}
		else if (testTree.empty()) { // 첫 번째 input
			testElement2.setKey(str1);
			testTree.insert(testElement2);
		}

		// 입력이 끝나면 초기화
		loop = 0;
		for (int i = 0; i < 3; i++) {
			input[i] = NULL;
		}
		str1 = "";
		str2 = "";
		str3 = "";
		testElement1.setKey("");
		testElement2.setKey("");
	}

	return 0;
}