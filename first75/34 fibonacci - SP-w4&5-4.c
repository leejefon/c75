/* Fibonacci serie */

#include<stdio.h>
#include<stdlib.h>

int main()
{
    int fibo=0, pprefibo=-1, prefibo=1, fir, las, i=1, j, k;
    
    printf("Enter the first # of term: ");
    scanf("%d", &fir);
    printf("Enter the last # of term: ");
    scanf("%d", &las);
    
    for(;i<fir;i++) {
       fibo=prefibo+pprefibo;
       pprefibo=prefibo;
       prefibo=fibo;
    }
    
    printf("\n\nFibonacci serie from %d term to %d term are: \n\n\t", fir, las);
    
    for (j=fir;j<las;j++) {
        fibo=prefibo+pprefibo;
        pprefibo=prefibo;
        prefibo=fibo;
        printf("%d, ", fibo);
    }
    printf("%d", prefibo+pprefibo);
    
    printf("\n\n");
    system("pause");
    return 0;
}
