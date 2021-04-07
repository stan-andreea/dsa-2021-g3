#include <stdio.h>
#include <stdlib.h>


//to solve this problem i used a directed graph, where we have arcs from a faster robot to a slower robot
//for example,if 1 faster than 2, then arc from 1 to 2

//I used the adjacency matrix and I observed that the greater the internal degree, the slower the robot
//so I made an array of all the nodes in the graph, and sorted them by their internal degree




//function to find the size of the  adjacency matrix:
//the matrix will be a square one with the size as the biggest number in the input file
int find_size(FILE *fi,int relations)
{
    int maxim=0,nr;
    long pos;
    pos=ftell(fi);

    for(int i=0; i<2*relations; i++)
    {
        fscanf(fi, "%d", &nr);

        if(nr>maxim)
            maxim=nr;
    }

    fseek(fi,pos,SEEK_SET);

    return maxim;

}

//function to find the internal degree,which is the number of ones on the collumn
int find_internal(int **matrix,int nr,int size)
{
    int idg=0;

    for(int i=0 ; i<size; i++)
        if(matrix[i][nr]!=0) idg++;

    return idg;
}


//made a structure, which i will use for the array where I put the information for the robots: the internal degree and their number
typedef struct
{
    int degree;
    int nr;
}nodeG;



//then I sort the degree by the internal degree
//i used bubble sort for this:
void sort(nodeG *array , int size)
{
    int ok,i,aux;
    do
    {
        ok=1;
        for(i=0; i<size-1; i++)

            if(array[i].degree>array[i+1].degree)
            {
                aux=array[i].degree;
                array[i].degree=array[i+1].degree;
                array[i+1].degree=aux;

                 aux=array[i].nr;
                array[i].nr=array[i+1].nr;
                array[i+1].nr=aux;

                ok=0;
            }
    }
    while(!ok);

}



FILE *openAndCheck(char *filePath, char *mode)
{
    FILE *f = fopen(filePath, mode);
    if (f==NULL)
    {
        printf("Cannot open the file");
        exit(0);
    }
    return f;
}


int main()
{

    FILE *fi, *fo;
    fi=openAndCheck("input.txt", "r");
    fo=openAndCheck("output.txt", "w");

    int relations,faster,slower,size;

    fscanf(fi,"%d", &relations);


    size=find_size(fi,relations);

    //allocate memory for the adj matrix:

    int **matrix = (int **)malloc( size* sizeof(int*));

    for(int i = 0; i < size; i++)
        matrix[i] = (int *)malloc(size * sizeof(int));



    //initialize it with 0
    for(int i=0; i<size; i++)
    {
        for(int j=0; j<size; j++)
            matrix[i][j]=0;

    }



    for(int i=0 ; i<size; i++)
    {
        fscanf(fi,"%d", &faster);
        fscanf(fi,"%d", &slower);
        matrix[faster-1][slower-1]=1;

    }


    //allocate memory for the array

    nodeG *array = (nodeG *)malloc( size* sizeof(nodeG*));

    for(int i=0; i<size; i++)
        {
            array[i].degree=find_internal(matrix,i,size);
            array[i].nr=i+1;
        }


    sort(array,size);

    for(int i=0;i<size;i++)
        fprintf(fo,"%d ",array[i].nr);

    //close all the files:

    fclose(fi);
    fclose(fo);

    //free the memory

     for(int i=0; i<size; i++)
            free(matrix[i]);
    free(matrix);

    free(array);









    return 0;
}
