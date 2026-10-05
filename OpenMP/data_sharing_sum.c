#include <stdio.h>
#include <omp.h>

int main(void){
    int N;
    long long expected_sum;
    long long sum;

    printf("Enter N: ");
    scanf("%d", &N);
    omp_set_num_threads(4);
    expected_sum = (long long)N * (N + 1) / 2;
    printf("\nExpected sum = %lld\n", expected_sum);

    // Shared

    sum = 0;
    #pragma omp parallel shared(sum)
    {
        #pragma omp for
        for (int i = 1; i <= N; i++){
            sum += i;
        }

        #pragma omp critical
        {
            printf("Thread %d sees shared sum = %lld\n", omp_get_thread_num(), sum);
        }
    }

    printf("Final value outside shared region = %lld\n", sum);

    // Private
    sum = 0;
    #pragma omp parallel private(sum)
    {
        sum = 0;
        #pragma omp for
        for (int i = 1; i <= N; i++){
            sum += i;
        }

        #pragma omp critical
        {
            printf("Thread %d has private partial sum = %lld\n", omp_get_thread_num(), sum);
            // each thread has its local value
        }
    }

    printf("Final value outside private region = %lld\n", sum);

    // firstprivate
    sum = 100;
    printf("Initial outside value = %lld\n", sum);
    #pragma omp parallel firstprivate(sum)
    {
        #pragma omp for
        for (int i = 1; i <= N; i++){
            sum += i;
        }

        #pragma omp critical
        {
            printf("Thread %d has firstprivate value = %lld\n", omp_get_thread_num(), sum);
        }
    }

    printf("Final value outside firstprivate region = %lld\n", sum);

    // lastprivate
    sum = 0;
    #pragma omp parallel for lastprivate(sum)
    for (int i = 1; i <= N; i++)
    {
        sum = i;
    }

    printf("Final value outside lastprivate region = %lld\n", sum);
    sum = 0;

    printf("\n--- Correct parallel sum using reduction ---\n");
    #pragma omp parallel for reduction(+:sum)
    for (int i = 1; i <= N; i++){
        sum += i;
    }
    printf("Final reduction sum = %lld\n", sum);
    return 0;
}