/* Cosine Law */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    float a, b, c, theta;
    
    printf ("Enter length of one side: ");
    scanf ("%f", &a);
    printf ("Enter length of another side: ");
    scanf ("%f", &b);
    printf ("The angle between the two(in radian): ");
    scanf ("%f", &theta);
    
    c = sqrt(pow(a,2)+pow(b,2)-2*a*b*cos(theta));
    
    printf ("\n");
    printf ("The third side length is: %f\n", c);
    printf ("\n");
    
    system ("pause");
    return 0;
    
}
