#include "sort.h"

/* 선택 정렬 */
SortStats selectionSort(int a[], int n) {
    SortStats stats = {0, 0};

    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;

        for (int j = i + 1; j < n; j++) {
            stats.comparisons++;

            if (a[j] < a[minIndex]) {
                minIndex = j;
            }
        }

        if (minIndex != i) {
            int temp = a[i];
            a[i] = a[minIndex];
            a[minIndex] = temp;

            stats.moves += 3;
        }
    }

    return stats;
}


/* 삽입 정렬 */
SortStats insertionSort(int a[], int n) {
    SortStats stats = {0, 0};

    for (int i = 1; i < n; i++) {
        int key = a[i];
        stats.moves++;

        int j = i - 1;

        while (j >= 0) {
            stats.comparisons++;

            if (a[j] > key) {
                a[j + 1] = a[j];
                stats.moves++;
                j--;
            } else {
                break;
            }
        }

        a[j + 1] = key;
        stats.moves++;
    }

    return stats;
}


/* 칵테일 셰이커 정렬 */
SortStats cocktailShakerSort(int a[], int n) {
    SortStats stats = {0, 0};

    int start = 0;
    int end = n - 1;
    int swapped = 1;

    while (swapped) {
        swapped = 0;

        /* 왼쪽 -> 오른쪽 */
        for (int i = start; i < end; i++) {
            stats.comparisons++;

            if (a[i] > a[i + 1]) {
                int temp = a[i];
                a[i] = a[i + 1];
                a[i + 1] = temp;

                stats.moves += 3;
                swapped = 1;
            }
        }

        if (!swapped) {
            break;
        }

        end--;
        swapped = 0;

        /* 오른쪽 -> 왼쪽 */
        for (int i = end; i > start; i--) {
            stats.comparisons++;

            if (a[i - 1] > a[i]) {
                int temp = a[i - 1];
                a[i - 1] = a[i];
                a[i] = temp;

                stats.moves += 3;
                swapped = 1;
            }
        }

        start++;
    }

    return stats;
}
