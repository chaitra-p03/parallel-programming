#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>

#define N 100000
#define THREADS 4

// Merge two sorted halves
void merge(int a[], int left, int mid, int right)
{
    int n = right - left + 1;
    int *temp = malloc(n * sizeof(int));

    int i = left;
    int j = mid + 1;
    int k = 0;

    while (i <= mid && j <= right)
    {
        if (a[i] <= a[j])
            temp[k++] = a[i++];
        else
            temp[k++] = a[j++];
    }

    while (i <= mid)
        temp[k++] = a[i++];

    while (j <= right)
        temp[k++] = a[j++];

    for (i = 0; i < n; i++)
        a[left + i] = temp[i];

    free(temp);
}


// Normal Sequential Merge Sort
void sequentialMergeSort(int a[], int left, int right)
{
    if (left < right)
    {
        int mid = (left + right) / 2;

        sequentialMergeSort(a, left, mid);
        sequentialMergeSort(a, mid + 1, right);

        merge(a, left, mid, right);
    }
}


// Parallel Merge Sort
void parallelMergeSort(int a[], int left, int right)
{
    if (left < right)
    {
        int mid = (left + right) / 2;

        // Left half becomes a task
        #pragma omp task shared(a)
        parallelMergeSort(a, left, mid);

        // Right half becomes another task
        #pragma omp task shared(a)
        parallelMergeSort(a, mid + 1, right);

        // Wait until both halves are sorted
        #pragma omp taskwait

        merge(a, left, mid, right);
    }
}


int main()
{
    int original[N];
    int seq[N];
    int par[N];

    for (int i = 0; i < N; i++)
        original[i] = rand() % 10000;

    memcpy(seq, original, sizeof(original));
    memcpy(par, original, sizeof(original));


    // Sequential 

    double start = omp_get_wtime();
    sequentialMergeSort(seq, 0, N - 1);
    double end = omp_get_wtime();
    double sequential_time = end - start;


    // Parallel 

    omp_set_num_threads(THREADS);
    start = omp_get_wtime();
    #pragma omp parallel
    {
        #pragma omp single
        {
            parallelMergeSort(par, 0, N - 1);
        }
    }

    end = omp_get_wtime();
    double parallel_time = end - start;


    //  Performance 

    double speedup = sequential_time / parallel_time;
    double efficiency = (speedup / THREADS) * 100.0;
    printf("Sequential Time = %f seconds\n",sequential_time);
    printf("Parallel Time = %f seconds\n", parallel_time);
    printf("Speedup = %.2f\n", speedup);
    printf("Efficiency = %.2f%%\n", efficiency);

    return 0;
}