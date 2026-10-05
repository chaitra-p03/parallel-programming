#include <stdio.h>
#include <omp.h>

int is_prime(int number){
    if (number < 2) return 0;

    for (int j=2; j * j <= number; j++){
        if (number % j == 0){
            return 0;
        }
    }
    return 1;
}

int main(void){
    int N;
    printf("Enter N: ");
    scanf("%d", &N);

    int static_owner[N + 1];
    int dynamic_owner[N + 1];
    int guided_owner[N + 1];

    int static_count = 0;
    int dynamic_count = 0;
    int guided_count = 0;

    double static_start, static_end;
    double dynamic_start, dynamic_end;
    double guided_start, guided_end;

    omp_set_num_threads(4);

    /*  STATIC  */

    static_start = omp_get_wtime();

    #pragma omp parallel for schedule(static) reduction(+:static_count)
    for (int number = 1; number <= N; number++)
    {
        static_owner[number] = omp_get_thread_num();
        if (is_prime(number)){
            static_count++;
        }
    }

    static_end = omp_get_wtime();

    /*  DYNAMIC  */

    dynamic_start = omp_get_wtime();

    #pragma omp parallel for schedule(dynamic) reduction(+:dynamic_count)
    for (int number = 1; number <= N; number++) {
        dynamic_owner[number] = omp_get_thread_num();
        if (is_prime(number)){
            dynamic_count++;
        }
    }

    dynamic_end = omp_get_wtime();

    /*  GUIDED  */

    guided_start = omp_get_wtime();

    #pragma omp parallel for schedule(guided) reduction(+:guided_count)
    for (int number = 1; number <= N; number++) {
        guided_owner[number] = omp_get_thread_num();
        if (is_prime(number)){
            guided_count++;
        }
    }

    guided_end = omp_get_wtime();

    /*  RESULTS  */

    printf("\nSTATIC SCHEDULING\n");
    for (int number = 1; number <= N; number++){
        printf("Number %d processed by Thread %d\n", number, static_owner[number]);
    }

    printf("Prime count: %d\n", static_count);
    printf("Execution time: %f seconds\n", static_end - static_start);

    printf("\nDYNAMIC SCHEDULING\n");
    for (int number = 1; number <= N; number++){
        printf("Number %3d processed by Thread %d\n", number, dynamic_owner[number]);
    }

    printf("Prime count: %d\n", dynamic_count);
    printf("Execution time: %f seconds\n", dynamic_end - dynamic_start);

    printf("\nGUIDED SCHEDULING\n");
    for (int number = 1; number <= N; number++){
        printf("Number %3d processed by Thread %d\n", number, guided_owner[number]);
    }

    printf("Prime count: %d\n", guided_count);
    printf("Execution time: %f seconds\n", guided_end - guided_start);

    return 0;
}