#include <mpi.h>
#include <stdio.h>

int fact(int no);
int fib(int no);
int main(int argc, char * argv[]){
    int rank, size;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if(rank%2==0){
        printf("Ranks is %d and Factorial is %d\n", rank, fact(rank));
    }
    else{
        printf("Rank if %d and Fibonacci is %d\n", rank, fib(rank));
    }
    MPI_Finalize();
    return 0;
}

int fact(int no){
    if(no<=1) return 1;
    return no*fact(no-1);
}

int fib(int no){
    if(no==0) return 0;
    if(no==1) return 1; 
    return fib(no-1) + fib(no-2);
}