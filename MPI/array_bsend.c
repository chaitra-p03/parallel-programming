#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    int rank, size, x;
    int *arr;

    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if(rank==0){
        arr = (int *) malloc(size * sizeof(int));
        printf("Enter %d elements:\n", size);
        for(int i=0; i<size; i++){
            scanf("%d",&arr[i]);
        }
        printf("Rank 0 : Square of %d = %d\n", arr[0], arr[0]*arr[0]);
        int buffer_size = (size-1)*(sizeof(int) + MPI_BSEND_OVERHEAD);
        char *buffer = (char *)malloc(buffer_size);
        MPI_Buffer_attach(buffer,buffer_size);
        for(int i=1; i<size; i++){
            MPI_Bsend(&arr[i],1,MPI_INT,i,0,MPI_COMM_WORLD);
        }
        MPI_Buffer_detach(&buffer, &buffer_size);
        free(buffer);
        free(arr);
    }
    else{
        MPI_Recv(&x, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        if(rank%2==0){
            printf("Rank %d : Square of %d = %d\n", rank, x, x*x);
        }
        else {
            printf("Rank %d : Cube of %d = %d\n", rank, x, x*x*x);
        }
    }
    MPI_Finalize();
    return 0;
}