/* Calendar */

#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n, w, i;
    
    printf("Enter number of days in month: ");
    scanf("%d", &n);
    printf("Enter starting day (1=Sun, ..., 7=Sat): ");
    scanf("%d", &w);
    printf("\n");
    
    switch (w){
           case 1: printf(""); break;
           case 2: printf("   "); break;
           case 3: printf("      "); break;
           case 4: printf("         "); break;
           case 5: printf("            "); break;
           case 6: printf("               "); break;
           case 7: printf("                  "); break;
           }
           
    if(n>31)
    printf("Too many days in a month\n\n");
    else
    for(i=1;i!=n+1;i+=1){
    printf("%3d", i); 
    if ((i+w-1)%7 == 0)
    printf("\n");}
    
    printf("\n\n");
    
    system("pause");
    return 0;
}
    
