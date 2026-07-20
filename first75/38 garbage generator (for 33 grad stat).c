/* Random number generator */

#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *garbage;
    int num, n;
    
    garbage = fopen("text\\38 garbage numbers.txt", "w");
    
    printf("how many garbage numbers do you want? ");
    scanf("%d", &n);
    
    for(;n>0;n--) {
      num = rand()%101;
      fprintf(garbage, "%3d\n", num);
    }
      
    printf("\n\tDone!\n\n");
    
    fclose(garbage);
    
    system("pause");
    return 0;
}
