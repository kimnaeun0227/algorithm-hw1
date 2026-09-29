#ifndef SORT_H
#define SORT_H

/* 정렬 과정에서 측정한 값 */
typedef struct {
    long long comparisons;
    long long moves;
} SortStats;

SortStats selectionSort(int a[], int n);
SortStats insertionSort(int a[], int n);
SortStats cocktailShakerSort(int a[], int n);

#endif /* SORT_H */
