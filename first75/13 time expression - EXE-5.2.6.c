/* Time expression */

#include <stdio.h>
#include <stdlib.h>

int main ()
{
    int hr, min;
    
    printf ("Enter a 24-hour time (hh:mm): ");
    scanf ("%d:%d", &hr, &min);
    printf ("Equivalent 12-hour time: ");
    
    if (hr<12)
       printf ("%.2d:%.2d AM\n\n", hr, min);
    else if (hr>12)
       printf ("%.2d:%.2d PM\n\n", hr-12, min);
    else
       printf ("%.2d:%.2d PM\n\n", hr, min);
    
    system ("pause");
    return 0;
}
