/* Reverse of a number */

#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a, k, b, c, x, y;
    
    printf("Enter a 3 digit number: ");
    scanf("%d", &x);
    
    a = x/100;
    k = x%100;
    b = k-k%10;
    c = k%10;
        
    y = 100*c + b + a;
    
    printf("\nThe inverse of %.3d is: %.3d\n\n", x, y);
       
    system("pause");
    return 0;
}
