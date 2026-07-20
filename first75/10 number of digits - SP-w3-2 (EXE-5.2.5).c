/* Number of Digits */

#include <stdio.h>
#include <stdlib.h>

int main ()
{
    int a;
    
    printf ("Enter an integer between 0-999: ");
    scanf ("%d", &a);
    
    if (0<=a && a<=9)
    printf ("\nThe number %d has 1 digit.\n\n", a);
    else if (10<=a && a<=99)
    printf ("\nThe number %d has 2 digits.\n\n", a);
    else if (100<=a && a<=999)
    printf ("\nThe number %d has 3 digits.\n\n", a);
    else
    printf ("\nAre you sure your number is between 0-999?\n\n");
    
    system ("pause");
    return 0;
}
