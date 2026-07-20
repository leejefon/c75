/* Number Triangle */

#include<stdio.h>
#include<stdlib.h>

int main()
{
    int n, n_ori, i=0, j, k=1, l, f;
    
    printf("\n\n\tEnter a number (better < 20): ");
    scanf("%d", &n);
    
    printf("\n\n\t\t");
    for (f=0;f<(n+4);f++)
       printf("*");
    
    printf("\n");
    for(;i<n;i++, k++) {
       printf("\t\t*");
       j=n-k+1;
       for(;j>0;j--)
          printf(" ");
       l=k;
       for(;l<=(2*k-1);l++) {
          printf("%d", l%10);
       }
       printf(" *\n");
    }

    printf("\t\t");
    for (f=0;f<(n+4);f++)
       printf("*");
    
    printf("\n\n\n");
    system("pause");
    return 0;
}
