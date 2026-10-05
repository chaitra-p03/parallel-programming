#include<stdio.h>
#include<omp.h>

int main(int argc, char * argv[]){
    int n;
    printf("Enter n: \n");
    scanf("%d",&n);
    int arr[n];
    int total = 0; 
    int divby3 = 0;
    #pragma omp parallel shared(n, arr, total, divby3)
    {
        int thread_id = omp_get_thread_num();
        int partial = 0;
        #pragma omp master 
        {
            for(int i=0; i<n; i++){
                arr[i] = i+1;
            }
            printf("total threads : %d\n",omp_get_num_threads());
        }

        #pragma omp barrier

        #pragma omp for reduction(+:total)
        for(int i=0; i<n; i++){
            total+=arr[i]*arr[i];
            partial += arr[i]*arr[i];
            if(arr[i]%3==0){
                #pragma atomic
                divby3++;
            }
        }

        # pragma omp critical 
        {
            printf("thread id: %d and partial sum %d \n", omp_get_thread_num(), partial);
        }

        #pragma omp barrier

        #pragma omp master
        {
            printf("Final sum of squares = %d\n", total);
            printf("Elements divisible by 3 = %d\n", divby3);

        }


    }
}