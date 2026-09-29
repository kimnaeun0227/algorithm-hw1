/* 실행: make run-c */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sort.h"

#define N 4000
#define DUPLICATE_RANGE 10
#define REPEAT 5

/* 배열 복사 */
void copyArray(int dest[], const int src[], int n) {
    for (int i = 0; i < n; i++) {
        dest[i] = src[i];
    }
}

/* 입력 데이터 생성 */
void makeSorted(int a[], int n) {
    for (int i = 0; i < n; i++) {
        a[i] = i;
    }
}

void makeReverse(int a[], int n) {
    for (int i = 0; i < n; i++) {
        a[i] = n - i;
    }
}

void makeRandom(int a[], int n) {
    for (int i = 0; i < n; i++) {
        a[i] = rand();
    }
}

void makeDuplicates(int a[], int n) {
    for (int i = 0; i < n; i++) {
        a[i] = rand() % DUPLICATE_RANGE;
    }
}

/* 정렬 성공 여부 확인 */
int isSorted(const int a[], int n) {
    for (int i = 1; i < n; i++) {
        if (a[i - 1] > a[i]) {
            return 0;
        }
    }
    return 1;
}

/* 한 종류의 입력에 대해 세 알고리즘 실험 */
void runExperiment(const char *inputName,
                   const int original[],
                   int n,
                   FILE *csv) {

    int *a = malloc((size_t)n * sizeof(int));

    if (a == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    printf("\n=== %s ===\n", inputName);
    printf("%-18s %12s %12s %12s %8s\n",
           "Algorithm",
           "AvgTime(ms)",
           "Comparisons",
           "Moves",
           "Sorted");

    printf("-----------------------------------------------------------------\n");

    /* ---------------- Selection Sort ---------------- */

    double totalTime = 0.0;
    SortStats stats = {0, 0};

    for (int r = 0; r < REPEAT; r++) {
        copyArray(a, original, n);

        clock_t start = clock();
        stats = selectionSort(a, n);
        clock_t end = clock();

        totalTime +=
            ((double)(end - start) / CLOCKS_PER_SEC) * 1000.0;
    }

    double averageTime = totalTime / REPEAT;

    printf("%-18s %12.3f %12lld %12lld %8s\n",
           "Selection",
           averageTime,
           stats.comparisons,
           stats.moves,
           isSorted(a, n) ? "YES" : "NO");

    fprintf(csv, "%s,%s,%.3f,%lld,%lld\n",
            inputName,
            "Selection",
            averageTime,
            stats.comparisons,
            stats.moves);


    /* ---------------- Insertion Sort ---------------- */

    totalTime = 0.0;

    for (int r = 0; r < REPEAT; r++) {
        copyArray(a, original, n);

        clock_t start = clock();
        stats = insertionSort(a, n);
        clock_t end = clock();

        totalTime +=
            ((double)(end - start) / CLOCKS_PER_SEC) * 1000.0;
    }

    averageTime = totalTime / REPEAT;

    printf("%-18s %12.3f %12lld %12lld %8s\n",
           "Insertion",
           averageTime,
           stats.comparisons,
           stats.moves,
           isSorted(a, n) ? "YES" : "NO");

    fprintf(csv, "%s,%s,%.3f,%lld,%lld\n",
            inputName,
            "Insertion",
            averageTime,
            stats.comparisons,
            stats.moves);


    /* ------------- Cocktail Shaker Sort ------------- */

    totalTime = 0.0;

    for (int r = 0; r < REPEAT; r++) {
        copyArray(a, original, n);

        clock_t start = clock();
        stats = cocktailShakerSort(a, n);
        clock_t end = clock();

        totalTime +=
            ((double)(end - start) / CLOCKS_PER_SEC) * 1000.0;
    }

    averageTime = totalTime / REPEAT;

    printf("%-18s %12.3f %12lld %12lld %8s\n",
           "Cocktail Shaker",
           averageTime,
           stats.comparisons,
           stats.moves,
           isSorted(a, n) ? "YES" : "NO");

    fprintf(csv, "%s,%s,%.3f,%lld,%lld\n",
            inputName,
            "Cocktail Shaker",
            averageTime,
            stats.comparisons,
            stats.moves);

    free(a);
}


/* ---------------- Stability Test ---------------- */

void copyRecords(Record dest[], const Record src[], int n) {
    for (int i = 0; i < n; i++) {
        dest[i] = src[i];
    }
}

void runStabilityTest(void) {

    Record original[] = {
        {2, 0},
        {2, 1},
        {1, 2}
    };

    int n = (int)(sizeof(original) / sizeof(original[0]));

    Record selectionData[3];
    Record insertionData[3];
    Record cocktailData[3];

    copyRecords(selectionData, original, n);
    copyRecords(insertionData, original, n);
    copyRecords(cocktailData, original, n);

    selectionSortRecords(selectionData, n);
    insertionSortRecords(insertionData, n);
    cocktailShakerSortRecords(cocktailData, n);

    printf("\n=== Stability Test ===\n");

    printf("%-18s %s\n",
           "Selection",
           isStable(selectionData, n)
               ? "STABLE"
               : "UNSTABLE");

    printf("%-18s %s\n",
           "Insertion",
           isStable(insertionData, n)
               ? "STABLE"
               : "UNSTABLE");

    printf("%-18s %s\n",
           "Cocktail Shaker",
           isStable(cocktailData, n)
               ? "STABLE"
               : "UNSTABLE");
}


/* ---------------- Main ---------------- */

int main(void) {

    int *data = malloc((size_t)N * sizeof(int));

    if (data == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    FILE *csv = fopen("results.csv", "w");

    if (csv == NULL) {
        printf("Could not create results.csv\n");
        free(data);
        return 1;
    }

    /* CSV header */
    fprintf(csv,
            "Input,Algorithm,AvgTime_ms,Comparisons,Moves\n");

    /*
     * 고정 seed를 사용하여
     * 동일한 무작위 입력을 재현한다.
     */
    srand(42);

    printf("Sorting Algorithm Experiment\n");
    printf("N = %d\n", N);
    printf("Time measurement = average of %d runs\n", REPEAT);

    /* Random */
    makeRandom(data, N);
    runExperiment("Random", data, N, csv);

    /* Sorted */
    makeSorted(data, N);
    runExperiment("Sorted", data, N, csv);

    /* Reverse */
    makeReverse(data, N);
    runExperiment("Reverse", data, N, csv);

    /* Many Duplicates */
    makeDuplicates(data, N);
    runExperiment("Many Duplicates", data, N, csv);

    /* Stability */
    runStabilityTest();

    fclose(csv);
    free(data);

    printf("\nExperiment results saved to results.csv\n");

    return 0;
}
