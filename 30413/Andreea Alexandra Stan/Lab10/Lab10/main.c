#include <stdio.h>
#include <stdlib.h>

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

int minimum(int a,int b,int c)
{
    if(a<b && a<c)
        return a;
    else if(b<a && b<c)
        return b;
    else return c;

}

void min_path(int **a,int **mc,int n,int m)
{

    mc[0][0]=a[0][0];

    for(int i=1; i<n; i++)
        mc[i][0]=mc[i-1][0]+a[i][0];

    for(int i=1; i<m; i++)
        mc[0][i]=mc[0][i-1]+a[0][i];

    for(int i=1; i<n; i++)
        for(int j=1; j<m; j++)
            mc[i][j]=minimum(mc[i-1][j-1],mc[i-1][j],mc[i][j-1])+a[i][j];

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


    int n,m;
    int **a,**mc;
    fscanf(fin,"%d",&n);
    fscanf(fin,"%d",&m);

    a=(int**)malloc(n*sizeof(int*));
    for(int i=0; i<m; i++)
        a[i]=(int*)malloc(sizeof(int));

    mc=(int**)malloc(n*sizeof(int*));
    for(int i=0; i<m; i++)
        mc[i]=(int*)malloc(sizeof(int));



    //printf("%d %d\n",n,m);


    for(int i=0; i<n; i++)
        for(int j=0; j<m; j++)
            fscanf(fin,"%d",&a[i][j]);


    min_path(a,mc,n,m);
    fprintf(fout,"%d",mc[n-1][m-1]);

    fclose(fin);
    fclose(fout);



    return 0;
}
