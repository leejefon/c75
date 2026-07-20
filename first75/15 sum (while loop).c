/* ¼Æ¦C©M */

#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n, i=1, sum=0;
    
    printf ("Enter the number of terms: ");
    scanf ("%d", &n);
    
    while (i <= n){
          sum += i;
          i++;
          }
          
    printf ("\nThe Sum of 1 to %d is: %d\n\n", n, sum);
    system ("pause");
    return 0;
}
