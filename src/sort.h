#ifndef SORT_H
#define SORT_H

/* 정렬 과정에서 측정한 값 */
typedef struct {
    long long comparisons;
    long long moves;
} SortStats;

/* 일반 정렬 함수 */
SortStats selectionSort(int a[], int n);
SortStats insertionSort(int a[], int n);
SortStats cocktailShakerSort(int a[], int n);


/* Stability 실험용 자료형
 * key: 실제 정렬 기준
 * tag: 정렬 전 원래 순서
 */
typedef struct {
    int key;
    int tag;
} Record;

/* Stability 실험용 정렬 함수 */
void selectionSortRecords(Record a[], int n);
void insertionSortRecords(Record a[], int n);
void cocktailShakerSortRecords(Record a[], int n);

/* 같은 key를 가진 원소들의 tag 순서가 유지되는지 검사 */
int isStable(const Record a[], int n);

#endif /* SORT_H */
