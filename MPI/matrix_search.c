#include<stdio.h>
#include<mpi.h>

int main(int argc,char *argv[]){
    int rank,i,j,key,count=0,total;
    int matrix[3][3],row[3];

    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);

    if(rank==0){
        printf("Enter 3x3 matrix:\n");
        for(i=0;i<3;i++)
            for(j=0;j<3;j++)
                scanf("%d",&matrix[i][j]);
        printf("Enter element to search: \n");
        scanf("%d",&key);
    }

    MPI_Bcast(&key,1,MPI_INT,0,MPI_COMM_WORLD);
    MPI_Scatter(matrix,3,MPI_INT,row,3,MPI_INT,0,MPI_COMM_WORLD);

    for(i=0;i<3;i++)
        if(row[i]==key)
            count++;

    MPI_Reduce(&count,&total,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
    if(rank==0) printf("Number of occurrences = %d\n",total);
    MPI_Finalize();
    return 0;
}
