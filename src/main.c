/* 실행: make run-c */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sort.h"

#define N 4000
#define DUPLICATE_RANGE 10

/* 배열 복사 */
void copyArray(int dest[], const int src[], int n) {
    for (int i = 0; i < n; i++) {
        dest[i] = src[i];
    }
}

/* 이미 정렬된 배열 생성 */
void makeSorted(int a[], int n) {
    for (int i = 0; i < n; i++) {
        a[i] = i;
    }
}

/* 역순 배열 생성 */
void makeReverse(int a[], int n) {
    for (int i = 0; i < n; i++) {
        a[i] = n - i;
    }
}

/* 무작위 배열 생성 */
void makeRandom(int a[], int n) {
    for (int i = 0; i < n; i++) {
        a[i] = rand();
    }
}

/* 중복 값이 많은 배열 생성 */
void makeDuplicates(int a[], int n) {
    for (int i = 0; i < n; i++) {
        a[i] = rand() % DUPLICATE_RANGE;
    }
}

/* 정렬이 제대로 되었는지 확인 */
int isSorted(const int a[], int n) {
    for (int i = 1; i < n; i++) {
        if (a[i - 1] > a[i]) {
            return 0;
        }
    }
    return 1;
}

/* 하나의 입력에 대해 세 알고리즘 실험 */
void runExperiment(const char *inputName, const int original[], int n) {
    int *a = malloc((size_t)n * sizeof(int));

    if (a == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    SortStats stats;
    clock_t start;
    clock_t end;
    double timeTaken;

    printf("\n=== %s ===\n", inputName);
    printf("%-18s %12s %12s %12s %8s\n",
           "Algorithm", "Time(ms)", "Comparisons", "Moves", "Sorted");
    printf("-----------------------------------------------------------------\n");

    /* Selection Sort */
    copyArray(a, original, n);

    start = clock();
    stats = selectionSort(a, n);
    end = clock();

    timeTaken = ((double)(end - start) / CLOCKS_PER_SEC) * 1000.0;

    printf("%-18s %12.3f %12lld %12lld %8s\n",
           "Selection",
           timeTaken,
           stats.comparisons,
           stats.moves,
           isSorted(a, n) ? "YES" : "NO");

    /* Insertion Sort */
    copyArray(a, original, n);

    start = clock();
    stats = insertionSort(a, n);
    end = clock();

    timeTaken = ((double)(end - start) / CLOCKS_PER_SEC) * 1000.0;

    printf("%-18s %12.3f %12lld %12lld %8s\n",
           "Insertion",
           timeTaken,
           stats.comparisons,
           stats.moves,
           isSorted(a, n) ? "YES" : "NO");

    /* Cocktail Shaker Sort */
    copyArray(a, original, n);

    start = clock();
    stats = cocktailShakerSort(a, n);
    end = clock();

    timeTaken = ((double)(end - start) / CLOCKS_PER_SEC) * 1000.0;

    printf("%-18s %12.3f %12lld %12lld %8s\n",
           "Cocktail Shaker",
           timeTaken,
           stats.comparisons,
           stats.moves,
           isSorted(a, n) ? "YES" : "NO");

    free(a);
}

int main(void) {
    int *data = malloc((size_t)N * sizeof(int));

    if (data == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    /*
     * seed를 고정한다.
     * 따라서 프로그램을 다시 실행해도 동일한 무작위 입력을 사용한다.
     */
    srand(42);

    printf("Sorting Algorithm Experiment\n");
    printf("N = %d\n", N);

    makeRandom(data, N);
    runExperiment("Random", data, N);

    makeSorted(data, N);
    runExperiment("Sorted", data, N);

    makeReverse(data, N);
    runExperiment("Reverse", data, N);

    makeDuplicates(data, N);
    runExperiment("Many Duplicates", data, N);

    free(data);

    return 0;
}
