/* Counting Characters */

#include<stdio.h>
#include<stdlib.h>
#include<ctype.h> 

int main()
{
    int i=0,j=0,k=0,l=0;
    char c;
    
    printf("Enter anything: ");
    
    c = getchar();
    
    while (c != '\n') {
       i++;
       if (isalpha(c))
          j++;
       else if (isdigit(c))
          k++;
       else if (isspace(c))
          l++;
       c = getchar();
    }
    
    printf("%d characters including %d letters and %d numbers and %d space\n\n", i, j, k, l);
    
    system("pause");
    return 0;
} 
