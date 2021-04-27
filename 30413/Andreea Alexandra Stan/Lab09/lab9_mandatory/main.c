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


//i divide the array in two parts
//the max sum can be either in the left array, in the right one or it can contain elements from both parts


//function to get the maximum from three number
int maxim(int a, int b, int c)
{
    if(a>=b && a>=c)
        return a;
    else if (b>=a && b>=c)
        return b;
    else
        return c;

}


//function to get the maximum sum of consecutive elements of the subarray, including the one in the middle
int max_midsum(int a[],int left, int mid, int right)
{
    int i = mid+1;
    int j = mid;
    int sum_left=0,sum_right=0;

    int maximl=INT_MIN;
    int maximr=INT_MIN;

    //start from the middle element (including it) and get the maximum of consecutive elements on its left side
    while(j >= left)
    {
        sum_left=sum_left+a[j];

        if(sum_left>maximl)
            maximl =sum_left;
        j--;
    }

    //repeat the same process for the right side(this time we don't include the middle element):
    while(i<=right)
    {
        sum_right=sum_right+a[i];

        if(sum_right>maximr)
            maximr =sum_right;

        i++;
    }

    //then we add the left maximum sum and the right maximum sum
    return maximl+maximr;


}

int maximl,maximr,maxim_intersect;

//this is the part where i divide the problem into subproblems
//first i divide the array into two parts
//the max sum can be either in the left subarray, in the right one or it can contain elements from both parts
//we check the third case with the max_midsum function

//with this function I check the three possible cases, and return the maximal one

int divide_et_impera(int a[],int left, int right)
{

    if(left < right)
    {
        int mid = (left + right) / 2;

        maximl=divide_et_impera(a,left, mid);
        maximr=divide_et_impera(a, mid + 1, right);
        maxim_intersect=max_midsum(a,left, mid, right);

        return maxim(maximl,maximr,maxim_intersect);
    }


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


    int n;
    int *a=(int *)calloc(n, sizeof(int));

    fscanf(fin,"%d",&n);


    for(int i=0; i<n; i++)
    {
        fscanf(fin,"%d",&a[i]);

    }

    int suma;
    suma=divide_et_impera(a,0,n-1);
    fprintf(fout,"%d",suma);

    fclose(fin);
    fclose(fout);
    free(a);




    return 0;
}
