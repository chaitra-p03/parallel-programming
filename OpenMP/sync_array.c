#include <stdio.h>
#include <omp.h>

int main(void)
{
    int N;

    printf("Enter the array size N: ");
    scanf("%d", &N);

    int array[N];
    long long total_sum = 0;
    int even_count = 0;

    #pragma omp parallel shared(array, N, total_sum, even_count)
    {
        int thread_id = omp_get_thread_num();
        long long partial_sum = 0;
        #pragma omp master
        {
            for (int i = 0; i < N; i++){
                array[i] = i + 1;
            }
            printf("\nArray initialized by master Thread %d.\n",thread_id);
            printf("Total participating threads: %d\n",omp_get_num_threads());
        }
        #pragma omp barrier
        #pragma omp for reduction(+:total_sum)
        for (int i = 0; i < N; i++)
        {
            total_sum += array[i];
            partial_sum += array[i];

            if (array[i] % 2 == 0){
                #pragma omp atomic
                even_count++;
            }
        }
        #pragma omp critical
        {
            printf("Thread %d partial sum = %lld\n",thread_id, partial_sum);
        }

        #pragma omp barrier
        #pragma omp master
        {
            printf("\nFinal sum = %lld\n", total_sum);
            printf("Total even elements = %d\n", even_count);
        }
    }

    printf("\nInitialized array:\n");
    for (int i = 0; i < N; i++){
        printf("%d ", array[i]);
    }
    printf("\n");

    return 0;
}