#include <stdio.h>
#include <stdlib.h>


int numberOfPaths(int n, int m)
{

    //dynamic allocation of memory for the matrix used for the dynamic programming
    int    dp[n][m];


    for (int i = 0; i < n; i++)
        dp[i][0] = 1;


    for (int j = 0; j <m; j++)
        dp[n-1][j] = 1;


    for (int i = n-1; i >0; i--)
        for (int j = 1; j < m; j++)


            dp[i][j] = dp[i - 1][j] + dp[i-1][j +1]+dp[i][j+1];
    return dp[0][m - 1];
}


int main()
{
    int n,m;

    printf("%d", numberOfPaths(2, 2));
    return 0;
}
