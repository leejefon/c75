/* Circle */

#include <stdio.h>
#include <stdlib.h>
#define pi 3.14159

int main (void)
{
     int n, r=1;
     
     printf ("Enter a number: ");
     scanf ("%d", &n);
     
     while (r <= n) {
           printf ("Radius    Diameter   Perimeter        Area      Volume\n");
           printf ("%6d%12d%12.2f%12.2f%12.2f\n\n", r, 2*r, 2*pi*r, pi*r*r, 4*pi*r*r*r/3);
           r++;
           }
           
     system ("pause");
     return 0;
}
