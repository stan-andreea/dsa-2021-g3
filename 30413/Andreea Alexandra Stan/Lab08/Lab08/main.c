#include <stdio.h>
#include <stdlib.h>
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

void greedy(int numerator, int denominator, FILE *fo)
{


    if(numerator==1 || denominator%numerator==0)
    {
        fprintf(fo,"1/%d",denominator/numerator);
        return;
    }
    //after we reach a fraction of the form 1/n we stop
    //we also stop after we reach something of the form a/a*n, because after dividing with a we obtain a fraction of the form 1/n
    //in this case we don't need to write the '+' at the end

    else
    {

        float div;
        div=(float)denominator/numerator;

        int aux;
        aux=ceil(div);

        fprintf(fo, "1/%d + ",aux);
        greedy(numerator*aux-denominator , denominator*aux , fo);

    }


}

int main()
{

    FILE *fi, *fo;
    fi=openAndCheck("input.txt", "r");
    fo=openAndCheck("output.txt", "w");

    int numerator, denominator;

    fscanf(fi,"%d", &numerator);
    fgetc(fi); // ignore the fraction bar
    fscanf(fi,"%d", &denominator);



    greedy(numerator,denominator,fo);

    fclose(fi);
    fclose(fo);





    return 0;
}
