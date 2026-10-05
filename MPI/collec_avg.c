#include <mpi.h> 
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char * argv[]){
    int rank, size;
    int m;
    int * arr;
    int * arr2;
    float * averages;
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if(rank == 0){
        printf("Enter M: \n");
        scanf("%d",&m);
        arr = malloc(sizeof(int) * m * size);
        averages = malloc(sizeof(float) * size);
        printf("Enter %d values: \n", m*size);
        for(int i=0; i<m*size; i++){
            scanf("%d",&arr[i]);
        }
    }
    MPI_Bcast(&m, 1, MPI_INT, 0, MPI_COMM_WORLD);
    arr2 = malloc(sizeof(int) * m);
    MPI_Scatter(arr,m,MPI_INT,arr2,m,MPI_INT,0,MPI_COMM_WORLD);
    int sum = 0;
    for(int i=0; i<m; i++){
        sum+=arr2[i];
    }
    float average = (float)sum / m;
    MPI_Gather(&average, 1, MPI_FLOAT, averages, 1, MPI_FLOAT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
    float total = 0;
    for (int i = 0; i < size; i++) {
        total += averages[i];
    }
    float total_average = total / size;
    printf("Total Average = %.2f\n", total_average);
    }
    MPI_Finalize();
}