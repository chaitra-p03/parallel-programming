#include <mpi.h>
#include <stdio.h>
#include <math.h>

int main(int argc, char *argv[]){
    int rank,size,x;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if(rank==0){
        printf("Enter the number:\n");
        scanf("%d",&x);
    }
    MPI_Bcast(&x,1,MPI_INT,0,MPI_COMM_WORLD);
    printf("Rank is %d and pow(%d, %d) is %.2f\n", rank, x, rank, pow(x,rank));
    MPI_Finalize();
    return 0;
}