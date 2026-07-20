/* 次方數列和 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h> 

int main()
{
    int p, n, i=1, j;
    long int sum;
    
    printf ("Enter power: ");
    scanf ("%d", &p);
    printf ("Enter the number of terms: ");
    scanf ("%d", &n);
    
    printf("\n");
    
    for(;i<=p;i++) {
       sum=0;
       for (j=1;j<=n;j++)
         sum += pow(j,i);
    printf("for power = %d, sum of the serie from 1 to %d is %ld\n", i, n, sum);
    }
    
    printf("\n");          
    
    system ("pause");
    return 0;
}



/*
//when power = 2

int main()
{
    int n, sum;
    
    printf ("Enter the number of terms: ");
    scanf ("%d", &n);
    
    sum = n*(n+1)*(2*n+1)/6;
    
    printf ("\nThe Square Sum of 1 to %d is: %d\n\n", n, sum);
    system ("pause");
    return 0;
}
*/
