#include<stdio.h>
#include<omp.h>

int main(int argc, char * argv[]){
    int n; 
    printf("Enter the no of threads: ");
    scanf("%d",&n);
    omp_set_num_threads(n);
    #pragma omp parallel 
    {
        printf("Thread ID: %d and Total threads: %d\n",omp_get_thread_num(),omp_get_num_threads());
    }
    return 0;
}