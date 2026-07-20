/* Average increment/decrement */

#include<stdio.h>
#include<stdlib.h>

int main()
{
    int a, b, c, pre_c, i=1, sum;
    
    printf("Enter a number: ");
    scanf("%d", &a);
    printf("Enter a number: ");
    scanf("%d", &b);
    
    c = b;
    pre_c = a;
    sum = a;
    
    if (b>a) {
       while(c>=pre_c) {
          pre_c=c;
          sum+=c;
          printf("Enter a number: ");
          scanf("%d", &c);
          i++;
       }
       printf("Average increment was %d/%d = %.2f\n\n", sum, i, 1.*sum/i);
    }
    else if (b<a) {
       while(c<=pre_c) {
          pre_c=c;
          sum+=c;
          printf("Enter a number: ");
          scanf("%d", &c);
          i++;
       }
       printf("Average decrement was %d/%d = %.2f\n\n", sum, i, 1.*sum/i);
    }
    else {
       printf("please enter 2 different number!\n\n");
       main();
    }
    
    system("pause");
    return 0;
}
