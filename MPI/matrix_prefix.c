#include<stdio.h>
#include<mpi.h>

int main(int argc,char *argv[]){
    int rank,i,j;
    int a[4][4],row[4],result[4],output[4][4];

    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    if(rank==0){
        printf("Enter 4x4 matrix:\n");
        for(i=0;i<4;i++)
        for(j=0;j<4;j++)
        scanf("%d",&a[i][j]);
    }

    MPI_Scatter(a,4,MPI_INT,row,4,MPI_INT,0,MPI_COMM_WORLD);
    MPI_Scan(row,result,4,MPI_INT,MPI_SUM,MPI_COMM_WORLD);
    MPI_Gather(result,4,MPI_INT,output,4,MPI_INT,0,MPI_COMM_WORLD);

    if(rank==0){
        printf("Output matrix:\n");
        for(i=0;i<4;i++){
            for(j=0;j<4;j++)
                printf("%d ",output[i][j]);
            printf("\n");
        }
    }
    MPI_Finalize();
    return 0;
}
