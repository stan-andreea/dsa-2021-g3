#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

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

int minimum(int a,int b)
{
    if(a<b)
        return a;
    else
        return b;


}

//function to sort the vector
void sort(int v[],int n)
{
    int ok,aux;
    do
    {
        ok=1;
        for(int i=0; i<n-1; i++)
            if(v[i]>v[i+1])
            {
                aux=v[i];
                v[i]=v[i+1];
                v[i+1]=aux;
                ok=0;
            }
    }
    while(ok==0);
}

//this problem is similar with the coin change problem so i used a similar solution
int minop(int v[],int n, int nr)
{
    int dp[1000];

    //the indexes of the array are the numbers till the different between a and b
    for(int i = 0; i<=nr; i++)
        dp[i] = INT_MAX; //we initialize with the maximal value


    dp[0] = 0;//because there's no way to obtain 0 by adding other numbers from the vector


    //for every other number we look for minimum number of operations using the given numbers in the vector
    //we store every minimum in dp
    //dp[i] is the minimum number of operations to obtain i
    //so we need dp[nr]

    for(int i = 1; i<=nr; i++)
    {

        for(int j = 0; j<n; j++)
        {

            if(abs(v[j]) <= i)
            {
                //we choose the minimum between the previous number of operations and the one including the current number
                dp[i] = minimum(dp[i], 1 + dp[i - v[j]]);
            }
        }
    }

    if(dp[n]==INT_MAX)
        return 0;//no solution found
    return dp[nr];
}











int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        printf("No file name given\n");
        exit(1);
    }


    FILE *fin, *fout;
    fin=openAndCheck(argv[1], "r");//argv[1]="input.txt"
    fout=openAndCheck(argv[2], "w");//argv[2]="output.txt"


    int a,b,i=0,n=0,nr;
    int v[50];



    fscanf(fin,"%d",&a);
    fscanf(fin,"%d",&b);

    //i solved this problem by obtaining the difference between a and b using numbers in v
    //if a>b we will substract all those numbers from a, otherwise we add them
    if(a>b) nr=a-b;
        else nr=b-a;



    while(!feof(fin))
    {
        fscanf(fin,"%d",&v[i]);
        i++;

    }
    n=i;//n=nr of elements in v


    sort(v,n);


    /*int *w=(int*)malloc(2*n*sizeof(int));
    i=0;

    for(int j=0; j<n; j++)
    {
        w[j]=v[i];
        i++;
    }
    i=0;

    for(int j=n; j<2*n; j++)
    {
        w[j]=-v[i];
        i++;

    }
    sort(w,2*n);*/


    fprintf(fout,"%d ", minop(v,n,nr));
    //in the given example the answer would be 2 because we add to A 21 and 31, so 2 operations

    fclose(fin);
    fclose(fout);



    return 0;
}
