#ifndef __SORTING_H__
#define __SORTING_H__

#define MAX_SIZE 10
#define true 1
#define false 0

template <class LE>
class Sorting {
public:

	Sorting(LE *original); //Constructor
	~Sorting(); 

	int insertion_sort(int n); //Insertion sort, compare횟수 반환
	int quick_sort(int left, int right); //quick sort, compare횟수 반환
	int merge_sort(int left, int right); //merge sort, compare횟수 반환

	void copy_list(LE newList[], int n, int compare); //list를 복사, compare 변수는 항상 0으로 초기화
	void print_list(int left, int right); //list를 left에서 right까지만 출력

private:
	void merge(LE keyList[], int left, int mid, int right); //merge
	int quickPartition(LE keyList[], int left, int right); //quick sort partition

	LE *list; //정렬할 데이터 list
	int num_compare; //키 값 비교회수 카운트를 위한 변수
};




#endif