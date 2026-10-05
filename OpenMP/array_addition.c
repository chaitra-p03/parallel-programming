#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char * argv[]) {
    int n;
    printf("Enter array size N: ");
    scanf("%d", &n);

    int *a = malloc(n * sizeof(int));
    int *b = malloc(n * sizeof(int));
    int *result = malloc(n * sizeof(int));
    int *element_owner = malloc(n * sizeof(int));

    if (a == NULL || b == NULL || result == NULL || element_owner == NULL)
    {
        printf("Memory allocation failed.\n");
        free(a);
        free(b);
        free(result);
        free(element_owner);
        return 1;
    }

    for (int i = 0; i < n; i++)
    {
        a[i] = i + 1;
        b[i] = (i + 1) * 10;
    }

    #pragma omp parallel for
    for (int i = 0; i < n; i++)
    {
        result[i] = a[i] + b[i];
        element_owner[i] = omp_get_thread_num();
    }

    printf("\nArray addition:\n");
    for (int i = 0; i < n; i++){
        printf("C[%d] = %d + %d = %d, computed by Thread %d\n", i, a[i], b[i], result[i], element_owner[i]);
    }

    free(a);
    free(b);
    free(result);
    free(element_owner);

    return 0;
}