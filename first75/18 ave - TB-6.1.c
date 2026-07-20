/* Average Calculator */

#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n=0;
    float i, sum=0;
    
    printf ("Enter the numbers (0 to terminate): ");
    
    scanf ("%f", &i);
    if (i!=0){
    while (i!=0){
          sum += i;
          scanf ("%f", &i);
          n++;
          }    
    printf ("The average of the %d is: %.2f\n\n", n, sum/n);}
    else
    printf ("There is no number\n\n");
    
    system ("pause");
    return 0;
}


/*
int main()
{
    int n=0;
    float i, sum=0;
    
    printf ("Enter the numbers (0 to terminate): ");
    
    scanf ("%f", &i);
    
    if (i!=0){
    do {sum += i;
        scanf ("%f", &i);
        n++;
        }while (i!=0);
        printf ("The average of the %d is: %.2f\n\n", n, sum/n);}
    else
    printf ("There is no number\n\n");
              
    
    
    system ("pause");
    return 0;
}
*/
