/* Out of Order */

#include<stdio.h>
#include<stdlib.h>

int main()
{
    char c, c_prev = 'a'-1, last;
    int i=1;
    
    printf("enter some garbage: ");
    
    c = getchar();
    
    while (c != '\n') {
          last = c;
          if (c >= 'A' && c <= 'Z')
             c = c+32;
          
          if (c >= 'a' && c<= 'z') {
             if (c <= c_prev) {
                printf("the sentence is out of order at the %d", i);
                switch(i){
                   case 1: case 11: case 21: printf("st"); break;
                   case 2: case 12: case 22: printf("nd"); break;
                   case 3: case 13: case 23: printf("rd"); break;
                   default: printf("th"); break;
                }
                printf(" letter which is %c\n\n", last);
                system ("pause");
                return -1;
             }
          }
          
          c_prev = c;
          c = getchar();
          i++;
    }
    
    printf("it's all in order\n\n");
    
    system("pause");
    return 0;
} 
