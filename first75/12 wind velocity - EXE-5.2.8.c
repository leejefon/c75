/* Wind Level */

#include <stdio.h>
#include <stdlib.h>

int main ()
{
    int v;
    
    printf ("Enter wind velocity (knots): ");
    scanf ("%d", &v);
    
    printf("Description: ");
    
    if (0<=v && v<1)
       printf("Calm");
    else if (1<=v && v<=3)
         printf("Light Air");
    else if (4<=v && v<=27)
         printf("Breeze");
    else if (28<=v && v<=47)
         printf("Gale");
    else if (48<=v && v<=63)
         printf("Storm");
    else
        printf("Hurricane");
    
    printf("\n\n");
        
    system ("pause");
    return 0;
}
