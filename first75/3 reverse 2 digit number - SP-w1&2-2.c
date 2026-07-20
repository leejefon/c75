/*Reverse Numbers*/

#include <stdio.h>
#include <stdlib.h>

int main ()
{
    int a, b, x, y;
    
    printf("Enter a number: ");
    scanf("%d", &x);
    
    a = x/10;
    b = x%10;
    
    y = 10 * b + a;
    
    printf ("\n");
    printf("The reverse of %d is: %d\n", x, y);
    printf ("\n");
    
    system("pause");
    return 0;
}
