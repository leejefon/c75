/* GCD & LCM */

#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int main()
{
    int gcd, lcm, a, b, diff, diff_prev, a_ori, b_ori;
    
    printf("Enter a number: ");
    scanf("%d", &a);
    printf("Enter another number: ");
    scanf("%d", &b);
    
    a_ori = a;
    b_ori = b;
    
    diff = abs(a-b);
    
    while (diff!=0) {
       diff_prev = diff;
       
       if (a>b)
         a=diff;
       else if (b>a)
         b=diff;
       
       diff=abs(a-b);
    }
    
    gcd = diff_prev;
    lcm = a_ori*b_ori/diff_prev;
    
    printf("\nThe GCD & LCM of %d and %d are %d & %d\n\n", a_ori, b_ori, gcd, lcm);
    
    system("pause");
    return 0;
} 
