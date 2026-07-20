/* Positive? Negaitve? */

#include <stdio.h>
#include <stdlib.h>

int main()
{
    int i, j=0, k=0;
    
    printf("Enter an integer: ");
    scanf("%d", &i);
    
    while (i != 0){
          if (i>0)
             j+=1;
          else
             k+=1;
          printf("Enter an integer: ");
          scanf("%d", &i);
          }
    
    printf("You entered %d positive and %d negaitve values.\n\n", j, k);
    
    system("pause");
    return 0;
}
