/* Cost */ 

#include <stdio.h>
#include <stdlib.h>

int main()
{
    float c, a;
    
    printf ("Cost of the item: ");
    scanf ("%f", &c);
    printf ("Amount tendered: ");
    scanf ("%f", &a);
    
    if (c < a)
    printf ("Change: %.2f\n\n", a - c);
    else if (c == a)
    printf ("You are free to go!\n\n");
    else
    printf ("Still due: %.2f\n\n", c - a);
    
    system ("pause");
    return 0;
} 
