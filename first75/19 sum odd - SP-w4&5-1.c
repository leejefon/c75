/* Adding Odd Numbers */

#include <stdio.h>
#include <stdlib.h>

int main()
{
    int i=1, n, sum=1;
    
    printf("Enter an odd number N: ");
    scanf("%d", &n); 
    
   while (i != n){
          i += 2;
          sum += i;
          }
          
    printf("The sum of the odd numbers to N is: %d\n\n", sum);
    
    system("pause");
    return 0;
}
